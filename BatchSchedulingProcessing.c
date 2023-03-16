#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

// declare global variables including a table structure to hold scheduling information
struct node {
    int id; 
    int arrival;
    int total_cpu;
    int total_remaining;
    int done;
    int start_time;
    int already_started;
    int end_time;
    int turnaround_time;
} *table_ptr = NULL;
typedef struct node table_type;

// Number of processes from user
int num_proc;

// optional: define a function that finds the maximum of two integers
#define max(a,b) (a > b ? a : b)

//***************************************************************
void print_contents() {
// declare local variables
// print table header
    printf("ID\tArrival\tTotal\tStart\tEnd\tTurnaround\n");
    printf("--------------------------------------------------\n");
// for each process
    for(int i = 0; i < num_proc; i++) {
        // print the contents (id, arrival time, total_cycles) of each field of the table's index
        printf("p%d\t%d\t%d\t", table_ptr[i].id, table_ptr[i].arrival, table_ptr[i].total_cpu);
        // if process has been scheduled ("done" field is 1, print other contents (start time, end time, turnaround time)
        if(table_ptr[i].done == 1) {
            printf("%d\t%d\t%d", table_ptr[i].start_time, table_ptr[i].end_time, table_ptr[i].turnaround_time);
        }
        printf("\n");
    }

return;
}

//*************************************************************
void enter_parameters() {
    // prompt for total number of processes
    printf("How many processes: ");
    scanf("%d", &num_proc);
    // allocate memory for table to hold process parameters
    table_ptr = (table_type* )calloc(num_proc, sizeof(table_type));
    // for each process
    for(int i = 0; i < num_proc; i++) {
        // prompt for arrival time, and total cycle time
        table_ptr[i].id = i;
        printf("Enter arrival cycle for process p%d: ", i);
        scanf("%d",&table_ptr[i].arrival);
        printf("Enter total cycles for process p%d ", i);
        scanf("%d",&table_ptr[i].total_cpu);
    }

    // print contents of table
    print_contents();
    return;
}

//*************************************************************
void fifo_scheduling() {
    // declare (and initialize when appropriate) local variables
    int numOfFinProc = 0;
    int earliestArrival;
    int earliestIndex;
    int currCycle = 0;
    // for each process, reset "done" field to 0
    for( int i = 0; i < num_proc; i++) {
        table_ptr[i].done = 0;
    }
    // while there are still processes to schedule
    while (numOfFinProc < num_proc) {
        // initialize the earliest arrival time to INT_MAX (the largest integer value)
        earliestArrival = INT_MAX;
        // for each process not yet scheduled
        for (int i = 0; i < num_proc; i++){
            if (table_ptr[i].done == 0) {
                // check if process has earlier arrival time than current earliest and update
                if(table_ptr[i].arrival < earliestArrival){
                    earliestArrival = table_ptr[i].arrival;
                    earliestIndex = i;
                } //if
            } //if
        }//for
        // set start time, end time, turnaround time, done fields for unscheduled process with the earliest arrival time
        table_ptr[earliestIndex].start_time = max(table_ptr[earliestIndex].arrival, currCycle);
        table_ptr[earliestIndex].end_time = table_ptr[earliestIndex].start_time + table_ptr[earliestIndex].total_cpu;
        table_ptr[earliestIndex].turnaround_time = table_ptr[earliestIndex].end_time - table_ptr[earliestIndex].arrival;

        // update current cycle time and increment number of processes scheduled
        currCycle = table_ptr[earliestIndex].end_time;
        table_ptr[earliestIndex].done = 1;
        numOfFinProc++;
    }// while

    // print contents of table
    print_contents();
    return;
}

//*************************************************************
void sjf_scheduling() {
    int num_in_proc = 0;
    int lowestIndex;
    int lowest_total_cycle_time;
    int curr_cycle = 0;
    int one_shot; //at least one process is ready

    // for each process, reset "done" field to 0
    for( int i = 0; i < num_proc; i++) {
        table_ptr[i].done = 0;
    }

    // while there are still processes to schedule
    while (num_in_proc < num_proc) {
        // initialize the lowest total cycle time to INT_MAX (the largest integer value)
        lowest_total_cycle_time = INT_MAX;
        one_shot = 0;
        // for each process not yet scheduled
        for (int i = 0; i < num_proc; i++) {
            if (table_ptr[i].done == 0) {
                // check if process has lower total cycle time than current lowest and has arrival time less than current cycle time and update
                if ((table_ptr[i].total_cpu < lowest_total_cycle_time) && (table_ptr[i].arrival <= curr_cycle)) {
                    one_shot = 1;
                    lowest_total_cycle_time = table_ptr[i].total_cpu;
                    lowestIndex = i;
                }//if
            }//if

        }//for

        if (one_shot == 0) {
            curr_cycle++;
        }
        else {
            // set start time, end time, turnaround time, done fields for unscheduled process with lowest (and available) total cycle time
            table_ptr[lowestIndex].start_time = max(table_ptr[lowestIndex].arrival, curr_cycle);
            table_ptr[lowestIndex].end_time = table_ptr[lowestIndex].start_time + table_ptr[lowestIndex].total_cpu;
            table_ptr[lowestIndex].turnaround_time = table_ptr[lowestIndex].end_time - table_ptr[lowestIndex].arrival;

            // update current cycle time and increment number of processes scheduled
            curr_cycle = table_ptr[lowestIndex].end_time;
            table_ptr[lowestIndex].done = 1;
            num_in_proc++;
        }
    }//while

    // print contents of table
    print_contents();
    return;
}

