	#include<stdio.h>
	int page[20];	
	int frame[20];
	int n , p;		// no. of frames , no. of pages
	int i , j , x , already_present , page_fault=0 , current_frame;
	int victim_list[20][2];		// [page] , [most_recent_position]
	 void  initializeFrames()
	  {
	  	for(j=0 ; j<20 ; j++)
		 {
		 	frame[j] = -1;
		 }
	  }
	 int search()
	  {
	  	already_present = 0;
		for(j=0 ; j<n ; j++)
		 {
		 	if(frame[j] == page[i])
			 {
			 	already_present = 1;
				break;
			 }
		 }
		return (already_present); 
	  }
	 void disp()
	  {
	  	if(already_present == 0)
			printf("\n ?? Page Request : %2d \t", page[i]);
		else
		 	printf("\n    Page Request : %2d \t", page[i]);
		for(j=0;j<n;j++)
		 {
		 	if(frame[j] == -1)
				printf(" |      *** \t");
			else
				printf(" |      %2d \t",frame[j]);			
		 }
		printf("\n-------------------------------------------------------------------");
	  }
	 int LRU()
	  {
		int t , max = 0 , index = -1;
		for(j=0; j<n; j++)
		 {
			victim_list[j][0] = frame[j];
		 }
		for(j=0;j<n;j++)	// currently allocated frames
		 {
		 	for(t=0; t<i; t++)	// 'i' is no. of page requests till now
			 {
				if(page[t] == victim_list[j][0])
			{	
					victim_list[j][1] = t;	// t is its last pos.
				}
			 }
		 }
		 // Now , out of these , page with largest distance from the current pos. is the victim
		 for(j=0;j<n;j++)
		  {
		  	if((i - victim_list[j][1]) > max)
			 {
			 	max = i - victim_list[j][1];
				index = j;
			 }
		  }  
		 return index; 
	  }
	 int main()
	  {
		system("clear");
		initializeFrames();
		printf("\n How many frames ? : ");
		scanf("%d",&n);
		printf("\n How many pages ? : ");
		scanf("%d",&p);
		printf("\n Enter the one by one : ");
		for(i=0; i<p; i++)
		 {
		 	printf("\n Page[%d]  :  ",i+1);
			scanf("%d",&page[i]);
		 } 
		printf("\n\n Frames  \t -->   ");
		for(i=0 ; i<n ; i++)
		 	printf("  |      %2d     ",i+1);
		printf("\n---------------------------------------------------------------------");
			/*  First n frames in FIFO manner */
		x = 0;
		for(i=0 ; i<p ; i++)
			 {
			if(search() == 1)
		 {		 	// OK , already present
			 }
			else
			 {
				page_fault++;
				current_frame = x++;
				frame[current_frame] = page[i];	
				if(x>n)
				 {
				 	 page_fault-- ;
					 break;
				 }
			 }
			disp();
		 }
		 	/* Actual LRU */
		 for(; i<p; i++)
		  {
		  	if(search() == 1)
			 {		//OK , already present
			 }
			else
			 {
				page_fault++;
				current_frame = LRU();
				frame[current_frame] = page[i];
			 }	 
			disp();   
		  }
		 printf("\n\n\t Total no. of Page Faults : %d \t\t(?? = Page Fault)\n\n",page_fault);
	}