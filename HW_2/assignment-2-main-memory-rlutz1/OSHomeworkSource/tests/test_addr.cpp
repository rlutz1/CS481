#include "src.hpp"

void print_err(int PFN, int offset, int page_size, int addr, int expected)
{
    fprintf(stderr, "Physical address of PFN %d, offset %d, page size %d: returned %d, should be %d\n", 
                PFN, offset, page_size, addr, expected);
}

int main(int argc, char** argv)
{
    int addr;

    int page_size = 4;
    int offset = 0;
    int PFN = 2;
    addr = get_physical_address(PFN, offset, page_size);
    if (addr != 8)
    {
        print_err(PFN, offset, page_size, addr, 8);
        return 1;
    }

    offset = 1;
    addr = get_physical_address(PFN, offset, page_size);
    if (addr != 9)
    {
        print_err(PFN, offset, page_size, addr, 9);
        return 9;
    }

    page_size = 16;
    offset = 0;
    PFN = 8;
    addr = get_physical_address(PFN, offset, page_size);
    if (addr != 128)
    {
        print_err(PFN, offset, page_size, addr, 128);
        return 1;
    }

    offset = 8;
    addr = get_physical_address(PFN, offset, page_size);
    if (addr != 136)
    {
        print_err(PFN, offset, page_size, addr, 136);
        return 1;
    }

}
