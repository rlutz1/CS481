#include "src.hpp"

int main(int argc, char** argv)
{
    int PFN;
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

    PFN = table_lookup(table, tlb, 4);
    if (PFN != 16)
    {
        fprintf(stderr, "table lookup for VPN 4 expected 16, but instead got %d\n", PFN);
        return 1;
    }

    try
    {
        exception = false;
        PFN = table_lookup(table, tlb, 6);
    }
    catch (const char* msg)
    {
        if (strcmp(msg, PROTECT_FAULT) != 0)
        {
            fprintf(stderr, "VPN 6, Expected PROTECT FAULT but instead got %s\n", msg);
            return 1;
        }
        exception = true;
    }
    if (not exception)
    {
        fprintf(stderr, "table lookup for VPN 6 expected protection fault but instead succeeded.\n");
        return 1;
    }


    try
    {
        exception = false;
        PFN = table_lookup(table, tlb, 8);
    }
    catch (const char* msg)
    {
        if (strcmp(msg, SEG_FAULT) != 0)
        {
            fprintf(stderr, "VPN 8, Expected SEGFAULT but instead got %s\n", msg);
            return 1;
        }
        exception = true;
    }
    if (not exception)
    {
        fprintf(stderr, "table lookup for VPN 8 expected segfault but instead succeeded.\n");
        return 1;
    }


    try
    {
        exception = false;
        PFN = table_lookup(table, tlb, 15);
    }
    catch (const char* msg)
    {
        if (strcmp(msg, SEG_FAULT) != 0)
        {
            fprintf(stderr, "VPN 15, Expected SEGFAULT but instead got %s\n", msg);
            return 1;
        }
        exception = true;
    }
    if (not exception)
    {
        fprintf(stderr, "table lookup for VPN 15 expected segfault but instead succeeded.\n");
        return 1;
    }



    try
    {
        exception = false;
        PFN = table_lookup(table, tlb, 2);
    }
    catch (const char* msg)
    {
        if (strcmp(msg, PAGE_FAULT) != 0)
        {
            fprintf(stderr, "VPN 2, Expected PAGE FAULT but instead got %s\n", msg);
            return 1;
        }
        exception = true;
    }
    if (not exception)
    {
        fprintf(stderr, "table lookup for VPN 2 expected page fault but instead succeeded.\n");
        return 1;
    }



    delete tlb;
    delete table; 
}
