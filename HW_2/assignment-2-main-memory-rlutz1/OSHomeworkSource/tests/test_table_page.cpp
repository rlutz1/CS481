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

    try
    {
        exception = false;
        printf("Looking up page 0\n");
        PFN = table_lookup(table, tlb, 0);
    }
    catch (const char* msg)
    {
        if (strcmp(msg, PAGE_FAULT) != 0)
        {
            fprintf(stderr, "Expected PAGE FAULT but got %s\n", msg);
            return 1;
        }
        exception = true;
    }
    if (not exception)
    {
        fprintf(stderr, "Expected PAGE FAULT but received no exception\n");
        return 1;
    }


    try
    {
        exception = false;
        printf("Looking up page 7\n");
        PFN = table_lookup(table, tlb, 7);
    }
    catch (const char* msg)
    {
        if (strcmp(msg, PAGE_FAULT) != 0)
        {
            fprintf(stderr, "Expected PAGE FAULT but got %s\n", msg);
            return 1;
        }
        exception = true;
    }
    if (not exception)
    {
        fprintf(stderr, "Expected PAGE FAULT but received no exception\n");
        return 1;
    }

    try
    {
        exception = false;
        printf("Looking up page 2\n");
        PFN = table_lookup(table, tlb, 2);
    }
    catch (const char* msg)
    {
        if (strcmp(msg, PAGE_FAULT) != 0)
        {
            fprintf(stderr, "Expected PAGE FAULT but got %s\n", msg);
            return 1;
        }
        exception = true;
    }
    if (not exception)
    {
        fprintf(stderr, "Expected PAGE FAULT but received no exception\n");
        return 1;
    }

    try
    {
        exception = false;
        printf("Looking up page 5\n");
        PFN = table_lookup(table, tlb, 5);
    }
    catch (const char* msg)
    {
        if (strcmp(msg, PAGE_FAULT) != 0)
        {
            fprintf(stderr, "Expected PAGE FAULT but got %s\n", msg);
            return 1;
        }
        exception = true;
    }
    if (not exception)
    {
        fprintf(stderr, "Expected PAGE FAULT but received no exception\n");
        return 1;
    }


    delete tlb;
    delete table; 
}

