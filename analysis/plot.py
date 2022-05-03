import numpy as np
import matplotlib.pyplot as plt
import sys
import os

if __name__ == "__main__":
    data = []
    key = sys.argv[1]

    os.mkdir(f"figs/{key}")
    with open("lat.csv", "r") as f:
        line = f.readlines()[0]
        data = [int(elem) for elem in line.split(",")[:-1]]


    # diff = [data[i + 1] - data[i] for i in range(len(data) - 1)]
    
    plt.figure(0)
    plt.title("Access Time")
    plt.ylabel("CPU Cycles")
    plt.xlabel("Probe Number")
    plt.plot(data[:])
    plt.savefig(f"figs/{key}/timeseries.png")

    plt.figure(1)
    x = np.sort(data)[:] # removing outlier
    y = np.arange(len(x)) / float(len(x))
    plt.title('access time cdf')
  
    plt.plot(x, y)
    plt.savefig(f"figs/{key}/cdf.png")

