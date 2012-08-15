class NumberAdapter: public TypeAdapter {

  public:

  boolean toBoolean(var value) {
  
    return value.numberValue == 0 ? false : true;
  
  }
  
  string toString(var value) {
  
    ostringstream ss;
    
    if (!(ss << value.numberValue))
      return "NaN";
    
    return ss.str();
    
  }

};

