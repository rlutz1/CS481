#include "src.hpp"

int main(int argc, char** argv)
{
    int PFN, VPN, expected;
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


    VPN = 64;
    PFN = TLB_lookup(tlb, VPN);
    expected = 256;
    if (PFN != expected)
    {
        fprintf(stderr, "TLB lookup for VPN %d returned %d, expected %d\n", VPN, PFN, expected);
        return 1;
    }

    VPN = 65;
    PFN = TLB_lookup(tlb, VPN);
    expected = 312;
    if (PFN != expected)
    {
        fprintf(stderr, "TLB lookup for VPN %d returned %d, expected %d\n", VPN, PFN, expected);
        return 1;
    }

    VPN = 66;
    PFN = TLB_lookup(tlb, VPN);
    expected = 1024;
    if (PFN != expected)
    {
        fprintf(stderr, "TLB lookup for VPN %d returned %d, expected %d\n", VPN, PFN, expected);
        return 1;
    }


    try
    {
        VPN = 67;
        exception = false;
        TLB_lookup(tlb, VPN);
    }
    catch (const char* msg)
    {
        if (strcmp(msg, PROTECT_FAULT) != 0)
        {
            fprintf(stderr, "VPN %d, Expected PROTECT FAULT but instead got %s\n", VPN, msg);
            return 1;
        }
        exception = true;
    }
    if (not exception)
    {
        fprintf(stderr, "VPN %d, Expected PROTECT FAULT, but succeeded\n", VPN);
        return 1;
    }

    try
    {
        VPN = 68;
        exception = false;
        TLB_lookup(tlb, VPN);
    }
    catch (const char* msg)
    {
        if (strcmp(msg, TLB_MISS) != 0)
        {
            fprintf(stderr, "VPN %d, Expected TLB MISS but instead got %s\n", VPN, msg);
            return 1;
        }
        exception = true;
    }
    if (not exception)
    {
        fprintf(stderr, "VPN %d, Expected TLB MISS but succeeded\n", VPN);
        return 1;
    }

    printf("Adding VPN 68 to TLB\n");
    tlb->add_entry(0, 17, table->entries[68]);
    try
    {
        VPN = 68;
        exception = false;
        TLB_lookup(tlb, VPN);
    }
    catch (const char* msg)
    {
        if (strcmp(msg, PROTECT_FAULT) != 0)
        {
            fprintf(stderr, "VPN %d, Expected PROTECT FAULT but instead got %s\n", VPN, msg);
            return 1;
        }
        exception = true;
    }
    if (not exception)
    {
        fprintf(stderr, "VPN %d, Expected PROTECT FAULT, but succeeded\n", VPN);
        return 1;
    }


    delete tlb; 
}
