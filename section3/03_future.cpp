#include <iostream>
#include <future>
#include <vector>

int doAsyncWork(int arg) noexcept
{
    std::cout << arg << " doAsyncWork: doing" << std::endl;
    int sleep_time = arg ;//(10 - arg) * 1000;
    std::this_thread::sleep_for(std::chrono::milliseconds(sleep_time));
    return arg;
}

int main(){
    auto start = std::chrono::system_clock::now();

    auto fut1 = std::async(doAsyncWork, 2);
    auto fut2 = std::async(doAsyncWork, 2);
    auto fut3 = std::async(doAsyncWork, 2);
    auto fut4 = std::async(doAsyncWork, 2);
    auto fut5 = std::async(doAsyncWork, 2);

    int ret1 = fut1.get();
    int ret2 = fut2.get();
    int ret3 = fut3.get();
    int ret4 = fut4.get();
    int ret5 = fut5.get();

    std::cout << "doAsyncWork output:" << ret1 << std::endl;
    std::cout << "doAsyncWork output:" << ret2 << std::endl;
    std::cout << "doAsyncWork output:" << ret3 << std::endl;
    std::cout << "doAsyncWork output:" << ret4 << std::endl;
    std::cout << "doAsyncWork output:" << ret5 << std::endl;

    auto end = std::chrono::system_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
    std::cout << "Duration: " << duration.count() << "ms" << std::endl;

    return 0;
}