namespace test_parser {

using namespace jsontool;

// parser stuff

TEST_CASE("parser/setup", "") {

  cout << "Testing parser" << endl;

}

TEST_CASE("parser/number", "") {

  string test = "123.456";
  var result = parse(test);

  CHECK(result == 123.456);
  CHECK(result == test);

}

TEST_CASE("parser/string", "") {

  string test = "\"abc\"";
  string result = parse(test);

  CHECK(result == "abc");

}

TEST_CASE("parser/array", "") {

  string test = "[\"ha\",123,7.89,\"he\"]";
  string result = parse(test);

  CHECK(test == result);

}

TEST_CASE("parser/array2", "") {

  string test = "[\"ha\",123,456,7.89]";
  string result = parse(test);

  CHECK(test == result);

}

TEST_CASE("parser/array3", "") {

  string test = "[\"ha\"]";
  string result = parse(test);

  CHECK(test == result);

}

TEST_CASE("parser/array4", "") {

  string test = "[123.456]";
  string result = parse(test);

  CHECK(test == result);

}

TEST_CASE("parser/array5", "") {

  string test = "[123.456,null]";
  string result = parse(test);

  CHECK(test == result);

}

TEST_CASE("parser/error", "") {

  string test = "[123.456,noun]";

  CHECK_THROWS_AS(parse(test), ParseError);

  test = "[123.456,argh]";

  CHECK_THROWS_AS(parse(test), ParseError);

}

TEST_CASE("parser/object", "") {

  string test = "{\"foo\":\"abc\",\"goo\":\"xyz\"}";
  string result = parse(test);

  CHECK(test == result);

}

TEST_CASE("parser/quoted_string", "") {

  string test = "\"a \\\"b\\\" c\"";
  var result = parse(test);

  CHECK((string)result == "a \"b\" c");

  CHECK(stringify(result) == test);

}

TEST_CASE("parser/array/quoted_string", "") {

  string test = "{\"x\":\"a \\\"b\\\" c\"}";
  string result = parse(test);

  CHECK(test == result);

}

// namespace
}
