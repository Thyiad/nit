#include <iostream>
#include <string>
#include <vector>

#include <nan.h>

#include <nit/enum/showdown_enumerator.h>
#include <nit/eval/make_evaluator.h>

using v8::FunctionTemplate;
using v8::Handle;
using v8::Object;
using v8::String;
using v8::Local;
using v8::Value;
using v8::Array;

using namespace std;

NAN_METHOD(calculateOdds) {
  string board;
  vector<string> hands;
  vector<nit::CardDistribution> handDists;

  if (info.Length() == 0) {
    cout << "WOWEE no args were passed in" << endl;
  }

  Local<Object> obj = info[0]->ToObject();
  Local<String> handProp  = Nan::New("hands").ToLocalChecked();
  Local<String> boardProp = Nan::New("board").ToLocalChecked();

  Local<Value> jsVal = Nan::Get(obj, handProp).ToLocalChecked();
  Local<Array> jsArr = Local<Array>::Cast(jsVal);

  for (int i = 0; i < jsArr->Length(); i++) {
    Local<Value> jsElement = jsArr->Get(i);
    string hand = string(*Nan::Utf8String(jsElement->ToString()));

    hands.push_back(hand);
    handDists.emplace_back();
    handDists.back().parse(hand);
  }

  unique_ptr<nit::PokerHandEvaluator> evaluator = nit::makeEvaluator("h");
  // fill with random if necessary
  if (handDists.size() == 1) {
    handDists.emplace_back();
    handDists.back().fill(evaluator->handSize());
  }

  Local<Value> boardValue = Nan::Get(obj, boardProp).ToLocalChecked();
  board = string(*Nan::Utf8String(boardValue->ToString()));

  nit::ShowdownEnumerator showdown;
  vector<nit::EquityResult> results = showdown.calculateEquity(
    handDists,
    nit::CardSet(board),
    *evaluator
  );

  double total = 0.0;
  for (const nit::EquityResult& result : results) {
    total += result.winShares + result.tieShares;
  }

  Local<Object> handsObject = Nan::New<Object>();
  Local<Array> handsArr = Nan::New<Array>(handDists.size());
  for (size_t i = 0; i < results.size(); ++i) {
    Local<Object> handObject = Nan::New<Object>();

    double win = results[i].winShares / total;
    double tie = results[i].tieShares / total;
    string hand = hands[i];

    Local<Value> winValue  = Nan::New(win);
    Local<Value> tieValue  = Nan::New(tie);
    Local<Value> handValue = Nan::New(hand).ToLocalChecked();

    Nan::Set(handObject, Nan::New("win").ToLocalChecked(), winValue);
    Nan::Set(handObject, Nan::New("tie").ToLocalChecked(), tieValue);
    Nan::Set(handObject, Nan::New("hand").ToLocalChecked(), handValue);

    handsArr->Set(i, handObject);
  }
  Nan::Set(handsObject, Nan::New("hands").ToLocalChecked(), handsArr);

  info.GetReturnValue().Set(handsObject);
}

void InitAll(Handle<Object> exports) {
  exports->Set(
    Nan::New<String>("calculateOdds").ToLocalChecked(),
    Nan::New<FunctionTemplate>(calculateOdds)->GetFunction()
  );
}

NODE_MODULE(addon, InitAll);
