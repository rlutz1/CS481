#include "src.hpp"
#include <cstring>

int main(int argc, char** argv)
{
    remove("journal.txt");
    char txb[] = "txe12";
    char ib[] = "ib";
    char bb[] = "bb";
    char str[] = "hello world";
    char txe[] = "";
    write_to_journal(sizeof(txb)-1, txb, sizeof(ib)-1, ib, sizeof(bb)-1, bb, sizeof(str)-1, str, sizeof(txe), txe);

    sleep(1);

    char txe_err[] = "txe21";
    int err = checkpoint(sizeof(txe_err), txe_err);
    if (err != -1)
    {
        fprintf(stderr, "Checkpointing return expected to be -1, was %d\n", err);
        return -1;
    }
}
