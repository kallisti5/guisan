/**
 * OpenGL/SDL widgets example for Guichan.
 */

#include <iostream>
#include <guisan.hpp>

#include "./opengl_helper.hpp"
#include "./widgets_example.hpp"

int main(int argc, char **argv)
{
	try
	{
		opengl::Application application("guisan OpenGL hello world", 700, 480);
		WidgetsExample::MainContainer mainContainer(application.getGui(), 700, 480);

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
