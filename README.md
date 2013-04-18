json_benchmark
==============

Simple benchmark for a number of C++ JSON libraries.

List of currently measured libraries: 

* [casablanca](https://casablanca.codeplex.com/) - C++ REST SDK (codename "Casablanca")
* [json_spirit](https://github.com/cierelabs/json_spirit)
* [jsoncpp](http://jsoncpp.sourceforge.net/)
* [libjson](http://sourceforge.net/projects/libjson/)
* [rapidjson](http://code.google.com/p/rapidjson/)

Disclaimer
----------

I created this benchmark driven by curiosity and for my own purposes, with hope to 
obtain useful and interesting results, for myself and others too.
I do not have any objective of making ultimate performance shootout.
This is not a rocket science, but a simple set of C++ programs, with likelyhood
of bugs or inconsistencies. Found any, please report. Comments and improvements
are always welcome!

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


Note, all libraries are used to read and parse strings of narrow ```char``` 
characters (```std::string```), no ```wchar_t``` strings are used.

Visual C++ 11.0
---------------

* small

```
rapidjson.small:  2 marks of 1000 x 500 batch of parsings in 0.961858 to 0.962361 per batch
libjson.small:    2 marks of 1000 x 500 batch of parsings in 5.2787 to 5.29663 per batch
jsoncpp.small:    2 marks of 1000 x 500 batch of parsings in 5.762 to 5.77978 per batch
casablanca.small: 2 marks of 1000 x 500 batch of parsings in 17.7374 to 17.7587 per batch
spirit.small:     2 marks of 1000 x 500 batch of parsings in 22.137 to 22.137 per batch
```
* large

```
rapidjson.large:  2 marks of 1000 x 1 batch of parsings in 7.96621 to 7.97555 sec per batch
libjson.large:    2 marks of 1000 x 1 batch of parsings in 240.289 to 240.289 sec per batch
```

Notes:
* rapidjson was used in DOM parsing mode, not SAX
* libjson supports lazy parsing, times collected for this modes was:
```
libjson.small:    2 marks of 1000 x 500 batch of parsings in 0.478065 to 0.486636 per batch
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
b2 -sBOOST_ROOT=/home/mloskot/boost/trunk -sJSON_SPIRIT_ROOT=/home/mloskot/json_spirit
```
and so on.

Or, simply edit ```Jamroot``` file.

License
=======

Distributed under the Boost Software License, Version 1.0.
See accompanying file LICENSE_1_0.txt or copy at 
http://www.boost.org/LICENSE_1_0.txt.

Copyright
=========

Copyright 2013 Mateusz Loskot <mateusz at loskot dot net>

and others (see copyright headers in source files).