//*************************************************************
void srt_scheduling() {
    // declare (and initialize when appropriate) local variables
    int numOfFinProc = 0;
    int lowestIndex;
    int lowestRemaining;
    int currCycle = 0;
    int one_shot; //at least one process is ready

    // for each process, reset "done", "totalRemaining" and "alreadyStarted" fields to 0
    for( int i = 0; i < num_proc; i++) {
        table_ptr[i].done = 0;
        table_ptr[i].already_started = 0;
        table_ptr[i].total_remaining = table_ptr[i].total_cpu;
    }

    // while there are still processes to schedule
    while (numOfFinProc < num_proc) {
        // initialize the lowest total remaining time to INT_MAX (the largest integer value)
        lowestRemaining = INT_MAX;
        one_shot = 0;
        // for each process not yet scheduled
        for (int i = 0; i < num_proc; i++) {
            // check if process already partially-scheduled
            if (table_ptr[i].done == 0) {
                // check if process has lower total remaining time than current lowest and has arrival time less than current cycle time and update
                if ((table_ptr[i].total_remaining < lowestRemaining) && (table_ptr[i].arrival <= currCycle)) {
                    one_shot = 1;
                    lowestRemaining = table_ptr[i].total_remaining;
                    lowestIndex = i;
                }//if
            }//if

        }//for

        if (one_shot == 0) {
            currCycle++;
        }
        else {
            // if so, set "start time", "alreadyStarted" fields of process with lowest (and available) total remaining cycle time
            if (table_ptr[lowestIndex].already_started == 0) {
                table_ptr[lowestIndex].start_time = max(table_ptr[lowestIndex].arrival, currCycle);
                table_ptr[lowestIndex].already_started = 1;
            }

            // set end time, turnaround time of process with lowest (and available) total remaining cycle time
            table_ptr[lowestIndex].end_time = currCycle + 1;
            table_ptr[lowestIndex].turnaround_time = table_ptr[lowestIndex].end_time - table_ptr[lowestIndex].arrival;
            // decrement total remaining time of process with lowest (and available) total remaining cycle time
            table_ptr[lowestIndex].total_remaining--;

            // update current cycle time and increment number of processes scheduled
            currCycle++;

            // if remaining time is 0, set done field to 1, increment cycle time and number of scheduled processes
            if (table_ptr[lowestIndex].total_remaining == 0) {
                table_ptr[lowestIndex].done = 1;
                numOfFinProc++;
            }//if
        }//else
    }//while

    // print contents of table
    print_contents();
}

//*************************************************************
void quit() {
    // free the schedule table if not NULL
    printf("\nQuitting program...");
    if (table_ptr != NULL) {
        free(table_ptr);
    }
    table_ptr = NULL;
return;
}

//*************************************************************
int main() {
      // declare local vars
    int select = 0;
    while (select != 5){ // while loop{
        // print menu of options
        printf("\nBatch Scheduling\n");
        printf("--------------------------------\n");
        printf("1) Enter parameters\n");
        printf("2) Schedule processes with FIFO algorithm.\n");
        printf("3) Schedule processes with SJF algorithm.\n");
        printf("4) Schedule processes with SRT algorithm.\n");
        printf("5) Quit and free memory.\n");
        // prompts for menu selection
        printf("Enter a selection: ");
        scanf("%d", &select);
        // call appropriate procedure based on choice--use switch statement or series of if, else if, else statements
        switch (select) {
            case 1:
                printf("\nEnter selection: %d", select);
                enter_parameters();break;
            case 2:
                printf("\nEnter selection: %d", select);
                fifo_scheduling();break;
            case 3:
                printf("\nEnter selection: %d", select);
                sjf_scheduling();break;
            case 4:
                printf("\nEnter selection: %d", select);
                srt_scheduling();break;
            case 5:
                printf("\nEnter selection: %d", select);
                quit();break;
            default:
                printf("Invalid Input. ");
        }
    } 
    return 1; // indicates success
} // end of procedure
