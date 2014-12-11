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

function extract_portion(fd, pos, length, output_file_path) {
	if(length) {
		var b = new Buffer(length);
		fs.read(fd, b, 0, length, pos, function(err, bytesRead) {
	    	if(err) {
	    	    console.log("Failed to read data: " + e.message);
	    	    return;
	    	} else if(bytesRead != length) {
	    	    console.log("Failed to read data, only got " + bytesRead + ' bytes, expecting ' + length + '.');
	    	    return;
	    	} 
	    	try { fs.writeFileSync(output_file_path, b); }
	    	catch(err) {
	    	    console.log("Failed to write data: " + err.message);
	    	    return;
	    	}
	    	console.log("Extracted " + output_file_path);
		});
	} else {
		try { fs.writeFileSync(output_file_path, ""); }
    	catch(err) {
    	    console.log("Failed to write data: " + err.message);
    	    return;
    	}
    	console.log("Extracted " + output_file_path);
	}
}

function extract_info(file_path, page_size) {
	fs.open(file_path, 'r', function(err, fd) {
	    if (err) {
	        console.log("Failed to read file: " + err.message);
	        return;
	    }
	    var header = new Buffer(page_size);
	    fs.read(fd, header, 0, page_size, 0, function(e, bytesRead) {
	    	if(e) {
	    	    console.log("Failed to read header: " + e.message);
	    	    return;
	    	} else if(bytesRead != page_size) {
	    	    console.log("Failed to read header, only got " + bytesRead + ' bytes, expecting ' + page_size + '.');
	    	    return;
	    	} 
	    	// Parse the header with struct below.
	    	if(header.slice(0, 8).toString() !== 'ANDROID!') {
	    	    console.log('Wrong magic header ' + header.slice(0, 8).toJSON() + ', expecting "ANDROID!".');
	    	    return;
	    	}
			var kernel_size = header.readUInt32LE(8);  /* size in bytes */
			var kernel_addr = header.readUInt32LE(12);  /* physical load addr */
			var ramdisk_size = header.readUInt32LE(16);   /* size in bytes */
			var ramdisk_addr = header.readUInt32LE(20);   /* physical load addr */
			var second_size = header.readUInt32LE(24);    /* size in bytes */
			var second_addr = header.readUInt32LE(28);    /* physical load addr */
			var tags_addr = header.readUInt32LE(32);      /* physical addr for kernel tags */
			var page_size_r = header.readUInt32LE(36);      /* flash page size we assume */
			var dt_size = header.readUInt32LE(40);        /* device tree in bytes */
			var unused = header.readUInt32LE(44);         /* future expansion: should be 0 */
			var name = header.slice(48, 48 + 16); /* asciiz product name */
			var cmdline = header.slice(64, 64 + 512);
			var id = header.slice(576, 576 + 8);   /* timestamp / checksum / sha1 / etc */

			console.log("Kernel  " + kernel_size + " bytes at 0x" + zeroFill(kernel_addr.toString(16), 8));
			console.log("Ramdisk " + ramdisk_size + " bytes at 0x" + zeroFill(ramdisk_addr.toString(16), 8));
			console.log("Second  " + second_size + " bytes at 0x" + zeroFill(second_addr.toString(16), 8));
			console.log("Tags at 0x" + zeroFill(second_addr.toString(16), 8));
			console.log("Page size: " + page_size_r);
			console.log("DT size: " + dt_size + " bytes");
			console.log("Unused: " + unused);
			console.log("Board name: " + name);
			console.log("Commandline: " + cmdline);
			console.log("ID: " + id.toJSON());

			// read the kernel, ramdisk, dt
			var prefix = path.basename(file_path),
				n = Math.floor((kernel_size + page_size_r - 1) / page_size_r),
				m = Math.floor((ramdisk_size + page_size_r - 1) / page_size_r),
				o = Math.floor((second_size + page_size_r - 1) / page_size_r),
				p = Math.floor((dt_size + page_size_r - 1) / page_size_r);
			extract_portion(fd, 1 * page_size_r, kernel_size, prefix + "-kernel");
			extract_portion(fd, (1 + n) * page_size_r, ramdisk_size, prefix + "-ramdisk");
			extract_portion(fd, (1 + n + m) * page_size_r, second_size, prefix + "-second");
			extract_portion(fd, (1 + n + m + o) * page_size_r, dt_size, prefix + "-dt");
	    });
	});
}

