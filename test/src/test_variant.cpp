namespace test_variant {

using namespace jsontool;

// string conversion

TEST_CASE("variant/setup", "") {

  cout << "Testing variant" << endl;

}

TEST_CASE("adapter/null/tostring", "Null to string") {

  var v;
  var v2 = null;
  var v3 = "haha";
  v3 = null;

  CHECK((string)v == "null");
  CHECK((string)v2 == "null");
  CHECK((string)v3 == "null");
  v3 = v2;
  CHECK((string)v3 == "null");

}

TEST_CASE("adapter/boolean/tostring", "Boolean to string") {

  var v = true;
  var v2 = false;

  CHECK((string)v == "true");
  CHECK((string)v2 == "false");

}

TEST_CASE("adapter/number/tostring", "Number to string") {

  var v = 123.456;
  var v2 = -8765;

  CHECK((string)v == "123.456");
  CHECK((string)v2 == "-8765");

}

TEST_CASE("adapter/string/tostring", "String to string") {

  var v = "blah";

  CHECK((string)v == "blah");

}

TEST_CASE("adapter/array/tostring", "Array to string") {

  var v = A_ {"lmno", 8, A_ {true, "3"}, 1};

  CHECK((string)v == "[\"lmno\",8,[true,\"3\"],1]");

}

TEST_CASE("adapter/object/tostring", "Object to string") {

  var v = O_ {
    { "foo", A_ {1, "b", false}},
    { "bar", O_ {
        { "x", 1.5}, {"y", null}
      }}
  };

  // object properties are sorted alphabetically!
  CHECK((string)v == "{\"bar\":{\"x\":1.5,\"y\":null},\"foo\":[1,\"b\",false]}");

}


TEST_CASE("variant/from_vector", "Variant from vector") {

  std::vector<int> vec;

  vec.push_back(1);

  var v = vec;

  CHECK((string)v == "[1]");

}


TEST_CASE("variant/from_map", "Variant from map") {

  std::map<string, int> m;

  m["a"] = 42;

  var v = m;

  CHECK((string)v == "{\"a\":42}");

}

TEST_CASE("variant/from_array", "Variant from array") {

  int iVals[] = {12, 34, 45};
  cstring cVals[] = {"FEE", "FIE", "FOE"};
  var vVals[] = {1, true, "three"};

  var v1 = iVals;
  var v2 = cVals;
  var v3 = vVals;

  CHECK((string)v1 == "[12,34,45]");
  CHECK((string)v2 == "[\"FEE\",\"FIE\",\"FOE\"]");
  CHECK((string)v3 == "[1,true,\"three\"]");

}

TEST_CASE("variant/from_2d", "Variant from 2d array") {

  var obj[][2] = { { "a", 12 }, { "b", 22 }, { "c", 34 } };

  var v1 = obj;

  CHECK((string)v1 == "{\"a\":12,\"b\":22,\"c\":34}");

}

}
