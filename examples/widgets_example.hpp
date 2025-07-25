#include <guisan.hpp>

#include <algorithm>
#include <memory>

namespace WidgetsExample
{

    class MainContainer : public gcn::ActionListener
    {
    public:
        MainContainer(gcn::Gui& gui, int width, int height) :
            demoListModel{{"zero", "one", "two", "three", "four"}}
        {
#if USE_SDL2_TTF
            TTF_Init();

            trueFont = std::make_unique<gcn::SDLTrueTypeFont>("dactylographe.ttf", 12);
#endif
            // Load the image font.
            imageFont = std::make_unique<gcn::ImageFont>(
                "fixedfont.bmp", " abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789");

            // The global font is static and must be set.
#if USE_SDL2_TTF
            gcn::Widget::setGlobalFont(trueFont.get());
#else
            gcn::Widget::setGlobalFont(imageFont.get());
#endif
            top = std::make_unique<gcn::Container>();
            // Set the dimension of the top container to match the screen.
            top->setDimension(gcn::Rectangle(0, 0, width, height));
            // Set the top container
            gui.setTop(top.get());

            guisanLogoImage.reset(gcn::Image::load("guisan-logo.png"));
            /*
             * Create all the widgets
             */
            label = std::make_unique<gcn::Label>("Label");

            icon = std::make_unique<gcn::Icon>("guisan.png");

            button = std::make_unique<gcn::Button>("Button");

            button->setHotKey('b');
            button->addActionListener(this);

            imageButton = std::make_unique<gcn::ImageButton>("guisan-logo.png");

            imageButton->setSize(220, 90);
            imageButton->setHotKey('g');
            imageButton->addActionListener(this);

            imageTextButton = std::make_unique<gcn::ImageTextButton>("guisan-logo.png", "Change color");
            imageTextButton->setSize(220, 100);
            imageTextButton->setAlignment(gcn::ImageTextButton::TOP);
            imageTextButton->addActionListener(this);

            inputBox = std::make_unique<gcn::InputBox>("Change name", " Set name of label ");

            inputBox->setVisible(false);
            inputBox->setMovable(true);
            inputBox->setFrameSize(1);
            inputBox->addActionListener(this);

            textField = std::make_unique<gcn::TextField>("Text field");

            passwordField = std::make_unique<gcn::TextField>("password");
            passwordField->setMaskingChar('*');

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

            toggleButton = std::make_unique<gcn::ToggleButton>("Toggle font");
            toggleButton->addActionListener(this);

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

            std::vector<std::string> button_names{"0", "25", "50", "75", "100", "-1", "+1"};
            messageBox = std::make_unique<gcn::MessageBox>("Change progression",
                                                           "Set progression value",
                                                           button_names);
            messageBox->setMovable(true);
            messageBox->setFrameSize(1);
            messageBox->addActionListener(this);

            guisanLogoIcon = std::make_unique<gcn::Icon>(guisanLogoImage);
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
            top->add(imageButton.get(), 10, 290);
            top->add(imageTextButton.get(), 10, 380);
            top->add(textField.get(), 375, 10);
            top->add(passwordField.get(), 375, 30);
            top->add(textBoxScrollArea.get(), 290, 50);
            top->add(inputBox.get(), 270, 180);
            top->add(listBox.get(), 290, 200);
            top->add(dropDown.get(), 580, 10);
            top->add(checkBox1.get(), 580, 50);
            top->add(checkBox2.get(), 580, 70);
            top->add(toggleButton.get(), 580, 90);
            top->add(radioButton1.get(), 580, 120);
            top->add(radioButton2.get(), 580, 140);
            top->add(radioButton3.get(), 580, 160);
            top->add(slider.get(), 580, 180);
            top->add(window.get(), 100, 350);
            top->add(nestedScrollArea.get(), 440, 350);

            top->add(progress.get(), 580, 200);
            top->add(messageBox.get(), 480, 220);
        }

        ~MainContainer() = default;

