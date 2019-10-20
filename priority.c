// #include <stdio.h>

// struct Process{
//   int pId;
//   int  arrivalTime;
//   int burstTime;
//   int priority;
// };
// void bubbleSort(struct Process arr[], int sizeOfArr);
// void display(struct Process arr[], int sizeOfArr);
// void setAllProcess(struct Process arr[], int sizeOfArr);

// void main(){
  
//   int totalProcess, i;
//   int serviceTime = 0;
//   printf("Enter the no. of processes you want to create: ");
//   scanf("%d", &totalProcess);
//   struct Process arr[totalProcess], readyQueue[totalProcess], finishedQueue[totalProcess];

//   // Create all processes and store in arr 
//   setAllProcess(arr, totalProcess);
  
//   // sort the array according to the priority
//   bubbleSort(arr, totalProcess);

   
//   serviceTime = arr[0].burstTime;
//   finishedQueue[0] = arr[0];
//   int j;
//   // Do the main priority scheduling algo below
//   for (i = 1; i < totalProcess;){

//     // 1) filter the remaining processes with arrivalTime less than the current serviceTime
//     for(j = i; j < totalProcess; j++){
//       if(arr[j].arrivalTime <= serviceTime){
//         // 2) and insert all the filtered processes inside readyQueue
//         readyQueue[j-1] = arr[j];
//       }
//     }

//     // 3) sort the readyQueue according to priority (with bubbleSort())
//     bubbleSort(readyQueue, totalProcess);

//     int counter = 0, k;
//     // 4) repeat step-2 and set new serviceTime with the value of the last process's burst time.
//     for(k = 0; k < totalProcess; k++){
//       if(readyQueue[k] != NULL){

//       }
//     }

//     i = j+1;
//   }
  




//   // display the array
//   display(arr, totalProcess);
  
// }
// void bubbleSort(struct Process arr[], int sizeOfArr){
//   printf("Inside bubble sort!");
//   int i, j;
//   struct Process temp;
//   for(i = 0; i < sizeOfArr; i++){
//     for (j = 0; j < sizeOfArr-i-1; j++){
//       if(arr[j].priority > arr[j+1].priority){
//         // swap
//         temp = arr[j];
//         arr[j] = arr[j+1];
//         arr[j+1] = temp;
//       }
//     }    
//   }
// }
// void display(struct Process arr[], int sizeOfArr){
//   int i;
//   // display the arr
//   printf("\n\nOutput:-\n====================\n");
//   for(i = 0; i < sizeOfArr; i++){
//     printf("Process-%d has arrival time: %d, burst time: %d and priority: %d\n", arr[i].pId, arr[i].arrivalTime, arr[i].burstTime, arr[i].priority);
//   }
// }
// void setAllProcess(struct Process arr[], int sizeOfArr){
//   int i;
//   // Set the arr of processess
//   for(i = 0; i < sizeOfArr; i++){
//     struct Process newProcess;
//     newProcess.pId = (i+1);
//     printf("\nEnter the Arrival time for process-%d: ", newProcess.pId);
//     scanf("%d", &newProcess.arrivalTime);
//     printf("Enter the Burst time for process-%d: ", newProcess.pId);
//     scanf("%d", &newProcess.burstTime);
//     printf("Enter the Priority for process-%d: ", newProcess.pId);
//     scanf("%d", &newProcess.priority);
//     arr[i] = newProcess;
//   }
// }
