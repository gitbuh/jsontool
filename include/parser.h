class Parser {

public:

  /**
   * Try to repair broken JSON
   */
  bool repair;

  /**
   * Report all errors
   */
  bool report;



  Parser(bool aRepair, bool aReport) {
    repair = aRepair;
    report = aReport;
    hasError = false;
  }

  Parser()  {
    repair = false;
    report = false;
    hasError = false;
  }

protected:

  bool hasError;

  void warn(ParseError error, bool repaired) {

    if (repaired) {

      cerr << error.what() << " (repaired)" << endl;
      return;

    }
    if (report) {

      hasError = true;
      cerr << error.what() << endl;
      return;

    }

    throw error;

  }
  void warn(ParseError error) {

    warn(error, false);

  }

public:

  enum ParserState {
    STATE_WHITESPACE, STATE_NUMBER, STATE_STRING
  };


  void append(var &context, string key, var value);

  var parse(string str);

};
