//
// Copyright (C) 2013 Mateusz Loskot <mateusz@loskot.net>
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//
#include "json_benchmark.hpp"
#include <rapidjson/rapidjson.h>
#include <rapidjson/document.h>
#include <rapidjson/filestream.h>
#include <rapidjson/prettywriter.h>
namespace rj = rapidjson;
namespace jb = jsonbench;
int main()
{
    try
    {
        //auto const jsons = jb::get_one_json_per_line();
        auto const jsons = jb::get_json();
        auto const marks = jb::benchmark(jsons, [](std::string const& s) {
            rj::Document d;
            d.Parse<0>(s.c_str());
#ifdef JSON_BENCHMARK_DUMP_PARSED_JSON
            rj::FileStream f(stdout);
            rj::PrettyWriter<rj::FileStream> writer(f);
            d.Accept(writer);
#endif
            return !d.IsNull();
        });

        jb::print_result(std::cout << "rapidjson: ", marks);
        return EXIT_SUCCESS;
    }
    catch (std::exception const& e)
    {
        std::cerr << e.what() <<std::endl;
    }
    return EXIT_FAILURE;
}
