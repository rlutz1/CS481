#include "src.hpp"

void protection_fault()
{
    throw PROTECT_FAULT;
}

void segmentation_fault()
{
    throw SEG_FAULT;
}

void page_fault()
{
    throw PAGE_FAULT;
}

void tlb_miss()
{
    throw TLB_MISS;
}


