from plot import *
import os

SUPPRESS_THRESHOLD = 15
CLASSIFY_THRESHOLD = 0.25


def mostfrequent(List, nonzero = False):
    counter = 0
    num = List[0]

    for i in List:
        if nonzero and i == 0:
            continue
        curr_frequency = List.count(i)
        if (curr_frequency > counter):
            counter = curr_frequency
            num = i

    return num

def decode(filename):
    with open(filename, 'r') as f:
        line = f.readlines()[0]
        data = [int(elem) for elem in line.split(",")[:-1]]

    diff = [data[i + 1] - data[i] for i in range(len(data) - 1)]
    plotList(diff)
    # filter out noise
    base = mostfrequent(diff)
    print(base)
    diff[:] = [max(0,-(val - base)) for val in diff]
    plotList(diff)
    # reduce initialization overhead & noise
    # secondary_base = mostfrequent(diff, nonzero=True)
    # print(secondary_base)
    # start_idx = np.where(np.array(diff) == secondary_base)[0][-1]
    # print(start_idx)
    # diff = diff[start_idx+1:]

    peak_list = np.where(np.array(diff) > 0)[0]
    # print(peak_list)
    plotList(peak_list)

    interval = [peak_list[i+1] - peak_list[i] for i in range(len(peak_list) - 1)]
    print(interval)
    plotList(interval)

    key_interval = list(filter(lambda num: num > SUPPRESS_THRESHOLD, interval))
    print(key_interval)
    plotList(key_interval)

    passcode_bin = []
    # for i, val in enumerate(key_interval):
    #     if val > INTERVAL_CLASSIFIER:
    #         passcode_bin.append(0)
    #     elif val < INTERVAL_CLASSIFIER:
    #         if i == len(key_interval) - 1 or key_interval[i + 1] >= INTERVAL_CLASSIFIER:
    #             passcode_bin.append(1)
    #             key_interval.pop(i)
    # for i, val in enumerate(key_interval):
    #     if i != len(key_interval)-1 and key_interval[i+1] >= val * (1 + CLASSIFY_THRESHOLD):
    #         passcode_bin.append(1)
    #         key_interval.pop(i+1)
    #     else:
    #         passcode_bin.append(0)
    flag = 0
    for i in range(len(key_interval)):
        if flag:
            flag = 0
            continue
        elif i != len(key_interval)-1 and key_interval[i+1] >= key_interval[i] * (1 + CLASSIFY_THRESHOLD):
            passcode_bin.append(1)
            flag = 1
        else:
            passcode_bin.append(0)

    passcode_bin[:] = passcode_bin[::-1]
    print("Password in binary form: ", passcode_bin)

    passcode_dec = 0
    for digit in passcode_bin: 
        passcode_dec = 2 * passcode_dec + digit
    print("Password in decimal form: ", passcode_dec)
    print("Password in binary form: ", bin(passcode_dec))
    # plotList(diff)
    print("Actual value:            ", bin(3874308138))


if __name__ == "__main__":
    decode("lat.csv")