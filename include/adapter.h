class TypeAdapter {

public:

  var* value;

  ValueType type;

  virtual boolean toBoolean(var &);

  virtual number toNumber(var &);

  virtual string toString(var &);

  virtual string toJSON(var &);

  TypeAdapter() :
    type(TYPE_UNDEFINED) {
  }

};

class UndefinedAdapter: public TypeAdapter {

public:

  UndefinedAdapter() :
    TypeAdapter() {
    type = TYPE_UNDEFINED;
  }

};

class NullAdapter: public TypeAdapter {

public:

  NullAdapter() :
    TypeAdapter() {
    type = TYPE_NULL;
  }

};

class BooleanAdapter: public TypeAdapter {

public:

  number toNumber(var &);
  string toString(var &);
  BooleanAdapter() :
    TypeAdapter() {
    type = TYPE_BOOLEAN;
  }

};

class NumberAdapter: public TypeAdapter {

public:

  boolean toBoolean(var &);
  string toString(var &);

  NumberAdapter() :
    TypeAdapter() {
    type = TYPE_NUMBER;
  }

};

class StringAdapter: public TypeAdapter {

public:

  boolean toBoolean(var &);
  number toNumber(var &);
  string toJSON(var &);

  StringAdapter() :
    TypeAdapter() {
    type = TYPE_STRING;
  }

};

class ObjectAdapter: public TypeAdapter {

public:

  boolean toBoolean(var &);
  number toNumber(var &);
  string toString(var &);

  ObjectAdapter() :
    TypeAdapter() {
    type = TYPE_OBJECT;
  }

};

class ArrayAdapter: public TypeAdapter {

public:

  boolean toBoolean(var &);
  number toNumber(var &);
  string toString(var &);

  ArrayAdapter() :
    TypeAdapter() {
    type = TYPE_ARRAY;
  }

};
