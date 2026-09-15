#include "src.hpp"

int main(int argc, char** argv)
{
    PageTable* table = new PageTable(16);

    PTE* entry = new PTE();
    entry->update_entry(20, 0, 1);

    int addr;
    int page_size = 4;
    int virtual_address;

    TLB* tlb = new TLB(4,2);
    printf("Adding PFN 20 to TLB at idx 2, tag 1\n");
    tlb->add_entry(2, 1, entry);
    virtual_address = 24;
    addr = virtual_to_physical(virtual_address, page_size, tlb, table);
    if (addr != 80)
    {
        fprintf(stderr, "Virtual Address %d, Page size %d, returned address %d but expected %d\n", 
                virtual_address, page_size, addr, 80);
        return 1;
    }

    virtual_address = 26;
    addr = virtual_to_physical(virtual_address, page_size, tlb, table);
    if (addr != 82)
    {
        fprintf(stderr, "Virtual Address %d, Page size %d, returned address %d but expected %d\n", 
                virtual_address, page_size, addr, 82);
        return 1;
    }


    delete tlb;
    delete table; 
    delete entry;
}
