class ArrayAdapter: public TypeAdapter {

  public:

  boolean toBoolean(var value) {
  
    return true;
  
  }
  
  number toNumber(var value) {
  
    return 0;
  
  }
  
  string toString(var value) {
    
    ostringstream ss;
    
    long size = value.arrayValue.size();
    
    ss << "[";
      
    for (Array::iterator it = value.arrayValue.begin(); it != value.arrayValue.end(); ++it) {
    
      cstring item = *it;
    
      if (it != value.arrayValue.begin())
        ss << ", ";
    
      if (it->isString()) {
      
        ss << "\"" << item << "\"";
      
      }
      
      else {
      
        ss << item;
      
      }
    
    } 
    
    ss << "]";
    
    return ss.str();
    
  }

};

