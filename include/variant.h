class var {

protected:

  var* parent;

  string tempKey; // string or unsigned

  Object tempKeys;

  bool isTemp;

  TypeAdapter* getAdapter(ValueType type) {

    static map<ValueType, TypeAdapter*> adapters;

    if (adapters.empty()) {

      static UndefinedAdapter a;
      static NullAdapter b;
      static BooleanAdapter c;
      static NumberAdapter d;
      static StringAdapter e;
      static ObjectAdapter f;
      static ArrayAdapter g;

      adapters[TYPE_UNDEFINED] = &a;
      adapters[TYPE_NULL] = &b;
      adapters[TYPE_BOOLEAN] = &c;
      adapters[TYPE_NUMBER] = &d;
      adapters[TYPE_STRING] = &e;
      adapters[TYPE_OBJECT] = &f;
      adapters[TYPE_ARRAY] = &g;

    }

    return adapters[type];

  }

  // initializers

  void reset() {

    booleanValue = false;
    numberValue = 0;
    stringValue = "null";

  }

  void init() {

    isTemp = false;
    isTemp= false;
    adapter = getAdapter(TYPE_UNDEFINED);

  }

  void setFromVariant(const var &value) {

    reset();
    adapter = getAdapter(TYPE_UNDEFINED);
    copy(value);

  }

  void setFromUndefined() {

    reset();
    adapter = getAdapter(TYPE_UNDEFINED);

  }

  void setFromNull() {

    reset();
    stringValue = "null";
    adapter = getAdapter(TYPE_NULL);

  }

  void setFromBoolean(boolean value) {

    reset();
    booleanValue = value;
    adapter = getAdapter(TYPE_BOOLEAN);

  }

  void setFromNumber(number value) {

    reset();
    numberValue = value;
    adapter = getAdapter(TYPE_NUMBER);

  }

  void setFromString(string value) {

    reset();
    stringValue = value;
    adapter = getAdapter(TYPE_STRING);

  }

  void setFromObject(Object value) {

    reset();
    objectValue = shared_ptr<Object> (new Object(value));
    adapter = getAdapter(TYPE_OBJECT);

  }

  void setFromArray(Array value) {

    reset();
    Array v = value;
    arrayValue = shared_ptr<Array> (new Array(value));
    adapter = getAdapter(TYPE_ARRAY);

  }

  template<typename T>
  static pair<T, T> arrayToPair(T(&p)[2]) {

    return make_pair(p[0], p[1]);
  }

  TypeAdapter* adapter;

  boolean booleanValue;

  number numberValue;

  string stringValue;

  shared_ptr<Object> objectValue;

  shared_ptr<Array> arrayValue;

public:

  friend class compare;
  friend class parser;
  friend class TypeAdapter;

  // cast operators

  operator boolean() {
    return adapter->toBoolean(*this);
  }

  operator unsigned() {
    return adapter->toNumber(*this);
  }

  operator number() {
    return adapter->toNumber(*this);
  }

  operator string() {
    return adapter->toString(*this);
  }

  operator Object() const {
    return *objectValue;
  }

  operator Array() const {
    return *arrayValue;
  }

  void checkTempMember() {

    if (isTemp) {

      isTemp = false;

      parent->adapter->promoteTemp(*this);

    }

  }

  void copy(var source) {

    adapter = source.adapter;

    booleanValue = source.booleanValue;

    numberValue = source.numberValue;

    stringValue = source.stringValue;

    objectValue = source.objectValue;

    arrayValue = source.arrayValue;

  }

  // equality operators

  template<typename T>
  bool operator ==(T val) {

    var rhs = val;
    return compare::equality(*this, rhs);

  }

  template<typename T>
  bool operator !=(T val) {

    var rhs = val;
    return !compare::equality(*this, rhs);

  }

  // http://es5.github.com/#x11.8.1

  template<typename T>
  bool operator <(T val) {

    var rhs = val;
    return compare::relation(*this, rhs);

  }

  // http://es5.github.com/#x11.8.2

  template<typename T>
  bool operator >(T val) {

    var rhs = val;
    return compare::relation(rhs, *this);

  }

  // http://es5.github.com/#x11.8.3

  template<typename T>
  bool operator <=(T val) {

    var rhs = val;
    return !compare::relation(rhs, *this);

  }

  // http://es5.github.com/#x11.8.4

  template<typename T>
  bool operator >=(T val) {

    var rhs = val;
    return !compare::relation(*this, rhs);

  }

  // assignment operators

  var operator =(var rhs) {

    copy(rhs);

    checkTempMember();

    return *this;
  }

  var operator +=(var rhs) {
    numberValue += rhs.numberValue;
    stringValue += rhs.stringValue;
    return *this;
  }

  var operator -=(var rhs) {
    numberValue -= rhs.numberValue;
    return *this;
  }

  var operator *=(var rhs) {
    numberValue *= rhs.numberValue;
    return *this;
  }

  var operator /=(var rhs) {
    numberValue /= rhs.numberValue;
    return *this;
  }

  // subscript notation

  template<typename T>
  var &operator [](const T &key) {

    return adapter->subscript(*this, key);

  }

  // ctors

  var() {

    init();
    setFromUndefined();

  }

  var(Null) {

    init();
    setFromNull();

  }

  var(bool value) {

    init();
    setFromBoolean(value);

  }

  var(long double value) {

    init();
    setFromNumber(value);

  }

  var(double value) {

    init();
    setFromNumber(value);

  }

  var(long value) {

    init();
    setFromNumber(value);

  }

  var(int value) {

    init();
    setFromNumber(value);

  }

  var(unsigned value) {

    init();
    setFromNumber(value);

  }

  var(unsigned long value) {

    init();
    setFromNumber(value);

  }

  var(cstring value) {

    init();
    setFromString(value);

  }

  var(string value) {

    init();
    setFromString(value);

  }

  var(Object value) {

    init();
    setFromObject(value);

  }

  var(Array value) {

    init();
    setFromArray(value);

  }

  // vector

  template<typename T>
  var(vector<T> value) {

    init();
    setFromArray(Array(value.begin(), value.end()));

  }

  // map

  template<typename T1, typename T2>
  var(map<T1, T2> value) {

    init();
    setFromObject(Object(value.begin(), value.end()));

  }

  // c array

  template<typename T, int N>
  var(T(& value)[N]) {

    init();
    setFromArray(Array(value, value + sizeof(value) / sizeof(T)));

  }

  // two dimensional c array

  template<typename T, int N>
  var(T(& value)[N][2]) {

    init();
    map<string, var> result;
    transform(value, value + N, inserter(result, result.begin()),
        arrayToPair<T> );
    setFromObject(result);

  }

  // type checks

  inline bool isUndefined() {

    return adapter->type == TYPE_UNDEFINED;

  }
  inline bool isNull() {

    return adapter->type == TYPE_NULL;

  }
  inline bool isBoolean() {

    return adapter->type == TYPE_BOOLEAN;

  }
  inline bool isNumber() {

    return adapter->type == TYPE_NUMBER;

  }
  inline bool isString() {

    return adapter->type == TYPE_STRING;

  }
  inline bool isObject() {

    return adapter->type == TYPE_OBJECT;

  }
  inline bool isArray() {

    return adapter->type == TYPE_ARRAY;

  }

  string toJSON() {
    return adapter->toJSON(*this);
  }

};
