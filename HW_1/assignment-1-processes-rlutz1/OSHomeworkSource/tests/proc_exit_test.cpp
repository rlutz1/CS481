#include "src.hpp"

FILE* fn;

void grandchild()
{
    fn = fopen("./procs.output", "w");
    int pid = getpid();
    fprintf(fn, "Grandchild %d\n", pid);
    fflush(fn);
    fclose(fn);
}

void child()
{
    fn = fopen("./procs.output", "a");
    int pid = getpid();
    fprintf(fn, "Child %d\n", pid);
    fflush(fn);
    fclose(fn);
}

void parent()
{
    fn = fopen("./procs.output", "a");
    int pid = getpid();
    fprintf(fn, "Parent %d\n", pid);
    fflush(fn);
    fclose(fn);
}

int main(int argc, char** argv)
{
    int pid = getpid();
    remove("./procs.output");
    run_processes();

    fn = fopen("./procs.output", "r");
    if (fn == NULL) {
        fprintf(stderr, "No parent/child/grandchild process called the appropriate routines.\n");
        return 1;
    }
    fclose(fn);
    

    if (getpid() != pid)
    {
        fprintf(stderr, "A PID that is not the parent is still running.  Make sure to have all children all exit()!\n");
        return 1;
    }

    return 0;
}



