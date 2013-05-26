//
// Copyright (C) 2013 Jeff Trull <jetrull@sbcglobal.net>
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//


#include "json_benchmark.hpp"

#include <QJsonDocument>


int main() {
    try
    {
        jsonbench::run_benchmark("QJsonDocument", [](std::string const& s) {
            QJsonParseError err;
            return !QJsonDocument::fromJson(s.c_str(), &err).isNull() && (err.error == QJsonParseError::NoError);
        });

        return EXIT_SUCCESS;
    }
    catch (std::exception const& e)
    {
        std::cerr << e.what() <<std::endl;
    }
    return EXIT_FAILURE;

}

