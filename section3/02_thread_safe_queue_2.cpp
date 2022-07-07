#include <iostream>
#include <optional>
#include <queue>
#include <thread>
#include <mutex>
#include <condition_variable>

template <class T>
class ThreadSafeQueue
{
public:
    explicit ThreadSafeQueue(size_t capacity = 1000) : mCapacity{capacity} {}
    void push(T && elem);
    T pop();
private:
    std::mutex mutex;
    std::condition_variable mNotEmpty;
    std::condition_variable mNotFull;
    std::queue<T> mQueue;
    const size_t mCapacity;
};

template<class T>
void ThreadSafeQueue<T>::push(T &&elem) {
    std::unique_lock<std::mutex> lck(mutex);
    mNotFull.wait(lck, [this]{ return mQueue.size() < mCapacity; });

    mQueue.push(std::forward<T>(elem));
    lck.unlock();

    mNotEmpty.notify_one();
}

template<class T>
T ThreadSafeQueue<T>::pop() {
    std::unique_lock<std::mutex> lck(mutex);
    mNotEmpty.wait(lck, [this]{ return !mQueue.empty();});

    T elem = mQueue.front();
    mQueue.pop();
    lck.unlock();

    mNotFull.notify_one();
    return elem;
}



// ============================== MAIN ===================================
namespace
{
    struct QueueEntry
    {
        static size_t ctr;
        size_t msg;
    };
    size_t QueueEntry::ctr = 0;

    QueueEntry CreateANewEntry() { return QueueEntry{ ++QueueEntry::ctr }; }
}
int main(){
    ThreadSafeQueue<QueueEntry> TSQ;

    auto producer = [](ThreadSafeQueue<QueueEntry> & TSQ){
        for(size_t i = 0; i != 10; i++){
            TSQ.push(CreateANewEntry());
            std::this_thread::sleep_for (std::chrono::seconds(1));
            std::cout << "Producer: From Thread ID : "<<std::this_thread::get_id() << "\n";
        }
    };

    auto consumer = [](ThreadSafeQueue<QueueEntry>& TSQ) {
        for (size_t i = 0; i != 10; ++i)
        {
            std::this_thread::sleep_for (std::chrono::seconds(1));
            std::cout << "Consumer: From Thread ID : "<<std::this_thread::get_id() << " get message " << TSQ.pop().msg << "\n";
        }
    };

    std::vector<std::thread> threads;
    int numb_producer = 10;
    int numb_consumer = 10;

    for(unsigned  i = 0; i < numb_producer; i++){
        threads.emplace_back(producer, std::ref(TSQ));
    }

    for(unsigned  i = 0; i < numb_consumer; i++){
        threads.emplace_back(consumer, std::ref(TSQ));
    }

    for(auto &thread : threads){
        if(thread.joinable())
            thread.join();
    }

    return 0;
}