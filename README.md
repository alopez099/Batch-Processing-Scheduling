# Batch-Processing-Scheduling
To calculate the timing parameters of  batch processes based on different scheduling algorithms. 

## Specification:
The program mimics the execution of different processes under different scheduling algorithms. The simulation maintains a table that reflects the current state of the system, based on choosing from a menu of choices, where each choice calls the appropriate procedure, where the choices are:
1) Enter parameters
2) Schedule processes with FIFO algorithm
3) Schedule processes with SJF algorithm
4) Schedule processes with SRT algorithm
5) Quit program and free memory
## Description

This is a C program that implements two CPU scheduling algorithms: First-In-First-Out (FIFO) and Shortest Job First (SJF). The program asks the user to enter the number of processes to be scheduled and their arrival and CPU burst times. The scheduling algorithms are implemented as separate functions, and the scheduling results are displayed in a table that shows the process ID, arrival time, CPU burst time, start time, end time, and turnaround time.

The program defines a structure called node that holds the scheduling information of each process, including the process ID, arrival time, total CPU time, remaining CPU time, start time, end time, turnaround time, and a flag indicating if the process has been scheduled. The program also defines a global pointer to an array of node structures, called table_ptr, to hold the scheduling information of all the processes. The table_ptr pointer is initialized to NULL.

The program contains three functions: enter_parameters(), fifo_scheduling(), and sjf_scheduling().

The enter_parameters() function prompts the user to enter the number of processes and their arrival and CPU burst times. It then allocates memory for the table_ptr pointer and stores the scheduling information in the node structures. Finally, it calls the print_contents() function to print the scheduling information in a table.

The fifo_scheduling() function implements the FIFO scheduling algorithm. It initializes the done flag of each process to 0, then schedules the processes according to their arrival times in ascending order. For each process, it sets the start time, end time, and turnaround time, updates the done flag, and increments the number of finished processes. Finally, it calls the print_contents() function to print the scheduling results.

The sjf_scheduling() function implements the SJF scheduling algorithm. It initializes the done flag of each process to 0, then schedules the processes according to their CPU burst times in ascending order. For each process, it sets the start time, end time, and turnaround time, updates the done flag, and increments the number of finished processes. The curr_cycle variable keeps track of the current CPU cycle, and the one_shot variable ensures that at least one process is ready to be scheduled. Finally, it calls the print_contents() function to print the scheduling results.


## Running Tests

To run tests, run the following command or simply type in terminal 

```bash
  testcases.text
```


## Usage/Examples

```doc
Sample output
Batch scheduling
----------------
1) Enter parameters
2) Schedule processes with FIFO algorithm
3) Schedule processes with SJF algorithm
4) Schedule processes with SRT algorithm
5) Quit and free memory
Enter selection: 1
Enter total number of processes: 3
Enter arrival cycle for process p0: 0
Enter total cycles for process p0: 6
Enter arrival cycle for process p1: 1
Enter total cycles for process p1: 3
Enter arrival cycle for process p2: 3
Enter total cycles for process p2: 2
ID Arrival Total Start End Turnaround
--------------------------------------------------
p0 0 6
p1 1 3
p2 3 2
Batch scheduling
----------------
1) Enter parameters
2) Schedule processes with FIFO algorithm
3) Schedule processes with SJF algorithm
4) Schedule processes with SRT algorithm
5) Quit and free memory
Enter selection: 2
ID Arrival Total Start End Turnaround
--------------------------------------------------
p0 0 6 0 6 6
p1 1 3 6 9 8
p2 3 2 9 11 8
Batch scheduling
----------------
1) Enter parameters
2) Schedule processes with FIFO algorithm
3) Schedule processes with SJF algorithm
4) Schedule processes with SRT algorithm
5) Quit and free memory
Enter selection: 3
ID Arrival Total Start End Turnaround
--------------------------------------------------
p0 0 6 0 6 6
p1 1 3 8 11 10
p2 3 2 6 8 5
Batch scheduling
----------------
1) Enter parameters
2) Schedule processes with FIFO algorithm
3) Schedule processes with SJF algorithm
4) Schedule processes with SRT algorithm
5) Quit and free memory
Enter selection: 4
ID Arrival Total Start End Turnaround
--------------------------------------------------
p0 0 6 0 11 11
p1 1 3 1 4 3
p2 3 2 4 6 3
Batch scheduling
----------------
1) Enter parameters
2) Schedule processes with FIFO algorithm
3) Schedule processes with SJF algorithm
4) Schedule processes with SRT algorithm
5) Quit and free memory
Enter selection: 5
Quitting program...>
}
```

