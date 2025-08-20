#include <time.h>
#include <iostream>
#include <chrono>
#include <ctime> // For std::cti
void sleep_ms(uint ms)
{
  struct timespec ts;
  ts.tv_sec = 0;
  ts.tv_nsec = ms * 1000000; // 500 ms = 500,000,000 ns

  nanosleep(&ts, nullptr);
}

uint32_t time_ms_32()
{
  // Get current time point from system clock
  auto now = std::chrono::system_clock::now();

  // Convert time point to time_t for traditional C-style time handling

  // To get time in milliseconds since epoch:
  auto epoch_time_ms = std::chrono::duration_cast<std::chrono::milliseconds>(
                           now.time_since_epoch())
                           .count();
  return epoch_time_ms;
}

uint32_t time_us_32()
{
  return 1000 * time_ms_32();
}