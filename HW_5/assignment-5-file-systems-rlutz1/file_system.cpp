#include "src.hpp"
#include <iostream>

void write_to_journal(int txb_bytes, char* txb, int ibytes, char* i, 
        int bbytes, char* b, int Db_bytes, char* Db, 
        int txe_bytes, char* txe)
{
  char *filename = "journal.txt";

  int file_desc = open(filename, O_WRONLY | O_CREAT, 0644); // open for write/create the journal

  int num_bytes_written = write(file_desc, txb, txb_bytes); // write the txb
  num_bytes_written = write(file_desc, i, ibytes); // write inode block
  num_bytes_written = write(file_desc, b, bbytes); // write bitmap block
  num_bytes_written = write(file_desc, Db, Db_bytes); // write data block
  num_bytes_written = write(file_desc, txe, txe_bytes); // write the txe

  int f_sync_ret = fsync(file_desc); // force the file write to disk, clear buffer

  close(file_desc); // close the file
}

int checkpoint(int txe_bytes, char* txe)
{
    //int curr_file_ptr = lseek(file_desc, 0, SEEK_SET); // set the seeker
    //curr_file_ptr = lseek(file_desc, txb_bytes, SEEK_CUR);
    char *journal_name = "journal.txt";

    int journal_desc = open(journal_name, O_RDONLY); // open the journal to read   

    // check if the journal data is complete -- txe at the end
    int curr_file_ptr = lseek(journal_desc, -txe_bytes, SEEK_END); // set the seeker to the txe zone
    char *txe_buff = (char *)malloc(txe_bytes * sizeof(char)); // buffer to read into
    int read_ret = read(journal_desc, txe_buff, txe_bytes); // attempt to read the txe
    
    if (strcmp(txe_buff, txe) != 0) { // if the end of file is not txe
	close(journal_desc); // close file
	free(txe_buff); // cleanup
	return -1; // return -1, as requested.
    } // end if

    // journal entry complete, continue to write to disk
    char *disk = "data.txt";

    int disk_desc = open(disk, O_WRONLY | O_CREAT, 0644); // open for write/create the disk

    // horribly inefficient way to do this, but testing to see if this is correct.
    // read each piece of file until EOF (read return 0)
    int sizeof_reader = 1;
    char *reader = (char *)malloc(sizeof_reader * sizeof(char)); // buffer to read into
    int bytes_read;

    curr_file_ptr = lseek(journal_desc, 0, SEEK_SET); // reset the file pointer to beginning of file
    
    // while not end of file
    while ((bytes_read = read(journal_desc, reader, sizeof_reader)) > 0) {
      write(disk_desc, reader, bytes_read);  
    } // end loop

    int f_sync_ret = fsync(disk_desc); // force the file write to disk, clear buffer

    // cleanup
    free(txe_buff);
    free(reader);
    // close all files
    close(journal_desc);
    close(disk_desc);
    return 0;
}



