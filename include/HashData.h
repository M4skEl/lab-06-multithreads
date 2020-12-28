//
// Created by elisey on 28.12.2020.
//

#ifndef LAB_06_MULTITHREADS_HASHDATA_H
#define LAB_06_MULTITHREADS_HASHDATA_H

#include <string>

#include "picosha2.h"

class HashData {
 public:
  size_t time;
  std::string hash;
  std::string data;

  HashData();
  HashData(const HashData& hd);
  HashData(size_t t, std::string& h, std::string& d);
};



#endif  // LAB_06_MULTITHREADS_HASHDATA_H
