/*
 * Code that sets up an opengl application with Guichan
 * using the Guichan SDL back end.
 */

#include <SDL.h>
#include <guisan.hpp>
#include <guisan/opengl.hpp>
#include <guisan/opengl/openglsdlimageloader.hpp>
#include <guisan/sdl.hpp>

#if defined(_WIN32)
# include <windows.h>
// Sometimes windows.h defines DELETE which causes a compilation
// error in a Guichan header.
# if defined(DELETE)
#  undef DELETE
# endif
#endif

#if defined(__APPLE__)
# include <OpenGL/gl.h>
#else
# include <GL/gl.h>
#endif

namespace opengl
{

    class Application
    {
    public:
        explicit Application(const char* title, int width = 680, int height = 480)
        {
            /*
             * Here we initialize SDL as we would do with any SDL application.
             */
            SDL_Init(SDL_INIT_VIDEO);

            /**
             * Initialises the SDL application. This function creates the global
             * Gui object that can be populated by various examples.
             */

            window = SDL_CreateWindow(title,
                                      SDL_WINDOWPOS_UNDEFINED,
                                      SDL_WINDOWPOS_UNDEFINED,
                                      width,
                                      height,
                                      SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN);

            // Attach GL context to our window
            context = SDL_GL_CreateContext(window);

            // Setup OpenGL
            glViewport(0, 0, width, height);
            glClearColor(0.0f, 0.0f, 0.0f, 0.0f);

            // We want to enable key repeat
            //SDL_EnableKeyRepeat(SDL_DEFAULT_REPEAT_DELAY, SDL_DEFAULT_REPEAT_INTERVAL);

            // The ImageLoader in use is static and must be set to be
            // able to load images
            gcn::Image::setImageLoader(&imageLoader);
            // We need to tell OpenGL graphics how big the screen is.
            graphics.setTargetPlane(width, height);

            /*
             * Last but not least it's time to initialize and create the gui
             * with Guichan stuff.
             */
            // Set gui to use the SDLGraphics object.
            gui.setGraphics(&graphics);
            // Set gui to use the SDLInput object
            gui.setInput(&input);
        }

        ~Application()
        {
            SDL_GL_DeleteContext(context);
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
                            printf("TODO: fullscreen!");
                        }
                    } else if (event.type == SDL_QUIT)
                    {
                        running = false;
                    }

                    // After we have manually checked user input with SDL for
                    // any attempt by the user to halt the application we feed
                    // the input to Guichan by pushing the input to the Input
                    // object.
                    input.pushInput(event);
                }

                // Now we let the Gui object perform its logic.
                gui.logic();

                // Draw the gui
                gui.draw();

                // Update the screen
                SDL_GL_SwapWindow(window);
            }
        }

    private:
        gcn::Gui gui;

        /*
         * SDL Stuff we need
         */
        SDL_Window* window;
        SDL_GLContext context;

        /*
         * Guichan OpenGL/SDL stuff we need
         */
        gcn::SDLInput input; // Input driver
        gcn::OpenGLGraphics graphics; // Graphics driver
        gcn::OpenGLSDLImageLoader imageLoader; // For loading images
    };

} // namespace opengl
