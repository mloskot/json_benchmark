json_benchmark
==============

Simple benchmark for a number of C++ JSON libraries.

List of currently measured libraries: 

* [casablanca](https://casablanca.codeplex.com/) - C++ REST SDK (codename "Casablanca")
* [json_spirit](https://github.com/cierelabs/json_spirit)
* [jsoncpp](http://jsoncpp.sourceforge.net/)
* [libjson](http://sourceforge.net/projects/libjson/)
* [rapidjson](http://code.google.com/p/rapidjson/)

Benchmark
=========

Reading
-------

Recorded are elapsed times of parsing/reading/consuming JSON string and
constructing corresponding value object in memory of type as defined 
by interface of a particular library.

Single mark of elapsed time is collected for ```I``` iterations of ```P``` parsings.
Each mark is repeated ```M``` times in order to obtain lowest and highest timing.

For example, if there are ```P``` JSON different strings loaded into test data container,
and all strings are parsed ```I``` times, total elapsed time of all ```I x P```
parsings is measured; this is repeated ```M``` times.

There are two sets of JSON test data:
* single large JSON object
  * ```data/canada.json``` contains contour of Canada border in [GeoJSON](http://geojson.org)
* collection of small JSON objects:
  * ```data/one-json-per-line.jsons``` collection of 500 sample JSON strings from sub-100 to 500 characters long.


Writing
-------

*TODO*

Results
======= 


Building
========

Boost.Build configuration is provided and it assumes either your ```user-config.jam``` 
file has ```use-project``` entry for [Boost](http://boost.org) (headers are required)
and for every JSON library. For example:

```
use-project /boost : /home/mloskot/boost/trunk ;
use-project /json_spirit  : /home/mloskot/json_spirit ;
```

Alternatively, set the environment variables:
* ```BOOST_ROOT``` for Boost
* ```<LIBRARY_NAME>_ROOT``` for each library.

The environment variables can be passed directly on the Boost.Build invocation:
```
b2 -sBOOST_ROOT=/home/mloskot/boost/trunk -sJSON_SPIRIT_ROOT=/home/mloskot/json_spirit
```
and so on.

License
=======

Distributed under the Boost Software License, Version 1.0.
See accompanying file LICENSE_1_0.txt or copy at 
http://www.boost.org/LICENSE_1_0.txt.

Copyright
=========

Copyright 2013 Mateusz Loskot <mateusz at loskot dot net>

and others (see copyright headers in source files).
