/**
 * SDL widgets example for Guichan.
 */

// Include all necessary headers.
#include <iostream>
#include <guisan.hpp>

#include "./sdl_helper.hpp"
#include "./widgets_example.hpp"

int main(int argc, char** argv)
{
	try {
		sdl::Application application("guisan SDL2 widget example", 700, 480);
		WidgetsExample::MainContainer mainContainer(application.getGui(), 700, 480);

		application.run();
	}
	/*
	 * Catch all Guichan exceptions
	 */
	catch (const gcn::Exception& e) {
		std::cerr << e.getMessage() << std::endl;
		return 1;
	}
	/*
	 * Catch all Std exceptions
	 */
	catch (const std::exception& e) {
		std::cerr << "Std exception: " << e.what() << std::endl;
		return 1;
	}
	/*
	 * Catch all Unknown exceptions
	 */
	catch (...) {
		std::cerr << "Unknown exception" << std::endl;
		return 1;
	}

	return 0;
}
