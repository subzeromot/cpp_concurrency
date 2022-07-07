#include <chrono>
#include <condition_variable>
#include <cstdio>
#include <iostream>
#include <mutex>
#include <string>
#include <thread>

int total_distance = 5;
int distance_covered = 0;

std::condition_variable cv;
std::mutex mutex;

void driver(){
    while(true){
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
        distance_covered++;
        printf("distance covered = %d \n", distance_covered);

        if(distance_covered == total_distance){
            printf("condition notify \n");
            cv.notify_one();
            break;
        }
    }
}

void passenger(){
    std::unique_lock<std::mutex> lk(mutex);

//    cv.wait(lk);
    cv.wait(lk, []{ return distance_covered == total_distance;});

    printf("passenger go");
}

int main(){
    std::thread driver_thread(driver);
    std::thread passenger_thread(passenger);

    driver_thread.join();
    passenger_thread.join();
}