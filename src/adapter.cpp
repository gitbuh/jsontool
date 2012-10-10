/**
 * Type adapter
 */

// final

boolean &TypeAdapter::getBoolean(var &value) {
  return value.booleanValue;
}

number &TypeAdapter::getNumber(var &value) {
  return value.numberValue;
}

string &TypeAdapter::getString(var &value) {
  return value.stringValue;
}

Object &TypeAdapter::getObject(var &value) {
  return *value.objectValue;
}

Array &TypeAdapter::getArray(var &value) {
  return *value.arrayValue;
}

var &TypeAdapter::setTemp(var &value, string key) {

  value.tempKeys[key] = var();
  value.tempKeys[key].isTemp = true;
  value.tempKeys[key].parent = (&value);
  value.tempKeys[key].tempKey = key;
  return value.tempKeys[key];

}

void TypeAdapter::promoteTemp(var &value) {

}

// virtual

boolean TypeAdapter::toBoolean(var &value) {
  return value.booleanValue;
}

number TypeAdapter::toNumber(var &value) {
  return value.numberValue;
}

string TypeAdapter::toString(var &value) {
  return value.stringValue.c_str();
}

string TypeAdapter::toJSON(var &value) {
  return (string) value;
}

var &TypeAdapter::subscript(var &, var) {
  static var undefined;
  return undefined;
}

string &TypeAdapter::getTempKey(var &value) {

  return value.tempKey;

}

var &TypeAdapter::getParent(var &value) {

  return *value.parent;

}
