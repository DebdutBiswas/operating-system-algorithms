/*Implementation of First Come First Serve Alorithm for Process Scheduling*/

#include<stdio.h>
//#include<conio.h>
#include<stdlib.h>

int main()
{
	int *at,*et,*wt,*tt,n,i,temp;
	float totalwt=0,totaltt=0;

	//clrscr();
	system("clear");
	
	printf("========Process Scheduling Algorithm: FCFS=======\n");

	printf("\nEnter number of process: ");
	scanf("%d",&n);

	at=(int *)malloc(n*sizeof(int));
	et=(int *)malloc(n*sizeof(int));
	wt=(int *)malloc(n*sizeof(int));
	tt=(int *)malloc(n*sizeof(int));

	for(i=0;i<n;i++)
	{
		printf("\nEnter AT of Process %d: ",i);
		scanf("%d",&at[i]);
		printf("Enter ET of Process %d: ",i);
		scanf("%d",&et[i]);
	}
	
	temp=0;
	wt[0]=0;
	for(i=0;i<n;i++)
	{
		//Waiting time calculation
		temp+=et[i];
		wt[i+1]=temp-at[i+1];//actually temp-0;
		totalwt+=wt[i];
		
		//Turn arround time calculation
		tt[i]=et[i]+wt[i];
		totaltt+=tt[i];
	}
	
	printf("\n==================================\n");
	printf("Process scheduling table:\n");
	printf("-----------------------------------\n");
	printf(" PS\tAT\tET\tWT\tTT\n");
	printf("-----------------------------------\n");
	for(i=0;i<n;i++)
	{
		printf("P%2d\t%2d\t%2d\t%2d\t%2d\n",i,at[i],et[i],wt[i],tt[i]);
	}
	printf("===================================\n");
	printf("Results:\n");
	printf("Avg Waiting Time: %.2f\n",totalwt/n);
	printf("Avg Turn Arround Time: %.2f\n\n",totaltt/n);
	
	free(et);
	free(wt);
	free(tt);

	//getch();
	return 0;
}
