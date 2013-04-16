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
#include <string>
#include <tuple>
#include <vector>
#include <utility>
#include "high_resolution_timer.hpp"

namespace jsonbench
{
std::size_t const MAX_ITERATIONS = 100;

typedef std::tuple<std::size_t, std::size_t, double, double> result_t;

template <typename Result>
inline std::ostream& print_result(std::ostream& os, Result r)
{
    using std::get;
    os << get<1>(r) << " x " << get<0>(r) << " iterations in " << get<2>(r) << " to " << get<3>(r) << std::endl;
    return os;
}

template <typename Result, typename Timer>
inline void set_result(Result& m, Timer const& t)
{
    using std::get;
    get<2>(m) = t.elapsed();
    get<3>(m) = (std::max)(get<2>(m), get<3>(m));
    get<2>(m) = (std::min)(get<2>(m), get<3>(m));
    std::get<1>(m) += 1;
}

template <typename Container, typename Parse>
inline result_t benchmark(std::size_t iterations, Container jsons, Parse parse)
{
    result_t m;
    std::get<0>(m) = jsons.size();
    std::sort(jsons.begin(), jsons.end());
    std::size_t rep = 0;
    do
    {
        util::high_resolution_timer t;
        for (auto const& s : jsons)
        {
            if (!parse(s))
                throw __LINE__;
        }
        set_result(m, t);
        rep++;
    } while (rep < iterations && std::next_permutation(jsons.begin(), jsons.end()));
    return m;
}

typedef std::vector<std::string> jsons_t;

inline jsons_t load_data(std::string file)
{
    jsons_t v;
    std::ifstream ifs(file);
    for (std::string line; std::getline(ifs, line); )
        v.push_back(line);
    return v;
}

inline jsons_t get_one_json_per_line()
{
    return load_data("data/one-json-per-line.txt");
}

}

#endif MLOSKOT_JSON_BENCHMARK_HPP_INCLUDED

