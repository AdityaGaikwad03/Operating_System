/*Preemptive Shortest Job First (SJF)(Set B)
1) Write the program to simulate Preemptive Shortest Job First (SJF) -scheduling. The arrival
time and first CPU-burst for different n number of processes should be input to the
algorithm Assume the fixed 10 waiting time (2 units). The next CPU-burst should be
generated randomly. The output should give Gantt chart, turnaround time and waiting time
for each process. Also find the average waiting time and turnaround time.*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <limits.h>
#include <time.h>
struct job
{
    char name[20];
    int at,bt,ct,tat,wt,st,tbt;
}
job[10];
int jno,n,i,j;
float avg_tat = 0;
float avg_wt = 0;
int getjob(int time);
void take_input()
{
    printf("\nEnter the number of processes: ");
    scanf("%d",&n);
    for(i=0;i<n;i++)
    {
        printf("enter the process name: ");
        scanf("%s",job[i].name);
        printf("enter arrival time: ");
        scanf("%d",&job[i].at);
        printf("enter burst time: ");
        scanf("%d",&job[i].bt);
        job[i].tbt = job[i].bt;
        printf("\n\n");
    }
}
void process()
{
    int time = 0,cnt = 0;
    char prev_job[10],cur_job[10];
    while(1)
    {
        jno = getjob(time);
        job[jno].tbt--;
        strcpy(cur_job,job[jno].name);
        if(strcmp(cur_job,prev_job)!=0)
            printf("%d| %s\t",time,job[jno].name);
        time++;
        if(job[jno].tbt == 0)
        {
            job[jno].ct = time;
            job[jno].tat = time - job[jno].at;
            job[jno].wt = job[jno].tat - job[jno].bt;
            cnt++; 
        }
        strcpy(prev_job,cur_job);
        if(cnt == n)
            break;
    }
    printf("end time %d",time);
}
int getjob(int time)
{
    int i, min = 999, k;
    for(i = 0; i < n; i++)
        if (job[i].at <= time && job[i].tbt != 0)
        {
            if(min > job[i].tbt)
            {
                min = job[i].tbt;
                k = i;
            }
        }
        return k; 
}
void print_output()
{
    printf("\n\n");
    printf("\n------------------------------------------------");
    printf("\n pname  \t at  \t bt  \t tat  \t wt");
    printf("\n------------------------------------------------");
    for(i = 0; i < n; i++)
    {
        printf("\n %s  \t %d  \t %d  \t %d  \t %d",job[i].name,job[i].at,job[i].bt,job[i].tat,job[i].wt);
        avg_tat = avg_tat + (float)(job[i].tat);
        avg_wt = avg_wt + (float)(job[i].wt);
    }
    printf("\n-----------------------------------------------");
    printf("\n avg wt is %f",avg_wt/n);
    printf("\n avg tat is %f",avg_tat/n);
}
int main()
{
    take_input();
    process();
    print_output();
    for ( i = 0; i < n; i++)
    {
        job[i].tbt = job[i].bt = rand()%10+1;
        job[i].at = job[i].ct + 2;
    }
    process();
    print_output();
}