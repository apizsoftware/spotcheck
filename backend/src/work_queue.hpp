#pragma once

#include <iostream>
#include <chrono>
#include <queue>
#include <mutex>

#include "smart_thread.hpp"

class work_queue {
public:
    explicit work_queue(const size_t pool_size);
    // It should not need to be moved or copied.
    work_queue(const work_queue &) = delete;
    work_queue(work_queue &&) = delete;
    work_queue & operator=(const work_queue &) = delete;
    work_queue & operator=(work_queue &&) = delete;
    // Functions submitted to a work_queue should take no
    // arguments and have void return type. Parameters may
    // be passed via lambda capture modes.
    void submit(std::function<void()> && work);
    bool has_work() const;
    int current_load() const;
    ~work_queue();
private:
    bool m_is_running;
    int m_load;
    mutable std::mutex m_load_mtx;
    mutable std::mutex m_queue_mtx;
    std::vector<smart_thread> m_pool;
    std::queue<std::function<void()>> m_queue;
};