#include "src.hpp"

int main(int argc, char** argv)
{
    PageTable* table = new PageTable(16);
    TLB* tlb = new TLB(4,2);
    printf("Adding page with VPN 4, PFN 16, protect bit 0, valid bit 1\n");
    table->add_page(4, 16, 0, 1);
    printf("Adding page with VPN 6, PFN 25, protect bit 1, valid bit 1\n");
    table->add_page(6, 25, 1, 1);
    printf("Adding page with VPN 8, PFN 0, protect bit 1, valid bit 0\n");
    table->add_page(8, 0, 1, 0);
    printf("Adding page with VPN 15, PFN 2, protect bit 0, valid bit 0\n");
    table->add_page(15, 2, 0, 0);

    int addr;
    int page_size = 4;
    int virtual_address = 16;
    addr = virtual_to_physical(virtual_address, page_size, tlb, table);
    if (addr != 64)
    {
        fprintf(stderr, "Virtual Address %d, Page size %d, returned physical address %d but expected 64\n",
                virtual_address, page_size, addr);
        return 1;
    }

    virtual_address = 19;
    addr = virtual_to_physical(virtual_address, page_size, tlb, table);
    if (addr != 67)
    {
        fprintf(stderr, "Virtual Address %d, Page size %d, returned physical address %d but expected 67\n",
                virtual_address, page_size, addr);
        return 1;
    }



    delete tlb;
    delete table; 
}
