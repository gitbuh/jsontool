
// boolean adapter

number BooleanAdapter::toNumber(var &value) {
  return value.booleanValue == false ? 0 : 1;
}
string BooleanAdapter::toString(var &value) {
  return value.booleanValue == false ? "false" : "true";
}
