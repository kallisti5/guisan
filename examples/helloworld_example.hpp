#include <guisan.hpp>

namespace HelloWorldExample
{

    class MainContainer
    {
    public:
        MainContainer(gcn::Gui& gui, int width = 680, int height = 480)
        {
            // Load the image font.
            font = new gcn::ImageFont(
                "fixedfont.bmp", " abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789");
            // The global font is static and must be set.
            gcn::Widget::setGlobalFont(font);

            top = new gcn::Container();
            // Set the dimension of the top container to match the screen.
            top->setDimension(gcn::Rectangle(0, 0, width, height));
            // Set the top container
            gui.setTop(top);

            // Create a label with test hello world
            label = new gcn::Label("Hello World");
            // Set the labels position
            label->setPosition(280, 220);
            // Add the label to the top container
            top->add(label);
        }

        ~MainContainer()
        {
            /*
             * Destroy font
             */
            delete font;

            /*
             * Widgets
             */
            delete top;
            delete label;
        }

    private:
        gcn::ImageFont* font; // A font

        /*
         * All of the widgets
         */
        gcn::Container* top; // A top container
        gcn::Label* label; // A label
    };

} // namespace HelloWorldExample
