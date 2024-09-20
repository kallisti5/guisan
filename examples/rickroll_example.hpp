#include <guisan.hpp>
#include <memory>

namespace RickRollExample
{

    /*
     * To be able to receive actions we must have a class inheriting from
     * ActionListener and implementing the action function.
     * When an action is generated in a Widget (i.e when a button is clicked)
     * that widget calls the action function for all its action listeners.
     */
    class MainContainer : public gcn::ActionListener
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

            // Create buttons
            button1 = std::make_unique<gcn::Button>("Click me");
            button2 = std::make_unique<gcn::Button>("Enter your name");
            // Set the buttons position
            button1->setPosition(120, 230);
            button2->setPosition(420, 230);
            // Add the buttons to the top container
            top->add(button1.get());
            top->add(button2.get());

            // Create labels
            label1 = std::make_unique<gcn::Label>("Get rick rolled");
            label2 = std::make_unique<gcn::Label>("What is your name");
            // Set the labels position
            label1->setPosition(100, 200);
            label2->setPosition(400, 200);
            // Add the labels to the top container
            top->add(label1.get());
            top->add(label2.get());

            // Set the buttons action event id's.
            button1->setActionEventId("button1");
            button2->setActionEventId("button2");

            // Add this to the buttons action listeners
            button1->addActionListener(this);
            button2->addActionListener(this);
        }

        ~MainContainer() override = default;

        // Implement the action function in ActionListener to receive actions
        // The eventId tells us which widget called the action function.
        void action(const gcn::ActionEvent& actionEvent) override
        {
            // Here we use the widget pointer to check which widget the action
            // originated from.
            if (actionEvent.getSource() == msgBox.get())
            {
                msgBox->setVisible(false);
                label1->setCaption("You have been rick rolled");
                // Adjust the label to fit the new caption
                label1->adjustSize();
                top->remove(msgBox.get());
            }
            else if (actionEvent.getSource() == button1.get())
            {
                msgBox =
                    std::make_unique<gcn::MessageBox>("Rick Astley", "Never gonna give you up");
                msgBox->setVisible(true);
                msgBox->addActionListener(this);
                top->add(msgBox.get(), 270, 180);
            }
            else if (actionEvent.getSource() == button2.get())
            {
                inputBox = std::make_unique<gcn::InputBox>(
                    "Name request", "Enter your name below", "Here you go", "No way");
                inputBox->setVisible(true);
                inputBox->addActionListener(this);
                top->add(inputBox.get(), 270, 180);
            }
            else if (actionEvent.getSource() == inputBox.get())
            {
                inputBox->setVisible(false);
                if (inputBox->getClickedButton() == 1)
                {
                    label2->setCaption("No name");
                } else
                {
                    label2->setCaption("Your name is " + inputBox->getText());
                }
                label2->adjustSize();
            }
        }

    private:
        std::unique_ptr<gcn::ImageFont> font; // A font

        /*
         * All of the widgets
         */
        std::unique_ptr<gcn::Container> top; // A top container
        std::unique_ptr<gcn::Button> button1; // A button for actionlistening (triggers msgbox)
        std::unique_ptr<gcn::Label> label1; // And a label for button1
        std::unique_ptr<gcn::Button> button2; // Button for InputBox
        std::unique_ptr<gcn::Label> label2; // Label for inputbox
        std::unique_ptr<gcn::MessageBox> msgBox;
        std::unique_ptr<gcn::InputBox> inputBox;
    };

} // namespace ActionExample
