#include "src.hpp"

int main(int argc, char** argv)
{
    FrameList* remove_frame;
    int count;
    int idx = 0;
    printf("Adding head, idx %d\n", idx);    
    FrameList* head = new FrameList(idx++);
    FrameList* tail = head;
    for (int i = 0; i < 10; i++)
    {
        printf("Adding next frame, idx %d\n", idx);
        FrameList* next = new FrameList(idx++);
        tail->next = next;
        tail = next;
    }

    count = fifo(head, &remove_frame);
    if (count != 1)
    {
        fprintf(stderr, "After first removal, count = %d, expected to be 1\n", count);
        return 1;
    }
    tail = remove_frame->next;
    delete remove_frame;
    head = tail;

    count = fifo(head, &remove_frame);
    if (count != 1)
    {
        fprintf(stderr, "After first removal, count = %d, expected to be 1\n", count);
        return 1;
    }
    tail = remove_frame->next;
    delete remove_frame;
    head = tail;

    count = fifo(head, &remove_frame);
    if (count != 1)
    {
        fprintf(stderr, "After first removal, count = %d, expected to be 1\n", count);
        return 1;
    }
    tail = remove_frame->next;
    delete remove_frame;
    head = tail;


    for (int i = 3; i < 10; i++)
    {
        FrameList* next = new FrameList(idx++);
        tail->next = next;
        tail = next;
    }
    count = fifo(head, &remove_frame);
    if (count != 1)
    {
        fprintf(stderr, "After first removal, count = %d, expected to be 1\n", count);
        return 1;
    }
}
