#include "src.hpp"

int main(int argc, char** argv)
{
    int count;
    int idx = 0;
    printf("Adding head, idx %d\n", idx);    
    FrameList* head = new FrameList(idx++);
    FrameList* tail = head;
    FrameList* remove_frame;
    for (int i = 0; i < 10; i++)
    {
        printf("Adding next frame, idx %d\n", idx);        
        FrameList* next = new FrameList(idx++);
        tail->next = next;
        tail = next;
    }

    count = clock_lru(head, &remove_frame);
    if (count != 12)
    {
        fprintf(stderr, "After first removal, count = %d, expected to be 12\n", count);
        return 1;
    }

    count = clock_lru(head, &remove_frame);
    if (count != 1)
    {
        fprintf(stderr, "After second removal, count = %d, expected to be 1\n", count);
        return 1;
    }

    tail = head;
    printf("Accessing head, ");
    for (int i = 0; i < 5; i++)
    {
        printf("New IDX %d\n", idx);
        tail->access(idx++);
        printf("Accessing next, ");
        tail = tail->next;
    }
    printf("\n");
    count = clock_lru(head, &remove_frame);
    if (count != 6)
    {
        fprintf(stderr, "After third removal, count = %d, expected to be 6\n", count);
        return 1;
    }



}



