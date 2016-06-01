#include <nan.h>

#include <string>
#include <node.h>
#include <cstdlib>
#include <ctime>

namespace demo {
    using v8::FunctionCallbackInfo;
    using v8::Isolate;
    using v8::Local;
    using v8::Object;
    using v8::String;
    using v8::Value;

    void Method(const FunctionCallbackInfo<Value>& args) {
        Isolate* isolate = args.GetIsolate();
        
        long x = std::rand() % 14620 + 1;
        for (long i = 0; i < 4000000000l; i++) {
            if (x % 2 == 0) {
                x++;
            }
        }
        
        char numstr[21]; // enough to hold all numbers up to 64-bits
        sprintf(numstr, "%li", x);
        
        // Blowing my mind!
        std::string a = "world! Enjoy your number: ";
        std::string b = numstr;
        std::string c = a + b;
        const char* d = c.c_str();
        
        args.GetReturnValue().Set(String::NewFromUtf8(isolate, d));
    }

    void init(Local<Object> exports) {
        std::srand(std::time(0));  // needed once per program run
        
        NODE_SET_METHOD(exports, "hello", Method);
    }

    NODE_MODULE(addon, init)
}
