#include "src.hpp"
#include <cstring>

int main(int argc, char** argv)
{
    char txb[] = "txe12";
    char ib[] = "ib";
    char bb[] = "bb";
    char str[] = "hello world";
    char txe[] = "txe21";
    write_to_journal(sizeof(txb)-1, txb, sizeof(ib)-1, ib, sizeof(bb)-1, bb, sizeof(str)-1, str, sizeof(txe), txe);

    char journal_name[] = "journal.txt";
    char sol[] = "txe12ibbbhello worldtxe21";

    int fd = open(journal_name, O_RDONLY);

    struct stat st;
    stat(journal_name, &st);
    int size = st.st_size;
    char* file_bytes = (char*)malloc(size*sizeof(char));
    file_bytes[size-1] = '\0';
    read(fd, file_bytes, size);
    
    printf(file_bytes);
    printf("\n");

    if (std::strcmp(file_bytes, sol) != 0) {
        fprintf(stderr, "File does not match input\n");
        return -1;
    }
    
    close(fd);
}
