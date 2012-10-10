
// array adapter

number ArrayAdapter::toNumber(var &value) {
  return 0; // FIXME
}

boolean ArrayAdapter::toBoolean(var &) {
  return true;
}

string ArrayAdapter::toString(var &value) {

  Array &arrayValue = getArray(value);
  string &stringValue = getString(value);

  ostringstream ss;

  ss << "[";

  for (Array::iterator it = arrayValue.begin(); it != arrayValue.end(); ++it) {

    var& item = *it;

    if (it != arrayValue.begin())
      ss << ",";

    ss << stringify(item);

  }

  ss << "]";

  stringValue = ss.str();

  return stringValue;

}

var& ArrayAdapter::subscript(var &value, var key) {

  Array &arrayValue = getArray(value);

  return key < arrayValue.size() ? arrayValue[key] : setTemp(value, key);

}

void ArrayAdapter::promoteTemp(var &value) {

  unsigned index = (var)getTempKey(value);
  Array &a = getArray(getParent(value));

  a.resize(index + 1);
  a[index] = value;
  // TODO: remove temporary value
  // parent->tempKeys.erase((string)(var)tempArrayKey);

}
