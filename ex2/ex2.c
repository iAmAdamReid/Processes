// Write a program that opens the text.txt  file (with the `fopen()` system call) located in this directory 
// and then calls `fork()` to create a new process. 

// Can both the child and parent access the file descriptor returned by `fopen()`?
// Yes, both processes can access the file descriptor.

// What happens when they are written to the file concurrently?
// We see both texts in the file, with a " " indicator. Either text may appear first depending on which process completes fastest.

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int main(void)
{
    // Your code here 

    FILE *fp = fopen("./text.txt", "w");

    int forked = fork();
    if(forked < 0){
        fprintf(stderr, "Fork attempt failed.\n");
        exit(1);
    } else if(forked == 0){
        char str[] = "This is the child fork text.";
        fwrite(str, 1, sizeof(str), fp);
    } else {
        wait(NULL); // this will make the parent process wait until other child processes are complete before running, resulting in the parent text appearing last.
        char str[] = "This is the parent fork text.";
        fwrite(str, 1, sizeof(str), fp);
    }
    fclose(fp);
    
    return 0;
}
