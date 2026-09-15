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
    if (remove_frame->idx != 0)
    {
        fprintf(stderr, "After first removal, remove_frame->idx = %d, expected to be 0\n", remove_frame->idx);
        return 1;
    }
    head = remove_frame->next;
    delete remove_frame;

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

    count = lru(head, &remove_frame);
    if (remove_frame->idx != 6)
    {
        fprintf(stderr, "After third removal, remove_frame->idx = %d, expected to be 6\n", remove_frame->idx);
        return 1;
    }
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
    printf("Accessing head, ");    
    while (tail->next)
    {
        if (tail->idx != 8)
        {
            printf("New IDX %d\n", idx);        
            tail->access(idx++);
            printf("Accessing next (skipping if next->idx 8), ");        
        } 
        tail = tail->next;
    }
    printf("\n");
    count = lru(head, &remove_frame);
    if (remove_frame->idx != 8)
    {
        fprintf(stderr, "After third removal, remove_frame->idx = %d, expected to be 8\n", remove_frame->idx);
        return 1;
    }
}

