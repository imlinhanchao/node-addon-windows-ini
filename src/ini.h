#ifndef __IniNode_H__
#define __IniNode_H__

#include <node.h>
#include <node_object_wrap.h>
#include "win-ini.h"

namespace __ini_node__ {

using node::ObjectWrap;
using v8::Object;
using v8::Local;
using v8::Isolate;
using v8::Persistent;
using v8::Value;
using v8::Function;
using v8::FunctionCallbackInfo;
using v8::String;

class IniNode : public ObjectWrap {
public:
    static void Init(Isolate* isolate);
    static void NewInstance(const FunctionCallbackInfo<Value>& args);

    const char* getPath();
    const char* setPath(const char* szPath);

	bool Write(char*  pszAppName, char*  pszKeyName, char*  pszValue);
	bool Read(char* pszAppName, char* pszKeyName, char* pszValue, int nMaxSize=1024);

	bool Remove(char* pszAppName, char* pszKeyName);
	bool Remove(char* pszAppName);

	bool GetAllKeys(char* pszAppName, char* pszKeys[], int& nCount);
	bool GetAllApps(char* pszAppNames[], int& nCount);

private:
    explicit IniNode(Local<String> value);
    ~IniNode();

    static void New(const FunctionCallbackInfo<Value>& args);
    static void getPath(const FunctionCallbackInfo<Value>& args);
    static void setPath(const FunctionCallbackInfo<Value>& args);
    static void Write(const FunctionCallbackInfo<Value>& args);
    static void Read(const FunctionCallbackInfo<Value>& args);
    static void Remove(const FunctionCallbackInfo<Value>& args);
    static void GetAllKeys(const FunctionCallbackInfo<Value>& args);
    static void GetAllApps(const FunctionCallbackInfo<Value>& args);

    static Persistent<Function> constructor;
    String::Utf8Value m_szIni;
    Ini m_ini;
};

}

#endif
