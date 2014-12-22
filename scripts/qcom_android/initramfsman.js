#!/usr/local/bin/node

var fs = require('fs'),
    path = require('path'),
    zlib = require('zlib');

function padLeft( number, width, filler ) {
    filler = filler || ' ';
    width -= number.toString().length;
    if ( width > 0 )
        return new Array( width + (/\./.test( number ) ? 2 : 1) ).join( filler ) + number;
    return number + ""; // always return a string
}

// Supports only gziped newc format initramfs

function enum_initramfs_entries(buffer, file_entry_cb) {
    zlib.gunzip(buffer, function(err, newc_data) {
        data = newc_data;
        for(var i = 0; i < newc_data.length; ) {
            if((i % 4) !== 0) i += 4 - (i % 4);
            if(newc_data.slice(i, i + 6).toString() !== '070701') {
                if(newc_data[i] !== 0) {
                    console.log('Error extracting file entry from initramfs.');
                    break;
                } else i++;
            }
            var file_entry = {
                    c_magic: newc_data.slice(i, i + 6).toString(),
                    c_ino: parseInt('0x' + newc_data.slice(i + 6, i + 14).toString()),          //File inode number
                    c_mode: parseInt('0x' + newc_data.slice(i + 14, i + 22).toString()),        //File mode and permissions
                    c_uid: parseInt('0x' + newc_data.slice(i + 22, i + 30).toString()),         //File uid
                    c_gid: parseInt('0x' + newc_data.slice(i + 30, i + 38).toString()),         //File gid
                    c_nlink: parseInt('0x' + newc_data.slice(i + 38, i + 46).toString()),       //Number of links
                    c_mtime: parseInt('0x' + newc_data.slice(i + 46, i + 54).toString()),       //Modification time
                    c_filesize: parseInt('0x' + newc_data.slice(i + 54, i + 62).toString()),    //Size of data field
                    c_maj: parseInt('0x' + newc_data.slice(i + 62, i + 70).toString()),         //Major part of file device number
                    c_min: parseInt('0x' + newc_data.slice(i + 70, i + 78).toString()),         //Minor part of file device number
                    c_rmaj: parseInt('0x' + newc_data.slice(i + 78, i + 86).toString()),        //Major part of device node reference
                    c_rmin: parseInt('0x' + newc_data.slice(i + 86, i + 94).toString()),        //Minor part of device node reference
                    c_namesize: parseInt('0x' + newc_data.slice(i + 94, i + 102).toString()),   //Length of filename, including final \0
                    c_chksum: parseInt('0x' + newc_data.slice(i + 102, i + 110).toString())     //zero
                }
            file_entry.filename = newc_data.slice(i + 110, i + 110 + file_entry.c_namesize).toString();
            file_entry.filename = file_entry.filename.replace(/\u0000$/, '');
            var data_start_pos = i + 110 + file_entry.c_namesize;
            if((data_start_pos % 4) !== 0) data_start_pos += 4 - (data_start_pos % 4);
            file_entry.data = newc_data.slice(data_start_pos, data_start_pos + file_entry.c_filesize);
            file_entry_cb(file_entry);

            if(file_entry.filename === "TRAILER!!!")
                if(file_entry.c_ino +
                    file_entry.c_mode +
                    file_entry.c_uid +
                    file_entry.c_gid +
                    file_entry.c_nlink +
                    file_entry.c_mtime +
                    file_entry.c_filesize +
                    file_entry.c_maj +
                    file_entry.c_min +
                    file_entry.c_rmaj +
                    file_entry.c_rmin +
                    file_entry.c_namesize +
                    file_entry.c_chksum +
                    file_entry.data.length === 12)
                    break;
            i = data_start_pos + file_entry.c_filesize;
        }
    });
}

enum_initramfs_entries(fs.readFileSync('/home/weever/initrd.img'), function(file_entry) {
    if(file_entry.filename === "TRAILER!!!") console.log(console.dir(file_entry));
    else console.log(file_entry.filename + ': ' + file_entry.c_nlink);
})

