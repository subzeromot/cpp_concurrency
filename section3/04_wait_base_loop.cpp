/** Key idea:
 *
 *   - The default launch policy's scheduling flexibility also affects
 *     wait-based for loops using timeouts, because calling wait_for or
 *     wait_until on a task (see Item 35) that's deferred yields the value
 *     std::launch::deferred.
 */

#include <future>
#include <iostream>

using namespace std::literals;         // for C++14 duration
// suffixes; see Item 34

void f()                               // f sleeps for 1 second,
{                                      // then returns
    std::cout << "Start" << std::endl;
    std::this_thread::sleep_for(1s);
    std::cout << "End" << std::endl;
}


int main()
{
    auto fut = std::async(std::launch::async, f);          // run f asynchronously (conceptually)
//    auto fut = std::async(std::launch::deferred, f); // ---> while loop below will never finish, cause fut.wait_for will always return std::future_status::deferred

    while (fut.wait_for(200ms) != std::future_status::ready)
    {
        // ...
        printf("done\n");
    }
}