        // Implement the action function in ActionListener to receive actions
        // The eventId tells us which widget called the action function.
        void action(const gcn::ActionEvent& actionEvent) override {
            if (actionEvent.getSource() == button.get())
            {
                inputBox->setVisible(true);
                top->moveToTop(inputBox.get());
            }
            else if (actionEvent.getSource() == imageButton.get()
                     || actionEvent.getSource() == imageTextButton.get())
            {
                const gcn::Color colours[] = {gcn::Color(212, 255, 150, 190),
                                              gcn::Color(212, 0, 0, 190),
                                              gcn::Color(0, 0, 150, 190)};
                const auto it = std::find(std::begin(colours), std::end(colours), window->getBaseColor());
                window->setBaseColor(
                    colours[(std::distance(std::begin(colours), it) + 1) % std::size(colours)]);
            }
            else if (actionEvent.getSource() == inputBox.get())
            {
                inputBox->setVisible(false);
                if (inputBox->getClickedButton() == 0)
                {
                    label->setCaption(inputBox->getText());
                    label->adjustSize();
                }
            }
            else if (actionEvent.getSource() == toggleButton.get())
            {
                if (gcn::Widget::getGlobalFont() == imageFont.get())
                {
#if USE_SDL2_TTF
                    gcn::Widget::setGlobalFont(trueFont.get());
#endif
                }
                else
                {
                    gcn::Widget::setGlobalFont(imageFont.get());
                }
            }
            else if (actionEvent.getSource() == messageBox.get())
            {
                switch (messageBox->getClickedButton())
                {
                    default:
                    case 0: progress->setValue(0); break;
                    case 1: progress->setValue(25); break;
                    case 2: progress->setValue(50); break;
                    case 3: progress->setValue(75); break;
                    case 4: progress->setValue(100); break;
                    case 5: progress->setValue(progress->getValue() - 1); break;
                    case 6: progress->setValue(progress->getValue() + 1); break;
                }
            }
        }

    private:
        std::unique_ptr<gcn::Font> imageFont; // A font
#if USE_SDL2_TTF
        std::unique_ptr<gcn::Font> trueFont; // A font
#endif
        /*
         * All of the widgets
         */
        std::unique_ptr<gcn::Container> top; // A top container
        gcn::StringListModel demoListModel;
        std::unique_ptr<gcn::Label> label; // A label
        std::unique_ptr<gcn::Icon> icon; // An icon (image)
        std::unique_ptr<gcn::Button> button; // A button
        std::unique_ptr<gcn::ImageButton> imageButton; // An image button
        std::unique_ptr<gcn::ImageTextButton> imageTextButton; // An image text button
        std::unique_ptr<gcn::InputBox> inputBox; // An input box
        std::unique_ptr<gcn::TextField> textField; // One-line text field
        std::unique_ptr<gcn::TextField> passwordField; // One-line password field
        std::unique_ptr<gcn::TextBox> textBox; // Multi-line text box
        std::unique_ptr<gcn::ScrollArea> textBoxScrollArea; // Scroll area for the text box
        std::unique_ptr<gcn::ListBox> listBox; // A list box
        std::unique_ptr<gcn::DropDown> dropDown; // Drop down
        std::unique_ptr<gcn::CheckBox> checkBox1; // Two checkboxes
        std::unique_ptr<gcn::CheckBox> checkBox2;
        std::unique_ptr<gcn::RadioButton> radioButton1; // Three radio buttons
        std::unique_ptr<gcn::RadioButton> radioButton2;
        std::unique_ptr<gcn::RadioButton> radioButton3;
        std::unique_ptr<gcn::ToggleButton> toggleButton;
        std::unique_ptr<gcn::Slider> slider; // A slider
        std::unique_ptr<gcn::Window> window;
        std::unique_ptr<gcn::MessageBox> messageBox;
        std::unique_ptr<gcn::ProgressBar> progress;
        std::shared_ptr<gcn::Image> guisanLogoImage;
        std::unique_ptr<gcn::Icon> guisanLogoIcon;
        std::unique_ptr<gcn::ScrollArea> nestedScrollArea;
        std::unique_ptr<gcn::Container> nestedContainer;
        std::unique_ptr<gcn::Slider> nestedSlider;
    };

} // namespace WidgetsExample
