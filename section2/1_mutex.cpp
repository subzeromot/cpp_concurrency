#include <iostream>
#include <thread>
#include <list>
#include <mutex>

std::list<int> my_list;
std::mutex m1, m2;

void get_size(){
    m1.lock();
    int size = my_list.size();
    m1.unlock();
    printf("List size = %d \n", size);
}

void add_to_list__mutex(int const &numb){
    m1.lock();
    my_list.push_back(numb);
    m1.unlock();
}

void add_to_list__lock_guard(int const &numb){
    std::lock_guard<std::mutex> lg(m1);
    my_list.push_back(numb);
}

int main(){
    std::thread thread_1;
    std::thread thread_2;

    // access is guaranteed to be mutually exclusive
    thread_1 = std::thread(add_to_list__mutex, 4);
    thread_2 = std::thread(get_size);
    thread_1.join();
    thread_2.join();

    // RAII style - lock guard
    thread_1 = std::thread(add_to_list__lock_guard, 4);
    thread_2 = std::thread(get_size);
    thread_1.join();
    thread_2.join();
}
