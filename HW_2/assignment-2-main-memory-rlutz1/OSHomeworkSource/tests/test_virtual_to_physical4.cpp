#include "src.hpp"

int main(int argc, char** argv)
{
    bool exception;
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
    int page_size = 8;
    int virtual_address = 120;

    try
    {
        exception = false;
        addr = virtual_to_physical(virtual_address, page_size, tlb, table);
    }
    catch (const char* msg)
    {
        if (strcmp(msg, SEG_FAULT) != 0)
        {
            fprintf(stderr, "Virtual Address %d, page size %d, expected SEGFAULT but got %s\n", 
                    virtual_address, page_size, msg);
            return 1;
        }
        exception = true;
    }
    if (not exception)
    {
        fprintf(stderr, "Virtual Address %d, page size %d, expected SEGFAULT but succeeded\n",
                virtual_address, page_size);
        return 1;
    }

    table->add_page(15, 12, 0, 1);
    tlb->add_entry(3, 3, table->entries[15]);
    addr = virtual_to_physical(virtual_address, page_size, tlb, table);
    if (addr != 96)
    {
        fprintf(stderr, "Virtual Address %d, Page size %d, returned physical address %d but expected 96\n",
                virtual_address, page_size, addr);
        return 1;
    }

    virtual_address = 127;
    addr = virtual_to_physical(virtual_address, page_size, tlb, table);
    if (addr != 103)
    {
        fprintf(stderr, "Virtual Address %d, Page size %d, returned physical address %d but expected 103\n",
                virtual_address, page_size, addr);
        return 1;
    }


    delete tlb;
    delete table; 
}
