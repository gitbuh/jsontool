class ParseError: public exception {

protected:

  string message;

  void setup(const int aPosition, const string& aMessage) {

    stringstream ss("Parse error at position ");
    ss << aPosition << ": " << aMessage;
    message = ss.str();

  }

public:

  const int position;

  explicit ParseError(const int aPosition, const string& aMessage) :
    position(aPosition) {
    setup(aPosition, aMessage);
  }

  explicit ParseError(const string& aMessage) :
    position(0) {
    setup(0, aMessage);
  }

  virtual ~ParseError() throw () {
  }

  const char * what() const throw () {
    return message.c_str();
  }

};
