/*
 * Code that sets up an SDL application with Guichan
 * using the Guichan SDL back end.
 */

#include <guisan.hpp>
#include <guisan/sdl.hpp>

namespace sdl
{
    class Application
    {
    public:
        explicit Application(const char* title, int width = 640, int height = 480)
        {
            /*
             * Here we initialize SDL as we would do with any SDL application.
             */
            SDL_Init(SDL_INIT_VIDEO);

            /**
             * Initialises the SDL application. This function creates the global
             * Gui object that can be populated by various examples.
             */
            window = SDL_CreateWindow(
                title, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width, height, 0);

            screen = SDL_GetWindowSurface(window);

            // We want to enable key repeat
            //SDL_EnableKeyRepeat(SDL_DEFAULT_REPEAT_DELAY, SDL_DEFAULT_REPEAT_INTERVAL);

            // Set the target for the graphics object to be the screen.
            // In other words, we will draw to the screen.
            // Note, any surface will do, it doesn't have to be the screen.
            graphics.setTarget(screen);

            // The ImageLoader in use is static and must be set to be
            // able to load images
            gcn::Image::setImageLoader(&imageLoader);
            /*
             * Last but not least it's time to initialize the gui with Guichan stuff.
             */

            // Set gui to use the SDLGraphics object.
            gui.setGraphics(&graphics);
            // Set gui to use the SDLInput object
            gui.setInput(&input);
        }

        ~Application()
        {
            SDL_FreeSurface(screen);
            SDL_DestroyWindow(window);
            /**
             * Halts the SDL application.
             */
            SDL_Quit();
        }

		gcn::Gui& getGui() { return gui; }

        /**
         * Runs the SDL application.
         */
        void run()
        {
            bool running = true;
            // The main loop
            while (running)
            {
                // Check user input
                SDL_Event event;
                while (SDL_PollEvent(&event))
                {
                    if (event.type == SDL_KEYDOWN)
                    {
                        if (event.key.keysym.sym == SDLK_ESCAPE)
                        {
                            running = false;
                        }
                        if (event.key.keysym.sym == SDLK_f && event.key.keysym.mod & KMOD_CTRL)
                        {
                            const Uint32 flags =
                                SDL_GetWindowFlags(window) & SDL_WINDOW_FULLSCREEN_DESKTOP;
                            SDL_SetWindowFullscreen(window, flags ^ SDL_WINDOW_FULLSCREEN_DESKTOP);
                            SDL_FreeSurface(screen);
                            screen = SDL_GetWindowSurface(window);
                            graphics.setTarget(screen);
                        }
                    } else if (event.type == SDL_QUIT)
                    {
                        running = false;
                    }

                    // After we have manually checked user input with SDL
                    // for any attempt by the user to halt the application
                    // we feed the input to Guichan by pushing the input
                    // to the Input object.
                    input.pushInput(event);
                }
                // Now we let the Gui object perform its logic.
                gui.logic();
                // Now we let the Gui object draw itself.
                gui.draw();
                // Finally we update the screen.
                SDL_UpdateWindowSurface(window);
            }
        }

    private:
        gcn::Gui gui;
        /*
         * SDL Stuff we need
         */
        SDL_Window* window;
        SDL_Surface* screen;

        // All back ends contain objects to make Guichan work on a specific target
        // - in this case SDL -
        // and they are a Graphics object to make Guichan able to draw itself using SDL,
        // an input object to make Guichan able to get user input using SDL
        // and an ImageLoader object to make Guichan able to load images using SDL.
        gcn::SDLGraphics graphics;
        gcn::SDLInput input;
        gcn::SDLImageLoader imageLoader;
    };

} // namespace sdl