// See: https://www.kernel.org/doc/Documentation/early-userspace/buffer-format.txt
//
//
//                initramfs buffer format
//                -----------------------
//
//                Al Viro, H. Peter Anvin
//               Last revision: 2002-01-13
//
// Starting with kernel 2.5.x, the old "initial ramdisk" protocol is
// getting {replaced/complemented} with the new "initial ramfs"
// (initramfs) protocol.  The initramfs contents is passed using the same
// memory buffer protocol used by the initrd protocol, but the contents
// is different.  The initramfs buffer contains an archive which is
// expanded into a ramfs filesystem; this document details the format of
// the initramfs buffer format.
//
// The initramfs buffer format is based around the "newc" or "crc" CPIO
// formats, and can be created with the cpio(1) utility.  The cpio
// archive can be compressed using gzip(1).  One valid version of an
// initramfs buffer is thus a single .cpio.gz file.
//
// The full format of the initramfs buffer is defined by the following
// grammar, where:
//     *    is used to indicate "0 or more occurrences of"
//     (|)    indicates alternatives
//     +    indicates concatenation
//     GZIP()    indicates the gzip(1) of the operand
//     ALGN(n)    means padding with null bytes to an n-byte boundary
//
//     initramfs  := ("\0" | cpio_archive | cpio_gzip_archive)*
//
//     cpio_gzip_archive := GZIP(cpio_archive)
//
//     cpio_archive := cpio_file* + (<nothing> | cpio_trailer)
//
//     cpio_file := ALGN(4) + cpio_header + filename + "\0" + ALGN(4) + data
//
//     cpio_trailer := ALGN(4) + cpio_header + "TRAILER!!!\0" + ALGN(4)
//
//
// In human terms, the initramfs buffer contains a collection of
// compressed and/or uncompressed cpio archives (in the "newc" or "crc"
// formats); arbitrary amounts zero bytes (for padding) can be added
// between members.
//
// The cpio "TRAILER!!!" entry (cpio end-of-archive) is optional, but is
// not ignored; see "handling of hard links" below.
//
// The structure of the cpio_header is as follows (all fields contain
// hexadecimal ASCII numbers fully padded with '0' on the left to the
// full width of the field, for example, the integer 4780 is represented
// by the ASCII string "000012ac"):
//
// Field name    Field size     Meaning
// c_magic          6 bytes         The string "070701" or "070702"
// c_ino          8 bytes         File inode number
// c_mode          8 bytes         File mode and permissions
// c_uid          8 bytes         File uid
// c_gid          8 bytes         File gid
// c_nlink          8 bytes         Number of links
// c_mtime          8 bytes         Modification time
// c_filesize    8 bytes         Size of data field
// c_maj          8 bytes         Major part of file device number
// c_min          8 bytes         Minor part of file device number
// c_rmaj          8 bytes         Major part of device node reference
// c_rmin          8 bytes         Minor part of device node reference
// c_namesize    8 bytes         Length of filename, including final \0
// c_chksum      8 bytes         Checksum of data field if c_magic is 070702;
//                  otherwise zero
//
// The c_mode field matches the contents of st_mode returned by stat(2)
// on Linux, and encodes the file type and file permissions.
//
// The c_filesize should be zero for any file which is not a regular file
// or symlink.
//
// The c_chksum field contains a simple 32-bit unsigned sum of all the
// bytes in the data field.  cpio(1) refers to this as "crc", which is
// clearly incorrect (a cyclic redundancy check is a different and
// significantly stronger integrity check), however, this is the
// algorithm used.
//
// If the filename is "TRAILER!!!" this is actually an end-of-archive
// marker; the c_filesize for an end-of-archive marker must be zero.
//
//
// *** Handling of hard links
//
// When a nondirectory with c_nlink > 1 is seen, the (c_maj,c_min,c_ino)
// tuple is looked up in a tuple buffer.  If not found, it is entered in
// the tuple buffer and the entry is created as usual; if found, a hard
// link rather than a second copy of the file is created.  It is not
// necessary (but permitted) to include a second copy of the file
// contents; if the file contents is not included, the c_filesize field
// should be set to zero to indicate no data section follows.  If data is
// present, the previous instance of the file is overwritten; this allows
// the data-carrying instance of a file to occur anywhere in the sequence
// (GNU cpio is reported to attach the data to the last instance of a
// file only.)
//
// c_filesize must not be zero for a symlink.
//
// When a "TRAILER!!!" end-of-archive marker is seen, the tuple buffer is
// reset.  This permits archives which are generated independently to be
// concatenated.
//
// To combine file data from different sources (without having to
// regenerate the (c_maj,c_min,c_ino) fields), therefore, either one of
// the following techniques can be used:
//
// a) Separate the different file data sources with a "TRAILER!!!"
//    end-of-archive marker, or
//
// b) Make sure c_nlink == 1 for all nondirectory entries.