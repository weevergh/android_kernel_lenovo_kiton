#!/usr/local/bin/node

var fs = require('fs'),
	path = require('path');

function zeroFill( number, width ) {
	width -= number.toString().length;
	if ( width > 0 ) {
		return new Array( width + (/\./.test( number ) ? 2 : 1) ).join( '0' ) + number;
	}
	return number + ""; // always return a string
}

function extract_portion(fd, pos, length, output) {
	function o(o_method, data) {
		if(typeof o_method === 'string') {
	    	try { fs.writeFileSync(o_method, b); }
	    	catch(err) {
	    	    console.log("Failed to write data: " + err.message);
	    	    return;
	    	}
	    	console.log("Extracted " + o_method);
		} else if(typeof o_method === 'function') o_method(data);
		else throw new Error('Invalid output method provided.');
	}
	if(length) {
		var b = new Buffer(length);
		fs.read(fd, b, 0, length, pos, function(err, bytesRead) {
	    	if(err) {
	    	    console.log("Failed to read data: " + e.message);
	    	    console.log("Possible corrupted image file.");
	    	    return;
	    	} else if(bytesRead != length) {
	    	    console.log("Failed to read data, only got " + bytesRead + ' bytes, expecting ' + length + '.');
	    	    return;
	    	} 
	    	o(output, b);
		});
	} else o(output, new Buffer(0));
}

function examine_dt(file_path, extract) {
	fs.open(file_path, 'r', function(err, fd) {
	    if (err) {
	        console.log("Failed to read file: " + err.message);
	        return;
	    }
	    var header_size = 12,
	    	header = new Buffer(header_size);
	    fs.read(fd, header, 0, header_size, 0, function(e, bytesRead) {
	    	if(e) {
	    	    console.log("Failed to read header: " + e.message);
	    	    return;
	    	} else if(bytesRead != header_size) {
	    	    console.log("Failed to read header, only got " + bytesRead + ' bytes, expecting ' + header_size + '.');
	    	    return;
	    	} 
	    	// Parse the header with struct below.
	    	if(header.slice(0, 4).toString() !== 'QCDT') {
	    	    console.log('Wrong magic header ' + header.slice(0, 4).toJSON() + ', expecting "QCDT".');
	    	    return;
	    	}
			var qcdt_ver = header.readUInt32LE(4);
			var dt_num = header.readUInt32LE(8);

			console.log("QCDT Version:  " + qcdt_ver);
			console.log("Number of DTs:  " + dt_num);
			console.log("");

			var current_pos = 12,
				current_dt_num = 0;

			function check_dt_info(dt_idx) {
				if(dt_idx >= dt_num) return;
				if(qcdt_ver === 1) extract_portion(fd, 12 + 20 * dt_idx, 20, function(entry) {
					var platform_id = entry.readUInt32LE(0);
					var variant_id = entry.readUInt32LE(4);
					var soc_rev = entry.readUInt32LE(8);
					var offset = entry.readUInt32LE(12);
					var size = entry.readUInt32LE(16);
					console.log("DT " + (++dt_idx) + ": Platform 0x" + platform_id.toString(16) + " Variant 0x" + variant_id.toString(16) + " SOC Rev 0x" + soc_rev.toString(16));
					if(extract) extract_portion(fd, offset, size, dt_idx + ".dtb");
					check_dt_info(dt_idx);
				}); else if(qcdt_ver === 2) {

				} else console.log("Unsupported QCDT version.");
			}

			check_dt_info(0);
	    });
	});
}

if(require.main === module) {
	var imgfile = process.argv[3],
		extract = false;
	if(process.argv.length != 4) {
		console.log("Usage:");
		console.log("  " + process.argv[1] + ' <info|extract> <input image>');
		return 0;
	}
	if((process.argv[2] === 'i') || (process.argv[2] === 'info')) extract = false;
	else if((process.argv[2] === 'e') || (process.argv[2] === 'extract')) extract = true;
	else {
		console.log("Invalid action: " + process.argv[2]);
		return 1;
	}
	if((!imgfile) || (typeof imgfile !== 'string') || 
		(imgfile.trim().length === 0) || (!fs.existsSync(imgfile)) ||
		(!fs.statSync(imgfile).isFile())) {
		console.log('Invalid image file: ' + imgfile);
		return 1;
	}
	examine_dt(imgfile, extract);
} else module.exports = examine_dt;


 //                               size
 //   x      +------------------+
 //   |      | MAGIC ("QCDT")   |   4B
 //   |      +------------------+
 // header   | VERSION          |   uint32 (initial version 1)
 //   |      +------------------+
 //   |      | num of DTBs      |   uint32 (number of DTB entries)
 //   x      +------------------+
 //   |      | platform id #1   |   uint32 (e.g. ID for MSM8974)
 //   |      +------------------+
 //   |      | variant id #1    |   uint32 (e.g. ID for CDP, MTP)
 // device   +------------------+
 //  #1      | soc rev #1       |   uint32 (e.g. MSM8974 v2)
 // entry    +------------------+
 //   |      | offset #1        |   uint32 (byte offset from start/before MAGIC
 //   |      +------------------+           to DTB entry)
 //   |      | size #1          |   uint32 (size in bytes of DTB blob)
 //   x      +------------------+
 //   .              .
 //   .              .  (repeat)
 //   .              .

 //   x      +------------------+
 //   |      | platform id #Z   |   uint32 (e.g. ID for MSM8974)
 //   |      +------------------+
 //  device  | variant id #Z    |   uint32 (e.g. ID for CDP, MTP)
 //  #Z      +------------------+
 //  entry   | soc rev #Z       |   uint32 (e.g. MSM8974 v2)
 //  (last)  +------------------+
 //   |      | offset #Z        |   uint32 (byte offset from start/before MAGIC
 //   x      +------------------+           to DTB entry)
 //          | 0 ("zero")       |   uint32 (end of list delimiter)
 //          +------------------+           to DTB entry)
 //          | padding          |   variable length for next DTB to start on
 //          +------------------+           page boundary
 //          | DTB #1           |   variable (start is page aligned)
 //          |                  |
 //          |                  |
 //          +------------------+
 //          | padding          |   variable length for next DTB to start on
 //          +------------------+           page boundary
 //                  .
 //                  .
 //                  .

 //          +------------------+
 //          | DTB #Z (last)    |   variable (start is page aligned)
 //          |                  |
 //          |                  |
 //          +------------------+