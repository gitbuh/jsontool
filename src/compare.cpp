var compare::toPrimitive(var& x) {
  if (!(x.isArray() || x.isObject()))
    return x;
  return (string) x;
}

// ES5 11.9.3 The Abstract Equality Comparison Algorithm
// http://es5.github.com/#x11.9.3

// The comparison x == y, where x and y are values, produces true or false. 
// Such a comparison is performed as follows:

bool compare::equality(var& x, var& y) {

  // 1. If Type(x) is the same as Type(y), then
  if (x.adapter->type == y.adapter->type) {

    // 1. If Type(x) is Undefined, return true.
    if (x.isUndefined())
      return true;

    // 2. If Type(x) is Null, return true.
    if (x.isNull())
      return true;

    // 3. If Type(x) is Number, then
    if (x.isNumber()) {

      // 1. If x is NaN, return false.
      // 2. If y is NaN, return false.

      // (TODO: NaN checks?)

      // 3. If x is the same Number value as y, return true.
      if (x.numberValue == y.numberValue)
        return true;

      // 4. If x is +0 and y is -0, return true.
      if (x.numberValue == +0 && y.numberValue == -0)
        return true;

      // 5. If x is -0 and y is +0, return true.
      if (x.numberValue == -0 && y.numberValue == +0)
        return true;

      // 6. Return false.
      return false;

    }

    // 4. If Type(x) is String, then return true if x and y are exactly the same sequence of characters 
    //    (same length and same characters in corresponding positions). Otherwise, return false.
    if (x.isString())
      return x.stringValue == y.stringValue;

    // 5. If Type(x) is Boolean, return true if x and y are both true or both false. Otherwise, return false.
    if (x.isBoolean())
      return x.booleanValue == y.booleanValue;

    // 6. Return true if x and y refer to the same object. Otherwise, return false.
    if (x.isObject())
      return x.objectValue == y.objectValue;
    if (x.isArray())
      return x.arrayValue == y.arrayValue;

    return false;

  }
  // 2. If x is null and y is undefined, return true.
  if (x.isNull() && y.isUndefined())
    return true;

  // 3. If x is undefined and y is null, return true.
  if (x.isUndefined() && y.isNull())
    return true;

  // 4. If Type(x) is Number and Type(y) is String, 
  //    return the result of the comparison x == ToNumber(y).
  if (x.isNumber() && y.isString())
    return x == (number) y;

  // 5. If Type(x) is String and Type(y) is Number, 
  //    return the result of the comparison ToNumber(x) == y.
  if (x.isString() && y.isNumber())
    return (var) (number) x == y;

  // 6. If Type(x) is Boolean, 
  //    return the result of the comparison ToNumber(x) == y.
  if (x.isBoolean())
    return (var) (number) x == y;

  // 7. If Type(y) is Boolean, 
  //    return the result of the comparison x == ToNumber(y).
  if (y.isBoolean())
    return x == (number) y;

  // 8. If Type(x) is either String or Number and Type(y) is Object, 
  //    return the result of the comparison x == ToPrimitive(y).
  if ((x.isString() || x.isNumber()) && (y.isObject() || y.isArray()))
    return x == (string) y;

  // 9. If Type(x) is Object and Type(y) is either String or Number, 
  //    return the result of the comparison ToPrimitive(x) == y.
  if ((x.isObject() || x.isArray()) && (y.isString() || y.isNumber()))
    return (var) (string) x == y;

  // 10. Return false.
  return false;

}

// ES5 11.8.5 The Abstract Relational Comparison Algorithm
// http://es5.github.com/#x11.8.5

/*
 The comparison x < y, where x and y are values, produces true, false, or undefined (which indicates that at least one operand is NaN). In addition to x and y the algorithm takes a Boolean flag named LeftFirst as a parameter. The flag is used to control the order in which operations with potentially visible side-effects are performed upon x and y. It is necessary because ECMAScript specifies left to right evaluation of expressions. The default value of LeftFirst is true and indicates that the x parameter corresponds to an expression that occurs to the left of the y parameter’s corresponding expression. If LeftFirst is false, the reverse is the case and operations must be performed upon y before x.
 */

bool compare::relation(var& x, var& y) {

  // 1. If the LeftFirst flag is true, then
  // 1. Let px be the result of calling ToPrimitive(x, hint Number).
  // 2. Let py be the result of calling ToPrimitive(y, hint Number).
  // 2. Else the order of evaluation needs to be reversed to preserve left to right evaluation
  // 1. Let py be the result of calling ToPrimitive(y, hint Number).
  // 2. Let px be the result of calling ToPrimitive(x, hint Number).

  // NOTE: The order of evaluation shouldn't matter in this case; don't use LeftFirst.

  var px = toPrimitive(x);
  var py = toPrimitive(y);

  // 3. If it is not the case that both Type(px) is String and Type(py) is String, then
  if (!(px.isString() && py.isString())) {

    // 1. Let nx be the result of calling ToNumber(px). 
    //    Because px and py are primitive values evaluation order is not important.
    number nx = px;

    // 2. Let ny be the result of calling ToNumber(py).
    number ny = py;

    // 3. If nx is NaN, return undefined.
    // 4. If ny is NaN, return undefined.

    // TODO: NaN checks?

    // 5. If nx and ny are the same Number value, return false.
    if (nx == ny)
      return false;

    // 6. If nx is +0 and ny is −0, return false.
    if (nx == +0 && ny == -0)
      return false;

    // 7. If nx is −0 and ny is +0, return false.
    if (nx == -0 && ny == +0)
      return false;

    // 8. If nx is +∞, return false.
    // 9. If ny is +∞, return true.
    // 10. If ny is −∞, return false.
    // 11. If nx is −∞, return true.

    // TODO: infinity checks?

    // 12. If the mathematical value of nx is less than the mathematical value of ny 
    //     —note that these mathematical values are both finite and not both zero—return true. Otherwise, return false.

    return nx < ny;

  } else {
    // 4. Else, both px and py are Strings
    // 1. If py is a prefix of px, return false. (A String value p is a prefix of String value q ifq can be the result of concatenating p and some other String r. Note that any String is a prefix of itself, because r may be the empty String.)
    // 2. If px is a prefix of py, return true.
    // 3. Let k be the smallest nonnegative integer such that the character at position kwithin px is different from the character at position k within py. (There must be such a k, for neither String is a prefix of the other.)
    // 4. Let m be the integer that is the code unit value for the character at position kwithin px.
    // 5. Let n be the integer that is the code unit value for the character at position kwithin py.
    // 6. If m < n, return true. Otherwise, return false.

    // NOTE: Should be close enough to std::string behavior.

    return (string) px < (string) py;

  }
}

