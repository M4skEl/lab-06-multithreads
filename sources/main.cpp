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
  srand(time(0));
  const size_t total_threads = std::thread::hardware_concurrency();

  //  if (argc > 1)
  //    total_threads = reinterpret_cast<size_t>(argv[1]);
  //  else
  //    total_threads = std::thread::hardware_concurrency();

  cout << total_threads << endl;
  vector<std::thread> thread_pull;
  std::string path = "../include/Hashes.json";

  std::ofstream head_file;
  head_file.open(path);
  head_file << "[\n";
  head_file.close();

  for (size_t i = 0; i < total_threads; i++) {
    thread_pull.push_back(std::thread(FindHash, path));
  }
  for (size_t i = 0; i < total_threads; i++) {
    thread_pull[i].join();
  }
  std::ofstream end_file;
  end_file.open(path, std::ofstream::app);
  end_file << "]\n";
  end_file.close();
  //  HashData hs;
  //  cout << hs.hash << endl;
  //  std::string h;
  //  std::string src_str = std::to_string(rand());
  //  cout << src_str << endl;
  //  picosha2::hash256_hex_string(src_str, h);
  //  cout << h << endl;
  //  h = "89320b8ca6f530a22fda049b0eaedd784a94f19a48e9ccfabeb7d6253e9e0000";
  //  cout << h << endl;
  //  cout << is_right_hash(h) << endl;
  return 0;
}