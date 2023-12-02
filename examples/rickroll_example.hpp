#include <guisan.hpp>

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
        MainContainer(gcn::Gui& gui, int width = 680, int height = 480) :
            msgBox(NULL),
            inputBox(NULL)
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

            // Add this to the buttons action listeners
            button1->addActionListener(this);
            button2->addActionListener(this);
        }

        ~MainContainer()
        {
            delete font;

            delete msgBox;
            delete inputBox;

            delete label1;
            delete button1;
            delete label2;
            delete button2;
            delete top;
        }

        // Implement the action function in ActionListener to receive actions
        // The eventId tells us which widget called the action function.
        virtual void action(const gcn::ActionEvent& actionEvent)
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
                if (msgBox)
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
                if (inputBox)
                {
                    delete inputBox;
                    inputBox = NULL;
                }
                inputBox = new gcn::InputBox(
                    "Name request", "Enter your name below", "Here you go", "No way");
                inputBox->setVisible(true);
                inputBox->addActionListener(this);
                top->add(inputBox, 270, 180);
            }
            else if (actionEvent.getSource() == inputBox)
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
        gcn::ImageFont* font; // A font

        /*
         * All of the widgets
         */
        gcn::Container* top; // A top container
        gcn::Button* button1; // A button for actionlistening (triggers msgbox)
        gcn::Label* label1; // And a label for button1
        gcn::Button* button2; // Button for InputBox
        gcn::Label* label2; // Label for inputbox
        gcn::MessageBox* msgBox;
        gcn::InputBox* inputBox;
    };

} // namespace ActionExample
