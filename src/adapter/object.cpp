
// object adapter

number ObjectAdapter::toNumber(var &) {
  return 0;
}

boolean ObjectAdapter::toBoolean(var &) {
  return true;
}

string ObjectAdapter::toString(var &value) {

  ostringstream ss;

  ss << "{";

  for (Object::iterator it = value.objectValue->begin(); it
      != value.objectValue->end(); ++it) {

    var& item = it->second;

    if (it != value.objectValue->begin())
      ss << ",";

    ss << "\"" << it->first << "\":";

    ss << stringify(item);

  }

  ss << "}";

  value.stringValue = ss.str();

  return value.stringValue.c_str();

}