if(require.main === module) {
	var imgfile = "",
		pagesize = 2048;
	if(process.argv.length <= 2) {
		console.log("Usage:");
		console.log("  " + process.argv[1] + ' [options]');
		console.log("  ");
		console.log("  Options:");
		console.log("     -i|--input [input file]");
		console.log("     <-p|--pagesize [size]>");
		return 0;
	}
	for(var i = 2; i < process.argv.length; i ++) {
		if((process.argv[i] === '-i') || ((process.argv[i] === '--input')))
			imgfile = process.argv[++i];
		else if((process.argv[i] === '-p') || ((process.argv[i] === '--pagesize')))
			pagesize = parseInt(process.argv[++i]);
		else {
			console.log('Invalid commandline option: ' + process.argv[i]);
			return 1;
		}
	}
	if((!imgfile) || (typeof imgfile !== 'string') || 
		(imgfile.trim().length === 0) || (!fs.existsSync(imgfile)) ||
		(!fs.statSync(imgfile).isFile())) {
		console.log('Invalid image file: ' + imgfile);
		return 1;
	}
	if((typeof pagesize !== 'number') || (pagesize % 2048 !== 0)) {
		console.log('Invalid pagesize: ' + pagesize);
		return 1;
	}
	extract_info(imgfile, pagesize);
} else {
	console.log('As module');
	module.exports = extract_info;
}


// The bootimg.h:
//
//		/* tools/mkbootimg/bootimg.h
//		**
//		** Copyright 2007, The Android Open Source Project
//		**
//		** Licensed under the Apache License, Version 2.0 (the "License"); 
//		** you may not use this file except in compliance with the License. 
//		** You may obtain a copy of the License at 
//		**
//		**     http://www.apache.org/licenses/LICENSE-2.0 
//		**
//		** Unless required by applicable law or agreed to in writing, software 
//		** distributed under the License is distributed on an "AS IS" BASIS, 
//		** WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied. 
//		** See the License for the specific language governing permissions and 
//		** limitations under the License.
//		*/
//
//		#ifndef _BOOT_IMAGE_H_
//		#define _BOOT_IMAGE_H_
//
//		typedef struct boot_img_hdr boot_img_hdr;
//
//		#define BOOT_MAGIC "ANDROID!"
//		#define BOOT_MAGIC_SIZE 8
//		#define BOOT_NAME_SIZE 16
//		#define BOOT_ARGS_SIZE 512
//
//		struct boot_img_hdr
//		{
//		    unsigned char magic[BOOT_MAGIC_SIZE];
//
//		    unsigned kernel_size;  /* size in bytes */
//		    unsigned kernel_addr;  /* physical load addr */
//
//		    unsigned ramdisk_size; /* size in bytes */
//		    unsigned ramdisk_addr; /* physical load addr */
//
//		    unsigned second_size;  /* size in bytes */
//		    unsigned second_addr;  /* physical load addr */
//
//		    unsigned tags_addr;    /* physical addr for kernel tags */
//		    unsigned page_size;    /* flash page size we assume */
//		    unsigned dt_size;      /* device tree in bytes */
//		    unsigned unused;       /* future expansion: should be 0 */
//		    unsigned char name[BOOT_NAME_SIZE]; /* asciiz product name */
//
//		    unsigned char cmdline[BOOT_ARGS_SIZE];
//
//		    unsigned id[8]; /* timestamp / checksum / sha1 / etc */
//		};
//
//		/*
//		** +-----------------+ 
//		** | boot header     | 1 page
//		** +-----------------+
//		** | kernel          | n pages  
//		** +-----------------+
//		** | ramdisk         | m pages  
//		** +-----------------+
//		** | second stage    | o pages
//		** +-----------------+
//		** | device tree     | p pages
//		** +-----------------+
//		**
//		** n = (kernel_size + page_size - 1) / page_size
//		** m = (ramdisk_size + page_size - 1) / page_size
//		** o = (second_size + page_size - 1) / page_size
//		** p = (dt_size + page_size - 1) / page_size
//		**
//		** 0. all entities are page_size aligned in flash
//		** 1. kernel and ramdisk are required (size != 0)
//		** 2. second is optional (second_size == 0 -> no second)
//		** 3. load each element (kernel, ramdisk, second) at
//		**    the specified physical address (kernel_addr, etc)
//		** 4. prepare tags at tag_addr.  kernel_args[] is
//		**    appended to the kernel commandline in the tags.
//		** 5. r0 = 0, r1 = MACHINE_TYPE, r2 = tags_addr
//		** 6. if second_size != 0: jump to second_addr
//		**    else: jump to kernel_addr
//		*/
//
//		#if 0
//		typedef struct ptentry ptentry;
//		struct ptentry {
//		    char name[16];      /* asciiz partition name    */
//		    unsigned start;     /* starting block number    */
//		    unsigned length;    /* length in blocks         */
//		    unsigned flags;     /* set to zero              */
//		};
//		/* MSM Partition Table ATAG
//		**
//		** length: 2 + 7 * n
//		** atag:   0x4d534d70
//		**         <ptentry> x n
//		*/
//		#endif
//
//		#endif