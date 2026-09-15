#include "src.hpp"

int main(int argc, char** argv)
{
    int PFN, expected;
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
    expected = 16;
    if (PFN != expected)
    {
        printf("Table Lookup for page 4 returned PFN %d, should be %d\n",
                PFN, expected);
        return 1;
    }

    PFN = table_lookup(table, tlb, 6);
    expected = 25;
    if (PFN != expected)
    {
        printf("Table Lookup for page 6 returned PFN %d, should be %d\n",
                PFN, expected);
        return 1;
    }

    PFN = table_lookup(table, tlb, 8);
    expected = 0;
    if (PFN != expected)
    {
        printf("Table Lookup for page 8 returned PFN %d, should be %d\n",
                PFN, expected);
        return 1;
    }

    PFN = table_lookup(table, tlb, 15);
    expected = 2;
    if (PFN != expected)
    {
        printf("Table Lookup for page 15 returned PFN %d, should be %d\n",
                PFN, expected);
        return 1;
    }

    delete tlb;
    delete table; 
}
