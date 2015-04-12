import re
import csv
import numpy as np
import matplotlib.pyplot as plt  

node_time = [[] for row in range(16)]  
msg_num = []
for line in open("log"):
    data = re.search("node\s*(\d+)\:\s*(\d+\.\d+)",line)
    if(data):
        node_time[int(data.group(1))-1].append(float(data.group(2)));
    num = re.search("Amount message number:\s*(\d+)",line)
    if(num):
        msg_num.append(int(num.group(1)));   
#save as csv file
with open("time_result.csv", 'wb') as csvfile:
    dataWriter = csv.writer(csvfile, delimiter=',',quotechar='|', quoting=csv.QUOTE_MINIMAL)
    for row in node_time:
        dataWriter.writerow(row)
average_ma = []
average_cmpw = []        
#save figure
for j in range(5):
    ma_time =[]
    cmpw_time =[]
    for i in range(16):
        cmpw_time.append(node_time[i][0+j])
        ma_time.append(node_time[i][5+j])
    print cmpw_time
    print ma_time
    n_groups=16
    fig, ax = plt.subplots()
    index = np.arange(n_groups)
    bar_width = 0.35
    opacity = 0.4  

    rects1 = plt.bar(index, cmpw_time, bar_width,alpha=opacity, color='b',label='CMPW')  
    rects2 = plt.bar(index+bar_width, ma_time, bar_width,alpha=opacity, color='r',label='Meakawa')  
    plt.xlabel('Node')
    plt.ylabel('Time (ms)')
    plt.xticks(index + bar_width, ('1', '2', '3', '4', '5','6','7','8','9','10','11','12','13','14','15','16'))
    plt.legend() 
    plt.tight_layout()
    plt.savefig('{0}_{1}.png'.format("Testcase",j+1)) 
    average_cmpw.append(np.mean(cmpw_time))
    average_ma.append(np.mean(ma_time))
#save average time figure
n_groups=5
fig, ax = plt.subplots()
index = np.arange(n_groups)
bar_width = 0.35
opacity = 0.4  

rects1 = plt.bar(index, average_cmpw, bar_width,alpha=opacity, color='b',label='CMPW')  
rects2 = plt.bar(index+bar_width, average_ma, bar_width,alpha=opacity, color='r',label='Meakawa')  
plt.xlabel('Testcase')
plt.ylabel('Average Time (ms)')
plt.xticks(index + bar_width, ('1', '2', '3', '4', '5'))
plt.legend() 
plt.tight_layout()
plt.savefig('{0}_{1}.png'.format("Average","Time")) 

#save message number
n_groups=5
fig, ax = plt.subplots()
index = np.arange(n_groups)
bar_width = 0.35
opacity = 0.4  

print msg_num[0:5]
print msg_num[5:10]

rects1 = plt.bar(index, msg_num[0:5], bar_width,alpha=opacity, color='b',label='CMPW')  
rects2 = plt.bar(index+bar_width, msg_num[5:10], bar_width,alpha=opacity, color='r',label='Meakawa')  
plt.xlabel('Testcase')
plt.ylabel('Message Number')
plt.xticks(index + bar_width, ('1', '2', '3', '4', '5'))
plt.legend() 
plt.tight_layout()
plt.savefig('{0}_{1}.png'.format("Message","Number")) 


