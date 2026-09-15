#include "src.hpp"

int main(int argc, char** argv)
{
    int PFN;
    PageTable* table = new PageTable(16);
    TLB* tlb = new TLB(4,2);
    printf("Adding page with VPN 4, PFN 16, protect bit 0, valid bit 1\n");
    table->add_page(4, 16, 0, 1);
    printf("Adding page with VPN 6, PFN 25, protect bit 0, valid bit 1\n");
    table->add_page(6, 25, 0, 1);
    printf("Adding page with VPN 8, PFN 0, protect bit 0, valid bit 1\n");
    table->add_page(8, 0, 0, 1);
    printf("Adding page with VPN 15, PFN 2, protect bit 0, valid bit 1\n");
    table->add_page(15, 2, 0, 1);

    PFN = table_lookup(table, tlb, 4);
    PFN = TLB_lookup(tlb, 4);
    if (PFN != 16)
    {
        fprintf(stderr, "TLB lookup for VPN 4 expected 16, but instead got %d\n", PFN);
        return 1;
    }

    PFN = table_lookup(table, tlb, 6);
    PFN = TLB_lookup(tlb, 6);    
    if (PFN != 25)
    {
        fprintf(stderr, "TLB lookup for VPN 6 expected 25, but instead got %d\n", PFN);
        return 1;
    }

    PFN = table_lookup(table, tlb, 8);
    PFN = TLB_lookup(tlb, 8);    
    if (PFN != 0)
    {
        fprintf(stderr, "TLB lookup for VPN 8 expected 0, but instead got %d\n", PFN);
        return 1;
    }

    PFN = table_lookup(table, tlb, 15);
    PFN = TLB_lookup(tlb, 15);    
    if (PFN != 2)
    {
        fprintf(stderr, "TLB lookup for VPN 15 expected 2, but instead got %d\n", PFN);
        return 1;
    }


    delete tlb;
    delete table; 
}
