class parser {

public:

  enum ParserState {
    STATE_WHITESPACE, STATE_NUMBER, STATE_STRING
  };

  static void append(var &context, string key, var value);

  static var parse(string str);

};
