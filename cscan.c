/*
	Disk Scheduling
	Scan
*/
#include "stdio.h"
#include "stdlib.h"
#include "stdbool.h"
#include "limits.h"

struct request
{
	int request_track_number;
	bool visited;
};

int main()
{
	int n, limit, choice, init_head;
	printf("\nPlease enter the number of requests:");
	scanf("%d",&n);

	printf("\nEnter the requests:");
	struct request req[n+1];
	int i=0,j=0;
	for(i=0;i<n;i++)
	{
		scanf("%d",&req[i].request_track_number);
		req[i].visited = false;
	}

	printf("\nEnter the limit of the disk:");
	scanf("%d",&limit);

	printf("\nPlease enter the initial head position:");
	scanf("%d",&init_head);

	req[n].request_track_number = init_head;
	for(i=0;i<n;i++)
	{
		for(j=0;j<n-i;j++)
		{
			if(req[j].request_track_number > req[j+1].request_track_number)
			{
				struct request temp;
				temp = req[j];
				req[j] = req[j+1];
				req[j+1] = temp;
			}
		}
	}

	int index;
	for(i=0;i<n+1;i++)
	{
		if(req[i].request_track_number == init_head)
		{
			index = i;
			break;
		}
	}

	choice = (limit-init_head <= init_head) ? 2 : 1;

	int seek_time = 0;
	if(choice==1)
	{
		seek_time+=(init_head);
		seek_time+=(limit-req[index+1].request_track_number);

		printf("\n");
		for(i=index;i>=0;i--)
		{
			printf("%d --> ",req[i].request_track_number);
		}
		for(i=n;i>index;i--)
		{
			printf("%d --> ",req[i].request_track_number);	
		}
		printf("\nThe total seek time is:%d\n",seek_time);

	}
	else if(choice==2)
	{
		int min_req = INT_MAX;
		for(i=0;i<n+1;i++)
		{
			if(req[i].request_track_number < min_req)
			{
				min_req = req[i].request_track_number;
			}
		}

		seek_time+=(limit-init_head);
		seek_time+=(req[index-1].request_track_number);

		printf("\n");
		for(i=index;i<n+1;i++)
		{
			printf("%d --> ",req[i].request_track_number);	
		}
		for(i=0;i<index;i++)
		{
			printf("%d --> ",req[i].request_track_number);
		}
		printf("\nThe total seek time is:%d\n",seek_time);

	}
	else{
		printf("\nInvalid choice");
		return 0;
	}

}