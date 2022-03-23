import matplotlib.pyplot as plt
import numpy as np
if __name__ == "__main__":
    data = []
    with open("data.txt", "r") as f:
        line = f.readlines()[0]
        data = [int(elem) for elem in line.split(",")[:-1]]

    diff = [data[i + 1] - data[i] for i in range(len(data) - 1)]
    
    plt.figure(0)
    plt.title("access time")
    plt.plot(diff[:])
    plt.savefig("timeseries.png")

    plt.figure(1)
    x = np.sort(diff)[:] # removing outlier
    y = np.arange(len(x)) / float(len(x))
    plt.title('access time cdf')
  
    plt.plot(x, y)
    plt.savefig("cdf.png")


