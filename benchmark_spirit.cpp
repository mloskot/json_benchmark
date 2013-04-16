//
// Copyright (C) 2013 Mateusz Loskot <mateusz@loskot.net>
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy 
// at http://www.boost.org/LICENSE_1_0.txt)
//
#include "json_benchmark.hpp"
#include <ciere/json/value.hpp>
#include <ciere/json/io.hpp>
namespace jb = jsonbench;
namespace cj = ciere::json;
int main()
{
    try
    {
        auto const jsons = jb::get_jsons();
        auto r = jb::benchmark(jb::MAX_ITERATIONS, jsons, [](std::string const& s) {
            cj::value jv;
            return cj::construct(s, jv);
            //return cj::construct(s.cbegin(), s.cend(), jv);
            //std::cout << jv << '\n';
            //return jv.type() != cj::null_type;
        });

        jb::print_result(std::cout << "spirit: ", r);
    }
    catch (...)
    {
        std::cerr << "error\n";
    }
    return 0;
}
