
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

var& ObjectAdapter::subscript(var &value, var key) {

  Object &obj = (*value.objectValue);

  return obj.count(key) ? obj[key] : setTemp(value, key);

}

void ObjectAdapter::promoteTemp(var &value) {

  (*getParent(value).objectValue)[getTempKey(value)] = value;
  // TODO: remove temporary value
  // parent->tempKeys.erase(tempObjectKey);

}
