//
// Copyright (C) 2013 Mateusz Loskot <mateusz@loskot.net>
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//
#include "json_benchmark.hpp"
#include <json/json.h> // jsoncpp
int main()
{
    try
    {
        jsonbench::run_benchmark("jsoncpp", [](std::string const& s) {
            Json::Value jv;
            Json::Reader jr;
#ifdef JSON_BENCHMARK_DUMP_PARSED_JSON
            Json::FastWriter jw;
            std::cout << jw.write(jv) << std::endl;
#endif
            return jr.parse(s, jv) && jv.type() != Json::nullValue;
        });

        return EXIT_SUCCESS;
    }
    catch (std::exception const& e)
    {
        std::cerr << e.what() <<std::endl;
    }
    return EXIT_FAILURE;
}
