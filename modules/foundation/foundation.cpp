
#include <include/v8.h>
#include <include/libplatform/libplatform.h>

#include <assert.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


using namespace v8;

int main()
{
	v8::V8::InitializeICU();
	v8::Platform* platform = v8::platform::CreateDefaultPlatform();
	v8::V8::InitializePlatform(platform);
	v8::V8::Initialize();
	Isolate* isolate = Isolate::New();
	Isolate::Scope isolate_scope(isolate);

	// Create a stack-allocated handle scope.
	HandleScope handle_scope(isolate);

	// Create a new context.
	Local<Context> context = Context::New(isolate);

	// Enter the context for compiling and running the hello world script.
	Context::Scope context_scope(context);

	// Create a string containing the JavaScript source code.
	Local<String> source = String::NewFromUtf8(isolate, "'Hello' + ', World!'");

	// Compile the source code.
	Local<Script> script = Script::Compile(source);

	// Run the script to get the result.
	Local<Value> result = script->Run();

	// Convert the result to an UTF8 string and print it.
	String::Utf8Value utf8(result);
	printf("%s\n", *utf8);

    system("pause");
    return 0;
}

