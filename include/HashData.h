//
// Created by elisey on 28.12.2020.
//

#ifndef LAB_06_MULTITHREADS_HASHDATA_H
#define LAB_06_MULTITHREADS_HASHDATA_H

#include <ctime>
#include <mutex>
#include <random>
#include <string>
#include <thread>
#include <vector>

#include "boost/log/trivial.hpp"
#include "picosha2.h"

class HashData {
 public:
  size_t time;
  std::string hash;
  std::string data;

  HashData() = default;
  HashData(const HashData& hd);
  HashData(size_t t, std::string h, std::string d);

  // std::ostream& operator<<(const HashData& hd,std::ostream out);
};

HashData::HashData(const HashData& hd)
    : time(hd.time), hash(hd.hash), data(hd.data) {}

HashData::HashData(size_t t, std::string h, std::string d)
    : time(t), hash(h), data(d) {}

std::ostream& operator<<(std::ostream& out, const HashData& hd) {
  out << "time: " << hd.time << std::endl
      << "hash: " << hd.hash << std::endl
      << "data: " << hd.data;
  return out;
}

bool is_right_hash(const std::string& str) {
  std::string substr = "0000";
  auto pos = str.find(substr, str.size() - 4);
  return pos != std::string::npos;
}

std::string RandData() { return std::to_string(rand()); }

std::mutex mtx;

std::vector<HashData> hashes;

HashData FindHash() {
  HashData hd;
  size_t start_time = clock();
  // for (;;) {
  hd.data = RandData();
  picosha2::hash256_hex_string(hd.data, hd.hash);
  if (is_right_hash(hd.hash)) {
    size_t end_time = clock();
    hd.time = end_time - start_time;
    BOOST_LOG_TRIVIAL(info)
        << "thread id" << std::this_thread::get_id() << std::endl
        << "time: " << hd.time << std::endl
        << "hash: " << hd.hash << std::endl
        << "data: " << hd.data;
    mtx.lock();
    // Write to file
    HashData right_hash(hd.time, hd.hash, hd.data);
    hashes.push_back(right_hash);
    mtx.unlock();
  }
  //}
  return hd;
}

#endif  // LAB_06_MULTITHREADS_HASHDATA_H
