import csv
import sys
import numpy as np
import matplotlib.pyplot as plt

def analyze(filename):
    with open(filename) as f:
        reader = csv.DictReader(f)
        err = 0
        tot = 0
        mismatch = np.zeros(32)
        tot_mismatch = 0
        for row in reader:
            truth = row['truth']
            decoded = row['decoded']
            for i in range(32):
                if truth[i] != decoded[i]:
                    mismatch[i] += 1
                    tot_mismatch += 1
            err += int(row['error'])
            tot += int(row['total'])
        print(f"Bit error is: {err/tot*100}%")
        mismatch[:] = [val/tot_mismatch for val in mismatch]
        plt.figure(figsize=(16,8))
        plt.ylim(0,0.1)
        plt.bar(np.arange(32)[::-1],mismatch)
        plt.title("Error Distribution")
        plt.ylabel("Error Percentage")
        plt.xlabel("Bit position")
        plt.savefig("error_dist_new.png")

if __name__ == '__main__':
    filename = 'stat.csv' if len(sys.argv) != 2 else sys.argv[1]
    analyze(filename)