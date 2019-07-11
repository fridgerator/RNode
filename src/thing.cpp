#include <sstream>
#include <RInside.h>
#include <Rinternals.h>
#include "thing.h"

// using namespace Rcpp;

RInside *r_instance;

RResponse call_it(std::string functionName, std::vector<RResponse> args)
{
  
  if (!r_instance) r_instance = new RInside();
  r_instance->parseEvalQ("source(\"rnode-test.R\")");
  
  std::ostringstream s;
  s << functionName << "(";

  for (unsigned long i = 0; i < args.size(); i++) {
    if (i != 0) s << ", ";
    auto arg = args[i];

    switch(arg.r_type) {
      case RSTRING:
        s << "\"" << arg.s << "\"";
        break;

      case RDOUBLE:
        s << arg.d;
        break;

      case RINT:
        s << arg.i;
        break;
      
      default:
        printf("Couldnt get type of argument\n");
    }
  }

  s << ")";

  printf("going to call : %s\n", s.str().c_str());

  SEXP response;
  // TODO: fail if r != 0
  auto r = r_instance->parseEval(s.str(), response);

  int t = TYPEOF(response);

  RResponse rresponse;

  if (t == STRSXP) {
    std::string response_string = RInside::Proxy(response);
    rresponse.r_type = RSTRING;
    rresponse.s = response_string;
  } else if (t == REALSXP) {
    double response_double = RInside::Proxy(response);
    rresponse.d = RDOUBLE;
    rresponse.d = response_double;
  }

  return rresponse;

  // working
  // RInside* q_ = new RInside();
  // RInside *q = q_;
  // q->assign("Hello, from R!\n", "txt");
  // q->parseEvalQ("cat(txt)");
  // print matrix
  // int n = 4;
  // Rcpp::NumericMatrix M(n, n);
  // for (int i = 0; i < n; i++) {
  //   for (int j = 0; j < n; j++) {
  //     M(i, j) = i * 10 + j;
  //   }
  // }
  // q->assign(M, "M");
  // q->parseEvalQ("print(M)");


  // works
  // RInside *q = new RInside();
  // q->parseEvalQ("source(\"rnode-test.R\")");
  // q->parseEvalQ("fahrenheit_to_kelvin(100)");

  // works
  // RInside *q = new RInside();
  // q->parseEvalQ("source(\"rnode-test.R\")");
  // // q->parseEvalQ("return_immediate(100)");
  // SEXP thing;
  // // std::string xx = q->parseEval("return_immediate(\"test\")");
  // auto x = q->parseEval("return_immediate(100.1)", thing);
  // printf("return_immediate : %d\n", x);
  // int t = TYPEOF(thing);
  // printf("type : %d\n", t);
  // if (t == STRSXP) {
  //   printf("returned a string\n");
  //   std::string s = RInside::Proxy(thing);
  //   printf("got string : %s\n", s.c_str());
  // } else if (t == INTSXP) {
  //   printf("returned an int\n");
  // } else if (t == REALSXP) {
  //   printf("returne a real\n");
  //   double d = RInside::Proxy(thing);
  //   printf("got double : %lf\n", d);
  // }

  // const char * i = q->parseEval("return_immediate(\"response\")");
  // printf("i : %s\n", i);
}
