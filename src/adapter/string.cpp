
// string adapter

boolean StringAdapter::toBoolean(var &value) {
  return value.stringValue == "" ? false : true;
}

number StringAdapter::toNumber(var &value) {
  number n;
  istringstream ss(value.stringValue);
  return ss >> n ? n : 0;
}

string StringAdapter::toJSON(var &value) {

  string str = (string)value;

  string::iterator it;

  char character;

  stringstream ss;

  ss << '"';

  for (it = str.begin(); it < str.end(); it++) {

    character = *it;

    switch (character) {

    case '"':
      ss << "\\\"";
      continue;
    case '\\':
      ss << "\\\\";
      continue;
    case '\b':
      ss << "\\b";
      continue;
    case '\f':
      ss << "\\f";
      continue;
    case '\n':
      ss << "\\n";
      continue;
    case '\r':
      ss << "\\r";
      continue;
    case '\t':
      ss << "\\t";
      continue;
    default:
      // TODO: check bad characters, encode unicode?
      ss << character;

    }

  }

  ss << '"';

  return ss.str();

}
