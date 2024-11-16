/******************************************************************************************************************
* @file pinfo.c
* @brief System Calls 
*
* Course: CPE2600
* Section: 111
* Assignment: CPE Lab 9
* Author: Reagan Burkemper
*
* Description: The program uses clock_gettime, uname, gethostname, get_nprocs,
*              sysconf, and getpagesize to print out the following:
*   
*
* Date: 11/13/2024
*
* Compile Instructions: 
*   To compile the pinfo.c, run:
*   - compile with: 
*       - make clean
*       - make
*   - run: ./pinfo
*
* NOTE: to see pmod's priority with pinfo: 
*   run pmod in the background
*       - run: ./pmod &
*   run pinfo with the PID as an argument
*       - run: ./pinfo <PID>
*   
*****************************************************************************************************************/
#define _GNU_SOURCE
#include <stdio.h>
#include <sched.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/resource.h>
#include <sys/syscall.h>
#include <sys/time.h>
#include <sys/resource.h>
#include <errno.h>

void printsched(int policy) {
    switch (policy) 
    {
        case SCHED_OTHER:
            printf("SCHED_OTHER\n");
            break;
        case SCHED_FIFO:
            printf("SCHED_FIFO\n");
            break;
        case SCHED_RR:
            printf("SCHED_RR\n");
            break;
        case SCHED_BATCH:
            printf("SCHED_BATCH\n");
            break;
        case SCHED_IDLE:
            printf("SCHED_IDLE\n");
            break;
        case SCHED_DEADLINE:
            printf("SCHED_DEADLINE\n");
            break;
        default:
            printf("unable to find\n");
    }
}

int main(int argc, char *argv[]) {
    pid_t pid;
    if (argc > 1) 
    {
        pid = atoi(argv[1]);
    } 
    else 
    {
        pid = getpid(); // default to current process 
    }

    // get the process priority
    int priority_process = getpriority(PRIO_PROCESS, pid);
    if (priority_process == -1 && errno != 0) 
    {
        perror("getpriority");
        return 1;
    }
    else 
    {
        printf("Process priority: %d\n", priority_process);
    }
    // get the scheduling method
    int scheduling_method = sched_getscheduler(pid);
    if (scheduling_method == -1) 
    {
        perror("sched_getscheduler");
        return 1;
    } 
    else 
    {
        printf("Scheduling method: ");
        printsched(scheduling_method);
    }
    printsched(scheduling_method);

    // get the CPU
    int cpu;
    if (syscall(SYS_getcpu, &cpu, NULL, NULL) == -1) 
    {
        perror("getcpu");
        return 1;
    }
    printf("CPU: %d\n", cpu);

    // get resource usage
    struct rusage usage;
    if (getrusage(RUSAGE_SELF, &usage) == -1) {
        perror("getrusage");
        return 1;
    }
    printf("User CPU time used: %ld.%06ld seconds\n", usage.ru_utime.tv_sec, usage.ru_utime.tv_usec);
    printf("System CPU time used: %ld.%06ld seconds\n", usage.ru_stime.tv_sec, usage.ru_stime.tv_usec);

    // get resource limits
    struct rlimit limit;
    if (getrlimit(RLIMIT_NOFILE, &limit) == -1) {
        perror("getrlimit");
        return 1;
    }
    printf("Limited to %ld of open files\n", limit.rlim_cur);

    return 0;
}





