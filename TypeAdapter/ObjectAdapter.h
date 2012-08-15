class ObjectAdapter: public TypeAdapter {

  public:

  boolean toBoolean(var value) {
  
    return true;
  
  }
  
  number toNumber(var value) {
  
    return 0;
  
  }
  
  string toString(var value) {
    
    ostringstream ss;
    
    ss << "{";

    // show content:
    
    for (Object::iterator it = value.objectValue.begin(); it != value.objectValue.end(); ++it) {
    
      if (it != value.objectValue.begin())
        ss << ", ";
        
      ss << "\"" << it->first << "\":" << (cstring)(it->second);
    }
    
    
    ss << "}";
    
    return ss.str();
    
  }

};

