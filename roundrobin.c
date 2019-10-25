#include<stdio.h>
void round_robin();
int main(){
	
	round_robin();
	return 0;
}
				
void round_robin() {
	int n,i,j,temp,time_quantum,remain,time=0,count,wait_time=0,flag=0;
	printf("enter the number of process: \n");
	scanf("%d",&n);
	remain=n;
	printf("enter the value of quantum:\n");
	scanf("%d",&time_quantum);
	int at[n],bt[n],pid[n],rt[n];
	for(i=0;i<n;i++){
		printf("\n enter process %d details:\n",i);
		printf("enter the arrivaltime %d;",i);
		scanf("%d",&at[i]);
		printf("enter the burst time %d;",i);
		scanf("%d",&bt[i]);
		pid[i]=i;
		rt[i]=bt[i];
	}
	for(i=0;i<n;i++){
		for(j=i+1;j<n;j++){
			if(at[i]>at[j]){
				temp=at[i];
				at[i]=at[j];
				at[j]=temp;
				temp=bt[i];
				bt[i]=bt[j];
				bt[j]=temp;
				temp=pid[i];
				pid[i]=pid[j];
				pid[j]=temp;
				temp=rt[i];
				rt[i]=rt[j];
				rt[j]=temp;
			}
		}
	}
	for(time=0,count=0;remain!=0;){
		if(rt[count]<=time_quantum && rt[count]>0){
			time+=rt[count];
			rt[count]=0;
			flag=1;
		}
		else if(rt[count]>0){
			rt[count]-=time_quantum;
			time+=time_quantum;
		}
		if(rt[count]==0 && flag==1){
			remain--;
			wait_time+=time-at[count]-bt[count];
			flag=0;
		}
		if(count==n-1){
			count=0;
		}
		else if(at[count+1]<=time){
			count++;
		}
		else{
			count=0;
		}
	}
	printf("\n average waiting time=%f\n",wait_time*1.0/n);
}

/*
Output:
=======

enter the number of process:
4
enter the value of quantum:
2

 enter process 0 details:
enter the arrivaltime 0;0
enter the burst time 0;8

 enter process 1 details:
enter the arrivaltime 1;1
enter the burst time 1;4

 enter process 2 details:
enter the arrivaltime 2;3
enter the burst time 2;9

 enter process 3 details:
enter the arrivaltime 3;4
enter the burst time 3;5

 average waiting time=12.000000

*/
