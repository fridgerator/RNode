enum RType {
  RSTRING,
  RDOUBLE,
  RINT
};

class RResponse {
public:
  int i;
  std::string s;
  double d;
  RType r_type;
};

RResponse call_it(std::string functionName, std::vector<RResponse> args);
