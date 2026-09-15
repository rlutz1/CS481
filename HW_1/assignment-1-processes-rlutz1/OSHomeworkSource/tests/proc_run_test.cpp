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
    remove("./procs.output");
    run_processes();

    // Sleep for half a second in case parent returns
    // while children are still running
    sleep(1);

    fn = fopen("./procs.output", "r");
    if (fn == NULL) {
        fprintf(stderr, "No parent/child/grandchild process called the appropriate routines.\n");
        return 1;
    }

    char buff[255];
    int pid_g, pid_c, pid_p;
    int ret;
    
    ret = fscanf(fn, "%s\n", buff);
    if (ret == EOF)
    {
        fprintf(stderr, "At least one of your processes did not call the appropriate routines.\n");
        return 1;
    }
    ret = fscanf(fn, "%d\n", &pid_g);
    if (ret == EOF)
    {
        fprintf(stderr, "At least one of your processes did not call the appropriate routines.\n");
        return 1;
    }
    ret = fscanf(fn, "%s\n", buff);
    if (ret == EOF)
    {
        fprintf(stderr, "At least one of your processes did not call the appropriate routines.\n");
        return 1;
    }
    ret = fscanf(fn, "%d\n", &pid_c);
    if (ret == EOF)
    {
        fprintf(stderr, "At least one of your processes did not call the appropriate routines.\n");
        return 1;
    }
    ret = fscanf(fn, "%s\n", buff);
    if (ret == EOF)
    {
        fprintf(stderr, "At least one of your processes did not call the appropriate routines.\n");
        return 1;
    }
    ret = fscanf(fn, "%d\n", &pid_p);
    if (ret == EOF)
    {
        fprintf(stderr, "At least one of your processes did not call the appropriate routines.\n");
        return 1;
    }

    fclose(fn);

    if (pid_p == pid_c)
    {
        fprintf(stderr, "Parent and Child PIDs are the same\n");
        return 1;
    }
    if (pid_p == pid_g)
    {
        fprintf(stderr, "Parent and Grandchild PIDs are the same\n");
        return 1;
    }
    if (pid_c == pid_g)
    {
        fprintf(stderr, "Child and Grandparent PIDs are the same\n");
        return 1;
    }

    return 0;

}



