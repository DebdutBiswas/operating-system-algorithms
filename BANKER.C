/*Implementation of Banker's Alorithm for DeadLock Prevention*/

#include<stdio.h>
//#include<conio.h>
#include<stdlib.h>

int m,n,**max,**alloc,**need,*totalres,*avlres,*totalavlres,*count,*recheck_count,i,j,k,temp,loopcount,recheck_loopcount,pc,*safesequence;
int input(),calculate(),output(),clean();

int input()
{		
	printf("\nEnter number of processes: ");
	scanf("%d",&m);

	printf("Enter number of resources of each process: ");
	scanf("%d",&n);

	max=(int **)malloc(m*sizeof(int *));
	alloc=(int **)malloc(m*sizeof(int *));
	need=(int **)malloc(m*sizeof(int *));
	totalres=(int *)malloc(m*sizeof(int));
	avlres=(int *)malloc(m*sizeof(int));
	totalavlres=(int *)malloc(m*sizeof(int));
	count=(int *)malloc(m*sizeof(int));
	safesequence=(int *)malloc(m*sizeof(int));

	for(i=0;i<m;i++)
	{
		max[i]=(int *)malloc(n*sizeof(int));
		alloc[i]=(int *)malloc(n*sizeof(int));
		need[i]=(int *)malloc(n*sizeof(int));		
	}
	
	printf("\nEnter the Max Matrix:\n");
	for(i=0;i<m;i++)
	{
		for(j=0;j<n;j++)
		{
			scanf("%d",&max[i][j]);
		}
	}
	
	printf("\nEnter the Alloc Matrix:\n");
	for(i=0;i<m;i++)
	{
		for(j=0;j<n;j++)
		{
			scanf("%d",&alloc[i][j]);
		}
	}

	printf("\nEnter the Total Resources:\n");
	for(i=0;i<n;i++)
	{
		scanf("%d",&totalres[i]);
	}
}

int calculate()
{
	//Needed Resource Calculation
	for(i=0;i<m;i++)
	{
		for(j=0;j<n;j++)
		{
			need[i][j]=max[i][j]-alloc[i][j];
		}
	}

	//Avilable Resource Calculation
	temp=0;
	for(i=0;i<n;i++)
	{
		for(j=0;j<m;j++)
		{
			temp+=alloc[j][i];
		}
		avlres[i]=totalres[i]-temp;
		totalavlres[i]=avlres[i];
		temp=0;
	}

	//Safe Secuence Calculation
	temp=0;
	loopcount=0;
	recheck_loopcount=0;
	pc=0;
Recheck:if(loopcount>0)
	{
		if(recheck_loopcount>0)
		{
			recheck_count=(int *)malloc(loopcount*sizeof(int));
		}

		for(i=0;i<loopcount;i++)
		{
			for(j=0;j<n;j++)
			{
				if(totalavlres[j]>=need[count[i]][j])
				{				
					temp+=0;
				}
				else
				{
					temp+=1;
				}

				if(temp==0)
				{
					totalavlres[j]+=alloc[count[i]][j];
				}

			}
			if(temp==0)
			{
				pc+=1;
				safesequence[(m-loopcount)+i]=count[i];
				//printf("\n P[%d]: Execute \n",count[i]);
			}
			else
			{
				recheck_loopcount+=temp;
				recheck_count[recheck_loopcount-1]=count[i];
				//printf("\n P[%d]: Wait \n",count[i]);
			}
			temp=0;
		}

		if(recheck_loopcount>0)
		{
			loopcount=recheck_loopcount;
			for(i=0;i<loopcount;i++)
			{
				count[i]=recheck_count[i];
			}
			free(recheck_count);
			goto Recheck;
		}

	}
	else
	{
		for(i=0;i<m;i++)
		{
			for(j=0;j<n;j++)
			{
				if(totalavlres[j]>=need[i][j])
				{				
					temp+=0;
				}
				else
				{
					temp+=1;
				}

				if(temp==0)
				{
					totalavlres[j]+=alloc[i][j];
				}
			}
			
			if(temp==0)
			{
				pc+=1;
				safesequence[i-loopcount]=i;
				//printf("\n P[%d]: Execute \n",i);
			}
			else
			{
				loopcount+=temp;
				count[loopcount-1]=i;
				//printf("\n P[%d]: Wait \n",i);
			}
			temp=0;
		}
		if(loopcount>0)
		{
			goto Recheck;
		}
	}
}

int output()
{
	if(pc==m)
	{
		printf("\nResource details table:\n");
		printf("---------------------------------------------------------------------\n");
		printf("  Alloc   |    Max    |   Need    |   Total   |    Avl    |  Final\n");
		printf("---------------------------------------------------------------------\n");
		for(i=0;i<m;i++)
		{
			for(j=0;j<n;j++)
			{
				printf("%2d ",alloc[i][j]);
			}
			printf(" | ");

			for(j=0;j<n;j++)
			{
				printf("%2d ",max[i][j]);
			}
			printf(" | ");

			for(j=0;j<n;j++)
			{
				printf("%2d ",need[i][j]);
			}
			printf(" | ");
			
			if(i==0)
			{
				for(k=0;k<n;k++)
				{
					printf("%2d ",totalres[k]);
				}
				printf(" | ");
				
				for(k=0;k<n;k++)
				{
						printf("%2d ",avlres[k]);
				}
				printf(" | ");

				for(k=0;k<n;k++)
				{
					printf("%2d ",totalavlres[k]);
				}
			}
				printf("\n");
		}
		
		printf("\n=============System State============\n");
		printf("System is in safe state!");
		printf("\nSafe Sequence: ");
		for(i=0;i<m;i++)
		{
			if(i==m-1)
			{
				printf("P%d",safesequence[i]);
			}
			else
			{
				printf("P%d->",safesequence[i]);
			}
		}
	}
	else
	{
		printf("\n=============System State============\n");
		printf("System is in unsafe state!\nDeadlock happened!\n");
		printf("Resource details table not avilable!\n");
	}
	printf("\n\n");
}

int clean()
{
	free(max);
	free(alloc);
	free(need);
	free(totalres);
	free(avlres);
	free(totalavlres);
	free(count);
	free(recheck_count);
	free(safesequence);
}

int main()
{	

	//clrscr();	
	system("clear");

	printf("========DeadLock Prevention Algorithm: BANKER=======\n");
	input();
	calculate();	
	output();
	clean();

	//getch();
	return 0;	
}
