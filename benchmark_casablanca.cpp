//
// Copyright (C) 2013 Mateusz Loskot <mateusz@loskot.net>
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//
#include "json_benchmark.hpp"
#include  <json.h> // casablanca
namespace jb = jsonbench;
namespace wj = web::json;
int main()
{
    try
    {
        //auto const jsons = jb::get_one_json_per_line();
        auto const jsons = jb::get_json();
        auto const marks = jb::benchmark(jsons, [](std::string const& s) {
            std::stringstream ss;
            ss << s;
            wj::value jv = wj::value::parse(ss);
#ifdef JSON_BENCHMARK_DUMP_PARSED_JSON
            jv.serialize(std::cout);
#endif
            return !jv.is_null();
        });

        jb::print_result(std::cout << "casablanca: ", marks);
        return EXIT_SUCCESS;
    }
    catch (std::exception const& e)
    {
        std::cerr << e.what() <<std::endl;
    }
    return EXIT_FAILURE;
}
