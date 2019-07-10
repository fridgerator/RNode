// https://github.com/Planeshifter/node-Rstats

// #include <Rcpp.h>

#include <nan.h>
#include "thing.h"

void Call(const Nan::FunctionCallbackInfo<v8::Value> &args)
{
  v8::String::Utf8Value functionName(args[0]);
  RResponse r = call_it(args);

  // if (r.d) {
  //   args.GetReturnValue().Set(Nan::New(r.d));
  // } else if (r.i) {
  //   args.GetReturnValue().Set(Nan::New(r.i));
  // } else if (r.s != "") {
  //   args.GetReturnValue().Set(Nan::New(r.s).ToLocalChecked());
  // }
}

void Initialize(v8::Local<v8::Object> exports)
{
  exports->Set(
    Nan::New("call").ToLocalChecked(),
    Nan::New<v8::FunctionTemplate>(Call)->GetFunction());
}

NODE_MODULE(addon, Initialize);
