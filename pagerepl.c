#include <stdio.h>
#define MAX 99999

int no_of_pframes, no_of_pageRef, front = 1, page_faults;

int initialize(int page_frame[])
{
    int i;
    for (i = 0; i < no_of_pframes; i++)
        page_frame[i] = -1;
    return 0;
}

int find(int arr[], int ele, int n)
{
    int i;
    for (i = 0; i < n; i++)
    {
        if (arr[i] == ele)
            return 1;
    }
    return -1;
}

int displayPF(int page_frame[])
{
    int i = 0;
    for (i = 0; i < no_of_pframes; i++)
    {
        printf("|%d", page_frame[i]);
    }
    printf("|\n\n");
}
int leftmost_minus1(int a[])
{
    int i = 0, pos = -1;
    for (i = 0; i < no_of_pframes; i++)
    {
        if (a[i] == -1)
        {
            pos = i;
            break;
        }
    }
    return (pos);
}

int fifo(int page_frame[], int pageRef[])
{
    initialize(page_frame);
    page_faults = 0;
    int i, ele;
    for (i = 0; i < no_of_pageRef; i++)
    {
        ele = pageRef[i];
        if (find(page_frame, ele, no_of_pframes) == -1)
        {
            printf(" %d - Miss\n", ele);
            page_faults++;

            page_frame[front - 1] = ele;
            displayPF(page_frame);
            front = front % (no_of_pframes) + 1;
        }
        else
        {
            printf(" %d - Hit\n", ele);
            displayPF(page_frame);
        }
    }
    printf(" Total number of page faults : %d\n", page_faults);
    return 0;
}
int optimal(int page_frame[], int pageRef[])
{
    initialize(page_frame);
    page_faults = 0;
    int i, j, k, ele, found, x;
    int future_used[no_of_pframes];
    for (i = 0; i < no_of_pframes; i++)
    {
        future_used[i] = -1;
    }
    for (i = 0; i < no_of_pageRef; i++)
    {
        if (find(page_frame, pageRef[i], no_of_pframes) == -1)
        {
            x = leftmost_minus1(page_frame);
            //printf("\nx : %d\n", x);
            if (x == -1)
            {
                //printf(" %d - Miss\n", pageRef[i]);
                for (j = 0; j < no_of_pframes; j++)
                {
                    int ele = page_frame[j];
                    found = 0;
                    for (k = i + 1; k < no_of_pageRef; k++)
                    {
                        if (ele == pageRef[k])
                        {
                            future_used[j] = k;
                            found = 1;
                            break;
                        }
                        else
                            found = 0;
                    }
                    if (!found)
                        future_used[j] = -1;
                }
                int maxx = -32767;
                int eleindex;
                for (j = 0; j < no_of_pframes; j++)
                {
                    if (future_used[j] == -1)
                    {
                        maxx = future_used[j];
                        eleindex = j;
                        break;
                    }
                    if (future_used[j] > maxx)
                    {
                        maxx = future_used[j];
                        eleindex = j;
                    }
                }

                page_frame[eleindex] = pageRef[i];
                page_faults++;
                printf(" %d - Miss\n", pageRef[i]);
                displayPF(page_frame);
            }
            else
            {
                page_frame[x] = pageRef[i];
                page_faults++;
                printf(" %d - Miss\n", pageRef[i]);
                displayPF(page_frame);
            }
        }
        else
        {
            printf(" %d - Hit\n", pageRef[i]);
            displayPF(page_frame);
        }
    }
    printf(" Total number of page faults : %d\n", page_faults);
    return 0;
}
int lru(int page_frame[], int pageRef[])
{
    initialize(page_frame);
    page_faults = 0;
    int i, j, k, ele, found;
    int least_used[no_of_pframes];
    for (i = 0; i < no_of_pageRef; i++)
    {
        if (find(page_frame, pageRef[i], no_of_pframes) == -1)
        {
            //printf(" %d - Miss\n", pageRef[i]);
            for (j = 0; j < no_of_pframes; j++)
            {
                int ele = page_frame[j];
                found = 0;
                for (k = i - 1; k >= 0; k--)
                {
                    if (ele == pageRef[k])
                    {
                        least_used[j] = k;
                        found = 1;
                        break;
                    }
                    else
                        found = 0;
                }
                if (!found)
                    least_used[j] = -1;
            }
            int min = MAX;
            int eleindex;
            for (j = 0; j < no_of_pframes; j++)
            {
                if (least_used[j] < min)
                {
                    min = least_used[j];
                    eleindex = j;
                }
            }
            page_frame[eleindex] = pageRef[i];
            page_faults++;
            printf(" %d - Miss\n", pageRef[i]);
            displayPF(page_frame);
        }
        else
        {

            printf(" %d - Hit\n", pageRef[i]);
            displayPF(page_frame);
        }
    }
    printf(" Total number of page faults : %d\n", page_faults);
    return 0;
}
int main()
{
    int i;
    printf("\n Enter number of page frames : ");
    scanf("%d", &no_of_pframes);
    int page_frame[no_of_pframes];
    printf(" Enter number of page references : ");
    scanf("%d", &no_of_pageRef);
    int pageRef[no_of_pageRef];
    printf(" Enter the page references : \n");
    for (i = 0; i < no_of_pageRef; i++)
        scanf("%d", &pageRef[i]);

    printf("\n FIFO Page Replacement Algorithm : \n");
    fifo(page_frame, pageRef);
    printf("\n Optimal Page Replacement Algorithm : \n");
    optimal(page_frame, pageRef);
    printf("\n LRU Page Replacement Algorithm : \n");
    lru(page_frame, pageRef);
    return 0;
}
