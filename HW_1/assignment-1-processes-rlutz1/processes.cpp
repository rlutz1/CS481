#include "src.hpp"

// Fill in this method to complete Homework 1, Part 1
// Method is called by 'parent' process
void run_processes()
{
  int childp = fork(); // create the child
  wait(NULL); // wait for kid

  if (childp < 0) {
    printf("Something went wrong in child creation.\n");
    return;
  } // end if
  

  if (childp == 0) { // if i'm the child
    int grandchildp = fork(); // i'm going to create the grandchild
    wait(NULL); // child wait for grandkid
    
    if (grandchildp < 0) {
      printf("Something went wrong in grandchild creation.\n");
      _exit(1);
    } // end if
      

    if (grandchildp == 0) { // if i am the grandchild
      grandchild(); // call grandchild method
      _exit(0);
    } // end if
     
    child(); // call the child method
    _exit(0);
  } // end if

  parent(); // finally, call parent
  return;
} // end method
