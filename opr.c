#include<stdio.h>
#include<stdlib.h>
#include<limits.h>

typedef struct{
	int id;
	int time;
} frame;

int main()
{
	int i=0,j=0,k=0;
	int total_pages;
	printf("\nPlease Enter the number of processes:");
	scanf("%d",&total_pages);

	int pages[total_pages];

	for(i=0;i<total_pages;i++)
	{
		scanf("%d",&pages[i]);
	}

	int total_frames;
	printf("\nPlease enter the number of frames:");
	scanf("%d",&total_frames);

	frame frames[total_frames];
	for(i=0;i<total_frames;i++)
	{
		frames[i].id = -1;
		frames[i].time = -1;
	}

	int hit_count=0;
	int fault_count=0;
	int time=0;
	for(i=0;i<total_pages;i++)
	{
		time++;
		int hit=0;
		for(j=0;j<total_frames;j++)
		{
			if(frames[j].id==pages[i])
			{
				hit = 1;
				break;
			}
		}

		if(hit)
		{
			printf("\nPage %d was found. PAGE HIT",pages[i]);
			hit_count++;
		}
		else if(!hit)
		{
			printf("\nPage %d not found. PAGE FAULT", pages[i]);
			fault_count++;

			int slot_empty = 0;
			int slot_to_fill = -1;
			for(j=0;j<total_frames;j++)
			{
				if(frames[j].id==-1)
					break;
			}
			if(j==total_frames)
				slot_empty = 0;
			else
			{
				slot_empty = 1;
				slot_to_fill = j;
			}

			if(slot_to_fill!=-1)
			{
				frames[slot_to_fill].id = pages[i];
			}
			else
			{
				int index = 0;

				int res = -1;
				int farthest = i+1;
				for(k=0;k<total_frames;k++)
				{
					int l;
					for(l=i+1; l< total_pages;l++)
					{
						if(frames[k].id==pages[l])
						{
							if(l>farthest)
							{
								farthest = l;
								res = k;
							}
							break;
						}
					}

					if(l==total_pages)
					{
						res = k;
						break;
					}
				}

				index = ((res==-1) ? 0 : res);

				frames[index].id = pages[i];
			}
		}

		printf("\n");
		for(j=0;j<total_frames;j++)
			printf("|%d",frames[j].id);
	}

	printf("\nfaults: %d and hits:%d",fault_count, hit_count);
	printf("\n");
}