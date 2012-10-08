
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
