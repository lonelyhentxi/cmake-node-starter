#pragma once
#include "napi.h"

class Example: public Napi::ObjectWrap<Example> {
public:
    static Napi::Object Init(Napi::Env env, Napi::Object exports);
    explicit Example(const Napi::CallbackInfo &info);

private:
    static Napi::FunctionReference constructor;
    double _value;
    Napi::Value GetValue(const Napi::CallbackInfo &info);
    Napi::Value SetValue(const Napi::CallbackInfo &info);
};