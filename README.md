# jsontool

Single-header C++ JSON library.

## Overview

jsontool provides a simple API for producing and consuming JSON data:

- `jsontool::var`: a variant class representing a piece of JSON data.
- `jsontool::parse`: convert a JSON string to a `jsontool::var`.
- `jsontool::stringify`: convert a `jsontool::var` to a JSON string.

## Usage

### Consuming JSON data

Use the `parse` function to create a `var` object from a string. 
Access its members using subscript notation (square brackets).

    #include "jsontool.h"
    // ...
    std::string json = "[1, true, \"three\"]";  // some test data
    jsontool::var data = jsontool::parse(json); // parse it
    cout << data[2] << endl;                    // output: three

Assignment, cast and comparison operators behave as closely as possible to 
ECMA-262 standard, 5th edition. For example, objects and arrays are copied 
by reference, while primitives are copied by value. The `==` operator uses 
the abstract comparison algorithm, so `0` is equal to `false`, `1` is equal 
to `true`, `33` is equal to `"33"`, and so on.

`jsontool::var` exposes the following methods to check the internal data type:

    inline bool isUndefined();
    inline bool isNull();
    inline bool isBoolean();
    inline bool isNumber();
    inline bool isString();
    inline bool isObject();
    inline bool isArray();

Internally, jsontool stores JSON arrays as `std::vector<jsontool::var>` 
and JSON objects as `std::map<std::string, jsontool::var>`, 
and variants will convert automatically to these types for member
iteration and advanced manipulation.

TODO: write example

### Producing JSON data

Use the `parse` function to produce a `var` object from a string. 

TODO: write docs
TODO: write example