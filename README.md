JSON Benchmark
==============

---------------------------------------

**NOTE: This benchmark is not actively maintained has been superseded by Milo's [Native JSON Benchmark]**

---------------------------------------


Simple benchmark for a number of **C++** **JSON** libraries.

List of currently measured libraries: 

* [casablanca](https://casablanca.codeplex.com/) - C++ REST SDK (codename "Casablanca")
* [json_spirit](https://github.com/cierelabs/json_spirit)
* [jsoncpp](http://jsoncpp.sourceforge.net/)
* [libjson](http://sourceforge.net/projects/libjson/)
* [rapidjson](http://code.google.com/p/rapidjson/)
* [QJsonDocument](http://qt-project.org/doc/qt-5.0/qtcore/qjsondocument.html)

Requirements
* C++11 compiler
* Boost headers
* 
There are no C libraries included in this benchmark, but feel free if you'd like to
contribute some (obviously, a C++ wrapper would be required).

JSON Reading
============

Recorded are elapsed times of parsing/reading/consuming JSON string and
constructing corresponding value object in memory of type as defined 
by interface of a particular library.

Single mark of elapsed time is collected for ```I``` iterations of ```P``` parsings.
Each mark is repeated ```M``` times in order to obtain lowest and highest timing.

For example, if there are ```P``` JSON different strings loaded into test data container,
and all strings are parsed ```I``` times, total elapsed time of all ```I x P```
parsings is measured; this is repeated ```M``` times.

There are two sets of JSON test data:
* **large** - single large JSON object
  * ```data/canada.json``` contains contour of Canada border in [GeoJSON](http://geojson.org)
* **small** - collection of small JSON objects:
  * ```data/one-json-per-line.jsons``` collection of 500 sample JSON strings from sub-100 to 500 characters long.


Important notes:
* All timings obtained running optimised builds of the binaries.
* All libraries are used to read and parse strings of narrow ```char``` 
characters (i.e. ```std::string```), no ```wchar_t``` strings are used.
* rapidjson was used in DOM parsing mode, not SAX
* libjson supports lazy parsing, times collected for this modes was:
```
libjson.small: 1000 iterations of 500 parsings in 0.478065 to 0.486636 sec based on 2 benchmarks
```

GCC 4.7 (64-bit build)
----------------------

HW: Intel(R) Xeon(R) CPU E5-2630L 0 @ 2.00GHz, 2 GB RAM;
OS: Linux 64-bit (Debian 7)
    
* small

```
rapidjson.small: 1000 iterations of 500 parsings in 1.08639 to 1.08639 sec based on 2 benchmarks
jsoncpp.small:   1000 iterations of 500 parsings in 18.5563 to 19.6208 sec based on 2 benchmarks
spirit.small:    1000 iterations of 500 parsings in 27.4479 to 27.4479 sec based on 2 benchmarks
```

* large

```
rapidjson.large: 1000 iterations of 1 parsings in 13.8156 to 14.2241 sec based on 2 benchmarks
jsoncpp.large:   1000 iterations of 1 parsings in 376.313 to 384.015 sec based on 2 benchmarks
spirit.large:    1000 iterations of 1 parsings in 988.167 to 995.634 sec based on 2 benchmarks
```

Visual C++ 11.0 (32-bit build)
------------------------------

HW: Intel(R) Xeon(R) CPU E5-2687W 0 @ 3.10GHz, 16 GB RAM;
OS: Windows 7 64-bit

* small

```
rapidjson.small:  1000 iterations of 500 parsings in 0.961858 to 0.962361 sec based on 2 benchmarks
libjson.small:    1000 iterations of 500 parsings in 5.2787 to 5.29663 sec based on 2 benchmarks
jsoncpp.small:    1000 iterations of 500 parsings in 5.762 to 5.77978 sec based on 2 benchmarks
casablanca.small: 1000 iterations of 500 parsings in 17.7374 to 17.7587 sec based on 2 benchmarks
spirit.small:     1000 iterations of 500 parsings in 22.137 to 22.137 sec based on 2 benchmarks
```

* large

```
rapidjson.large:  1000 iterations of 1 parsings in 7.96621 to 7.97555 sec based on 2 benchmarks
libjson.large:    1000 iterations of 1 parsings in 240.289 to 240.289 sec based on 2 benchmarks
```

JSON Writing
============

*TODO*

Building
========

[Boost.Build](http://www.boost.org/boost-build2/) configuration is provided and
it assumes either your ```user-config.jam``` file has ```use-project``` entry for
[Boost](http://boost.org) (headers are required) and for every JSON library. For example:

```
use-project /boost : /home/mloskot/boost/trunk ;
use-project /json_spirit  : /home/mloskot/json_spirit ;
```

Alternatively, set the environment variables:
* ```BOOST_ROOT``` for Boost
* ```<LIBRARY_NAME>_ROOT``` for each library.

The environment variables can be passed directly on the Boost.Build invocation:
```
b2 -sBOOST_ROOT=/home/mloskot/boost/trunk \
   -sJSON_SPIRIT_ROOT=/home/mloskot/json_spirit \
   -sRAPIDJSON_ROOT=/home/mloskot/rapidjson
```
and so on.

Or, simply edit ```Jamroot``` file.

In order to build the benchmark programs run:

```
b2 variant=release
```

Other Benchmarks
================

List of other benchmarks of JSON C++ libraries available on the Web:

* [Native JSON Benchmark] (https://github.com/miloyip/nativejson-benchmark) by Milo Yip (2015)
* [Thiago Macieira's benchmark](https://plus.google.com/108138837678270193032/posts/7EVTACgwtxK)

Disclaimer
==========

I created this benchmark driven by curiosity and for my own purposes, with hope to 
obtain useful and interesting results, for myself and others too.
I do not have any objective of making ultimate performance shootout.
This is not a rocket science, but a simple set of C++ programs, with likelyhood
of bugs or inconsistencies. Found any, please report. Comments and improvements
are always welcome!

License
=======

Distributed under the Boost Software License, Version 1.0.
See accompanying file LICENSE_1_0.txt or copy at 
http://www.boost.org/LICENSE_1_0.txt.

Copyright
=========

Copyright 2013 Mateusz Loskot <mateusz at loskot dot net>

and other hackers (see copyright headers in source files).
