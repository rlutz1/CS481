#include "src.hpp"

int main(int argc, char** argv)
{
    int page_size, virtual_address, vpn, offset, expected;

    page_size = 4096;
    virtual_address = 65536;
    split_virtual_address(virtual_address, page_size, &vpn, &offset);
    expected = 16;
    if (vpn != expected)
    {
        fprintf(stderr, "Virtual Address %d, Page size %d, returned VPN %d but expected %d\n", 
                virtual_address, page_size, vpn, expected);
        return 1;
    }

    virtual_address = 68999;
    split_virtual_address(virtual_address, page_size, &vpn, &offset);
    expected = 16;
    if (vpn != expected)
    {
        fprintf(stderr, "Virtual Address %d, Page size %d, returned VPN %d but expected %d\n", 
                virtual_address, page_size, vpn, expected);
        return 1;
    }


    page_size = 1024;
    virtual_address = 65536;
    split_virtual_address(virtual_address, page_size, &vpn, &offset);
    expected = 64;
    if (vpn != expected)
    {
        fprintf(stderr, "Virtual Address %d, Page size %d, returned VPN %d but expected %d\n", 
                virtual_address, page_size, vpn, expected);
        return 1;
    }


    page_size = 1024;
    virtual_address += 3000;
    split_virtual_address(virtual_address, page_size, &vpn, &offset);
    expected = 66;
    if (vpn != expected)
    {
        fprintf(stderr, "Virtual Address %d, Page size %d, returned VPN %d but expected %d\n", 
                virtual_address, page_size, vpn, expected);
        return 1;
    }

}
