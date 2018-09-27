#include <nit/eval/card_set.h>
#include <iostream>
#include <string>
#include <vector>

#include <nan.h>

using v8::FunctionTemplate;
using v8::Handle;
using v8::Object;
using v8::String;

using namespace std;

NAN_METHOD(meme) {

  info.GetReturnValue().Set(
    Nan::New<String>("something.str()").ToLocalChecked()
  );
}

void InitAll(Handle<Object> exports) {
  exports->Set(
    Nan::New<String>("meme").ToLocalChecked(),
    Nan::New<FunctionTemplate>(meme)->GetFunction()
  );
}

NODE_MODULE(addon, InitAll);
