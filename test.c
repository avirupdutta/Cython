#include <stdio.h>

struct Process{
    int p_id;
    int arrivalTime;
    int burstTime;
    int waitingTime;
};

struct AvgWaitTimeOutput{
    double fcfs;
    double sjfP;
    double sjfNP;
    double roundRobin;
};

double fcfs(struct Process arr[], int arrLen);
double sjf_Non_Preemptive(struct Process arr[], int arrLen);
double sjf_Preemptive(struct Process arr[], int limit);

void main(){
    int num, i;
    
    
    // testing input data
    //---------------------------------
    num = 4;
    // getting the total no. of processes from the user (DYNAMICALLY)
    // printf("Enter the num of processes: ");
    // scanf("%d", &num);
    // ------------
    
    struct Process allProcess[num];
    struct AvgWaitTimeOutput avgWtTime;

    // testing input data
    //---------------------------------
    num = 4;
    allProcess[0].arrivalTime = 0;
    allProcess[0].burstTime = 8;

    allProcess[1].arrivalTime = 1;
    allProcess[1].burstTime = 4;
    
    allProcess[2].arrivalTime = 3;
    allProcess[2].burstTime = 9;
    
    allProcess[3].arrivalTime = 4;
    allProcess[3].burstTime = 5;

    // Creating and storing all processes inside allProcess Array (DYNAMICALLY)
    // for(i = 0; i < num; i++){
    //     printf("\nEnter the arrival time of p:%d -> ", i);
    //     scanf("%d", &allProcess[i].arrivalTime);
        
    //     printf("Enter the burst time of p:%d -> ", i);
    //     scanf("%d", &allProcess[i].burstTime);
        
    //     allProcess[i].p_id = i;
    // }
    //---------------------------------

    //>>Toggler>> 0.0; //
    avgWtTime.fcfs = fcfs(allProcess, num);
    avgWtTime.sjfNP = sjf_Non_Preemptive(allProcess, num);
    avgWtTime.sjfP = sjf_Preemptive(allProcess, num);

    printf("FCFS\t\tSJF(Non-Pre-eemptive)\t\tSJF(Pre-eemptive)\n");
    printf("%lf\t\t%lf\t\t%lf\n", avgWtTime.fcfs, avgWtTime.sjfNP, avgWtTime.sjfP);
}

double fcfs(struct Process arr[], int arrLen){
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
    
    // calculating the waiting time
    arr[0].waitingTime = 0;
    for(i=1; i<arrLen; i++){
        arr[i].waitingTime = (arr[i-1].burstTime + arr[i-1].waitingTime);   
        
    }

    // calculating the avg waiting time
    double avgWtTime=0.0;
    for(i = 0; i<arrLen; i++){
        avgWtTime += arr[i].waitingTime;
    }
    return (avgWtTime/arrLen);
}

double sjf_Non_Preemptive(struct Process arr[], int arrLen){
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

    // calculating the waiting time
    arr[0].waitingTime = 0;
    for(i=1; i<arrLen; i++){
        arr[i].waitingTime = (arr[i-1].burstTime + arr[i-1].waitingTime);   
        
    }

    // calculating the avg waiting time
    double avgWtTime=0.0;
    for(i = 0; i<arrLen; i++){
        avgWtTime += arr[i].waitingTime;
    }
    return (avgWtTime/arrLen);
}

double sjf_Preemptive(struct Process arr[], int limit){
	int arrival_time[limit], burst_time[limit+1], temp[limit];
    double total_waitTime = 0, end;
    float average_waiting_time;
    int i, smallest, count = 0, time;

    int smallestBurstTime = 999999;
     
    // printf("\nEnter Details of %d Processes\n", limit);
    for(i = 0; i < limit; i++){
    //     printf("\nEnter Arrival Time:\t");
    //     scanf("%d", &arrival_time[i]);
    //     printf("Enter Burst Time:\t");
    //     scanf("%d", &burst_time[i]); 
        temp[i] = arr[i].burstTime;
    }
    // printf("\nEnter Details of %d Processes You Entered\n", limit);
    // printf("\t Process Name \t Arrival Time \t Brust Time");
    // for(i = 0; i < limit; i++){
    // 	printf("\n");
    //     printf("\t\tP%d",i);
    //     printf("\t\t%d",arrival_time[i]);
    //     printf("\t\t%d",burst_time[i]);
        
    // }
    // burst_time[limit] = 999;  
    for(time = 0; count != limit; time++){
        smallest = limit;
        for(i = 0; i < limit; i++){
            if((arr[i].arrivalTime <= time) && (arr[i].burstTime < smallestBurstTime) && (arr[i].burstTime > 0)){
                smallest = i;
            }
        }
        arr[smallest].burstTime--; 
        if(arr[smallest].burstTime == 0){
            count++;
            end = time+1;
            total_waitTime = total_waitTime + end - arr[smallest].arrivalTime - temp[smallest];
        }
    }
    average_waiting_time = total_waitTime / limit; 
    printf("\nTotal Waiting Time:\t%lf\n", total_waitTime);
    printf("\nAverage Waiting Time:\t%lf\n\n", average_waiting_time);
    return(average_waiting_time);
}

