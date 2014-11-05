#include "Abot/Foundation.h"
#include "FoundationCommon.h"

#include <include/v8.h>
#include <include/libplatform/libplatform.h>

#include <assert.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>



using namespace v8;



class Test : public std::enable_shared_from_this<Test> {
public:
	void test2(Abot::NodePtr n1, Abot::NodePtr b2, Abot::NodePtr c3) {
		std::cout << 3333 << std::endl;
	}
	void test3(Abot::NodePtr n1, Abot::NodePtr b2, Abot::NodePtr c3) {
		std::cout << 2222 << std::endl;
	}
	void test() {

		auto node1 = Abot::Node::Create();
		auto node2 = Abot::Node::Create();
		auto group = Abot::Group::Create(node2);



		auto h1 = node1->OnNodeAdded()->Connect(std::bind(&Test::test2,
			shared_from_this(),
			std::placeholders::_1,
			std::placeholders::_2,
			std::placeholders::_3));
		auto h2 = node2->OnNodeAdded()->Connect(std::bind(&Test::test3,
			shared_from_this(),
			std::placeholders::_1,
			std::placeholders::_2,
			std::placeholders::_3));

		std::cout << node1.use_count() << std::endl;
		node2->AddNode(node1);
		std::cout << node1.use_count() << node2.get()->GetNodes().size() << group->GetDescendants()->GetNodes().size() << std::endl;
		node2->RemoveNode(node1);
		std::cout << node1.use_count() << std::endl;
		std::cout << h1 << h2 << std::endl;


	}
};

int test2(int argc, _TCHAR* argv[]) {
	std::shared_ptr<Test> test;

	test = std::shared_ptr<Test>(new Test());
	test->test();

	return 0;
}


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

	test2(3, nullptr);
    system("pause");
    return 0;
}

