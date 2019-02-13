#include <node.h>
#include "ini.h"

namespace __ini_node__ {

using v8::Local;
using v8::Object;

void InitAll(Local<Object> exports, Local<Object> module)
{
    IniNode::Init(exports->GetIsolate());
    NODE_SET_METHOD(module, "exports", IniNode::NewInstance);
}

NODE_MODULE(addon1, InitAll)

}
