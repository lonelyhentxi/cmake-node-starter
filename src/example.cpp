#include "example.hpp"

Napi::Object Example::Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "Example", {
            InstanceMethod("GetValue", &Example::GetValue),
            InstanceMethod("SetValue", &Example::SetValue)
    });
    constructor = Napi::Persistent(func);
    constructor.SuppressDestruct();
    exports.Set("Example", func);
    return exports;
}

Example::Example(const Napi::CallbackInfo &info): Napi::ObjectWrap<Example>(info) {
    Napi::Env env = info.Env();
    Napi::Number value = info[0].As<Napi::Number>();
    this->_value = value.DoubleValue();
}

Napi::FunctionReference Example::constructor;

Napi::Value Example::GetValue(const Napi::CallbackInfo &info){
    Napi::Env env = info.Env();
    return Napi::Number::New(env, this->_value);
}


Napi::Value Example::SetValue(const Napi::CallbackInfo &info) {
    Napi::Env env = info.Env();
    Napi::Number value = info[0].As<Napi::Number>();
    this->_value = value.DoubleValue();
    return this->GetValue(info);
}

Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Example::Init(env, exports);
    return exports;
}

NODE_API_MODULE(example , Init);