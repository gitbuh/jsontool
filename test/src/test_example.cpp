namespace test_example {

using namespace jsontool;

// string conversion

TEST_CASE("example/setup", "") {

  cout << "Testing examples" << endl;

}

TEST_CASE("example/producing/1", "Producing JSON data 1") {

  Object result;
  string tags[] = {"good", "bad", "ugly"};

  result["id"] = 32;
  result["name"] = "Bob";
  result["tags"] = tags;

  cout << stringify(result) << endl;

  CHECK(stringify(result) == "{\"id\":32,\"name\":\"Bob\",\"tags\":[\"good\",\"bad\",\"ugly\"]}");

}

TEST_CASE("example/producing/2", "Producing JSON data 2") {

  string tags[] = { "good", "bad", "ugly" };

  var result[][2] = {
      { "id", 32 },
      { "name", "Bob" },
      { "tags", tags }
  };

  cout << stringify(result) << endl;

  CHECK(stringify(result) == "{\"id\":32,\"name\":\"Bob\",\"tags\":[\"good\",\"bad\",\"ugly\"]}");

}

}
