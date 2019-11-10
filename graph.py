import matplotlib.pyplot as plt
import numpy as np

def gather_output():
   op=open("sample.txt","r")
   output=[]
   for line in op:
      for data in line.split('\n'):
         if(data!=''):
            output.append(float(data))
   return(output)


label = ['FCFS','Non Premptive SJF','Premptive SJF','Round Robin']
output=gather_output()
index = np.arange(len(label))
plt.bar(index, output)
plt.xlabel('Precess Scheduling', fontsize=10)
plt.ylabel('Average Waiting Time', fontsize=10)
plt.xticks(index, label, fontsize=7, rotation=30)
plt.title('Average Waiting time With All Process Scheduling Algorithm')
plt.show()
