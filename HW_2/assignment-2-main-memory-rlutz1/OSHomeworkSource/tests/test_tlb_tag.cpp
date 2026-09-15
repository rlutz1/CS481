#include "src.hpp"

int main(int argc, char** argv)
{
    int VPN, k, index, tag, expected;

    k = 2;
    VPN = 16;
    split_VPN(VPN, k, &index, &tag);
    expected = 8;
    if (tag != expected)
    {
        fprintf(stderr, "split VPN with VPN %d, k %d, returned tag %d, expected %d\n",
                VPN, k, tag, expected);
        return 1;
    }

    VPN = 17;
    split_VPN(VPN, k, &index, &tag);
    expected = 8;
    if (tag != expected)
    {
        fprintf(stderr, "split VPN with VPN %d, k %d, returned tag %d, expected %d\n",
                VPN, k, tag, expected);
        return 1;
    }

    VPN = 32;
    split_VPN(VPN, k, &index, &tag);
    expected = 16;
    if (tag != expected)
    {
        fprintf(stderr, "split VPN with VPN %d, k %d, returned tag %d, expected %d\n",
                VPN, k, tag, expected);
        return 1;
    }

    VPN = 33;
    split_VPN(VPN, k, &index, &tag);
    expected = 16;
    if (tag != expected)
    {
        fprintf(stderr, "split VPN with VPN %d, k %d, returned tag %d, expected %d\n",
                VPN, k, tag, expected);
        return 1;
    }

    k = 4;
    VPN = 16;
    split_VPN(VPN, k, &index, &tag);
    expected = 4;
    if (tag != expected)
    {
        fprintf(stderr, "split VPN with VPN %d, k %d, returned tag %d, expected %d\n",
                VPN, k, tag, expected);
        return 1;
    }

    VPN = 17;
    split_VPN(VPN, k, &index, &tag);
    expected = 4;
    if (tag != expected)
    {
        fprintf(stderr, "split VPN with VPN %d, k %d, returned tag %d, expected %d\n",
                VPN, k, tag, expected);
        return 1;
    }

    VPN = 18;
    split_VPN(VPN, k, &index, &tag);
    expected = 4;
    if (tag != expected)
    {
        fprintf(stderr, "split VPN with VPN %d, k %d, returned tag %d, expected %d\n",
                VPN, k, tag, expected);
        return 1;
    }

    VPN = 19;
    split_VPN(VPN, k, &index, &tag);
    expected = 4;
    if (tag != expected)
    {
        fprintf(stderr, "split VPN with VPN %d, k %d, returned tag %d, expected %d\n",
                VPN, k, tag, expected);
        return 1;
    }

}
