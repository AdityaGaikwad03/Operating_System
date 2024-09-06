/*Set A
Write the program to simulate FCFS CPU-scheduling. The arrival time and first CPU burst for different n
number of processes should be input to the algorithm. Assume that the fixed I0 waiting time (2 units).
The next CPU-burst should be generated randomly.The output should give Gantt chart, turnaround time
and waiting time for each process.Also find the average waiting time and turnaround time.*/

#include<stdio.h>
#include<string.h>
#include<math.h>
struct job
{
    char name[20];
    int at,bt,ct,tat,wt,st,tbt;
}
job[10];
int n,i,j;
float avg_tat=0;
float avg_wt=0;
void take_input()
{
    printf("Enter the no of jobs : ");
    scanf("%d",&n);
    for(i=0;i<n;i++)
    {
        printf("Enter the arrival time of the job",i);
        scanf("%d",&job[i].at);
        printf("Enter the bust time of the job",i);
        scanf("%d",&job[i].bt);
        printf("Enter the name of the job",i);
        scanf("%s",&job[i].name);
        job[i].tbt=job[i].bt;
        printf("\n\n");
    }
}
 // to sort the processes by arriaval time
void sort()
{
    struct job temp;
    for(i=0;i<n;i++)
    {
        for(j=i+1;j<n;j++)
        {
            if(job[i].at>job[j].at)
            {
                temp=job[i];
                job[i]=job[j];
                job[j]=temp;
            }
        }
    }
}
// to calculate the tat n wt
void process()
{
    int time=job[0].at;
    for(j=0;j<n;j++)
    {
        job[j].st=time;
        printf("| %d %s ",job[j].st,job[j].name);
        time=time+job[j].tbt;
        job[j].ct = time;
        job[j].tat=time-job[j].at;
        job[j].wt=job[j].tat-job[j].tbt;
        printf("%d |",time);
    }
}
//to print the output table
void print_output()
{
    printf("\n\n");
    printf("\n---------------------------------------");
    printf("\n PName AT BT TAT WT ");
    printf("\n---------------------------------------");
    for(i=0;i<n;i++)
    {
        printf("\n%s %d %d %d %d",job[i].name,job[i].at,job[i].bt,job[i].tat,job[i].wt);
        avg_tat=avg_tat+(float)(job[i].tat);
        avg_wt=(float)avg_wt+(float)(job[i].wt);
    }
    printf("\n-----------------------------------------");
    printf("\nTheavg of the Turn Around Time is %f",avg_tat/n);
    printf("\nTheavg of the Waiting Time is %f",avg_wt/n);
}
int main()
{
    int i;
    take_input();
    sort();
    process();
    print_output();
    printf("\n\n");
    for(i=0;i<n;i++)
    {
        //job[i].tbt=job[i].bt=rand()%10+1;
        job[i].at=job[i].ct+2;
    }
    process();
    print_output();
}