
// boolean adapter

number BooleanAdapter::toNumber(var &value) {
  return getBoolean(value) == false ? 0 : 1;
}
string BooleanAdapter::toString(var &value) {
  return getBoolean(value) == false ? "false" : "true";
}
