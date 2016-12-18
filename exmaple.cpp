#include <iostream>
#include <functional>
#include <ctime>

// C++11 headers
#include <atomic>
#include <chrono>
#include <unordered_map>
#include <thread>

// use using
using sysclock = std::chrono::system_clock;


// C++11 compile-time assertion
static_assert(sizeof(void*) == sizeof(char*), "compile time assertion failed");
std::string now () {
  // use clocks
  auto now = sysclock::now();
  auto time = sysclock::to_time_t(now);
  return ::ctime(&time);
}

// use C++11 function syntax
auto callback () -> void {
  std::cout << "thread started at " << now() << std::endl;

  std::this_thread::sleep_for(std::chrono::milliseconds(5000));

  std::cout << "thread finished at " << now() << std::endl;
};


int main (int, char*[]) {
  auto&& start = now();

  std::cout << "program started at " << start << std::endl;

  // use unordered map and initializer list
  std::unordered_map<std::string, std::string> values = { 
    { "Hello", "World" } 
  };

  // use auto and range iterator syntax
  for (auto const& it : values) {
    std::cout << it.first << " " << it.second << std::endl;
  }

  // use std::thread
  std::thread thread(callback);
  thread.join();

  std::cout << "program finished at " << now() << std::endl;
  return 0;
}
