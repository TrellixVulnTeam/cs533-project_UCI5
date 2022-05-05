from testcase import testcase
import sys
import os
import csv

def levenshteinDistance(s1, s2):
    if len(s1) > len(s2):
        s1, s2 = s2, s1

    distances = range(len(s1) + 1)
    for i2, c2 in enumerate(s2):
        distances_ = [i2+1]
        for i1, c1 in enumerate(s1):
            if c1 == c2:
                distances_.append(distances[i1])
            else:
                distances_.append(1 + min((distances[i1], distances[i1 + 1], distances_[-1])))
        distances = distances_
    return distances[-1]

def compute_error(decoded, truth):
    edit_dist = levenshteinDistance(decoded, truth)
    return edit_dist

def writecsv(truth, decoded, error, filename="stat.csv"):
    with open(filename, 'a') as f:
        writer = csv.writer(f)
        writer.writerow([truth, decoded, 32, error])

if __name__ == "__main__":
    if len(sys.argv) != 2:
        print("usage: {} <testcase num>".format(sys.argv[0]))
        os.exit(1)

    decoded = 0
    testcase_index = int(sys.argv[1])
    with open("decoded.txt", "r") as f:
        decoded = f.readline().strip()

    truth = format(testcase[testcase_index], '032b')
    error_num = compute_error(decoded, truth)
    writecsv(truth, decoded, error_num)