#include "ini.h"
#include <string>

namespace __ini_node__ {

using v8::Isolate;
using v8::FunctionTemplate;
using v8::String;
using v8::Number;
using v8::Context;
using v8::String;
using v8::Array;
using v8::Boolean;

Persistent<Function> IniNode::constructor;

IniNode::IniNode(Local<String> value) : m_szIni(value), m_ini(*m_szIni)
{

}

IniNode::~IniNode()
{
}

void IniNode::Init(Isolate* isolate)
{
    Local<FunctionTemplate> tpl = FunctionTemplate::New(isolate, New);
    tpl->SetClassName(String::NewFromUtf8(isolate, "IniNode"));
    tpl->InstanceTemplate()->SetInternalFieldCount(1);
    
    NODE_SET_PROTOTYPE_METHOD(tpl, "getPath", getPath);
    NODE_SET_PROTOTYPE_METHOD(tpl, "setPath", setPath);
    NODE_SET_PROTOTYPE_METHOD(tpl, "read", Read);
    NODE_SET_PROTOTYPE_METHOD(tpl, "write", Write);
    NODE_SET_PROTOTYPE_METHOD(tpl, "remove", Remove);
    NODE_SET_PROTOTYPE_METHOD(tpl, "keys", GetAllKeys);
    NODE_SET_PROTOTYPE_METHOD(tpl, "sections", GetAllApps);

    constructor.Reset(isolate, tpl->GetFunction());
}

void IniNode::New(const FunctionCallbackInfo<Value>& args)
{
    Local<String> str = args[0]->IsString() ? Local<String>::Cast(args[0]) : String::NewFromUtf8(Isolate::GetCurrent(), "");
    IniNode* obj = new IniNode(str);
    obj->Wrap(args.This());
    args.GetReturnValue().Set(args.This());
}

void IniNode::NewInstance(const FunctionCallbackInfo<Value>& args)
{
    Isolate* isolate = args.GetIsolate();

    const int argc = 1;
    Local<Value> argv[argc] = { args[0] };
    Local<Context> context = isolate->GetCurrentContext();
    Local<Function> cons = Local<Function>::New(isolate, constructor);
    Local<Object> result =
            cons->NewInstance(context, argc, argv).ToLocalChecked();
    args.GetReturnValue().Set(result);
}

void IniNode::getPath(const FunctionCallbackInfo<Value>& args)
{
    Isolate* isolate = args.GetIsolate();

    IniNode* obj = ObjectWrap::Unwrap<IniNode>(args.Holder());
    args.GetReturnValue().Set(String::NewFromUtf8(isolate, obj->getPath()));
}

void IniNode::setPath(const FunctionCallbackInfo<Value>& args)
{
    Isolate* isolate = args.GetIsolate();

    String::Utf8Value path(Local<String>::Cast(args[0]));

    IniNode* obj = ObjectWrap::Unwrap<IniNode>(args.Holder());
    args.GetReturnValue().Set(String::NewFromUtf8(isolate, obj->setPath(*path)));
}

void IniNode::Read(const FunctionCallbackInfo<Value>& args)
{
    Isolate* isolate = args.GetIsolate();

    String::Utf8Value appName(Local<String>::Cast(args[0]));
    String::Utf8Value keyName(Local<String>::Cast(args[1]));
    char szValue[1024];
    IniNode* obj = ObjectWrap::Unwrap<IniNode>(args.Holder());
    if(obj->Read(*appName, *keyName, szValue))
        args.GetReturnValue().Set(String::NewFromUtf8(isolate, szValue));
    else
        args.GetReturnValue().Set(Null(isolate));
}

void IniNode::Write(const FunctionCallbackInfo<Value>& args)
{
    Isolate* isolate = args.GetIsolate();

    String::Utf8Value appName(Local<String>::Cast(args[0]));
    String::Utf8Value keyName(Local<String>::Cast(args[1]));
    String::Utf8Value value(Local<String>::Cast(args[2]));
    IniNode* obj = ObjectWrap::Unwrap<IniNode>(args.Holder());
    args.GetReturnValue().Set(Boolean::New(isolate, obj->Write(*appName, *keyName, *value)));
}

void IniNode::Remove(const FunctionCallbackInfo<Value>& args)
{
    Isolate* isolate = args.GetIsolate();

    IniNode* obj = ObjectWrap::Unwrap<IniNode>(args.Holder());
    String::Utf8Value appName(Local<String>::Cast(args[0]));
    if(args[1]->IsUndefined()) {
        args.GetReturnValue().Set(Boolean::New(isolate, obj->Remove(*appName)));
    } else {
        String::Utf8Value keyName(Local<String>::Cast(args[1]));
        args.GetReturnValue().Set(Boolean::New(isolate, obj->Remove(*appName, *keyName)));
    }
}

void IniNode::GetAllKeys(const FunctionCallbackInfo<Value>& args)
{
    Isolate* isolate = args.GetIsolate();

    String::Utf8Value appName(Local<String>::Cast(args[0]));
    char* szTmp[1] = { 0 };
    szTmp[0] = new char[1];
    int nCount = 1;
    IniNode* obj = ObjectWrap::Unwrap<IniNode>(args.Holder());
    if(obj->GetAllKeys(*appName, szTmp, nCount))
    {
        delete szTmp[0];
        szTmp[0] = NULL;
        char ** pszKeys = new char*[++nCount];
        for(uint32_t i = 0; i < nCount; i++){
            pszKeys[i] = new char[1024];
        }
        obj->GetAllKeys(*appName, pszKeys, nCount);
        Local<Array> ret = Array::New(isolate, nCount);
        for(uint32_t i = 0; i < nCount; i++)
        {
            Local<String> v = String::NewFromUtf8(isolate, pszKeys[i]);
            ret->Set(i, v);
        }

        args.GetReturnValue().Set(ret);

        for(uint32_t i = 0; i < nCount; i++){
            delete[] pszKeys[i];
            pszKeys[i] = NULL;
        }

        delete[] pszKeys;
        pszKeys = NULL;
    }
    else
        args.GetReturnValue().Set(Null(isolate));
}

void IniNode::GetAllApps(const FunctionCallbackInfo<Value>& args)
{
    Isolate* isolate = args.GetIsolate();

    char* szTmp[1] = { 0 };
    szTmp[0] = new char[1];
    int nCount = 1;
    IniNode* obj = ObjectWrap::Unwrap<IniNode>(args.Holder());
    if(obj->GetAllApps(szTmp, nCount))
    {
        delete szTmp[0];
        szTmp[0] = NULL;
        char ** pszKeys = new char*[++nCount];
        for(uint32_t i = 0; i < nCount; i++){
            pszKeys[i] = new char[1024];
        }
        obj->GetAllApps(pszKeys, nCount);
        Local<Array> ret = Array::New(isolate, nCount);
        for(uint32_t i = 0; i < nCount; i++)
        {
            Local<String> v = String::NewFromUtf8(isolate, pszKeys[i]);
            ret->Set(i, v);
            delete[] pszKeys[i];
            pszKeys[i] = NULL;
        }

        args.GetReturnValue().Set(ret);

        delete[] pszKeys;
        pszKeys = NULL;
    }
    else
        args.GetReturnValue().Set(Null(isolate));
}

const char* IniNode::getPath() 
{
    std::string str(*m_szIni);
    return str != "undefined" ? *m_szIni : "";
}

const char* IniNode::setPath(const char* szPath)
{
    m_ini.SetFile(szPath);
    return szPath;
}
	
bool IniNode::Write(char*  pszAppName, char*  pszKeyName, char*  pszValue)
{
    return m_ini.Write(pszAppName, pszKeyName, pszValue);
}

bool IniNode::Read(char* pszAppName, char* pszKeyName, char* pszValue, int nMaxSize)
{
    return m_ini.Read(pszAppName, pszKeyName, pszValue, nMaxSize);
}

bool IniNode::Remove(char* pszAppName, char* pszKeyName)
{
    return m_ini.Remove(pszAppName, pszKeyName);
}

bool IniNode::Remove(char* pszAppName)
{
    return m_ini.Remove(pszAppName);
}

bool IniNode::GetAllKeys(char* pszAppName, char* pszKeys[], int& nCount)
{
    return m_ini.GetAllKeys(pszAppName, pszKeys, nCount);
}

bool IniNode::GetAllApps(char* pszAppNames[], int& nCount)
{
    return m_ini.GetAllApps(pszAppNames, nCount);
}

}
