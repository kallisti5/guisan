/**
 * SDL ActionListner example for Guichan.
 */

// Include all necessary headers.
#include <iostream>
#include <sstream>         // Used for int to string conversion
#include <guisan.hpp>
#include <guisan/sdl.hpp>
#include "SDL.h"

/*
 * Common stuff we need
 */
bool running = true;

/*
 * SDL Stuff we need
 */
SDL_Surface* sdlScreen;
SDL_Window* sdlWindow;
SDL_Event event;

/*
 * Guichan SDL stuff we need
 */
gcn::SDLInput* input;             // Input driver
gcn::SDLGraphics* graphics;       // Graphics driver
gcn::SDLImageLoader* imageLoader; // For loading images

/*
 * Guichan stuff we need
 */
gcn::Gui* gui;            // A Gui object - binds it all together
gcn::Container* top;      // A top container
gcn::ImageFont* font;     // A font
gcn::Button* button1;     // A button for actionlistening (triggers msgbox)
gcn::Label* label1;       // And a label for button1
gcn::Button* button2;     // Button for InputBox
gcn::Label* label2;       // Label for inputbox
gcn::MessageBox* msgBox = NULL;
gcn::InputBox* inputBox = NULL;

/*
 * To be able to recieve actions we must have a class inheriting from
 * ActionListener and implementing the action function.
 * When an action is generated in a Widget (i.e when a button is clicked)
 * that widget calls the action function for all its action listeners.
 * Below we make a class to be able to recieve our buttons actions.
 */
class ButtonActionListener : public gcn::ActionListener
{
public:
	// Implement the action function in ActionListener to recieve actions
	// The eventId tells us which widget called the action function.
	void action(const gcn::ActionEvent& actionEvent)
	{
		// Here we use the widget pointer to check which widget the action
        // originated from.
		if (actionEvent.getSource() == msgBox)
		{
			msgBox->setVisible(false);
			label1->setCaption("You have been rick rolled");
			// Adjust the label to fit the new caption
			label1->adjustSize();
			top->remove(msgBox);
		} 
		else if (actionEvent.getSource() == button1) 
		{
			if(msgBox)
			{
				delete msgBox;
				msgBox = NULL;
			}
			msgBox = new gcn::MessageBox("Rick Astley", "Never gonna give you up");
			msgBox->setVisible(true);
			msgBox->addActionListener(this);
			top->add(msgBox, 270, 180);
		}
		else if (actionEvent.getSource() == button2)
		{
			if(inputBox)
			{
				delete inputBox;
				inputBox = NULL;
			}
			inputBox = new gcn::InputBox("Name request", "Enter your name below", "Here you go", "No way");
			inputBox->setVisible(true);
			inputBox->addActionListener(this);
			top->add(inputBox, 270, 180);
		}
		else if (actionEvent.getSource() == inputBox)
		{
			inputBox->setVisible(false);
			if(inputBox->getClickedButton() == 1)
			{
				label2->setCaption("No name");
			}
			else
			{
				label2->setCaption("Your name is " + inputBox->getText());
			}
			label2->adjustSize();
		}
	}
};

ButtonActionListener* buttonActionListener; // A pointer to the above class

/**
 * Initializes the Hello World
 */
