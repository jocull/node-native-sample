#include <nan.h>

#include <string>
#include <node.h>
#include <cstdlib>
#include <ctime>

using namespace v8;
using namespace node;

namespace {
    class MyAsyncWorker : public Nan::AsyncWorker {
        public:
            MyAsyncWorker(Nan::Callback *callback)
                : Nan::AsyncWorker(callback) {
            }

            ~MyAsyncWorker() {}

            void Execute() {
                
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
                
                result = (a + b);
            }

            void HandleOKCallback() {
                Nan::HandleScope scope;

                Local<Value> argv[2];
                argv[0] = Nan::Undefined();
                argv[1] = Nan::Encode(result.c_str(), result.size(), Nan::BINARY);
                callback->Call(2, argv);
            }

        private:
            std::string result;
    };

    NAN_METHOD(GenerateMessage) {
        Nan::HandleScope scope;

        if (info.Length() < 1) {
            Nan::ThrowTypeError("1 argument expected");
            return;
        }
        
        Local<Function> callback = Local<Function>::Cast(info[0]);

        MyAsyncWorker* myWorker = new MyAsyncWorker(new Nan::Callback(callback));

        Nan::AsyncQueueWorker(myWorker);
    }
}

NAN_MODULE_INIT(init) {
    std::srand(std::time(0));  // needed once per program run
    
    Nan::Export(target, "hello", GenerateMessage);
};

NODE_MODULE(bcrypt_lib, init);