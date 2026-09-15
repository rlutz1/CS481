#include "src.hpp"

int main(int argc, char** argv)
{
    int page_size, virtual_address, vpn, offset;

    page_size = 4096;
    virtual_address = 65536;
    split_virtual_address(virtual_address, page_size, &vpn, &offset);
    if (offset != 0)
    {
        fprintf(stderr, "Virtual Address %d, page size %d, expected offset 0 but got %d\n",
                virtual_address, page_size, offset);
        return 1;
    }

    virtual_address = 68999;
    split_virtual_address(virtual_address, page_size, &vpn, &offset);
    if (offset != 3463)
    {
        fprintf(stderr, "Virtual Address %d, page size %d, expected offset 3463 but got %d\n",
                virtual_address, page_size, offset);
        return 1;
    }

    page_size = 1024;
    virtual_address = 65536;
    split_virtual_address(virtual_address, page_size, &vpn, &offset);
    if (offset != 0)
    {
        fprintf(stderr, "Virtual Address %d, page size %d, expected offset 0 but got %d\n",
                virtual_address, page_size, offset);
        return 1;
    }

    page_size = 1024;
    virtual_address += 3000;
    split_virtual_address(virtual_address, page_size, &vpn, &offset);
    if (offset != 952)
    {
        fprintf(stderr, "Virtual Address %d, page size %d, expected offset 952 but got %d\n",
                virtual_address, page_size, offset);
        return 1;
    }
}
