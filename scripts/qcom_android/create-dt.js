#!/usr/local/bin/node

var fs = require('fs'),
	path = require('path');

function padLeft( number, width, filler ) {
	filler = filler || ' ';
	width -= number.toString().length;
	if ( width > 0 ) {
		return new Array( width + (/\./.test( number ) ? 2 : 1) ).join( filler ) + number;
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

var OF_DT_HEADER = 0xd00dfeed;
var OF_DT_BEGIN_NODE = 0x1;
var OF_DT_END_NODE = 0x2;
var OF_DT_PROP = 0x3;
var OF_DT_END = 0x9

function examine_dtb(file_path, cb) {
	fs.open(file_path, 'r', function(err, fd) {
	    if (err) {
	        console.log("Failed to read file: " + err.message);
	        return;
	    }
	    var header_size = 28,
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
	    	if(header.readUInt32BE(0) !== OF_DT_HEADER) {
	    	    console.log('Wrong magic header 0x' + header.readUInt32BE(0).toString(16) + ', expecting "0x' + OF_DT_HEADER.toString(16) + '".');
	    	    return;
	    	}
			var totalsize = header.readUInt32BE(4);
			var off_dt_struct = header.readUInt32BE(8);
			var off_dt_strings = header.readUInt32BE(12);
			var off_mem_rsvmap = header.readUInt32BE(16);
			var version = header.readUInt32BE(20);
			var last_comp_version = header.readUInt32BE(24);

			console.log('Version: ' + version);
			console.log('CompVer: ' + last_comp_version);
			console.log('off_dt_struct: ' + off_dt_struct);
			console.log('off_dt_strings: ' + off_dt_strings);
			console.log('off_mem_rsvmap: ' + off_mem_rsvmap);
			console.log();

			var off_dt_struct_prox_len = off_dt_strings - off_dt_struct;
			var off_dt_strings_prox_len = totalsize - off_dt_strings;

			extract_portion(fd, off_dt_struct, off_dt_struct_prox_len, function(dt_struct) {
				extract_portion(fd, off_dt_strings, off_dt_strings_prox_len, function(dt_strings) {
					function parse_node(start_idx) {
						if(dt_struct.readUInt32BE(start_idx) !== OF_DT_BEGIN_NODE) 
							throw new Error(OF_DT_BEGIN_NODE);
						var node_name,
							node_name_len = 0;
						do {
							node_name_len += 4;
							node_name = dt_struct.slice(start_idx + 4, start_idx + 4 + node_name_len).toString().replace(/\u0000*$/, '');
						} while(node_name.length === node_name_len);

						var pos = start_idx + 4 + node_name_len;

						while(dt_struct.readUInt32BE(pos) === OF_DT_PROP)
							pos += parse_prop(pos);						
						while(dt_struct.readUInt32BE(pos) === OF_DT_BEGIN_NODE)
							pos += parse_node(pos);

						if(dt_struct.readUInt32BE(pos) !== OF_DT_END_NODE)
							//throw new Error(JSON.stringify(dt_struct.slice(pos - 5, pos + 5)) + JSON.stringify(dt_struct.slice(pos, pos + 8)));
							throw new Error("Invalid DT");

						return pos + 4 - start_idx;
					}
					function parse_prop(start_idx) {
						if(dt_struct.readUInt32BE(start_idx) !== OF_DT_PROP)
							throw new Error(OF_DT_PROP);
						var value_size = dt_struct.readUInt32BE(start_idx + 4),
							name_offset = dt_struct.readUInt32BE(start_idx + 8),
							value = dt_struct.slice(start_idx + 12, start_idx + 12 + value_size),
							name = dt_strings.slice(name_offset).toString().split(/\u0000/)[0];
						cb(name, value)
						return Math.ceil(value_size / 4) * 4 + 12;
					}
					parse_node(0);
				});
			});
		});
	});
}

if(require.main === module) {
	examine_dtb("test.dtb");
} else module.exports = examine_dtb;


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