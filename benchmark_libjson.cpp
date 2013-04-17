//
// Copyright (C) 2013 Mateusz Loskot <mateusz@loskot.net>
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//
#include "json_benchmark.hpp"
#include <libjson/libjson.h>
namespace jb = jsonbench;
int main()
{
    try
    {
        //auto const jsons = jb::get_one_json_per_line();
        auto const jsons = jb::get_json();
        auto const marks = jb::benchmark(jsons, [](std::string const& s) -> bool {
            auto jv = libjson::parse(s.c_str());
#ifdef JSON_BENCHMARK_DUMP_PARSED_JSON
            std::cout << jv.write() << std::endl;
#endif
            return jv.type() != JSON_NULL;
        });

        jb::print_result(std::cout << "libjson: ", marks);
        return EXIT_SUCCESS;
    }
    catch (std::exception const& e)
    {
        std::cerr << e.what() <<std::endl;
    }
    return EXIT_FAILURE;
}