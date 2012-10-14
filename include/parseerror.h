class ParseError: public exception {

protected:

  string message;

  void setup(const int aLine, const int aPosition, const string& aMessage) {

    stringstream ss;
    ss << "Parse error at line " << aLine << ", position " << aPosition << ": " << aMessage;
    message = ss.str();

  }

public:

  explicit ParseError(const int aLine, const int aPosition, const string& aMessage) {
    setup(aLine, aPosition, aMessage);
  }

  explicit ParseError(const string& aMessage) {
    setup(0, 0, aMessage);
  }

  virtual ~ParseError() throw () {
  }

  const char * what() const throw () {
    return message.c_str();
  }

};
