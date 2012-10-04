namespace test_compare {

using namespace jsontool;

TEST_CASE("compare/setup", "") {

  cout << "Testing compare" << endl;

}

TEST_CASE("compare/relational", "Relational operators") {

  var v;
  var v2;

  v = "apple";
  v2 = "banana";

  CHECK(v < v2);
  CHECK(v <= v2);

  CHECK(v2 > v);
  CHECK(v2 >= v);

  v = "foo";
  v2 = "foo";

  CHECK(v2 >= v);
  CHECK(v2 <= v);
  CHECK(v >= v2);
  CHECK(v <= v2);

  v = 3;
  v2 = 5.5;

  CHECK(v < v2);
  CHECK(v <= v2);

  CHECK(v2 > v);
  CHECK(v2 >= v);

}

TEST_CASE("compare/equality", "Abstract equality operators") {

  var v = 1;
  var v2 = true;

  CHECK(v == true);
  CHECK(v != false);

  v = 2;

  CHECK(v != true);
  CHECK(v != false);

  v = "3.0";

  CHECK(v == 3);
  CHECK(v != 4);

  v = 3.0;

  CHECK(v == "3");
  CHECK(v != "4");

  v = "haha";
  v2 = "haha";

  CHECK(v == v2);

  v2 = "hehe";

  CHECK(v != v2);

  v = A_ {1, true, "three"};

  v2 = A_ {1, true, "three"};

  CHECK(v != v2);

  v2 = v;

  v2[0] = 2;

  CHECK(v[0] == 2);
  CHECK(v == v2);

  v2[6] = "foo";

  cout << v2 << endl;

}

}
