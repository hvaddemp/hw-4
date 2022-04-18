

## Description

Homework four focuses on developing a simple job scheduler for non-interactive tasks that run in the background and do not need user interaction.

Each program is implemented in a specific number at a time, with the rest held in reserve until the pre-programme is completeBecause these jobs are non-interactive, their errors and output are printed into files with their associated job ids as names.This procedure reads keywords, command-line arguments, job schedulers, background processing, pids, threads, queues, and C language.




$ make
    You'll get an output with a filename of jobq


Execute the command lines as follows:

    $./jobq <integer input>
       Here, integer input> is the number of concurrent programs you want to run, with a maximum of eight.

    The program will now go to the scheduler with the specified settings, and the appropriate applications will be run using the commands below.

    Enter Command> submit <command argument> <input> (input if necessary)
    Enter Command> showjobs
    Enter Command> submithistory

Use 'CNTL+c' or 'CNTL+' to terminate the pprogram if necessary.

### Sample Tests

Samples of the program on the provided commands
Enter command> submit ./sleep 50
job 1 added to the queue
Enter command> submit ./sleep 50
job 2 added to the queue
Enter command> submit ./sleep 15
job 3 added to the queue
Enter command> submit ./sleep 45
job 4 added to the queue
Enter command> showjobs
jobid   command         status
1       ./sleep 50      working
2       ./sleep 50      working
3       ./sleep 15      waiting
4       ./sleep 45      waiting
Enter command> showjobs
jobid   command         status
1       ./sleep 50      working
2       ./sleep 50      working
3       ./sleep 15      waiting
4       ./sleep 45      waiting
Enter command> showjobs
jobid   command         status
2       ./sleep 50      working
3       ./sleep 15      working
4       ./sleep 45      waiting
Enter command> showjobs
jobid   command         status
3       ./sleep 15      working
4       ./sleep 45      working
Enter command> showjobs
jobid   command         status
4       ./sleep 45      working
Enter command> submithistory
jobid   command         starttime                       endtime                         status
1       ./sleep 50      Sat Apr 17 13:17:22 2022        Sat Apr 17 13:19:12 2022        success
2       ./sleep 50      Sat Apr 17 13:17:29 2022        Sat Apr 17 13:19:19 2022        success
3       ./sleep 15      Sat Apr 17 13:19:13 2022        Sat Apr 17 13:19:28 2022        success
Enter command> submithistory
jobid   command         starttime                       endtime                         status
1       ./sleep 50      Sat Apr 17 13:17:22 2022        Sat Apr 17 13:19:12 2022        success
2       ./sleep 50      Sat Apr 17 13:17:29 2022        Sat Apr 17 13:19:19 2022        success
3       ./sleep 15      Sat Apr 17 13:19:13 2022        Sat Apr 17 13:19:28 2022        success
4       ./sleep 45      Sat Apr 17 13:19:19 2022        Sat Apr 17 13:20:04 2022        success
Enter command>
