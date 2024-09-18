#include <guisan.hpp>

namespace WidgetsExample
{

    /*
     * List boxes and dropdowns needs an instance of a listmodel
     * to know what elements they have.
     */
    class DemoListModel : public gcn::ListModel
    {
    public:
        int getNumberOfElements() override { return 5; }

        std::string getElementAt(int i) override
        {
            switch (i)
            {
                case 0: return std::string("zero");
                case 1: return std::string("one");
                case 2: return std::string("two");
                case 3: return std::string("three");
                case 4: return std::string("four");
                default: // Just to keep warnings away
                    return std::string("");
            }
        }
    };

    class MainContainer
    {
    public:
        MainContainer(gcn::Gui& gui, int width, int height)
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
            /*
             * Create all the widgets
             */
            label = new gcn::Label("Label");

            image = gcn::Image::load("guisan.png");
            icon = new gcn::Icon(image);

            button = new gcn::Button("Button");

            textField = new gcn::TextField("Text field");

            textBox = new gcn::TextBox("Lorem ipsum dolor sit amet consectetur\n"
                                       "adipiscing elit Integer vitae ultrices\n"
                                       "eros Curabitur malesuada dolor imperdieat\n"
                                       "ante facilisis ut convallis sem rutrum\n"
                                       "Praesent consequat urna convallis leo\n"
                                       "aliquam pellentesque Integer laoreet enim\n"
                                       "vehicula libero blandit at pellentesque\n"
                                       "ipsum vehicula Mauris id turpis hendrerit\n"
                                       "tempor velit nec hendrerit nulla");
            textBoxScrollArea = new gcn::ScrollArea(textBox);
            textBoxScrollArea->setWidth(270);
            textBoxScrollArea->setHeight(100);
            textBoxScrollArea->setFrameSize(1);

            listBox = new gcn::ListBox(&demoListModel);
            listBox->setFrameSize(1);

            dropDown = new gcn::DropDown(&demoListModel);

            checkBox1 = new gcn::CheckBox("Checkbox 1");
            checkBox2 = new gcn::CheckBox("Checkbox 2");

            radioButton1 = new gcn::RadioButton("Radio Button 1", "radiogroup", true);
            radioButton2 = new gcn::RadioButton("Radio Button 2", "radiogroup");
            radioButton3 = new gcn::RadioButton("Radio Button 3", "radiogroup");

            slider = new gcn::Slider(0, 10);
            slider->setSize(100, 10);

            window = new gcn::Window("I am a window  Drag me");
            window->setBaseColor(gcn::Color(212, 255, 150, 190));

            progress = new gcn::ProgressBar(0, 100, 30);
            progress->setCaption("Loading");
            progress->setWidth(100);

            guisanLogoImage = gcn::Image::load("guisan-logo.png");
            guisanLogoIcon = new gcn::Icon(guisanLogoImage);
            window->add(guisanLogoIcon);
            window->resizeToContent();

            nestedSlider = new gcn::Slider(0, 10);
            nestedSlider->setSize(100, 10);

            nestedContainer = new gcn::Container();
            nestedContainer->setSize(400, 200);
            nestedContainer->add(nestedSlider, 50, 70);

            nestedScrollArea = new gcn::ScrollArea(nestedContainer);
            nestedScrollArea->setSize(180, 90);
            nestedScrollArea->setFrameSize(1);

            /*
             * Add them to the top container
             */
            top->add(label, 290, 10);
            top->add(icon, 10, 10);
            top->add(button, 325, 10);
            top->add(textField, 375, 10);
            top->add(textBoxScrollArea, 290, 50);
            top->add(listBox, 290, 200);
            top->add(dropDown, 580, 10);
            top->add(checkBox1, 580, 50);
            top->add(checkBox2, 580, 70);
            top->add(radioButton1, 580, 120);
            top->add(radioButton2, 580, 140);
            top->add(radioButton3, 580, 160);
            top->add(slider, 580, 200);
            top->add(window, 100, 350);
            top->add(nestedScrollArea, 440, 350);

            top->add(progress, 580, 200);
        }

        ~MainContainer()
        {
            delete font;

            /*
             * Widgets
             */
            delete top;
            delete label;
            delete icon;
            delete button;
            delete textField;
            delete textBox;
            delete textBoxScrollArea;
            delete listBox;
            delete dropDown;
            delete checkBox1;
            delete checkBox2;
            delete radioButton1;
            delete radioButton2;
            delete radioButton3;
            delete slider;
            delete window;
            delete progress;
            delete guisanLogoIcon;
            delete guisanLogoImage;
            delete nestedScrollArea;
            delete nestedContainer;
            delete nestedSlider;
        }

    private:
        gcn::ImageFont* font; // A font

        /*
         * All of the widgets
         */
        gcn::Container* top; // A top container
        DemoListModel demoListModel;
        gcn::Label* label; // A label
        gcn::Icon* icon; // An icon (image)
        gcn::Button* button; // A button
        gcn::TextField* textField; // One-line text field
        gcn::TextBox* textBox; // Multi-line text box
        gcn::ScrollArea* textBoxScrollArea; // Scroll area for the text box
        gcn::ListBox* listBox; // A list box
        gcn::DropDown* dropDown; // Drop down
        gcn::CheckBox* checkBox1; // Two checkboxes
        gcn::CheckBox* checkBox2;
        gcn::RadioButton* radioButton1; // Three radio buttons
        gcn::RadioButton* radioButton2;
        gcn::RadioButton* radioButton3;
        gcn::Slider* slider; // A slider
        gcn::Image* image; // An image for the icon
        gcn::Window* window;
        gcn::ProgressBar* progress;
        gcn::Image* guisanLogoImage;
        gcn::Icon* guisanLogoIcon;
        gcn::ScrollArea* nestedScrollArea;
        gcn::Container* nestedContainer;
        gcn::Slider* nestedSlider;
    };

} // namespace WidgetsExample
