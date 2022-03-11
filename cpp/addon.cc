/*********************************************************************
 * NAN - Native Abstractions for Node.js
 *
 * Copyright (c) 2017 NAN contributors
 *
 * MIT License <https://github.com/nodejs/nan/blob/master/LICENSE.md>
 ********************************************************************/

#include <nan.h>

#include "cpuminer.h"


namespace miner {

  using namespace Nan;


  ::CpuMiner* cpuminer = nullptr;


  //call C++ dtors:
  void cleanup(void* p) {
    delete reinterpret_cast<CpuMiner*>(p);
  }


  class Miner : public AsyncWorker {
    public:
      Miner(Callback *callback)
        : AsyncWorker(callback)
      { }

      ~Miner() {}

      // This function runs in a thread spawned by NAN
      void Execute () {
        if (cpuminer) {
          cpuminer->run(); // blocking call
        } else {
          SetErrorMessage("{error: 'no cpuminer!'}");
        }
      }

    private:
      // Executed when the async work is complete
      // this function will be run inside the main event loop
      // so it is safe to use V8 again
      void HandleOKCallback () {
        HandleScope scope;

        v8::Local<v8::Value> argv[] = {
          Null(),
          New<v8::String>(cpuminer->solution()).ToLocalChecked()
        };

        callback->Call(2, argv);
      }
  };

  // Run an asynchronous function
  //  First and only parameter is a callback function
  //  receiving the solution when found
  NAN_METHOD(run) {
    Callback *callback = new Callback(To<v8::Function>(info[0]).ToLocalChecked());
    AsyncQueueWorker(new Miner(callback));
  }

  NAN_METHOD(stop) {
    cpuminer->stop();
    info.GetReturnValue().SetUndefined();
  }

  NAN_METHOD(setChallengeNumber) {
    MaybeLocal<v8::String> inp = Nan::To<v8::String>(info[0]);
    if (!inp.IsEmpty()) {
      cpuminer->setChallengeNumber(std::string(*Nan::Utf8String(inp.ToLocalChecked())));
    }
    info.GetReturnValue().SetUndefined();
  }
  NAN_METHOD(setDifficultyTarget) {
    MaybeLocal<v8::String> inp = Nan::To<v8::String>(info[0]);
    if (!inp.IsEmpty()) {
      cpuminer->setDifficultyTarget(std::string(*Nan::Utf8String(inp.ToLocalChecked())));
    }
    info.GetReturnValue().SetUndefined();
  }
  NAN_METHOD(setMinerAddress) {
    MaybeLocal<v8::String> inp = Nan::To<v8::String>(info[0]);
    if (!inp.IsEmpty()) {
      cpuminer->setMinerAddress(std::string(*Nan::Utf8String(inp.ToLocalChecked())));
    }
    info.GetReturnValue().SetUndefined();
  }

  NAN_METHOD(setParameters) {
    cpuminer->setParameters(info[0]->IntegerValue(Nan::GetCurrentContext()).FromJust(),
                            info[1]->IntegerValue(Nan::GetCurrentContext()).FromJust(),
                            info[2]->IntegerValue(Nan::GetCurrentContext()).FromJust());
    info.GetReturnValue().SetUndefined();
  }

  NAN_METHOD(setWhetherBalloon) {
    cpuminer->setWhetherBalloon(info[0]->BooleanValue(Nan::GetCurrentContext()->GetIsolate()));
    info.GetReturnValue().SetUndefined();
  }

  // Get the number of hashes performed until now
  //  and reset it to 0
  NAN_METHOD(hashes) {
    uint32_t const value = Solver::hashes;
    Solver::hashes = 0;
    info.GetReturnValue().Set(value);
  }

  // Defines the functions our add-on will export
  NAN_MODULE_INIT(Init) {
    Set(target,
      New<v8::String>("run").ToLocalChecked(),
      GetFunction(New<v8::FunctionTemplate>(run)).ToLocalChecked()
    );

    Set(target,
      New<v8::String>("stop").ToLocalChecked(),
      GetFunction(New<v8::FunctionTemplate>(stop)).ToLocalChecked()
    );

    Set(target,
      New<v8::String>("setChallengeNumber").ToLocalChecked(),
      GetFunction(New<v8::FunctionTemplate>(setChallengeNumber)).ToLocalChecked()
    );
    
    Set(target,
      New<v8::String>("setMinerAddress").ToLocalChecked(),
      GetFunction(New<v8::FunctionTemplate>(setMinerAddress)).ToLocalChecked()
    );

    Set(target,
      New<v8::String>("setDifficultyTarget").ToLocalChecked(),
      GetFunction(New<v8::FunctionTemplate>(setDifficultyTarget)).ToLocalChecked()
    );

    Set(target,
      New<v8::String>("setParameters").ToLocalChecked(),
      GetFunction(New<v8::FunctionTemplate>(setParameters)).ToLocalChecked()
    );

    Set(target,
      New<v8::String>("setWhetherBalloon").ToLocalChecked(),
      GetFunction(New<v8::FunctionTemplate>(setWhetherBalloon)).ToLocalChecked()
    );

    Set(target,
      New<v8::String>("hashes").ToLocalChecked(),
      GetFunction(New<v8::FunctionTemplate>(hashes)).ToLocalChecked()
    );

    cpuminer = new CpuMiner;
    node::AtExit(cleanup, cpuminer);
  }

  NODE_MODULE(cpumining, Init)

}
