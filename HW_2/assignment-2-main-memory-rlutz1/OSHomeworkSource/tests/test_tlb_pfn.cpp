#include "src.hpp"

int main(int argc, char** argv)
{
    int PFN;

    PageTable* table = new PageTable(128);
    printf("Adding page with VPN 64, PFN 256, protect bit 0, valid bit 1\n");
    table->add_page(64, 256, 0, 1);
    printf("Adding page with VPN 65, PFN 312, protect bit 0, valid bit 1\n");
    table->add_page(65, 312, 0, 1);
    printf("Adding page with VPN 66, PFN 1024, protect bit 0, valid bit 1\n");
    table->add_page(66, 1024, 0, 1);
    printf("Adding page with VPN 67, PFN 0, protect bit 0, valid bit 1\n");
    table->add_page(67, 0, 0, 1);


    TLB* tlb = new TLB(4,4);
    printf("Adding VPN 64 to TLB\n");
    tlb->add_entry(0, 16, table->entries[64]);
    printf("Adding VPN 65 to TLB\n");
    tlb->add_entry(1, 16, table->entries[65]);
    printf("Adding VPN 66 to TLB\n");
    tlb->add_entry(2, 16, table->entries[66]);
    printf("Adding VPN 67 to TLB\n");
    tlb->add_entry(3, 16, table->entries[67]);

    PFN = TLB_lookup(tlb, 64);
    if (PFN != 256)
    {
        fprintf(stderr, "TLB lookup of VPN returned %d, expected 256\n", PFN);
        return 1;
    }

    PFN = TLB_lookup(tlb, 65);
    if (PFN != 312)
    {
        fprintf(stderr, "TLB lookup of VPN returned %d, expected 312\n", PFN);
        return 1;
    }

    PFN = TLB_lookup(tlb, 66);
    if (PFN != 1024)
    {
        fprintf(stderr, "TLB lookup of VPN returned %d, expected 1024\n", PFN);
        return 1;
    }

    PFN = TLB_lookup(tlb, 67);
    if (PFN != 0)
    {
        fprintf(stderr, "TLB lookup of VPN returned %d, expected 0\n", PFN);
        return 1;
    }

    delete tlb; 
}
