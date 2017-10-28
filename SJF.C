/*Implementation of Shortest JOB First Alorithm for Process Scheduling*/

#include<stdio.h>
//#include<conio.h>
#include<stdlib.h>

int main()
{
	int *p,*at,*et,*wt,*tt,n,i,j,temp;
	float totalwt=0,totaltt=0;

	//clrscr();
	system("clear");
	
	printf("========Process Scheduling Algorithm: SJF=======\n");

	printf("\nEnter number of process: ");
	scanf("%d",&n);

	p=(int *)malloc(n*sizeof(int));
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
		
		p[i]=i;
	}
	
	//Execution time shorting, arrival time shorting and process indexing
	temp=0;
	for(i=0;i<n;i++)
	{
		for(j=1;j<n-i-1;j++)
		{
			if(et[j]>et[j+1])
			{
				temp=et[j];
				et[j]=et[j+1];
				et[j+1]=temp;

				temp=at[j];
				at[j]=at[j+1];
				at[j+1]=temp;
				
				temp=p[j];
				p[j]=p[j+1];
				p[j+1]=temp;
			}
		}
	}
	
	//Waiting time calculation
	temp=0;
	wt[0]=0;
	for(i=1;i<=n;i++)
	{
		temp+=et[i-1];
		wt[i]=temp-at[i];
		totalwt+=wt[i-1];
	}
	
	//Turn arround time calculation
	for(i=0;i<n;i++)
	{
		tt[i]=et[i]+wt[i];
		totaltt+=tt[i];
	}
	
	printf("\n===================================\n");
	printf("Process scheduling table:\n");
	printf("-----------------------------------\n");
	printf(" PS\tAT\tET\tWT\tTT\n");
	printf("-----------------------------------\n");
	for(i=0;i<n;i++)
	{
		printf("P%2d\t%2d\t%2d\t%2d\t%2d\n",p[i],at[i],et[i],wt[i],tt[i]);
	}
	printf("===================================\n");
	printf("Results:\n");
	printf("Avg Waiting Time: %.2f\n",totalwt/n);
	printf("Avg Turn Arround Time: %.2f\n\n",totaltt/n);
	
	free(p);
	free(at);
	free(et);
	free(wt);
	free(tt);

	//getch();
	return 0;
}
