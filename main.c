#include <stdio.h>
struct Process{
    int p_id;
    int arrivalTime;
    int burstTime;
    int waitingTime;
};

struct AvgWaitTimeOutput{
    int fcfs;
    int sjfP;
    int sjfNP;
    int roundRobin;
};


// function declarations
int fcfs(struct Process arr[], int arrLen);
int sjf_Non_Preemptive(struct Process arr[], int arrLen);
int sjf_Preemptive(struct Process arr[], int limit);

void main(){
    int num, i;
    float avgWtTime;
    printf("Enter the num of processes: ");
    scanf("%d", &num);
    
    struct Process allProcess[num];
    struct Process *sortedArr;
    struct AvgWaitTimeOutput avgWtTime;


    
    // Creating and storing all processes inside allProcess Array

    for(i = 0; i < num; i++){
        printf("\nEnter the arrival time of p:%d -> ", i);
        scanf("%d", &allProcess[i].arrivalTime);
        
        printf("Enter the burst time of p:%d -> ", i);
        scanf("%d", &allProcess[i].burstTime);
        
        allProcess[i].p_id = i;
    }
    
    // sortedArr = fcfsBubbleSort(allProcess, num);
    sortedArr = sjf_Non_Preemptive(allProcess, num);
    
    // Setting the waiting time accordingly
    sortedArr[0].waitingTime = 0;
    for(i=1; i<num; i++){
        sortedArr[i].waitingTime = (sortedArr[i-1].burstTime + sortedArr[i-1].waitingTime);   
        
    }
    
    // Displaying the 3 arrays
    printf("\nOutput:-\n====================\n");
    for(i = 0; i<num; i++){
        printf("p%d has arrival time = %d, burst time = %d and waiting time = %d\n", sortedArr[i].p_id, sortedArr[i].arrivalTime, sortedArr[i].burstTime, sortedArr[i].waitingTime);
    }
    
    // Calculating the average waiting time from all processes
    avgWtTime=0.0;
    for(i = 0; i<num; i++){
        avgWtTime += sortedArr[i].waitingTime;
    }
    printf("\nAverage Waiting Time = %f \n", (avgWtTime/num));
}

// Defining the fcfs algorithm
int fcfs(struct Process arr[], int arrLen){
    int i, j;
    for(i=0; i<arrLen; i++){
        for(j=0; j<arrLen-i-1; j++){
            if(arr[j].arrivalTime > arr[j+1].arrivalTime){
                struct Process temp = arr[j];
                arr[j] = arr[j+1];
                arr[j+1] = temp;
            }
        }
    }
    return arr;
}

// Defining the non-pre-emptive sjf algorithm
int sjf_Non_Preemptive(struct Process arr[], int arrLen){
    int i, j;
    for(i=0; i<arrLen; i++){
        for(j=0; j<arrLen-i-1; j++){
            if(arr[j].burstTime > arr[j+1].burstTime){
                struct Process temp = arr[j];
                arr[j] = arr[j+1];
                arr[j+1] = temp;
            }
        }
    }
    return arr;
}


int sjf_Preemptive(struct Process arr[], int limit){
	int arrival_time[limit], burst_time[limit+1], temp[limit];
    double wait_time = 0, end;
    float average_waiting_time;
    int i, smallest, count = 0, time;
     
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
    return(average_waiting_time);
}