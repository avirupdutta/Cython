#include <stdio.h>
#include <stdlib.h>

struct Process{
    int p_id;
    int arrivalTime;
    int burstTime;
    int waitingTime;
    int remainingTime;
};

struct AvgWaitTimeOutput{
    double fcfs;
    double sjfP;
    double sjfNP;
    double roundRobin;
};

double fcfs(struct Process arr[], int arrLen);
double sjf_Non_Preemptive(struct Process arr[], int arrLen);
double sjf_Preemptive(struct Process arr[], int arrLen);
double round_robin(struct Process arr[], int arrLen);

int main(){
    int num, i;
    FILE *fptr = fopen("sample.txt", "w"); 
    if (fptr == NULL) 
    { 
        printf("Could not open file"); 
        return 0; 
    } 
    
    
    // getting the total no. of processes from the user (DYNAMICALLY)
    printf("Enter the num of processes: ");
    scanf("%d", &num);
    
    struct Process allProcess[num];
    struct AvgWaitTimeOutput avgWtTime;

    // Creating and storing all processes inside allProcess Array (DYNAMICALLY)
    for(i = 0; i < num; i++){
        printf("\nEnter the arrival time of p:%d -> ", i);
        scanf("%d", &allProcess[i].arrivalTime);
        
        printf("Enter the burst time of p:%d -> ", i);
        scanf("%d", &allProcess[i].burstTime);
        
        allProcess[i].p_id = i;
    }

    avgWtTime.fcfs = fcfs(allProcess, num);
    avgWtTime.sjfNP = sjf_Non_Preemptive(allProcess, num);
    avgWtTime.roundRobin = round_robin(allProcess, num);
    avgWtTime.sjfP = sjf_Preemptive(allProcess, num);
    fprintf(fptr,"%f\n%f\n%f\n%f\n",avgWtTime.fcfs,avgWtTime.sjfNP,avgWtTime.sjfP,avgWtTime.roundRobin); 
    fclose(fptr);
    printf("\nAlgos:\t\tFCFS\t\tSJF(Non-Pre-eemptive)\t\tSJF(Pre-eemptive)\t\t Round-Robin\n");
    printf("Avg. Wt Time:\t\t%lf\t\t%lf\t\t%lf\t\t%lf\n", avgWtTime.fcfs, avgWtTime.sjfNP, avgWtTime.sjfP, avgWtTime.roundRobin);

    system("python graph.py");
}

double fcfs(struct Process arr[], int arrLen){
    printf("\nInitiating fcfs algo...\n");
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
    printf("Finishing fcfs algo...\n");
    return (avgWtTime/arrLen);
}

double sjf_Non_Preemptive(struct Process arr[], int arrLen){
    printf("\nInitiating sjf(non-preemptive) algo...\n");

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
    printf("Finishing sjf(Non-preemptive) algo...\n");

    return (avgWtTime/arrLen);
}

double round_robin(struct Process arr[], int arrLen) {
    printf("\nInitiating Round Robin algo...\n");
	int n = arrLen, i,j,temp,time_quantum,remain,time=0,count,wait_time=0,flag=0;
	remain=n;
	printf("Enter the time quantum: ");
	scanf("%d",&time_quantum);
	
    // setting the remaining time for each process
    for(i=0;i<n;i++){
		arr[i].remainingTime=arr[i].burstTime;
	}
    // sorting the processes according to their arriaval time
	for(i=0; i<n; i++){
		for(j=i+1; j<n; j++){
			if(arr[i].arrivalTime > arr[j].arrivalTime){
				temp = arr[i].arrivalTime;
				arr[i].arrivalTime = arr[j].arrivalTime;
				arr[j].arrivalTime = temp;

				temp=arr[i].burstTime;
				arr[i].burstTime = arr[j].burstTime;
				arr[j].burstTime = temp;

				temp=arr[i].p_id;
				arr[i].p_id = arr[j].p_id;
				arr[j].p_id = temp;
				
                temp = arr[i].remainingTime;
				arr[i].remainingTime = arr[j].remainingTime; 
				arr[j].remainingTime = temp;
			}
		}
	}


    arr[0].arrivalTime = 0;
	
    // main algo starts below
    for(time=0,count=0;remain!=0;){
		if(arr[count].remainingTime <= time_quantum && arr[count].remainingTime > 0){
			time += arr[count].remainingTime;
			arr[count].remainingTime = 0;
			flag = 1;
		}
		else if(arr[count].remainingTime > 0){
			arr[count].remainingTime -= time_quantum;
			time += time_quantum;
		}
		if(arr[count].remainingTime == 0 && flag == 1){
            printf("%d\n", remain);
			remain--;
			wait_time += time - arr[count].arrivalTime - arr[count].burstTime;
			flag = 0;
		}
		if(count == n-1){
			count=0;
		}
		else if(arr[count+1].arrivalTime <= time){
			count++;
		}
		else{
			count=0;
		}
	}
    printf("Finishing Round Robin algo...\n");
    return (wait_time*1.0/n);
}

double sjf_Preemptive(struct Process arr[], int arrLen){
    printf("\nInitiating sjf(Preemptive) algo...\n");

	int temp[arrLen];
    double total_waitTime = 0, end;
    float average_waiting_time;
    int i, smallest, count = 0, time;
     
     
    for(i = 0; i < arrLen; i++){
        temp[i] = arr[i].burstTime;
    }
    
    arr[arrLen].burstTime = 999;
    for(time = 0; count != arrLen; time++){
        smallest = arrLen;
        for(i = 0; i < arrLen; i++){
            if(arr[i].arrivalTime <= time && arr[i].burstTime < arr[smallest].burstTime && arr[i].burstTime > 0){
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
    average_waiting_time = total_waitTime / arrLen; 
    printf("Finishing sjf(Preemptive) algo...\n");
    return(average_waiting_time);
}