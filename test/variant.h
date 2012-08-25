
#include "jsontool.h"

using namespace jsontool;

// string conversion

TEST_CASE("variant/equality", "operator ==") {

  var v = 1;
  var v2 = true;
  
  REQUIRE(v == true);
  REQUIRE(v != false);
  
  v = 2; 
  
  REQUIRE(v != true);
  REQUIRE(v != false);
  
  v = "3.0";
  
  REQUIRE(v == 3);
  REQUIRE(v != 4);
  
  v = 3.0;
  
  REQUIRE(v == "3");
  REQUIRE(v != "4");
  
  v = "haha";
  v2 = "haha";
  
  REQUIRE(v == v2);
  
  v2 = "hehe";
  
  REQUIRE(v != v2);
  
  v = A_{ 1, true, "three" };
  
  v2 = A_{ 1, true, "three" };
  
  REQUIRE(v != v2);
  
  v2 = v;
  
  //v2[0] = 2;
  
  cout << "v: " << v << endl;
  cout << "v2: " << v2 << endl;
  
  // REQUIRE(v[0] == 2);
  REQUIRE(v == v2);

}

TEST_CASE("adapter/null/tostring", "Null to string") {

  var v;
  var v2 = null;
  var v3 = "haha";
  v3 = null;
  
  // cout << v << endl;
  
  REQUIRE((string)v == "null");
  REQUIRE((string)v2 == "null");
  REQUIRE((string)v3 == "null");
  v3 = v2;
  REQUIRE((string)v3 == "null");

}

TEST_CASE("adapter/boolean/tostring", "Boolean to string") {

  var v = true;
  var v2 = false;
  
  REQUIRE((string)v == "true");
  REQUIRE((string)v2 == "false");

}

TEST_CASE("adapter/number/tostring", "Number to string") {

  var v = 123.456;
  var v2 = -8765;
  
  REQUIRE((string)v == "123.456");
  REQUIRE((string)v2 == "-8765"); 

}

TEST_CASE("adapter/string/tostring", "String to string") {

  var v = "blah";
  
  REQUIRE((string)v == "blah");

}

TEST_CASE("adapter/array/tostring", "Array to string") {

  var v = A_{ "lmno", 8, A_{ true, "3" }, 1 };
  
  REQUIRE((string)v == "[\"lmno\",8,[true,\"3\"],1]");

}

TEST_CASE("adapter/object/tostring", "Object to string") {

  var v = O_{ 
    { "foo", A_{ 1, "b", false } }, 
    { "bar", O_{ 
      { "x", 1.5 }, { "y", null } 
    } } 
    };
  
  // object properties are sorted alphabetically!
  REQUIRE((string)v == "{\"bar\":{\"x\":1.5,\"y\":null},\"foo\":[1,\"b\",false]}"); 

}



