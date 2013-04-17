//
// Copyright (C) 2013 Mateusz Loskot <mateusz@loskot.net>
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy 
// at http://www.boost.org/LICENSE_1_0.txt)
//
#ifndef MLOSKOT_JSON_BENCHMARK_HPP_INCLUDED
#define MLOSKOT_JSON_BENCHMARK_HPP_INCLUDED
#include <algorithm>
#include <cassert>
#include <fstream>
#include <iostream>
#include <sstream>
#include <stdexcept>
#include <string>
#include <tuple>
#include <vector>
#include <utility>
#include "high_resolution_timer.hpp"

// Uncomment to print all tested JSON data to stdout
#ifndef JSON_BENCHMARK_DUMP_PARSED_JSON
//#define JSON_BENCHMARK_DUMP_PARSED_JSON
#endif

namespace jsonbench
{

//
// Default benchmark settings
//
std::size_t max_marks = 10;
std::size_t max_iterations = 1000;

//
// Routines handling test data files
//
typedef std::vector<std::string> jsons_t;

inline jsons_t load_json(std::string file)
{
    typedef std::string::value_type char_t;
    typedef std::istreambuf_iterator<char_t> iterator_t;

    jsons_t v;
    std::ifstream ifs(file);
    v.push_back(std::string(iterator_t(ifs), (iterator_t())));
    return v; 
}

inline jsons_t load_jsons(std::string file)
{
    jsons_t v;
    std::ifstream ifs(file);
    for (std::string line; std::getline(ifs, line); )
        v.push_back(line);
    return v;
}

// load single large JSON string
inline jsons_t get_large()
{
    return load_json("data/canada.json");
}

// load collection of small to medium size JSON strings
inline jsons_t get_small()
{
    return load_jsons("data/one-json-per-line.jsons");
}

//
// Benchmark running routines
//
typedef std::tuple<std::size_t, std::size_t, std::size_t, double, double> result_t;

template <typename Result>
inline std::ostream& print_result(std::ostream& os, Result r)
{
    using std::get;
    os << get<1>(r) << " iterations of " << get<2>(r) << " parsings in " 
        << get<3>(r) << " to " << get<4>(r) << " sec based on " 
        << get<0>(r) << " benchmarks" << std::endl;
    return os;
}

template <typename Result, typename Timer>
inline void set_mark(Result& r, Timer const& t)
{
    using std::get;
    get<3>(r) = t.elapsed();
    get<4>(r) = (std::max)(get<3>(r), get<4>(r));
    get<3>(r) = (std::min)(get<3>(r), get<4>(r));
}

template <typename Container, typename Parse>
inline result_t benchmark(std::size_t marks, std::size_t iterations, Container const& jsons, Parse parse)
{
    result_t r;
    std::get<0>(r) = marks;
    std::get<1>(r) = iterations;
    std::get<2>(r) = jsons.size(); // batch size per iteration

    for (decltype(marks) m = 0; m < marks; ++m)
    {
        util::high_resolution_timer t;
        for (decltype(iterations) i = 0U; i < iterations; ++i)
        {
            for (auto const& s : jsons)
            {
                if (!parse(s))
                    throw std::runtime_error("parse failed");
            }
        }
        set_mark(r, t);
    }
    return r;
}

template <typename Container, typename Parse>
inline result_t benchmark(Container const& jsons, Parse parse)
{
    return benchmark(max_marks, max_iterations, jsons, parse);
}

template <typename Parse>
inline void run_benchmark(char const* name, Parse parse)
{
    {
        auto const marks = benchmark(max_marks, max_iterations, get_small(), parse);
        print_result(std::cout << name << ".small: ", marks);
    }
    {
        auto const marks = benchmark(max_marks, max_iterations, get_large(), parse);
        print_result(std::cout << name << ".large: ", marks);
    }
}

} // namespace jsonbench

#endif
