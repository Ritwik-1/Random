#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <wait.h>
#include <time.h>
#include <math.h>
#include <string.h>

#define BILLION 1000000000L;

int main(){
    pid_t pid1;

    struct timespec pro1,pro2,pro3;
    struct timespec end;

    long int start_p1_sec;
    long int start_p2_sec;
    long int start_p3_sec;

    long int start_p1_nsec;
    long int start_p2_nsec;
    long int start_p3_nsec;

    long int diff1;
    long int diff2;
    long int diff3;

    pid1 = fork();

    if(pid1 == 0){
        clock_gettime(CLOCK_MONOTONIC,&pro1);
        start_p1_sec= pro1.tv_sec;
        start_p1_nsec = pro1.tv_nsec;

        char buff[20];
        sprintf(buff,"%d",getpid());
        char comm[100] = "/usr/bin/chrt -o -p 0 ";
        strcat(comm,buff);
        system(comm);

        // char comm2[100] = "/usr/bin/chrt -p ";
        // strcat(comm2,buff);

        // system(comm2);

        char* comm3[2]={NULL};
        // execvp("./kernel1.sh",comm3);
        execvp("./new.sh",comm3);
    }
    else{
        pid_t pid2 = fork();

        if(pid2 == 0){
            clock_gettime(CLOCK_MONOTONIC,&pro2);
            start_p2_sec= pro2.tv_sec;
            start_p2_nsec = pro2.tv_nsec;

            char buff[20];
            sprintf(buff,"%d",getpid());

            char comm[100] = "/usr/bin/chrt -r -p 50 ";
            strcat(comm,buff);
            system(comm);

            // char comm2[100] = "/usr/bin/chrt -p ";
            // strcat(comm2,buff);

            // system(comm2);

            char* comm3[2]={NULL};
            // execvp("./kernel1.sh",comm3);
            execvp("./new.sh",comm3);
        }
        else{
            pid_t pid3 = fork();
            if(pid3 == 0){
                clock_gettime(CLOCK_MONOTONIC,&pro3);
                start_p3_sec= pro3.tv_sec;
                start_p3_nsec = pro3.tv_nsec;

                char buff[20];
                sprintf(buff,"%d",getpid());

                char comm[100] = "/usr/bin/chrt -f -p 50 ";
                strcat(comm,buff);
                system(comm);

                // char comm2[100] = "/usr/bin/chrt -p ";
                // strcat(comm2,buff);

                // system(comm2);

                char* comm3[2]={NULL};
                // execvp("./kernel1.sh",comm3);
                execvp("./new.sh",comm3);
            }
            else{
                wait(NULL);
            }
        }
        
    }
    
    long int end_time_sec;
    long int end_time_nsec;

    clock_gettime(CLOCK_MONOTONIC,&end);
    end_time_nsec = end.tv_nsec;
    end_time_sec = end.tv_sec;

    diff1 = (end_time_sec - start_p1_sec) + (end_time_nsec - start_p1_nsec)/BILLION;
    diff2= (end_time_sec - start_p2_sec) + (end_time_nsec - start_p2_nsec)/BILLION;
    diff3 = (end_time_sec - start_p3_sec) + (end_time_nsec - start_p3_nsec)/BILLION;

    printf("Time for fork 1 : %ld\n",diff1);
    printf("Time for fork 2 : %ld\n",diff2);
    printf("Time for fork 3 : %ld\n",diff3);

}