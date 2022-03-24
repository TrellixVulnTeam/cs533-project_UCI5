#include <x86intrin.h>
#include <iostream>
#include <fstream>
#include <thread>
#include <vector>
#include "cacheline.h"

static constexpr int32_t x_tag = 1;
static constexpr int32_t base_tag = 2;
static constexpr int probe_time = 50'000;
static constexpr std::chrono::milliseconds headstart(100);
static constexpr std::chrono::nanoseconds instr(100'000'000);

static auto cast_time(std::chrono::system_clock::time_point t) {
    return static_cast<double>(
               std::chrono::duration_cast<std::chrono::nanoseconds>(
                   t.time_since_epoch())
                   .count()) /
           1'000'000'000;
}

void attacker(Cacheline &cl, std::vector<uint64_t> &ts) {
    auto start = std::chrono::system_clock::now();
    std::cout << "attacker start:\t" << std::fixed << cast_time(start)
              << std::endl;

    for (int i = 0; i < probe_time; ++i) {
        // flush + reload
        ts[i] = _rdtsc();
        (void)cl.read(x_tag);
    }

    auto end = std::chrono::system_clock::now();
    std::cout << "attacker end:\t" << std::fixed << cast_time(end) << std::endl;
}

int32_t square_multiply(Cacheline &cl, int32_t exp, int32_t mod) {
    auto start = std::chrono::system_clock::now();
    std::cout << "victim start:\t" << std::fixed << cast_time(start)
              << std::endl;
    if (exp == 0)
        return 1;
    int bits, var = exp;
    for (bits = 0; var != 0; var >>= 1, bits++)
        ;
    int32_t x = 1;
    for (; bits > 0; bits--) {
        // instr time
        x = (x * x) % mod;
        std::this_thread::sleep_for(instr);
        if (exp & (1L << (bits - 1))) {
            x = (x * cl.read(base_tag)) % mod;
            std::this_thread::sleep_for(instr);
            // instr time
        }
    }
    auto end = std::chrono::system_clock::now();
    std::cout << "victim end:\t" << std::fixed << cast_time(end) << std::endl;
    return x;
}

int main() {
    Cacheline cl;
    cl.write(base_tag, 2);
    cl.write(x_tag, 0);

    // uint64_t ts[probe_time];
    std::vector<uint64_t> ts;
    ts.reserve(probe_time);
    // attacker(cl, ts);
    std::thread t1(attacker, std::ref(cl), std::ref(ts));
    std::this_thread::sleep_for(headstart);
    std::thread t2(square_multiply, std::ref(cl), 0b110101001, 64);

    t1.join();
    t2.join();
    std::cout << "CL miss: " << cl.miss_count() << std::endl;

    std::ofstream dataf("data.txt");
    for (int i = 0; i < probe_time; ++i) {
        dataf << ts[i] << ",";
    }
    dataf.close();
    return 0;
}
