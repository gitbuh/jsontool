class StringAdapter: public TypeAdapter {

  public:

  boolean toBoolean(var value) {
  
    return value.stringValue == "" ? false : true;
  
  }
  
  number toNumber(var value) {
  
    number n;
  
    istringstream in(value.stringValue);
    
    in >> n;
    
    return n;
  
  }

};

