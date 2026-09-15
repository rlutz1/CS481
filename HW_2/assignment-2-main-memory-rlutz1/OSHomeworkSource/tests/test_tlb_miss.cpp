#include "src.hpp"

int main(int argc, char** argv)
{
    bool exception;

    PageTable* table = new PageTable(128);
    printf("Adding page with VPN 64, PFN 256, protect bit 0, valid bit 1\n");    
    table->add_page(64, 256, 0, 1);
    printf("Adding page with VPN 65, PFN 312, protect bit 0, valid bit 1\n");    
    table->add_page(65, 312, 0, 1);
    printf("Adding page with VPN 66, PFN 1024, protect bit 0, valid bit 1\n");    
    table->add_page(66, 1024, 0, 1);
    printf("Adding page with VPN 67, PFN 0, protect bit 1, valid bit 1\n");    
    table->add_page(67, 0, 1, 1);
    printf("Adding page with VPN 68, PFN 120, protect bit 1, valid bit 1\n");    
    table->add_page(68, 120, 1, 1);

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
        TLB_lookup(tlb, 68);
    }
    catch (const char* msg)
    {
        if (strcmp(msg, TLB_MISS) != 0)
        {
            fprintf(stderr, "TLB lookup of VPN 68 threw %s", msg);
            return 1;
        }
        exception = true;
    }
    if (not exception)
    {
        fprintf(stderr, "TLB lookup for VPN 68 expected TLB MISS.\n");
        return 1;
    }

    try
    {
        exception = false;
        TLB_lookup(tlb, 0);
    }
    catch (const char* msg)
    {
        if (strcmp(msg, TLB_MISS) != 0)
        {
            fprintf(stderr, "TLB lookup of VPN 0 threw %s", msg);
            return 1;
        }
        exception = true;
    }
    if (not exception)
    {
        fprintf(stderr, "TLB lookup for VPN 0 expected TLB MISS.\n");
        return 1;
    }


    try
    {
        exception = false;
        TLB_lookup(tlb, 123);
    }
    catch (const char* msg)
    {
        if (strcmp(msg, TLB_MISS) != 0)
        {
            fprintf(stderr, "TLB lookup of VPN 123 threw %s", msg);
            return 1;
        }
        exception = true;
    }
    if (not exception)
    {
        fprintf(stderr, "TLB lookup for VPN 123 expected TLB MISS.\n");
        return 1;
    }


    try
    {
        exception = false;
        TLB_lookup(tlb, 37);
    }
    catch (const char* msg)
    {
        if (strcmp(msg, TLB_MISS) != 0)
        {
            fprintf(stderr, "TLB lookup of VPN 37 threw %s", msg);
            return 1;
        }
        exception = true;
    }
    if (not exception)
    {
        fprintf(stderr, "TLB lookup for VPN 37 expected TLB MISS.\n");
        return 1;
    }

    
    delete tlb; 
}
