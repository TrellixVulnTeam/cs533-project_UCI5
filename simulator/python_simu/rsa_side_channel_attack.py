import numpy as np
import time
import threading

# A cacheline that can read or write
class Cacheline:
    def __init__(self, latency=None):
        self.lock = threading.Lock()
        self.tag = None
        self.data = None
        self.datalib = {}
        self.latency = 1 if latency is None else latency
        self.replacement = 0

    def get(self, tag):
        self.lock.acquire()
        # cache hit still takes some time
        time.sleep(self.latency / 10)
        # print("request for: ", tag)
        if tag == self.tag:
            data = self.data
            self.lock.release()
            return data
        elif tag in self.datalib:
            self.replacement += 1
            time.sleep(self.latency)
            # get the data after sleep
            self.tag = tag
            self.data = self.datalib[tag]
            self.lock.release()
            return self.data
        else:
            print("Error: Data not in cache")
            self.lock.release()
            return 0


    def store(self, tag, data):
        if self.tag == tag:
            self.lock.acquire()
            self.data = data
            self.datalib.update({tag: data})
            self.lock.release()
        else:
            self.lock.acquire()
            time.sleep(self.latency)
            self.tag = tag
            self.data = data
            self.datalib.update({tag: data})
            self.lock.release()


# def mod(x, N):
#     if x >= N:
#         x = x % N
#     return x

# a Square and Multiply algorithm in RSA
def square_and_multiply(cline, j, N, d):
    print("victim start", time.time())
    x = cline.get("C")
    for i in range(j):
        x = x ** 2 % N
        time.sleep(0.05) # simulate instr time
        if d[i]:
            # print(i)
            # print(cline.tag)
            x = (x * cline.get("C")) % N
            time.sleep(0.05) # simulate instr time
            # print(cline.tag)
    print("victim end", time.time())
    print("Thread output: ", x)


def attack(cline, ts):
    print("start attack", time.time())
    last = time.time()
    for i in range(200):
        start = last
        cline.get("X")
        last = time.time()
        ts[i] = last - start
    print("end attack", time.time())
    probe_list = [
        (index, value) for index, value in enumerate(ts) if value > 0.8 * cline.latency
    ]
    print(probe_list)
    print("Probed count: ", len(probe_list))


if __name__ == "__main__":
    cline = Cacheline(1)
    cline.store("C", 5)
    cline.store("X", 100)
    j = 20
    d = [0, 1, 0, 1, 0, 1, 1, 0, 0, 0, 1, 1, 1, 0, 1, 0, 1, 0, 0, 1]
    # d = [1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1]
    access_count = np.sum(d) + 1
    N = 10
    ts = [None] * 200
    # Creating threads
    thread1 = threading.Thread(
        target=square_and_multiply,
        args=(
            cline,
            j,
            N,
            d,
        ),
    )
    thread2 = threading.Thread(
        target=attack,
        args=(
            cline,
            ts,
        ),
    )
    # Starting the threads
    thread2.start()
    time.sleep(0.1)
    thread1.start()

    thread1.join()
    thread2.join()
    print("Actual access count: ", access_count)
    print("Run complete")
    # print(ts[:10])
    # print(cline.replacement)
