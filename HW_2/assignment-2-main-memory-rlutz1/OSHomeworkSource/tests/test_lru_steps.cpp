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

    count = lru(head, &remove_frame);
    head = remove_frame->next;
    delete remove_frame;

    tail = head;
    for (int i = 0; i < 5; i++)
    {
        tail->access(idx++);
        tail = tail->next;
    }
    count = lru(head, &remove_frame);
    tail = head;
    while (tail->next)
    {
        if (tail->next == remove_frame)
        {
            tail->next = remove_frame->next;
            delete remove_frame;
            break;
        }
        tail = tail->next;
    }

    tail = head;
    while (tail->next)
    {
        if (tail->idx != 8)
            tail->access(idx++);
        tail = tail->next;
    }
    count = lru(head, &remove_frame);

}

