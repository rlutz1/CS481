#include "src.hpp"
#include <cstring>

int main(int argc, char** argv)
{
    char journal_name[] = "journal.txt";
    char data_name[] = "data.txt";

    remove(journal_name);

    char txb[] = "txe12";
    char ib[] = "ib";
    char bb[] = "bb";
    char str[] = "hello world";
    char txe[] = "txe21";
    write_to_journal(sizeof(txb)-1, txb, sizeof(ib)-1, ib, sizeof(bb)-1, bb, sizeof(str)-1, str, sizeof(txe), txe);

    sleep(1);

    int err = checkpoint(sizeof(txe), txe);
    if (err != 0)
    {
        fprintf(stderr, "Error while checkpointing\n");
        return -1;
    }

    sleep(1);

    char sol[] = "txe12ibbbhello worldtxe21";

    int fd = open(journal_name, O_RDONLY);
    int fd2 = open(data_name, O_RDONLY);

    struct stat st;
    stat(journal_name, &st);
    int size = st.st_size + 1;
    if (size <= 0)
    {
        fprintf(stderr, "Journal size was %d\n", size);
        return -1;
    }

    char* journal_bytes = (char*)malloc(size);
    char* data_bytes = (char*)malloc(size);
    read(fd, journal_bytes, size);
    read(fd2, data_bytes, size);
    journal_bytes[size-1] = '\0';
    data_bytes[size-1] = '\0';
    if (std::strcmp(data_bytes, journal_bytes) != 0) {
        fprintf(stderr, "Data and journal strings are not the same\n");
        return -1;
    }
    if (std::strcmp(sol, data_bytes) != 0) {
        fprintf(stderr, "Data written is not the same as input\n");
        return -1;
    }

    free(journal_bytes);
    free(data_bytes);
    close(fd);
    close(fd2);
}

