// defaults (undefined and null)

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
  return (string)value;
}

