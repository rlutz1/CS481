#include "src.hpp"

int main(int argc, char** argv)
{
    bool exception;

    PageTable* table = new PageTable(128);
    printf("Adding page with VPN 64, PFN 256, protect bit 1, valid bit 1\n");
    table->add_page(64, 256, 1, 1);
    printf("Adding page with VPN 65, PFN 312, protect bit 1, valid bit 1\n");
    table->add_page(65, 312, 1, 1);
    printf("Adding page with VPN 66, PFN 1024, protect bit 1, valid bit 1\n");
    table->add_page(66, 1024, 1, 1);
    printf("Adding page with VPN 67, PFN 0, protect bit 1, valid bit 1\n");
    table->add_page(67, 0, 1, 1);


    TLB* tlb = new TLB(4,4);
    printf("Adding VPN 64 to TLB\n");
    tlb->add_entry(0, 16, table->entries[64]);
    printf("Adding VPN 65 to TLB\n");
    tlb->add_entry(1, 16, table->entries[65]);
    printf("Adding VPN 66 to TLB\n");
    tlb->add_entry(2, 16, table->entries[66]);
    printf("Adding VPN 67 to TLB\n");
    tlb->add_entry(3, 16, table->entries[67]);


    try
    {
        exception = false;
        TLB_lookup(tlb, 64);
    }
    catch (const char* msg)
    {
        if (strcmp(msg, PROTECT_FAULT) != 0)
        {
            fprintf(stderr, "VPN 64, Expected PROTECT FAULT but instead got %s\n", msg);
            return 1;
        }
        exception = true;
    }
    if (not exception)
    {
        fprintf(stderr, "VPN 64, expected PROTECT FAULT but succeeded\n");
        return 1;
    }

    try
    {
        exception = false;
        TLB_lookup(tlb,65);
    }
    catch (const char* msg)
    {
        if (strcmp(msg, PROTECT_FAULT) != 0)
        {
            fprintf(stderr, "VPN 65, Expected PROTECT FAULT but instead got %s\n", msg);
            return 1;
        }
        exception = true;
    }
    if (not exception)
    {
        fprintf(stderr, "VPN 64, expected PROTECT FAULT but succeeded\n");
        return 1;
    }


    try
    {
        exception = false;
        TLB_lookup(tlb, 66);
    }
    catch (const char* msg)
    {
        if (strcmp(msg, PROTECT_FAULT) != 0)
        {
            fprintf(stderr, "VPN 66, Expected PROTECT FAULT but instead got %s\n", msg);
            return 1;
        }
        exception = true;
    }
    if (not exception)
    {
        fprintf(stderr, "VPN 64, expected PROTECT FAULT but succeeded\n");
        return 1;
    }


    try
    {
        exception = false;
        TLB_lookup(tlb, 67);
    }
    catch (const char* msg)
    {
        if (strcmp(msg, PROTECT_FAULT) != 0)
        {
            fprintf(stderr, "VPN 67, Expected PROTECT FAULT but instead got %s\n", msg);
            return 1;
        }
        exception = true;
    }
    if (not exception)
    {
        fprintf(stderr, "VPN 64, expected PROTECT FAULT but succeeded\n");
        return 1;
    }



    
    delete tlb; 
}
