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
standard ECMA-262, edition 5. For example, objects and arrays are copied 
by reference, while primitives are copied by value. The `==` operator uses 
the abstract comparison algorithm, so `0` is equal to `false`, `1` is equal 
to `true`, `33` is equal to `"33"`, and so on.

The `var` class exposes the following methods to check the internal data type:

    inline bool isUndefined();
    inline bool isNull();
    inline bool isBoolean();
    inline bool isNumber();
    inline bool isString();
    inline bool isObject();
    inline bool isArray();

Internally, jsontool stores array data as `vector<var>` and object data as 
`map<string, var>`, and variants will cast to these types for member iteration.

    using namespace std;
    using namespace jsontool;
    
    string json = "{ \"x\": 32.1, \"y\": 78.9 }";   // some test data
    map<string, var> data = parse(json);            // parse it
    map<string, var>::iterator i;                   // map iterator
    for (i = data.begin(); i != data.end(); ++i) {  // iterate
        cout << i->first << endl;                   // output: x, y
        cout << i->second << endl;                  // output: 32.1, 78.9
    }


`jsontool::Array` and `jsontool::Object` can be used as aliases for 
`vector<var>` and `map<string, var>`, respectively.

### Producing JSON data

Use the `stringify` function to convert a `var` object to a JSON string. 

TODO: write docs

TODO: write example