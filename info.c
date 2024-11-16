/******************************************************************************************************************
* @file info.c
* @brief System Calls 
*
* Course: CPE2600
* Section: 111
* Assignment: CPE Lab 9
* Author: Reagan Burkemper
*
* Description: The program uses clock_gettime, uname, gethostname, get_nprocs,
*              sysconf, and getpagesize to print out the following:
*    • The current time of day - in nanoseconds
*    • The system’s network name
*    • The operating system name
*    • The operating system release and version
*    • The system’s hardware type
*    • The number of CPUs on the system
*    • The total amount of physical memory IN BYTES
*    • The total amount of free memory IN BYTES
*
* Date: 11/13/2024
*
* Compile Instructions: 
*   To compile the info.c, run:
*   - compile with: 
*       - make clean
*       - make
*   - run: ./info
*   
*****************************************************************************************************************/

#include <stdio.h> 
#include <sys/utsname.h> // uname
#include <sys/sysinfo.h> // get_nprocs
#include <unistd.h> // gethostname
#include <limits.h> // gethostname
#include <time.h> // clock_gettime
#include <unistd.h> // sysconf

int main(int argc, char* argv[])
{
    //current time of day:
    struct timespec time;
    if (clock_gettime(CLOCK_REALTIME, &time) == 0) 
    {
        printf("Current time of day: %ld ns\n", time.tv_nsec);
    }
    // systems network name
    char hostname[HOST_NAME_MAX + 1]; 
    if (gethostname(hostname, sizeof(hostname)) == 0 && hostname[0] != '\0')
    {
        printf("Hostname: %s\n", hostname);
    }

    // all statements that use uname
    struct utsname buffer;
    if (uname(&buffer) == 0 && buffer.sysname[0] != '\0' && buffer.release[0] != '\0' 
    && buffer.version[0] != '\0' && buffer.machine[0] != '\0') 
    {
        printf("Operating System:\n");
        printf("    Name: %s\n", buffer.sysname);
        printf("    Release: %s\n", buffer.release);
        printf("    Version: %s\n", buffer.version);
        printf("    Hardware Type: %s\n", buffer.machine);
    }

    // the number of cpus on the system
    int CPUs = get_nprocs();
    if (CPUs > 0) 
    {
        printf("Number of CPUs: %d\n", CPUs);
    }
    // total amount of physical memory in bytes
    long physicalmem = sysconf(_SC_PHYS_PAGES) * sysconf(_SC_PAGESIZE);
    if (physicalmem > 0) 
    {
        printf("Total amount of physical memory: %ld bytes\n", physicalmem);
    }

    // total amount of free memory in bytes
    long freemem = sysconf(_SC_AVPHYS_PAGES) * sysconf(_SC_PAGESIZE);
    if (freemem > 0) 
    {
        printf("Total amount of free memory: %ld bytes\n", freemem);
    }
    return 0;
}