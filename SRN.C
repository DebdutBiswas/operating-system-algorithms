/*Implementation of Shortest Remaining Next Alorithm for Process Scheduling*/

#include<stdio.h>
//#include<conio.h>
#include<stdlib.h>

int main()
{
	int i,j,n,time,smallest,remain;
	int at[10],et[10],priority[10];
	float totalwt=0,totaltt=0;
	
	//clrscr();
	system("clear");
	
	printf("======Process Scheduling Algorithm: SRN/SRTF======\n");

	printf("\nEnter number of process: ");
	scanf("%d",&n);
	
	remain=n;
	
	for(i=0;i<n;i++)
	{
		printf("\nEnter AT of Process %d: ",i);
		scanf("%d",&at[i]);
		printf("Enter ET of Process %d: ",i);
		scanf("%d",&et[i]);
		printf("Enter Priority of Process %d: ",i);
		scanf("%d",&priority[i]);
	}
	
	priority[9]=11;
	
	printf("\n=========================\n");
	printf("Process scheduling table:\n");
	printf("---------------------------\n");
	printf(" PS\tWT\tTT\n");
	printf("---------------------------\n");
	for(time=0;remain!=0;)
	{
		smallest=9;
		for(i=0;i<n;i++)
		{
			if(at[i]<=time && priority[i]<priority[smallest] && et[i]>0)
			{
				smallest=i;
			}
		}
		time+=et[smallest];
		remain--;
		printf("P%2d\t%2d\t%2d\n",smallest+1,time-at[smallest],time-at[smallest]-et[smallest]);
		totalwt+=time-at[smallest]-et[smallest];
		totaltt+=time-at[smallest];
		et[smallest]=0;
	}
  
	printf("===========================\n");
	printf("Results:\n");
	printf("Avg Waiting Time: %.2f\n",totalwt/n);
	printf("Avg Turn Arround Time: %.2f\n\n",totaltt/n);
	
	//getch();
	return 0;
}