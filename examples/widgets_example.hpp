#include <guisan.hpp>
#include <memory>

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
            font = std::make_unique<gcn::ImageFont>(
                "fixedfont.bmp", " abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789");
            // The global font is static and must be set.
            gcn::Widget::setGlobalFont(font.get());

            top = std::make_unique < gcn::Container>();
            // Set the dimension of the top container to match the screen.
            top->setDimension(gcn::Rectangle(0, 0, width, height));
            // Set the top container
            gui.setTop(top.get());
            /*
             * Create all the widgets
             */
            label = std::make_unique<gcn::Label>("Label");

            image.reset(gcn::Image::load("guisan.png"));
            icon = std::make_unique<gcn::Icon>(image.get());

            button = std::make_unique<gcn::Button>("Button");

            textField = std::make_unique<gcn::TextField>("Text field");

            textBox = std::make_unique<gcn::TextBox>("Lorem ipsum dolor sit amet consectetur\n"
                                                     "adipiscing elit Integer vitae ultrices\n"
                                                     "eros Curabitur malesuada dolor imperdieat\n"
                                                     "ante facilisis ut convallis sem rutrum\n"
                                                     "Praesent consequat urna convallis leo\n"
                                                     "aliquam pellentesque Integer laoreet enim\n"
                                                     "vehicula libero blandit at pellentesque\n"
                                                     "ipsum vehicula Mauris id turpis hendrerit\n"
                                                     "tempor velit nec hendrerit nulla");
            textBoxScrollArea = std::make_unique<gcn::ScrollArea>(textBox.get());
            textBoxScrollArea->setWidth(270);
            textBoxScrollArea->setHeight(100);
            textBoxScrollArea->setFrameSize(1);

            listBox = std::make_unique<gcn::ListBox>(&demoListModel);
            listBox->setFrameSize(1);

            dropDown = std::make_unique<gcn::DropDown>(&demoListModel);

            checkBox1 = std::make_unique<gcn::CheckBox>("Checkbox 1");
            checkBox2 = std::make_unique<gcn::CheckBox>("Checkbox 2");

            radioButton1 = std::make_unique<gcn::RadioButton>("Radio Button 1", "radiogroup", true);
            radioButton2 = std::make_unique<gcn::RadioButton>("Radio Button 2", "radiogroup");
            radioButton3 = std::make_unique<gcn::RadioButton>("Radio Button 3", "radiogroup");

            slider = std::make_unique<gcn::Slider>(0, 10);
            slider->setSize(100, 10);

            window = std::make_unique<gcn::Window>("I am a window  Drag me");
            window->setBaseColor(gcn::Color(212, 255, 150, 190));

            progress = std::make_unique<gcn::ProgressBar>(0, 100, 30);
            progress->setCaption("Loading");
            progress->setWidth(100);

            guisanLogoImage.reset(gcn::Image::load("guisan-logo.png"));
            guisanLogoIcon = std::make_unique<gcn::Icon>(guisanLogoImage.get());
            window->add(guisanLogoIcon.get());
            window->resizeToContent();

            nestedSlider = std::make_unique<gcn::Slider>(0, 10);
            nestedSlider->setSize(100, 10);

            nestedContainer = std::make_unique<gcn::Container>();
            nestedContainer->setSize(400, 200);
            nestedContainer->add(nestedSlider.get(), 50, 70);

            nestedScrollArea = std::make_unique<gcn::ScrollArea>(nestedContainer.get());
            nestedScrollArea->setSize(180, 90);
            nestedScrollArea->setFrameSize(1);

            /*
             * Add them to the top container
             */
            top->add(label.get(), 290, 10);
            top->add(icon.get(), 10, 10);
            top->add(button.get(), 325, 10);
            top->add(textField.get(), 375, 10);
            top->add(textBoxScrollArea.get(), 290, 50);
            top->add(listBox.get(), 290, 200);
            top->add(dropDown.get(), 580, 10);
            top->add(checkBox1.get(), 580, 50);
            top->add(checkBox2.get(), 580, 70);
            top->add(radioButton1.get(), 580, 120);
            top->add(radioButton2.get(), 580, 140);
            top->add(radioButton3.get(), 580, 160);
            top->add(slider.get(), 580, 200);
            top->add(window.get(), 100, 350);
            top->add(nestedScrollArea.get(), 440, 350);

            top->add(progress.get(), 580, 200);
        }

        ~MainContainer() = default;

    private:
        std::unique_ptr<gcn::ImageFont> font; // A font

        /*
         * All of the widgets
         */
        std::unique_ptr<gcn::Container> top; // A top container
        DemoListModel demoListModel;
        std::unique_ptr<gcn::Label> label; // A label
        std::unique_ptr<gcn::Icon> icon; // An icon (image)
        std::unique_ptr<gcn::Button> button; // A button
        std::unique_ptr<gcn::TextField> textField; // One-line text field
        std::unique_ptr<gcn::TextBox> textBox; // Multi-line text box
        std::unique_ptr<gcn::ScrollArea> textBoxScrollArea; // Scroll area for the text box
        std::unique_ptr<gcn::ListBox> listBox; // A list box
        std::unique_ptr<gcn::DropDown> dropDown; // Drop down
        std::unique_ptr<gcn::CheckBox> checkBox1; // Two checkboxes
        std::unique_ptr<gcn::CheckBox> checkBox2;
        std::unique_ptr<gcn::RadioButton> radioButton1; // Three radio buttons
        std::unique_ptr<gcn::RadioButton> radioButton2;
        std::unique_ptr<gcn::RadioButton> radioButton3;
        std::unique_ptr<gcn::Slider> slider; // A slider
        std::unique_ptr<gcn::Image> image; // An image for the icon
        std::unique_ptr<gcn::Window> window;
        std::unique_ptr<gcn::ProgressBar> progress;
        std::unique_ptr<gcn::Image> guisanLogoImage;
        std::unique_ptr<gcn::Icon> guisanLogoIcon;
        std::unique_ptr<gcn::ScrollArea> nestedScrollArea;
        std::unique_ptr<gcn::Container> nestedContainer;
        std::unique_ptr<gcn::Slider> nestedSlider;
    };

} // namespace WidgetsExample
