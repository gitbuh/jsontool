
void Parser::append(var &context, string key, var value) {

  if (context.isObject()) {
    context[key] = value;

  } else if (context.isArray()) {

    context.arrayValue->push_back(value);

  }

}

var Parser::parse(string str) {

  string::iterator it;
  char character;
  ParserState state = STATE_WHITESPACE;
  stringstream keyBuffer("");
  stringstream valBuffer("");
  int index = -1;
  int linePosition = -1;
  int line = 1;

  bool hasEscape = false;
  bool isKey = false;
  bool expectColon = false;

  var context = Array();
  Array contextStack;
  contextStack.push_back(context);

  for (it = str.begin(); it < str.end(); it++) {

    ++index;
    ++linePosition;

    character = *it;

    switch (state) {

    case STATE_WHITESPACE:

      // whitespace

      if (character == '\n') {

        ++line;
        linePosition = -1;

        continue;

      }

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
        linePosition += 3;

        continue;

      }

      // boolean

      if (character == 't' && str.compare(index, 4, "true") == 0) {

        append(context, keyBuffer.str(), null);

        it += 3;
        index += 3;
        linePosition += 3;

        continue;

      }

      if (character == 'f' && str.compare(index, 5, "false") == 0) {

        append(context, keyBuffer.str(), null);

        it += 4;
        index += 4;
        linePosition += 4;

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

        warn(ParseError(line, linePosition, "Found unexpected colon"), repair);

        continue;

      }

      keyBuffer.str("");
      warn(ParseError(line, linePosition,
          "Found unexpected character: " + str.substr(index, 1)), repair);

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

        warn(ParseError(line, linePosition,
            "Expected number, found " + str.substr(index, 1)), repair);

      }

    case STATE_STRING: {

      stringstream &buffer = isKey ? keyBuffer : valBuffer;

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

        stringstream ss;
        ss << "Bad escape sequence: backslash " << character;
        ParseError err = ParseError(line, linePosition, ss.str());

        if (repair) {

          buffer << "\\" << character;

        }

        warn(err, repair);

        // buffer << character;
        // continue;

      }

      if (character == '\\') {

        hasEscape = true;
        continue;

      }

      //TODO: disallow some characters, or only allow certain character


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

  if (hasError) {

    hasError = false;
    throw(ParseError("Multiple errors."));

  }

  return context[0];

}


