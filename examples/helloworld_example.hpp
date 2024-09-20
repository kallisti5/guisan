#include <guisan.hpp>
#include <memory>

namespace HelloWorldExample
{

    class MainContainer
    {
    public:
        MainContainer(gcn::Gui& gui, int width = 680, int height = 480)
        {
            // Load the image font.
            font = std::make_unique<gcn::ImageFont>(
                "fixedfont.bmp", " abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789");
            // The global font is static and must be set.
            gcn::Widget::setGlobalFont(font.get());

            top = std::make_unique<gcn::Container>();
            // Set the dimension of the top container to match the screen.
            top->setDimension(gcn::Rectangle(0, 0, width, height));
            // Set the top container
            gui.setTop(top.get());

            // Create a label with test hello world
            label = std::make_unique<gcn::Label>("Hello World");
            // Set the labels position
            label->setPosition(280, 220);
            // Add the label to the top container
            top->add(label.get());
        }

        ~MainContainer() = default;

    private:
        std::unique_ptr<gcn::ImageFont> font; // A font

        /*
         * All of the widgets
         */
        std::unique_ptr<gcn::Container> top; // A top container
        std::unique_ptr<gcn::Label> label; // A label
    };

} // namespace HelloWorldExample
