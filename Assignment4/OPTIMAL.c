#include<stdio.h>
#include<stdlib.h>

typedef struct queue
{
	int data;
	struct queue *next;
}Node;

Node *start=NULL,*last=NULL,*ptr;
int pgfault=0,n,nof;
int a[80];
int n1,i,k,min=0;
main()
{
	
	printf("\nHow many Frames\t");
	scanf("%d",&n);

	printf("\n\nEnter the no of page\t");
	scanf("%d",&n1);

	for(i=0;i<n1;i++)
	{
		printf("\n\nEnter the Pade no %d\t",i);
		scanf("%d",&a[i]);
	}
	for(i=0;i<n1;i++)
	{
		if(search(a[i])==0)
		{

			addlist(a[i]);
			pgfault++;
			printf("\nPage fault Occurs");
			print();
		}
		printf("\n");
		print();
	}
	printf("\n No of page Fault=%d",pgfault);
}

int search(int page)
{
     for(ptr=start;ptr!=NULL;ptr=ptr->next)
          {
            if(page==ptr->data)
		return 1;

		}
	return 0;
}



void print()
{
	Node *ptr;
	for(ptr=start;ptr!=NULL;ptr=ptr->next)
		printf("%d\t",ptr->data);
	printf("\n\n");
}

void addlist(int page)
{
	Node *ptr=NULL,*temp,*ptr1,*prev;
        int cnt1=1;
	static int cnt=0;
        int j;
	ptr=(Node *)malloc(sizeof(Node));
	ptr->data=page;
	ptr->next=NULL;
	if(start==NULL)
	{

		start=last=ptr;
		cnt++;
	}
	else if(cnt<n)
	{

		last->next=ptr;
		last=ptr;
		last->next=NULL;
		cnt++;
	}
	else
	{
          for(temp=start;temp!=NULL;prev=temp,temp=temp->next)
          {
              
             for(j=i+1;j<n1;j++)
             {
                if(a[j]==temp->data)
                {
                  k=j;
                  
                }
              }
             if(min<=k)
             {
                min=k;
                ptr1=temp;
             }

           }
           if(ptr1==start)
           {
            start= start->next;
            last->next=ptr;
            last = ptr;
           }
           else if(ptr1==last)
          {
            last->data=ptr->data;
          }
          else
         {
              prev->next=ptr1->next;
              ptr1->next=NULL;              
              last->next=ptr;
              last=ptr;
           }         


	}
}
