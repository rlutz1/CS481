#include "src.hpp"

int main(int argc, char** argv)
{
    int count;
    FrameList* remove_frame;
    int idx = 0;
    FrameList* head = new FrameList(idx++);
    FrameList* tail = head;
    for (int i = 0; i < 10; i++)
    {
        FrameList* next = new FrameList(idx++);
        tail->next = next;
        tail = next;
    }

    count = fifo(head, &remove_frame);
    if (remove_frame->idx != 0)
    {
        fprintf(stderr, "After first removal, remove_frame->idx = %d, expected to be 0\n", remove_frame->idx);
        return 1;
    }
    tail = remove_frame->next;
    delete remove_frame;
    head = tail;

    count = fifo(head, &remove_frame);
    if (remove_frame->idx != 1)
    {
        fprintf(stderr, "After first removal, remove_frame->idx = %d, expected to be 1\n", remove_frame->idx);
        return 1;
    }
    tail = remove_frame->next;
    delete remove_frame;
    head = tail;

    count = fifo(head, &remove_frame);
    if (remove_frame->idx != 2)
    {
        fprintf(stderr, "After first removal, remove_frame->idx = %d, expected to be 2\n", remove_frame->idx);
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
    if (remove_frame->idx != 3)
    {
        fprintf(stderr, "After first removal, remove_frame->idx = %d, expected to be 3\n", remove_frame->idx);
        return 1;
    }



}

