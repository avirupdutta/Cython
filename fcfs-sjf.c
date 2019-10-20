#include <stdio.h>
struct Process{
    int p_id;
    int arrivalTime;
    int burstTime;
    int waitingTime;
};

struct Process * fcfsBubbleSort(struct Process arr[], int arrLen);
struct Process * sjf_NP_BubbleSort(struct Process arr[], int arrLen);

void main(){
    int num, i;
    float avgWtTime;
    printf("Enter the num of processes: ");
    scanf("%d", &num);
    
    struct Process allProcess[num];
    struct Process *sortedArr;
    
    // Creating and storing all processes inside allProcess Array
    
    for(i = 0; i < num; i++){
        printf("\nEnter the arrival time of p:%d -> ", i);
        scanf("%d", &allProcess[i].arrivalTime);
        
        printf("Enter the burst time of p:%d -> ", i);
        scanf("%d", &allProcess[i].burstTime);
        
        allProcess[i].p_id = i;
    }
    
    // sortedArr = fcfsBubbleSort(allProcess, num);
    sortedArr = sjf_NP_BubbleSort(allProcess, num);
    
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

struct Process * fcfsBubbleSort(struct Process arr[], int arrLen){
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

struct Process * sjf_NP_BubbleSort(struct Process arr[], int arrLen){
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