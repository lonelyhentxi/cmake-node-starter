#pragma once
#include <cstdint>
#include "napi.h"
#include "napi-inl.h"

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

Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Example::Init(env, exports);
    return exports;
}

NODE_API_MODULE("112", Init);