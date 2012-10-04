
// number adapter

boolean NumberAdapter::toBoolean(var &value) {
  return value.numberValue == 0 ? false : true;
}

string NumberAdapter::toString(var &value) {
  ostringstream ss;
  value.stringValue = ss << value.numberValue ? ss.str() : "NaN";
  return value.stringValue.c_str();
}
