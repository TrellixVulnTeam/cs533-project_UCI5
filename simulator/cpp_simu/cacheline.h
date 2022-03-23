#pragma once
#include <unordered_map>
#include <unistd.h>
#include <mutex>
#include <chrono>

class Cacheline {
  public:
    Cacheline()
        : tag(-1), data(-1), hit_latency(1'000), miss_latency(1'000'000), miss(0) {
    }

    int32_t read(int32_t tag);
    int32_t write(int32_t tag, int32_t data);
    int32_t miss_count();

  private:
    std::unordered_map<int32_t, int32_t> mem;
    std::mutex mtx;
    int32_t tag;
    int32_t data;
    std::chrono::nanoseconds hit_latency, miss_latency;
    int32_t miss;
};