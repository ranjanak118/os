#include<stdio.h>
#include<stdlib.h>


typedef struct{
	int id;
	int size;
	int allocated;
} process;

typedef struct{
	int id;
	int size;
	int fragment;
} block;

int main()
{
	int num_blocks,num_process;

	printf("\nPlease enter the number of blocks and processes:");
	scanf("%d %d",&num_blocks,&num_process);

	process proc[num_process];
	block blk[num_blocks];

	int i=0;
	for(i=0;i<num_blocks;i++)
	{
		printf("\nPlease enter the size of block %d:",i+1);
		scanf("%d",&blk[i].size);
		blk[i].id = i;
		blk[i].fragment = blk[i].size;
	}

	for(i=0;i<num_process;i++)
	{
		printf("\nPlease enter the size of process %d:",i+1);
		scanf("%d",&proc[i].size);
		proc[i].id = i;
		proc[i].allocated = -1;
	}

	int j=0;
	i=0;

	for(i=0;i<num_process;i++)
	{
		for(j=0;j<num_blocks;j++)
		{
			if(proc[i].size <= blk[j].fragment){
				proc[i].allocated = j;
				blk[j].fragment-=proc[i].size;
				break;
			}
		}
	}

	printf("Process No.\tProcess Size\tBlock No.");
	for(i=0;i<num_process;i++)
	{
		if(proc[i].allocated == -1)
		{
			printf("\n%d\t\t%d\t\t%s",proc[i].id + 1, proc[i].size, "Non allocated");
			continue;
		}
		printf("\n%d\t\t%d\t\t%d",proc[i].id + 1, proc[i].size, proc[i].allocated + 1);
	}
	printf("\n");

	printf("\nInternal fragments:");
	printf("\nBlock No.\tinternal fragment");
	for(i=0;i<num_blocks;i++)
	{
		printf("\n%d\t\t%d",blk[i].id + 1, blk[i].fragment);
	}
	printf("\n");
	return 0;
}