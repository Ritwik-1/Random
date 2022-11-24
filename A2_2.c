#include <linux/kernel.h>
#include <linux/syscalls.h>

/*
 * Definition for onedcopy system call 
 */
SYSCALL_DEFINE3(onedcopy, int*, src, int*, dest, int, len)
{
    /* Allocate a buffer of size len to hold the elements of array */
    int buffer[5]; 
    
    /* Copy from user copies the data from src to buffer of size len */
    if (__copy_from_user(buffer, src, sizeof(int)* (len)))
       return -EFAULT;

   /* Copy to user copies the data from buffer to dest of size len */
    if (__copy_to_user(dest, buffer, sizeof(int)*(len)))
       return -EFAULT;

    return 0;
}