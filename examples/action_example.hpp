#include <guisan.hpp>
#include <sstream>

namespace ActionExample
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
            clickCountButton1(0),
            clickCountButton2(0)
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
            button1 = new gcn::Button("Button 1");
            button2 = new gcn::Button("Button 2");
            // Set the buttons position
            button1->setPosition(120, 230);
            button2->setPosition(420, 230);
            // Add the buttons to the top container
            top->add(button1);
            top->add(button2);

            // Create labels
            label1 = new gcn::Label("Button1 clicks 0");
            label2 = new gcn::Label("Button2 clicks 0");
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

            /*
             * Destroy Guichan stuff
             */
            delete label1;
            delete label2;
            delete button1;
            delete button2;
            delete top;
        }

        // Implement the action function in ActionListener to receive actions
        // The eventId tells us which widget called the action function.
        virtual void action(const gcn::ActionEvent& actionEvent)
        {
            std::string str;
            std::ostringstream os(str);

            // Here we use the widget pointer to check which widget the action
            // originated from.
            if (actionEvent.getSource() == button1)
            {
                clickCountButton1++;
                os << "Button1 clicks " << clickCountButton1;
                // Change the caption to show number of clicks
                label1->setCaption(os.str());
                // Adjust the label to fit the new caption
                label1->adjustSize();
            }
            // Here we use the event id in order to check what action occured.
            else if (actionEvent.getId() == "button2")
            {
                clickCountButton2++;
                os << "Button2 clicks " << clickCountButton2;
                // Change the caption to show number of clicks
                label2->setCaption(os.str());
                // Adjust the label to fit the new caption
                label2->adjustSize();
            }
        }

    private:
        gcn::ImageFont* font; // A font

        /*
         * All of the widgets
         */
        gcn::Container* top; // A top container
        gcn::Button* button1; // A button for actionlistening
        gcn::Button* button2; // Another button for actionlistening
        gcn::Label* label1; // And a label for button1 click count display
        gcn::Label* label2; // And another label for button2 click count display

        int clickCountButton1; // Count clicks for button1
        int clickCountButton2; // Count clicks for button2
    };

} // namespace ActionExample