void init()
{
	/*
	 * Here we initialize SDL as we would do with any SDL application.
	 */
        SDL_Init(SDL_INIT_VIDEO);
        sdlWindow = SDL_CreateWindow("guisan SDL2 message box example",
                SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 640, 480, 0);

        sdlScreen = SDL_GetWindowSurface(sdlWindow);

	// We want to enable key repeat
	//SDL_EnableKeyRepeat(SDL_DEFAULT_REPEAT_DELAY, SDL_DEFAULT_REPEAT_INTERVAL);

	/*
	 * Now it's time for Guichan SDL stuff
	 */
	imageLoader = new gcn::SDLImageLoader();
	// The ImageLoader in use is static and must be set to be
	// able to load images
	gcn::Image::setImageLoader(imageLoader);
	graphics = new gcn::SDLGraphics();
	// Set the target for the graphics object to be the screen.
	// In other words, we will draw to the screen.
	// Note, any surface will do, it doesn't have to be the screen.
	graphics->setTarget(sdlScreen);
	input = new gcn::SDLInput();

	/*
	 * Last but not least it's time to initialize and create the gui
	 * with Guichan stuff.
	 */
	top = new gcn::Container();
	// Set the dimension of the top container to match the screen.
	top->setDimension(gcn::Rectangle(0, 0, 640, 480));
	gui = new gcn::Gui();
	// Set gui to use the SDLGraphics object.
	gui->setGraphics(graphics);
	// Set gui to use the SDLInput object
	gui->setInput(input);
	// Set the top container
	gui->setTop(top);
	// Load the image font.
	font = new gcn::ImageFont("fixedfont.bmp", " abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789");
	// The global font is static and must be set.
	gcn::Widget::setGlobalFont(font);

	// Create buttons
	button1 = new gcn::Button("Click me");
	button2 = new gcn::Button("Enter your name");
	// Set the buttons position
	button1->setPosition(120, 230);
	button2->setPosition(420, 230);
	// Add the buttons to the top container
	top->add(button1);
	top->add(button2);

	// Create labels
	label1 = new gcn::Label("Get rick rolled");
	label2 = new gcn::Label("What is your name");
	// Set the labels position
	label1->setPosition(100, 200);
	label2->setPosition(400, 200);
	// Add the labels to the top container
	top->add(label1);
	top->add(label2);

	// Set the buttons action event id's.
	button1->setActionEventId("button1");
	button2->setActionEventId("button2");

	// Make an instance of the ButtonActionListener
	buttonActionListener = new ButtonActionListener();

	// Add the ButtonActionListener to the buttons action listeners
	button1->addActionListener(buttonActionListener);
	button2->addActionListener(buttonActionListener);
}

/**
 * Halts the application
 */
void halt()
{
	/*
	 * Destroy our action listener
	 */
	delete buttonActionListener;

	/*
	 * Destroy Guichan stuff
	 */
	if(msgBox != NULL)
	{
		delete msgBox;
	}
	if(inputBox != NULL)
	{
		delete inputBox;
	}
	delete label1;
	delete button1;
	delete label2;
	delete button2;
	delete font;
	delete top;
	delete gui;

	/*
	 * Destroy Guichan SDL stuff
	 */
	delete input;
	delete graphics;
	delete imageLoader;

	/*
	 * Destroy SDL stuff
	 */
	SDL_Quit();
}

/**
 * Checks input. On escape halt the application.
 */
void checkInput()
{
	/*
	 * Poll SDL events
	 */
	while(SDL_PollEvent(&event))
	{
		if (event.type == SDL_KEYDOWN)
		{
			if (event.key.keysym.sym == SDLK_ESCAPE)
			{
				running = false;
			}
			if (event.key.keysym.sym == SDLK_f)
			{
				if (event.key.keysym.mod & KMOD_CTRL)
				{
					printf("TODO: fullscreen!");
				}
			}
		}
		else if(event.type == SDL_QUIT)
		{
			running = false;
		}

		/*
		 * Now that we are done polling and using SDL events we pass
		 * the leftovers to the SDLInput object to later be handled by
		 * the Gui. (This example doesn't require us to do this 'cause a
		 * label doesn't use input. But will do it anyway to show how to
		 * set up an SDL application with Guichan.)
		 */
		input->pushInput(event);
	}
}

/**
 * Runs the application
 */
void run()
{
	while(running)
	{
		// Poll input
		checkInput();
		// Let the gui perform it's logic (like handle input)
		gui->logic();
		// Draw the gui
		gui->draw();
		// Update the screen
		SDL_UpdateWindowSurface(sdlWindow);
	}
}

int main(int argc, char **argv)
{
	try
	{
 		init();
		run();
		halt();
	}
	/*
	 * Catch all Guichan exceptions
	 */
	catch (gcn::Exception e)
	{
		std::cerr << e.getMessage() << std::endl;
		return 1;
	}
	/*
	 * Catch all Std exceptions
	 */
	catch (std::exception e)
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
