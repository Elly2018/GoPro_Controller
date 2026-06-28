/*
 * Copyright (c) [2026] [Elly/Funique]
 *
 * This software is licensed under the [MIT License].
 * See the LICENSE file in the project root for more information.
*/
#pragma once
#ifndef GCG_THREAD_SAFE_QUEUE_H
#define GCG_THREAD_SAFE_QUEUE_H
#include <queue>
#include <mutex>
#include <condition_variable>
#include <optional>

template <typename T>
class thread_safe_queue {
private:
    std::queue<T> q;
    std::mutex mtx;
    std::condition_variable cv;

public:
    void push(T value) {
        std::lock_guard<std::mutex> lock(mtx);
        q.push(std::move(value));
        cv.notify_one(); 
    }

    T pop() {
        std::unique_lock<std::mutex> lock(mtx);
        cv.wait(lock, [this] { return !q.empty(); });
        
        T value = std::move(q.front());
        q.pop();
        return value;
    }

    bool empty() {
        std::lock_guard<std::mutex> lock(mtx);
        return q.empty();
    }
};
#endif