//
// Created by elisey on 28.12.2020.
//

#include "HashData.h"

HashData::HashData() : time(0), hash("0"), data("0") {}

HashData::HashData(const HashData& hd)
    : time(hd.time), hash(hd.hash), data(hd.data) {}

HashData::HashData(size_t t, std::string& h, std::string& d)
    : time(t), hash(h), data(d) {}

HashData FindHash(){



}

