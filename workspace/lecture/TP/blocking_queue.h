#pragma once

#include <cassert>
#include <cstdlib>
#include <deque>
#include <mutex>
#include <condition_variable>
#include <thread>
#include <chrono>

using namespace std::chrono_literals;

namespace tp {

//Unbounded Multi-Producer / Multi-Consumer (MPMC) Blocking Queue

template<typename T>
class UnboundedBlockingMPMCQeue {
public:

    // Thread role: producer
    void Put(T value)
    {
        std::lock_guard guard(mutex_);
        buffer_.push_back(std::move(value));
        cv_.notify_one();
    }

    T Take() {
        std::unique_lock lock(mutex_);
        while (buffer_.empty())
        {
            // 1) Release mutex 2) Wait 3) Reacquire mutex
            cv_.wait(lock);
        }
        return TakeLocked();
    }

private:
    T TakeLocked() {
        assert(!buffer_.empty());
        T front{std::move(buffer_.front())};
        buffer_.pop_front();
        return front;
    }

private:

    std::deque<T> buffer_; // Guarded by mutex_
    std::mutex mutex_;
    std::condition_variable cv_;
};

}