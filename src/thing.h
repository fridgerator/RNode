#include <nan.h>

class RResponse {
public:
  int i;
  std::string s;
  double d;
};


RResponse call_it(Nan::NAN_METHOD_ARGS_TYPE args);
