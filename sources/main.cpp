//
// Created by elisey on 28.12.2020.
//
#include <picosha2.h>

#include <csignal>
#include <ctime>
#include <iostream>
#include <string>
#include <thread>
#include <vector>

#include "HashData.h"

using std::cout;
using std::endl;
using std::vector;

int main(int argc, char* argv[]) {
  srand(time(0));
  size_t total_threads = std::thread::hardware_concurrency();

  if (argc > 1)
    total_threads = std::stoul(argv[1]);
  else
    total_threads = std::thread::hardware_concurrency();

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

  return 0;
}
