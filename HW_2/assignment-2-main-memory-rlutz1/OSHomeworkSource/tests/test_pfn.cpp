#include "src.hpp"

int main(int argc, char** argv)
{
    int PFN, page_size, offset;
    int physical_address;
    int expected;

    page_size = 4096;
    offset = 256;
    PFN = 4096;
    physical_address = get_physical_address(PFN, offset, page_size);
    expected = 16777472;
    if (physical_address != expected)
    {
        fprintf(stderr, "PFN %d, offset %d, page_size %d; expected physical address %d but got %d\n",
                PFN, offset, page_size, expected, physical_address);
        return 1;
    }


    offset += 17;
    physical_address = get_physical_address(PFN, offset, page_size);
    expected = 16777489;
    if (physical_address != expected)
    {
        fprintf(stderr, "PFN %d, offset %d, page_size %d; expected physical address %d but got %d\n",
                PFN, offset, page_size, expected, physical_address);
        return 1;
    }

    PFN = 1024;
    offset = 4096;
    physical_address = get_physical_address(PFN, offset, page_size);
    expected = 4198400;
    if (physical_address != expected)
    {
        fprintf(stderr, "PFN %d, offset %d, page_size %d; expected physical address %d but got %d\n",
                PFN, offset, page_size, expected, physical_address);
        return 1;
    }


    page_size = 1024;
    offset = 256;
    PFN = 4096;
    physical_address = get_physical_address(PFN, offset, page_size);
    expected = 4194560;
    if (physical_address != expected)
    {
        fprintf(stderr, "PFN %d, offset %d, page_size %d; expected physical address %d but got %d\n",
                PFN, offset, page_size, expected, physical_address);
        return 1;
    }

}
