// number adapter

boolean NumberAdapter::toBoolean(var &value) {
  return getNumber(value) == 0 ? false : true;
}

string NumberAdapter::toString(var &value) {
  string &stringValue = getString(value);
  ostringstream ss;
  stringValue = ss << getNumber(value) ? ss.str() : "NaN";
  return stringValue;
}
