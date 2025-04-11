/*
 * @Author: Ning Zhang
 * @Date: 2025-04-11 14:30:48
 * @Last Modified by: Ning Zhang
 * @Last Modified time: 2025-04-11 14:45:00
 */

#include <omp.h>
#include <stdio.h>
#include <stdlib.h>

class Class_with_Clock {
 public:
  Class_with_Clock() noexcept { omp_init_lock(&lock); }     /* RAII */
  ~Class_with_Clock() noexcept { omp_destroy_lock(&lock); } /* RAII */
  void set_lock() noexcept { omp_set_lock(&lock); }
  void unset_lock() noexcept { omp_unset_lock(&lock); }
  int test_lock() noexcept { return omp_test_lock(&lock); }

 protected:
  omp_lock_t lock;
};

class Test : public Class_with_Clock {
 public:
  Test() noexcept { printf("Test constructor\n"); }
  ~Test() noexcept { printf("Test destructor\n"); }
  void test() noexcept {
    set_lock();
    printf("Thread is in the critical section test::test()\n");
    unset_lock();
  }
};

class Task {
 public:
  Task(int begin, int end, Test& input)
      : begin_(begin), end_(end), test_(input) {
    printf("Task constructor\n");
  }
  ~Task() noexcept { printf("Task destructor\n"); }

  void Run() noexcept {
#pragma omp parallel for
    for (int i = begin_; i < end_; ++i) {
      test_.test();
    }
  }

 protected:
  int begin_;
  int end_;
  Test& test_;
};

int main() {
  Test test;
  omp_set_num_threads(16);

  Task task(0, 317, test);

  task.Run();

  return 0;
}