#include <iostream>
#include <vector>
#include <deque>
#include <list>
#include <string>
#include <thread>
#include <chrono>
#include <mutex>
#include <atomic>

#include "dbg.h"

using namespace std;

int counter = 0;
int NUM = 1000000;

atomic<int> at_counter = 0;

mutex counter_mtx;

void no_mutex_counter()
{   

    auto f1 = [&](){
        
        for (size_t i = 0; i < NUM; i++)
        {
            counter++;
        }
    };

    auto f2 = [&](){
        
        for (size_t i = 0; i < NUM; i++)
        {
            counter++;
        }
    };

    thread t1(f1);
    thread t2(f2);

    t1.join();
    t2.join();

    log_info(RED"counter = %d" NONE, counter);

}


void mutex_counter()
{   

    auto f1 = [&](int index){
        auto start = chrono::steady_clock::now();

        for (size_t i = 0; i < NUM; i++)
        {
            counter_mtx.lock();
            counter++;
            counter_mtx.unlock();
        }

        auto end = chrono::steady_clock::now();

        auto ms = chrono::duration_cast<chrono::milliseconds>(end-start).count();

        log_info("thread %d : counter [%d]", index, counter);
        log_info("thread %d : time used [%ld]ms", index, ms);
    };

    thread t1(f1, 1);
    thread t2(f1, 2);

    t1.join();
    t2.join();

    log_info(RED"counter = %d" NONE, counter);

}

void atomic_counter()
{
    
    auto add_counter = [&](int index)
    {
        auto start = chrono::steady_clock::now();
        for (size_t i = 0; i < NUM; i++)
        {
            at_counter++;
        }
        auto end = chrono::steady_clock::now();
        auto ms = chrono::duration_cast<chrono::milliseconds>(end-start).count();

        log_info("thread %d : at_counter [%d]", index, at_counter.load());
        log_info("thread %d : time used [%ld]ms", index, ms);
    };

   
    thread t1(add_counter, 1);
    thread t2(add_counter, 2);
    
    t1.join();
    t2.join();

    log_info(RED"at_counter = %d" NONE, at_counter.load());

}


int main(int argc, char const *argv[])
{

    // no_mutex_counter();
    // mutex_counter();

    // atomic_counter();

    return 0;
}