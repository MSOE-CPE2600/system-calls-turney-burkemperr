/******************************************************************************************************************
* @file finfo.c
* @brief System Calls
*
* Course: CPE2600
* Section: 111
* Assignment: CPE Lab 9
* Author: Reagan Burkemper
*
* Description: Modifies its own priority to REDUCE it by 10, specifies the correct number to 
*              REDUCE the priority not increase. Sleeps for 1,837,272,638 nano seconds and 
*              prints a goodbye message and exits
* Date: 11//14/2024
*
* Compile Instructions: 
*   To compile pmod.c, run:
*   - compile with: 
*       - make clean
*       - make
*   - run: ./pmod
*   
*****************************************************************************************************************/


#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>        // atoi and atol
#include <unistd.h>        // sleep and getpid
#include <sys/resource.h>  // nice
#include <time.h>          // nanosleep
#include <errno.h>

int main(int argc, char* argv[]) {
    int priority_adjustment = 10;  // default priority reduction
    long seconds = 1;
    long nanoseconds = 837272638;  // default sleep time: 1.837 seconds
    
    // see if command-line arguments were provided
    if (argc > 1) {
        priority_adjustment = atoi(argv[1]);  // change priority if argument is given
    }
    if (argc > 2) {
        seconds = atol(argv[2]);  // set seconds portion of sleep duration
        nanoseconds = atol(argv[3]);  // set nanoseconds portion of sleep duration
    }

    //Modifies its own priority to REDUCE it by 10 - 
    //NOTE Make sure you specify the correct number to REDUCE the priority not increase.
    int new_priority = nice(priority_adjustment);  // Positive value reduces priority
    if (new_priority == -1 && errno != 0) {
        perror("Error setting priority");
        return 1;
    }
    printf("New priority set to: %d\n", new_priority);

    // Sleep for 1,837,272,638 nano seconds
    struct timespec req;
    req.tv_sec = seconds;
    req.tv_nsec = nanoseconds;
    if (nanosleep(&req, NULL) == -1) {
        perror("Error during nanosleep");
        return 1;
    }

    printf("Goodbye!\n"); // Prints a goodbye message and exits
    return 0;
}