#include "Abot/Foundation.h"
#include "FoundationCommon.h"

#include <include/v8.h>
#include <include/libplatform/libplatform.h>


#include <dlib/gui_widgets.h>


using namespace std;
using namespace dlib;

//  ----------------------------------------------------------------------------

class color_box : public draggable {
	/*
	Here I am defining a custom drawable widget that is a colored box that
	you can drag around on the screen.  draggable is a special kind of drawable
	object that, as the name implies, is draggable by the user via the mouse.
	To make my color_box draggable all I need to do is inherit from draggable.
	*/
	unsigned char red, green, blue;

public:
	color_box(
		drawable_window& w,
		rectangle area,
		unsigned char red_,
		unsigned char green_,
		unsigned char blue_
		) :
		draggable(w),
		red(red_),
		green(green_),
		blue(blue_) {
		rect = area;
		set_draggable_area(rectangle(10, 10, 400, 400));

		// Whenever you make your own drawable widget (or inherit from any drawable widget 
		// or interface such as draggable) you have to remember to call this function to 
		// enable the events.  The idea here is that you can perform whatever setup you 
		// need to do to get your object into a valid state without needing to worry about 
		// event handlers triggering before you are ready.
		enable_events();
	}

	~color_box(
		) {
		// Disable all further events for this drawable object.  We have to do this 
		// because we don't want any events (like draw()) coming to this object while or 
		// after it has been destructed.
		disable_events();

		// Tell the parent window to redraw its area that previously contained this
		// drawable object.
		parent.invalidate_rectangle(rect);
	}

private:

	void draw(
		const canvas& c
		) const {
		// The canvas is an object that represents a part of the parent window
		// that needs to be redrawn.  

		// The first thing I usually do is check if the draw call is for part
		// of the window that overlaps with my widget.  We don't have to do this 
		// but it is usually good to do as a speed hack.  Also, the reason
		// I don't have it set to only give you draw calls when it does indeed
		// overlap is because you might want to do some drawing outside of your
		// widget's rectangle.  But usually you don't want to do that :)
		rectangle area = c.intersect(rect);
		if (area.is_empty() == true)
			return;

		// This simple widget is just going to draw a box on the screen.   
		fill_rect(c, rect, rgb_pixel(red, green, blue));
	}
};

//  ----------------------------------------------------------------------------

class win : public drawable_window {
	/*
	Here I am going to define our window.  In general, you can define as
	many window types as you like and make as many instances of them as you want.
	In this example I am only making one though.
	*/
public:
	win(
		) : // All widgets take their parent window as an argument to their constructor.
		c(*this),
		b(*this),
		cb(*this, rectangle(100, 100, 200, 200), 0, 0, 255), // the color_box will be blue and 101 pixels wide and tall
		mbar(*this) {
		// tell our button to put itself at the position (10,60). 
		b.set_pos(10, 60);
		b.set_name("button");

		// lets put the label 5 pixels below the button
		c.set_pos(b.left(), b.bottom() + 5);


		// set which function should get called when the button gets clicked.  In this case we want
		// the on_button_clicked member to be called on *this.
		b.set_click_handler(*this, &win::on_button_clicked);
		// Alternatively, if you have a compiler which supports the lambda functions from the
		// new C++ standard then you can use a lambda function instead of telling the click
		// handler to call one of the member functions.  So for example, you could do this
		// instead (uncomment the code if you have C++0x support):
		/*
		b.set_click_handler([&](){
		++counter;
		ostringstream sout;
		sout << "Counter: " << counter;
		c.set_text(sout.str());
		});
		*/
		// In general, all the functions which register events can take either member 
		// functions or lambda functions.


		// Lets also make a simple menu bar.  
		// First we say how many menus we want in our menu bar.  In this example we only want 1.
		mbar.set_number_of_menus(1);
		// Now we set the name of our menu.  The 'M' means that the M in Menu will be underlined
		// and the user will be able to select it by hitting alt+M
		mbar.set_menu_name(0, "Menu", 'M');

		// Now we add some items to the menu.  Note that items in a menu are listed in the
		// order in which they were added.

		// First lets make a menu item that does the same thing as our button does when it is clicked.
		// Again, the 'C' means the C in Click is underlined in the menu. 
		mbar.menu(0).add_menu_item(menu_item_text("Click Button!", *this, &win::on_button_clicked, 'C'));
		// lets add a separator (i.e. a horizontal separating line) to the menu
		mbar.menu(0).add_menu_item(menu_item_separator());
		// Now lets make a menu item that calls show_about when the user selects it.  
		mbar.menu(0).add_menu_item(menu_item_text("About", *this, &win::show_about, 'A'));


		// set the size of this window
		set_size(430, 380);

		counter = 0;

		set_title("dlib gui example");
		show();
	}

	~win(
		) {
		// You should always call close_window() in the destructor of window
		// objects to ensure that no events will be sent to this window while 
		// it is being destructed.  
		close_window();
	}

private:

	void on_button_clicked(
		) {
		// when someone clicks our button it will increment the counter and 
		// display it in our label c.
		++counter;
		ostringstream sout;
		sout << "counter: " << counter;
		c.set_text(sout.str());
	}

	void show_about(
		) {
		message_box("About", "This is a dlib gui example program");
	}

	unsigned long counter;
	label c;
	button b;
	color_box cb;
	menu_bar mbar;
};

//  ----------------------------------------------------------------------------

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

	// create our window
	win my_window;


	// wait until the user closes this window before we let the program 
	// terminate.
	my_window.wait_until_closed();
    system("pause");
    return 0;
}

