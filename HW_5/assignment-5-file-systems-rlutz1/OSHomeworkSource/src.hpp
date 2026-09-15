#ifndef TEST_SRC_HPP
#define TEST_SRC_HPP

#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>


void write_to_journal(int txb_bytes, char* txb, int ibytes, char* i,
        int bbytes, char* b, int Db_bytes, char* Db, int txe_bytes, char* txe);
int checkpoint(int txe_bytes, char* txe);

#endif
