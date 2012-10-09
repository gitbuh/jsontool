
// array adapter

number ArrayAdapter::toNumber(var &value) {
  return 0; // FIXME
}

boolean ArrayAdapter::toBoolean(var &) {
  return true;
}

string ArrayAdapter::toString(var &value) {

  ostringstream ss;

  ss << "[";

  for (Array::iterator it = value.arrayValue->begin(); it
      != value.arrayValue->end(); ++it) {

    var& item = *it;

    if (it != value.arrayValue->begin())
      ss << ",";

    ss << stringify(item);

  }

  ss << "]";

  value.stringValue = ss.str();

  return value.stringValue.c_str();

}

var& ArrayAdapter::subscript(var &value, var key) {

  Array &arrayValue = *value.arrayValue;

  return key < arrayValue.size() ? arrayValue[key] : setTemp(value, key);

}

void ArrayAdapter::promoteTemp(var &value) {

  unsigned index = (var)getTempKey(value);
  Array &a = *getParent(value).arrayValue;

  a.resize(index + 1);
  a[index] = value;
  // TODO: remove temporary value
  // parent->tempKeys.erase((string)(var)tempArrayKey);

}
