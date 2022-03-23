#include "cacheline.h"
#include <thread>
#include <iostream>

int32_t Cacheline::read(int32_t tag) {
    std::lock_guard<std::mutex> guard(this->mtx);
    if (tag == this->tag) {
        std::this_thread::sleep_for(hit_latency);
        return this->data;
    } else {
        std::this_thread::sleep_for(miss_latency);
        this->miss++;
        // std::cout << "tag: " << tag << std::endl;
        auto it = this->mem.find(tag);
        if (it != this->mem.end()) {
            this->tag = tag;
            this->data = it->second;
            return this->data;
        } else {
            std::cout << "non existent tag: " << tag << std::endl;
            return -1;
        }
    }
}

int32_t Cacheline::write(int32_t tag, int32_t data) {
    std::lock_guard<std::mutex> guard(this->mtx);
    if (tag == this->tag) {
        std::this_thread::sleep_for(hit_latency);
    } else {
        std::this_thread::sleep_for(miss_latency);
    }
    this->mem[tag] = data;
    this->tag = tag;
    this->data = data;
    return 0;
}

int32_t Cacheline::miss_count() {
    return this->miss;
}
