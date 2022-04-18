#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <time.h>
#include <string.h>
#include <fcntl.h>
#include <stdlib.h>

typedef struct _queue
{
    int size;    /* maximum size of the queue */
    int *buffer; /* queue buffer */
    int start;   /* index to the start of the queue */
    int end;     /* index to the end of the queue */
    int count;   /* no. of elements in the queue */
} queue;

queue *queue_init(int n);
int queue_insert(queue *q, int item);
int queue_delete(queue *q);
void queue_display(queue *q);
void queue_destroy(queue *q);

queue *queue_init(int n)
{
    queue *q = (queue *)malloc(sizeof(queue));
    q->size = n;
    q->buffer = malloc(sizeof(int) * n);
    q->start = 0;
    q->end = 0;
    q->count = 0;

    return q;
}

/* insert an item into the queue, update the pointers and count, and
   return the no. of items in the queue (-1 if queue is null or full) */
int queue_insert(queue *q, int item)
{
    if ((q == NULL) || (q->count == q->size))
        return -1;

    q->buffer[q->end % q->size] = item;
    q->end = (q->end + 1) % q->size;
    q->count++;

    return q->count;
}

/* delete an item from the queue, update the pointers and count, and
   return the item deleted (-1 if queue is null or empty) */
int queue_delete(queue *q)
{
    if ((q == NULL) || (q->count == 0))
        return -1;

    int x = q->buffer[q->start];
    q->start = (q->start + 1) % q->size;
    q->count--;

    return x;
}

/* display the contents of the queue data structure */
void queue_display(queue *q)
{
    int i;
    if (q != NULL && q->count != 0)
    {
        printf("queue has %d elements, start = %d, end = %d\n",
               q->count, q->start, q->end);
        printf("queue contents: ");
        for (i = 0; i < q->count; i++)
            printf("%d ", q->buffer[(q->start + i) % q->size]);
        printf("\n");
    }
    else
        printf("queue empty, nothing to display\n");
}

/* delete the queue data structure */
void queue_destroy(queue *q)
{
    free(q->buffer);
    free(q);
}

int main(int argc, char **argv)
{
    pid_t pid;
    char input[1000], *stringSplitter = malloc(100 * sizeof(char)), *inputStr, *command = malloc(1000 * sizeof(char)), *dummy = malloc(1000 * sizeof(char)), processidOut[1000], processidError[1000];
    char *inputSplit[100000], *finalSplit[10000], buf[BUFSIZ];
    char showJobs[1000] = {"jobId\t Comand \t \t \t Status"};
    char submitHistory[1000] = {"jobId\t command \t\t\t starttime\t endtime\t status\t"};

    // char source_dir[1000];
    // getcwd(source_dir, 1000);
    FILE *fp1 = fopen("showStatus.log", "w");
    fprintf(fp1, "%s", showJobs);
    FILE *fp2 = fopen("submitHistory.log", "w");
    fprintf(fp2, "%s", submitHistory);
    int fderr, fdout;
    time_t t1, t2;
    int i = 0, k = 0, maxLen, status, jobid=0;

    if (argc != 2)
    {
        printf("Usage: %s <number of processes>\n", argv[0]);
        return 0;
    }
    // while (argc==2)
    //{
    printf("Enter command> ");
    fgets(input, 1000, stdin);
    input[strlen(input) - 1] = '\0';
    // if (input[0] == '\n')
    //         continue;
    //}
    stringSplitter = strtok(input, " ");
    while (stringSplitter != NULL)
    {
        if (i != 0)
        {
            if (i == 1)
                strcpy(command, stringSplitter);
            finalSplit[k++] = stringSplitter;
            if (i != 1)
            {
                strcat(command, " ");
                strcat(command, stringSplitter);
            }
        }
        inputSplit[i++] = stringSplitter;
        stringSplitter = strtok(NULL, " ");
    }
    inputStr = inputSplit[0];
    // printf("Command: %s\n", command);
    // printf("input: %s\n", input);
    // for (int j = 0; j < i; j++)
    // {
    //     printf("finalSplit[%d] %s\n", j, finalSplit[j]);
    //     printf("inputSplit[%d] %s\n", j, inputSplit[j]);
    // }

    if (strstr(inputStr, "submit"))
    {

        time(&t1);
        pid = fork();
        if (pid == 0)
        {
            jobid++;
            sprintf(processidOut, "%d", jobid);
            sprintf(processidError, "%d", jobid);
            strcat(processidOut, ".out");
            strcat(processidError, ".err");
            if ((fdout = open(processidOut, O_CREAT | O_APPEND | O_WRONLY, 0755)) == -1)
            {
                printf("Error opening file %s for output\n", processidOut);
                exit(-1);
            }
            if ((fderr = open(processidError, O_CREAT | O_APPEND | O_WRONLY, 0755)) == -1)
            {
                printf("Error opening file %s for output\n", processidError);
                exit(-1);
            }
            dup2(fdout, 1);
            dup2(fderr, 2);
            execvp(finalSplit[0], finalSplit);
            perror("exec");
            exit(-1);
        }
        else if (pid > 0)
        {
            wait(&status);
            time(&t2);
        }
        else
        {
            perror("fork");
            exit(EXIT_FAILURE);
        }
    }

    return 0;
}