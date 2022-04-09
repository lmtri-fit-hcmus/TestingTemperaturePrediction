import matplotlib
import matplotlib.pyplot as plt
import csv

from numpy import double
  
x = []
y = []
with open('Data\\TAVG_Dataset_78-018.csv','r') as csvfile:
    lines = csv.reader(csvfile, delimiter=',')
    for row in lines:
        x.append(row[0])
        y.append(double(row[1]))
  
plt.bar(x, y, color = 'b', width = 0.72, label = "Temperature")
plt.xlabel('Dates')
plt.ylabel('Temperature(°C)')
plt.title('Weather Report 1978-2018', fontsize = 20)
plt.legend()
plt.show()