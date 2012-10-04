
void parser::append(var &context, string key, var value) {

  cout << "appending " << (string) value << " (" << key << ") to "
      << (string) context << endl;

  if (context.isObject()) {
    context[key] = value;

  } else if (context.isArray()) {

    context.arrayValue->push_back(value);

  }

}

var parser::parse(string str) {

  string::iterator it;
  char character;
  ParserState state = STATE_WHITESPACE;
  stringstream keyBuffer("");
  stringstream valBuffer("");
  int index = -1;

  bool hasComma = false;
  bool hasColon = false;
  bool hasQuote = false;
  bool hasEscape = false;
  bool isKey = false;
  bool expectColon = false;

  var context = Array();
  Array contextStack;
  contextStack.push_back(context);

  for (it = str.begin(); it < str.end(); it++) {

    ++index;

    //cout << "[main loop] key buffer: " << keyBuffer.str() << endl;
    // cout << "[main loop] character: " << character << endl;

    character = *it;

    // cout << character << endl;

    switch (state) {

    case STATE_WHITESPACE:

      // whitespace

      if (isspace(character)) {

        continue;

      }

      // comma

      if (character == ',') {

        if (context.isObject()) {
          isKey = true;
        }
        continue;

      }

      // null

      if (character == 'n' && str.compare(index, 4, "null") == 0) {

        append(context, keyBuffer.str(), null);

        it += 3;
        index += 3;

        continue;

      }

      // boolean

      if (character == 't' && str.compare(index, 4, "true") == 0) {

        append(context, keyBuffer.str(), null);

        it += 3;
        index += 3;

        continue;

      }

      if (character == 'f' && str.compare(index, 5, "false") == 0) {

        append(context, keyBuffer.str(), null);

        it += 4;
        index += 4;

        continue;

      }

      // number

      if (isdigit(character) || character == '-') {

        state = STATE_NUMBER;
        valBuffer << character;
        continue;

      }

      // string

      if (character == '"') {

        state = STATE_STRING;
        continue;

      }

      // object

      if (character == '{') {

        var newContext = Object();

        append(context, keyBuffer.str(), newContext);
        keyBuffer.str("");

        context = newContext;
        contextStack.push_back(context);

        isKey = true;
        continue;

      }

      if (character == '}') {

        contextStack.pop_back();
        context = contextStack.back();
        continue;

      }

      // array

      if (character == '[') {

        var newContext = Array();

        append(context, keyBuffer.str(), newContext);
        keyBuffer.str("");

        context = newContext;
        contextStack.push_back(context);

        isKey = false;
        continue;

      }

      if (character == ']') {

        contextStack.pop_back();
        context = contextStack.back();

        continue;

      }

      if (character == ':') {

        if (expectColon) {

          expectColon = false;

          continue;

        }

        throw ParseError(index, "Found unexpected colon");

        continue;

      }

      throw ParseError(index,
          "Found unexpected character(s): " + str.substr(index, 8));

      continue;

    case STATE_NUMBER:

      if (character == ']' || character == '}' || character == ',') {

        if (character == ']' || character == '}')
          it--;

        state = STATE_WHITESPACE;
        append(context, keyBuffer.str(), strtod(valBuffer.str().c_str(), 0));
        keyBuffer.str("");
        valBuffer.str("");

        if (character == ',') {

          if (context.isObject()) {

            isKey = true;

          }

        }

        continue;

      }

      //TODO: don't allow more than one decimal dot
      //TODO: scientific notation
      if (isdigit(character) || character == '-' || character == '.') {

        valBuffer << character;
        continue;

      } else {

        stringstream ss("Expected number, found ");
        ss << str.substr(index, 1);
        throw ParseError(index, ss.str());

      }

    case STATE_STRING: {

      // cout << "character: " << character << "\tis key: " << isKey << endl;

      stringstream &buffer = isKey ? keyBuffer : valBuffer;

      if (character == '\\') {

        hasEscape = true;
        continue;

      }

      if (hasEscape) {

        hasEscape = false;

        switch (character) {

        case '"':
        case '\\':
        case '/':
          buffer << character;
          continue;

        case 'b':
          buffer << '\b';
          continue;
        case 'f':
          buffer << '\f';
          continue;
        case 'n':
          buffer << '\n';
          continue;
        case 'r':
          buffer << '\r';
          continue;
        case 't':
          buffer << '\t';
          continue;

          // TODO: \u unicode escapes

        }

        stringstream ss("Bad escape sequence: \\");
        ss << character;
        throw ParseError(index, ss.str());

        // buffer << character;
        // continue;

      }

      if (character == '"') {

        state = STATE_WHITESPACE;

        if (!isKey) {

          append(context, keyBuffer.str(), valBuffer.str());
          keyBuffer.str("");
          valBuffer.str("");
          // isKey = true;
          continue;

        }
        // it was a key
        // TODO: throw if no colon
        expectColon = true;
        isKey = false;
        continue;

      }

      buffer << character;
      continue;

    }
    }

  }

  if (state == STATE_NUMBER) {
    append(context, keyBuffer.str(), strtod(valBuffer.str().c_str(), 0));
  }

  return context[0];

}


