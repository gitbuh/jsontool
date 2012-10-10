
// object adapter

number ObjectAdapter::toNumber(var &) {
  return 0;
}

boolean ObjectAdapter::toBoolean(var &) {
  return true;
}

string ObjectAdapter::toString(var &value) {

  Object &objectValue = getObject(value);
  string &stringValue = getString(value);

  ostringstream ss;

  ss << "{";

  for (Object::iterator it = objectValue.begin(); it
      != objectValue.end(); ++it) {

    var& item = it->second;

    if (it != objectValue.begin())
      ss << ",";

    ss << "\"" << it->first << "\":";

    ss << stringify(item);

  }

  ss << "}";

  stringValue = ss.str();

  return stringValue;

}

var& ObjectAdapter::subscript(var &value, var key) {

  Object &objectValue = getObject(value);

  return objectValue.count(key) ? objectValue[key] : setTemp(value, key);

}

void ObjectAdapter::promoteTemp(var &value) {

  getObject(getParent(value))[getTempKey(value)] = value;
  // TODO: remove temporary value
  // parent->tempKeys.erase(tempObjectKey);

}
