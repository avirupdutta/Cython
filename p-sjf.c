#include<stdio.h>
 
int main(){
	int limit;
	int Premptive_SJF(int);
	printf("\nEnter the Total Number of Processes:\t");
    scanf("%d", &limit);
    Premptive_SJF(limit);
}

int Premptive_SJF(int limit){
	int arrival_time[limit], burst_time[limit+1], temp[limit];
    int i, smallest, count = 0, time;
    double wait_time = 0, end;
    float average_waiting_time;
     
    printf("\nEnter Details of %d Processes\n", limit);
    for(i = 0; i < limit; i++){
        printf("\nEnter Arrival Time:\t");
        scanf("%d", &arrival_time[i]);
        printf("Enter Burst Time:\t");
        scanf("%d", &burst_time[i]); 
        temp[i] = burst_time[i];
    }
    printf("\nEnter Details of %d Processes You Entered\n", limit);
    printf("\t Process Name \t Arrival Time \t Brust Time");
    for(i = 0; i < limit; i++){
    	printf("\n");
        printf("\t\tP%d",i);
        printf("\t\t%d",arrival_time[i]);
        printf("\t\t%d",burst_time[i]);
        
    }
    burst_time[limit] = 999;  
    for(time = 0; count != limit; time++){
        smallest = limit;
        for(i = 0; i < limit; i++){
            if((arrival_time[i] <= time) && (burst_time[i] < burst_time[smallest]) && (burst_time[i] > 0)){
                smallest = i;
            }
        }
        burst_time[smallest]--;
        if(burst_time[smallest] == 0){
            count++;
            end = time + 1;
            wait_time = wait_time + end - arrival_time[smallest] - temp[smallest];
        }
    }
    average_waiting_time = wait_time / limit; 
    printf("\n\nAverage Waiting Time:\t%lf\n", average_waiting_time);
    return(0);
}