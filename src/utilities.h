/*
 * utilities.h
 *
 *  Created on: May 31, 2018
 *      Author: lake
 */

#ifndef UTILITIES_H_
#define UTILITIES_H_

#include <string>
#include <cstdio>
#include <memory>

template<typename ... Ts>
std::string fmt(const std::string &fmt, Ts ... vs)
{
    size_t required = std::snprintf(nullptr, 0, fmt.c_str(), vs...) + 1;
    std::unique_ptr<char[]> buf(new char[required]);
    std::snprintf(buf.get(), required, fmt.c_str(), vs...);
    return std::string(buf.get(), buf.get() + required - 1);
}

#endif /* UTILITIES_H_ */
