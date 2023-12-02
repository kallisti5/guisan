/**
 * SDL Hello World example for Guichan.
 */

#include <guisan.hpp>
#include <iostream>

#include "./helloworld_example.hpp"
#include "./sdl_helper.hpp"

int main(int argc, char **argv)
{
	try
	{
		sdl::Application application("guisan SDL2 hello world");
		HelloWorldExample::MainContainer mainContainer(application.getGui());
		application.run();
	}
	/*
	 * Catch all Guichan exceptions
	 */
	catch (const gcn::Exception& e)
	{
		std::cerr << e.getMessage() << std::endl;
		return 1;
	}
	/*
	 * Catch all Std exceptions
	 */
	catch (const std::exception& e)
	{
		std::cerr << "Std exception: " << e.what() << std::endl;
		return 1;
	}
	/*
	 * Catch all Unknown exceptions
	 */
	catch (...)
	{
		std::cerr << "Unknown exception" << std::endl;
		return 1;
	}

	return 0;
}
