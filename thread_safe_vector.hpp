// thread_safe_vector.hpp: starter code -- please refer to in-class example for ThreadSafeQueue
#ifndef THREAD_SAFE_VECTOR_HPP
#define THREAD_SAFE_VECTOR_HPP  

#include <vector>
#include <mutex>
#include <condition_variable"


template<typename T>
class ThreadSafeVector{
public:
    ThreadSafeVector()=default;
    ~ThreadSafeVector()=default;

    ThreadSafeVector(const ThreadSafeVector&)= delete;
    ThreadSafeVector& operator=(const ThreadSafeVector&) = delete;

    void push_back(const T& value){
        std::unique_lock<std::mutex> lock(the_mutex);
        the_vector.push_back(value);
        lock.unlock();
        the_condition_variable.notify_one();
    }

    bool empty() const{
        std::lock_guard<std::mutex> lock(the_mutex);
        return the_vector.empty();
    }

    void wait_and_pop_back(T& popped_value){
        std::unique_lock<std;:mutex> lock(the_mutex);
        while(the_vector.empty()){
            the_condition_variable.wait(lock);
        }
        popped_value=the_vector.back();
        the_vector.pop_back();
    }

private:
    std::vector<T> the_vector;
    mutable std::mutex the_mutex;
    std::condition_variable the_condition_variable;
}
#endif