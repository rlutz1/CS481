#include "src.hpp"

int main(int argc, char** argv)
{
    int VPN, k, index, tag;

    k = 2;
    VPN = 16;
    split_VPN(VPN, k, &index, &tag);
    if (index != 0)
    {
        fprintf(stderr, "VPN %d, k %d, expected index 0 but got %d\n", 
                VPN, k, index);
        return 1;
    }

    VPN = 17;
    split_VPN(VPN, k, &index, &tag);
    if (index != 1)
    {
        fprintf(stderr, "VPN %d, k %d, expected index 1 but got %d\n", 
                VPN, k, index);
        return 1;
    }

    VPN = 32;
    split_VPN(VPN, k, &index, &tag);
    if (index != 0)
    {
        fprintf(stderr, "VPN %d, k %d, expected index 0 but got %d\n", 
                VPN, k, index);
        return 1;
    }

    VPN = 33;
    split_VPN(VPN, k, &index, &tag);
    if (index != 1)
    {
        fprintf(stderr, "VPN %d, k %d, expected index 1 but got %d\n", 
                VPN, k, index);
        return 1;
    }

    k = 4;
    VPN = 16;
    split_VPN(VPN, k, &index, &tag);
    if (index != 0)
    {
        fprintf(stderr, "VPN %d, k %d, expected index 0 but got %d\n", 
                VPN, k, index);
        return 1;
    }

    VPN = 17;
    split_VPN(VPN, k, &index, &tag);
    if (index != 1)
    {
        fprintf(stderr, "VPN %d, k %d, expected index 1 but got %d\n", 
                VPN, k, index);
        return 1;
    }

    VPN = 18;
    split_VPN(VPN, k, &index, &tag);
    if (index != 2)
    {
        fprintf(stderr, "VPN %d, k %d, expected index 2 but got %d\n", 
                VPN, k, index);
        return 1;
    }

    VPN = 19;
    split_VPN(VPN, k, &index, &tag);
    if (index != 3)
    {
        fprintf(stderr, "VPN %d, k %d, expected index 3 but got %d\n", 
                VPN, k, index);
        return 1;
    }

}
