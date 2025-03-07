#pragma once

#include<iostream>
#include<thread>
#include "tasks.h"

namespace tp {

class ThreadPool
{

private:
    void StartWorkerThreads(size_t count);
    void JoinWorkerThreads();
    void Invoke(Task& task);

    void WorkerRoutine();

private:
    std::vector<std::thread> workers_;
};

}