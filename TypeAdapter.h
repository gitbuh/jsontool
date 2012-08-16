// default exports, overridden

boolean TypeAdapter::toBoolean(var value) {
  return value.booleanValue;
}
  
number TypeAdapter::toNumber(var value) {
  return value.numberValue;
}
  
cstring const TypeAdapter::toString(var value) {
  return value.stringValue.c_str();
}
  
Object TypeAdapter::toObject(var value) {
  return value.objectValue;
}
  
Array TypeAdapter::toArray(var value) {
  return value.arrayValue;
}

// boolean adapter

number BooleanAdapter::toNumber(var value) {
  return value.booleanValue == false ? 0 : 1;
}
cstring const BooleanAdapter::toString(var value) {
  return value.booleanValue == false ? "false" : "true";
}
  
// number adapter

boolean NumberAdapter::toBoolean(var value) {
  return value.numberValue == 0 ? false : true;
}
cstring const NumberAdapter::toString(var value) {
  ostringstream ss;
  return ss << value.numberValue ? ss.str().c_str() : "NaN";
}

// string adapter

boolean StringAdapter::toBoolean(var value) {
  return value.stringValue == "" ? false : true;
}
number StringAdapter::toNumber(var value) {
  number n;  
  istringstream ss(value.stringValue);
  return ss >> n ? n : 0;
}

  
// object adapter

number ObjectAdapter::toNumber(var value) {
  return 0;
}
boolean ObjectAdapter::toBoolean(var value) {
  return true;
}
cstring const ObjectAdapter::toString(var value) {

    ostringstream ss;
    
    ss << "{";

    // show content:
    
    for (Object::iterator it = value.objectValue.begin(); it != value.objectValue.end(); ++it) {
    
      if (it != value.objectValue.begin())
        ss << ", ";
        
      ss << "\"" << it->first << "\":" << (cstring)(it->second);
    }
    
    
    ss << "}";
    
    return ss.str().c_str();

}


// array adapter

number ArrayAdapter::toNumber(var value) {
  return StringAdapter().toNumber(value.arrayValue);
}
boolean ArrayAdapter::toBoolean(var value) {
  return true;
}
cstring const ArrayAdapter::toString(var value) {

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
    
    return ss.str().c_str();

}
