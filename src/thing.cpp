#include <sstream>
#include <RInside.h>
#include <Rinternals.h>
#include "thing.h"

// using namespace Rcpp;

// [[Rcpp::export]]
RResponse call_it(std::string functionName, int arg)
{
  
  RInside *q = new RInside();
  q->parseEvalQ("source(\"rnode-test.R\")");
  
  std::ostringstream s;
  s << functionName << "(" << arg << ")";
  
  SEXP response;
  // TODO: fail if r != 0
  auto r = q->parseEval(s.str(), response);

  int t = TYPEOF(response);

  RResponse rresponse;

  if (t == STRSXP) {
    std::string response_string = RInside::Proxy(response);
    rresponse.s = response_string;
  } else if (t == REALSXP) {
    double response_double = RInside::Proxy(response);
    rresponse.d = response_double;
  }

  return rresponse;

  // int temperature = 32;

  // segfaults
  // Rprintf("hello, world", 13);
  // Rcpp::NumericVector a(0);
  // Function func("fahrenheit_to_kelvin");
  // auto x = Rcpp::wrap(temperature);
  // auto result = func(x);
  // auto t = Rcpp::as<double>(result);

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
