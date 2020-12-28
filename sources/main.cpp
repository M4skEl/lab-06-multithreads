//
// Created by elisey on 28.12.2020.
//
#include <picosha2.h>

#include <ctime>
#include <iostream>
#include <vector>

#include "HashData.h"
#include "boost/thread.hpp"
#include "thread"

using std::cout;
using std::endl;
using std::vector;

int main() {
  const size_t total_threads = std::thread::hardware_concurrency();

  //  if (argc > 1)
  //    total_threads = reinterpret_cast<size_t>(argv[1]);
  //  else
  //    total_threads = std::thread::hardware_concurrency();

  cout << total_threads << endl;
  vector<std::thread> thread_pull;


  std::string h;
  std::string src_str="sad_boy";
  picosha2::hash256_hex_string(src_str,h);
  cout<<h<<endl;
      return 0;
}