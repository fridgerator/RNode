// https://github.com/Planeshifter/node-Rstats

// #include <Rcpp.h>

#include <tuple>
#include <vector>
#include <nan.h>
#include "thing.h"

void Call(const Nan::FunctionCallbackInfo<v8::Value> &args)
{
  v8::String::Utf8Value functionName(args[0]);

  std::vector<RResponse> r_args;

  for (int i = 1; i < args.Length(); i++) {
    auto arg = args[i];
    RResponse inner;

    if (arg->IsNumber()) {
      double num = arg->NumberValue();
      inner.r_type = RDOUBLE;
      inner.d = num;
    } else if (arg->IsString()) {
      v8::String::Utf8Value str(arg);
      inner.r_type = RSTRING;
      inner.s = *str;
    }

    r_args.push_back(inner);
  }
  

  RResponse r = call_it(*functionName, r_args);

  switch(r.r_type) {
      case RSTRING:
        args.GetReturnValue().Set(Nan::New(r.s).ToLocalChecked());
        break;

      case RDOUBLE:
        args.GetReturnValue().Set(Nan::New(r.d));
        break;

      case RINT:
        args.GetReturnValue().Set(Nan::New(r.i));
        break;
      
      default:
        printf("Couldnt get type of return\n");
    }
}

void Initialize(v8::Local<v8::Object> exports)
{
  exports->Set(
    Nan::New("call").ToLocalChecked(),
    Nan::New<v8::FunctionTemplate>(Call)->GetFunction());
}

NODE_MODULE(addon, Initialize);
