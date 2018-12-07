/*      _______   __   __   __   ______   __   __   _______   __   __
 *     / _____/\ / /\ / /\ / /\ / ____/\ / /\ / /\ / ___  /\ /  |\/ /\
 *    / /\____\// / // / // / // /\___\// /_// / // /\_/ / // , |/ / /
 *   / / /__   / / // / // / // / /    / ___  / // ___  / // /| ' / /
 *  / /_// /\ / /_// / // / // /_/_   / / // / // /\_/ / // / |  / /
 * /______/ //______/ //_/ //_____/\ /_/ //_/ //_/ //_/ //_/ /|_/ /
 * \______\/ \______\/ \_\/ \_____\/ \_\/ \_\/ \_\/ \_\/ \_\/ \_\/
 *
 * Copyright (c) 2004 - 2008 Olof Naessén and Per Larsson
 *
 *
 * Per Larsson a.k.a finalman
 * Olof Naessén a.k.a jansem/yakslem
 *
 * Visit: http://guichan.sourceforge.net
 *
 * License: (BSD)
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in
 *    the documentation and/or other materials provided with the
 *    distribution.
 * 3. Neither the name of Guichan nor the names of its contributors may
 *    be used to endorse or promote products derived from this software
 *    without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
 * A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
 * OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 * SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED
 * TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR
 * PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
 * LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
 * NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#include <iostream>
#include <sstream>

#include "ffdemo.hpp"

FFDemo::FFDemo()
{
    mRunning = true;

    /*
     * Here we initialize SDL as we would do with any SDL application.
     */
    SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO);
    mWindow = SDL_CreateWindow("Guisan SDL2 FF demo",
        SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 320, 240, 0);

    mScreen = SDL_GetWindowSurface(mWindow);

    //SDL_EnableKeyRepeat(SDL_DEFAULT_REPEAT_DELAY, SDL_DEFAULT_REPEAT_INTERVAL);
    SDL_ShowCursor(0);
    Mix_OpenAudio(22050, MIX_DEFAULT_FORMAT, 2, 1024);

    mChooseSound = Mix_LoadWAV("sound/sound1.wav");
    mEscapeSound = Mix_LoadWAV("sound/sound2.wav");

    mSDLImageLoader = new gcn::SDLImageLoader();
    gcn::Image::setImageLoader(mSDLImageLoader); 
    mSDLGraphics = new gcn::SDLGraphics();
    mSDLGraphics->setTarget(mScreen);
    mSDLInput = new gcn::SDLInput();
	
    mSplashImage = gcn::Image::load("images/splash.png");	

    mTop = new gcn::Container();
    mTop->setBaseColor(gcn::Color(0x000000));
    mTop->setDimension(gcn::Rectangle(0, 0, 320, 240));
    mGui = new gcn::Gui();
    mGui->setTabbingEnabled(false);
    mGui->setGraphics(mSDLGraphics);
    mGui->setInput(mSDLInput);	
    mGui->setTop(mTop);
    mFontWhite = new gcn::ImageFont("images/rpgfont.png", " abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789.,!?-+/():;%&`'*#=[]\""); 	
    mFontCyan = new gcn::ImageFont("images/rpgfont2.png", " abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789.,!?-+/():;%&`'*#=[]\"");	
    gcn::Widget::setGlobalFont(mFontWhite);
	
    initMain();

    mMenu = new FFContainer();
    mMenu->setDimension(gcn::Rectangle(230, 0, 90, 130));
    mMenu->setOpaque(false);
    mTop->add(mMenu);
	
    mGoldFootsteps = new FFContainer();
    mGoldFootsteps->setDimension(gcn::Rectangle(210, 170, 110, 70));
    mGoldFootsteps->setOpaque(false);
    mGoldFootsteps->setBorderSize(0);
    mTop->add(mGoldFootsteps);

    mTime = new FFContainer();
    mTime->setDimension(gcn::Rectangle(230, 130, 90, 40));
    mTime->setOpaque(false);
    mTop->add(mTime);
																	 
    mGoldFootstepsInfo1 = new gcn::TextBox("Steps\n\nGP");
    mGoldFootstepsInfo1->setFont(mFontCyan);
    mGoldFootstepsInfo1->setOpaque(false);
    mGoldFootstepsInfo1->setEditable(false);
    mGoldFootstepsInfo1->setFocusable(false);
    mGoldFootstepsInfo1->setBorderSize(0);
		
    mGoldFootstepsInfo2 = new gcn::TextBox("\n    9119092\n\n    1009213");
    mGoldFootstepsInfo2->setOpaque(false);
    mGoldFootstepsInfo2->setEditable(false);
    mGoldFootstepsInfo2->setFocusable(false);
    mGoldFootstepsInfo2->setBorderSize(0);
	
    mTimeLabel1 = new gcn::Label("Time");
    mTimeLabel1->setFont(mFontCyan);
    mTimeLabel2 = new gcn::Label();
    mTime->add(mTimeLabel1, 5, 5);	
    mTime->add(mTimeLabel2, 22, 20);

	
    mGoldFootsteps->add(mGoldFootstepsInfo2, 5, 0);
    mGoldFootsteps->add(mGoldFootstepsInfo1, 5, 5);
	
    mMenuListModel = new StringListModel();
    mMenuListModel->add("Items");
    mMenuListModel->add("Status");
    mMenuListModel->add("Skills");
    mMenuListModel->add("Magic");
    mMenuListModel->add("About");
    mMenuListModel->add("");
    mMenuListModel->add("Quit");
	
    mMenuList = new FFListBox();
    mMenuList->setActionEventId("menu");
    mMenuList->addActionListener(this);	
    mMenuList->setListModel(mMenuListModel);
    mMenu->add(mMenuList, 5, 5);
    mMenuList->setSelected(0);
    mMenuList->requestFocus();

    initStatus();
    initAbout();
    initItems();
    initMagicSkills();
}

FFDemo::~FFDemo()
{
    cleanStatus();
    cleanAbout();
    cleanItems();
    cleanMagicSkills();	
    cleanMain();
	

    delete mSplashImage;

    delete mTimeLabel1;
    delete mTimeLabel2; 
    delete mTime;
	
    delete mGoldFootstepsInfo1;
    delete mGoldFootstepsInfo2;
    delete mGoldFootsteps;

    delete mMenuList;
    delete mMenuListModel;
    delete mMenu;

    delete mMain;
	
    delete mFontWhite;
    delete mFontCyan;
    delete mTop;
    delete mGui;

    delete mSDLInput;
    delete mSDLGraphics;
    delete mSDLImageLoader;
	 
    Mix_FreeChunk(mChooseSound);
    Mix_FreeChunk(mEscapeSound);
    Mix_CloseAudio();
	
    SDL_Quit();
}

void FFDemo::initMain()
{
    mMain = new FFContainer();
    mMain->setDimension(gcn::Rectangle(0, 0, 320, 240));
    mTop->add(mMain);

    mPerImage = gcn::Image::load("images/finalman.png");
    mOlofImage = gcn::Image::load("images/yakslem.png");
    mTomasImage = gcn::Image::load("images/peak.png");

    mPerIcon = new gcn::Icon(mPerImage);
    mOlofIcon = new gcn::Icon(mOlofImage);
    mTomasIcon = new gcn::Icon(mTomasImage);

    mPerInfo1 = new gcn::TextBox("\n  LV\n  HP\n  MP");
    mPerInfo1->setFont(mFontCyan);
    mPerInfo1->setOpaque(false);
    mPerInfo1->setEditable(false);
    mPerInfo1->setFocusable(false);
    mPerInfo1->setBorderSize(0);
	
    mPerInfo2 = new gcn::TextBox("FINALMAN\n     13\n       12/ 336\n       33/  40");
    mPerInfo2->setOpaque(false);
    mPerInfo2->setEditable(false);
    mPerInfo2->setFocusable(false);
    mPerInfo2->setBorderSize(0);
		 
    mOlofInfo1 = new gcn::TextBox("\n  LV\n  HP\n  MP");
    mOlofInfo1->setFont(mFontCyan);
    mOlofInfo1->setOpaque(false);
    mOlofInfo1->setEditable(false);
    mOlofInfo1->setFocusable(false);
    mOlofInfo1->setBorderSize(0);
	
    mOlofInfo2 = new gcn::TextBox("YAKSLEM\n     41\n     1304/2932\n      298/ 300");
    mOlofInfo2->setOpaque(false);
    mOlofInfo2->setEditable(false);
    mOlofInfo2->setFocusable(false);
    mOlofInfo2->setBorderSize(0);
	
    mTomasInfo1 = new gcn::TextBox("\n  LV\n  HP\n  MP");
    mTomasInfo1->setFont(mFontCyan);
    mTomasInfo1->setOpaque(false);
    mTomasInfo1->setEditable(false);
    mTomasInfo1->setFocusable(false);
    mTomasInfo1->setBorderSize(0);
	
    mTomasInfo2 = new gcn::TextBox("PEAK\n      6\n      101/ 101\n        0/   0");
    mTomasInfo2->setOpaque(false);
    mTomasInfo2->setEditable(false);
    mTomasInfo2->setFocusable(false);
    mTomasInfo2->setBorderSize(0);
	
    int offset = 6;
    mMain->add(mPerIcon, 10, offset);
    mMain->add(mPerInfo2, 60, offset);
    mMain->add(mPerInfo1, 60, offset);
    offset += 76;
    mMain->add(mOlofIcon, 10, offset);
    mMain->add(mOlofInfo2, 60, offset);
    mMain->add(mOlofInfo1, 60, offset);
    offset += 76;
    mMain->add(mTomasIcon, 10, offset);
    mMain->add(mTomasInfo2, 60, offset);
    mMain->add(mTomasInfo1, 60, offset);	
	
    mCharacterChooser = new FFCharacterChooser();	
    mCharacterChooser->setActionEventId("character");
    mCharacterChooser->addActionListener(this);

    mMain->add(mCharacterChooser, 5, 25);

    mNavigationLabel = new gcn::Label("STATUS ");
    mNavigationLabel->setVisible(false);
    mMain->add(mNavigationLabel, 230, 20);


}

void FFDemo::cleanMain()
{
    delete mNavigationLabel;
    delete mCharacterChooser;
	
    delete mPerInfo1;
    delete mOlofInfo1;
    delete mTomasInfo1;
	
    delete mPerInfo2;
    delete mOlofInfo2;
    delete mTomasInfo2;

    delete mPerIcon;
    delete mOlofIcon;
    delete mTomasIcon;
	
    delete mPerImage;
    delete mOlofImage;
    delete mTomasImage;
}

void FFDemo::initStatus()
{
    mStatus = new FFContainer();
    mStatus->setDimension(gcn::Rectangle(0, 80, 320, 160));
    mStatus->setVisible(false);
    mTop->add(mStatus);

    mPerStatus1 = new gcn::TextBox("  STR           EXP\n"
                                   "  INT           NEXT\n"
                                   "  DEF\n"
                                   "  MAGDEF\n");
    mPerStatus1->setFont(mFontCyan);
    mPerStatus1->setOpaque(false);
    mPerStatus1->setEditable(false);
    mPerStatus1->setFocusable(false);
    mPerStatus1->setVisible(false);
    mPerStatus1->setBorderSize(0);
	
    mPerStatus2 = new gcn::TextBox("         32          12382\n"
                                   "         56          13872\n"
                                   "         12\n"
                                   "         11\n\n"
                                   " FINALMAN is immune against\n"
                                   " poisinous attacks, thanks to his\n"
                                   " face mask.");
    mPerStatus2->setOpaque(false);
    mPerStatus2->setEditable(false);
    mPerStatus2->setFocusable(false);
    mPerStatus2->setVisible(false);	
    mPerStatus2->setBorderSize(0);
	
    mOlofStatus1 = new gcn::TextBox("  STR           EXP\n"
                                    "  INT           NEXT\n"
                                    "  DEF\n"
                                    "  MAGDEF\n");
    mOlofStatus1->setFont(mFontCyan);
    mOlofStatus1->setOpaque(false);
    mOlofStatus1->setEditable(false);
    mOlofStatus1->setFocusable(false);
    mOlofStatus1->setVisible(false);
    mOlofStatus1->setBorderSize(0);
	
    mOlofStatus2 = new gcn::TextBox("          2          412382\n"
                                    "         72          513872\n"
                                    "          4\n"
                                    "         34\n\n"
                                    " YAKSLEM has one passion in life,\n"
                                    " to annoy other people...\n"
                                    " especially FINALMAN.");
    mOlofStatus2->setOpaque(false);
    mOlofStatus2->setEditable(false);
    mOlofStatus2->setFocusable(false);
    mOlofStatus2->setVisible(false);	
    mOlofStatus2->setBorderSize(0);
	
    mTomasStatus1 = new gcn::TextBox("  STR           EXP\n"
                                     "  INT           NEXT\n"
                                     "  DEF\n"
                                     "  MAGDEF\n");
    mTomasStatus1->setFont(mFontCyan);
    mTomasStatus1->setOpaque(false);
    mTomasStatus1->setEditable(false);
    mTomasStatus1->setFocusable(false);
    mTomasStatus1->setVisible(false);
    mTomasStatus1->setBorderSize(0);
	
    mTomasStatus2 = new gcn::TextBox("          1          412382\n"
                                     "          3          513872\n"
                                     "          9\n"
                                     "         24\n\n"
                                     " PEAK is very weak but so cute!\n"
                                     " He has a tendency of answering\n"
                                     " any question with \"KUPO!\"");
    mTomasStatus2->setOpaque(false);
    mTomasStatus2->setEditable(false);
    mTomasStatus2->setFocusable(false);
    mTomasStatus2->setVisible(false);	
    mTomasStatus2->setBorderSize(0);
	
    mStatus->add(mPerStatus2, 5, 10);
    mStatus->add(mPerStatus1, 5, 10);
    mStatus->add(mOlofStatus2, 5, 10);
    mStatus->add(mOlofStatus1, 5, 10);
    mStatus->add(mTomasStatus2, 5, 10);
    mStatus->add(mTomasStatus1, 5, 10);
}

void FFDemo::initMagicSkills()
{
    mMagicSkills = new FFContainer();
    mMagicSkills->setDimension(gcn::Rectangle(0, 80, 320, 160));
    mMagicSkills->setVisible(false);
	
    mMagicSkillsScroll = new FFScrollArea();
    mMagicSkillsScroll->setDimension(gcn::Rectangle(5, 5, 310, 150));

    mMagicSkillsList = new FFListBox();
    mMagicSkillsList->setWidth(300);
    mMagicSkillsScroll->setContent(mMagicSkillsList);
    mMagicSkills->add(mMagicSkillsScroll);
    mTop->add(mMagicSkills);

    mPerSkills = new StringListModel();
    mPerMagic = new StringListModel();
    mOlofSkills = new StringListModel();
    mOlofMagic = new StringListModel();
    mTomasSkills = new StringListModel();
    mTomasMagic = new StringListModel();	

    mPerSkills->add("Use");
    mPerSkills->add("Steal");
    mPerSkills->add("Disassemble");	
    mPerSkills->add("Tech-Talk");
    mPerSkills->add("Double Compile");

    mPerMagic->add("Fire");
    mPerMagic->add("Fire 2");
    mPerMagic->add("Bio");
    mPerMagic->add("Magic Missile");

    mOlofSkills->add("Annoy");
    mOlofSkills->add("Juggle");
    mOlofSkills->add("Somersault");
    mOlofSkills->add("Evil Laughter");
    mOlofSkills->add("Meta-circular Evaluation");
    mOlofSkills->add("Lisp");
    mOlofSkills->add("Cursing PHP");	
    mOlofSkills->add("Paint");
    mOlofSkills->add("Compose obscure music");
	
    mOlofMagic->add("Ultima");
    mOlofMagic->add("Sonic Blast");	

    mTomasSkills->add("Precision Throw");
    mTomasSkills->add("Jump");
    mTomasSkills->add("Dance");	
    mTomasSkills->add("Much talk and little factory");
    mTomasSkills->add("Cheat");
    mTomasSkills->add("Wear hotpants");
    mTomasSkills->add("Programming Pong games");
    mTomasSkills->add("Eat meat pie");
		
    mTomasMagic->add("Slow");
    mTomasMagic->add("Sleep");
    mTomasMagic->add("Doom");
}

void FFDemo::cleanMagicSkills()
{
    delete mMagicSkills;
    delete mMagicSkillsList;
    delete mMagicSkillsScroll;
    delete mPerSkills;
    delete mPerMagic;
    delete mOlofSkills;
    delete mOlofMagic;
    delete mTomasSkills;
    delete mTomasMagic;
}

void FFDemo::cleanStatus()
{
    delete mStatus;
    delete mPerStatus1;
    delete mPerStatus2;	
    delete mOlofStatus1;
    delete mOlofStatus2;	
    delete mTomasStatus1;
    delete mTomasStatus2;	
}

void FFDemo::initItems()
{
    mItems = new FFContainer();

    mItemsListModel = new StringListModel();
    mItemsInfoListModel = new StringListModel();
    mItemsListModel->add("23 x Potion");
    mItemsInfoListModel->add("Restores 100 HP");
    mItemsListModel->add("12 x Ether");
    mItemsInfoListModel->add("Restores 50 MP");
    mItemsListModel->add(" 8 x Elixir");
    mItemsInfoListModel->add("Restores all HP/MP");
    mItemsListModel->add("16 x Fenix Up");
    mItemsInfoListModel->add("Kills a party member");
    mItemsListModel->add(" 1 x Brass Key");
    mItemsInfoListModel->add("No idea...");
    mItemsListModel->add(" 1 x Atma Weapon");		
    mItemsInfoListModel->add("Grows with it's user");
    mItemsListModel->add(" 1 x Converse Allstars");
    mItemsInfoListModel->add("Yakslems red shoes");
    mItemsListModel->add(" 1 x Oil Canister");
    mItemsInfoListModel->add("Get greasy!");
    mItemsListModel->add(" 1 x Geeky t-shirt");
    mItemsInfoListModel->add("Belongs to finalman");
    mItemsListModel->add(" 1 x Synthesizer");
    mItemsInfoListModel->add("Yakslems mega cool Ensoniq EPS 16+");
    mItemsListModel->add(" 1 x Graphic Pen");
    mItemsInfoListModel->add("Someone left it here. Maybe\nNodajo?");
    mItemsListModel->add(" 1 x Floppy Disk");
    mItemsInfoListModel->add("Stores your important data");
    mItemsListModel->add(" 1 x Gui-chan Plush Doll");
    mItemsInfoListModel->add("Soooo cute and soooo plushy!!!");
    mItemsListModel->add(" 1 x Fenix Blade");
    mItemsInfoListModel->add("We are waiting for Demo3");
    mItemsListModel->add(" 2 x Joy Division LP");
    mItemsInfoListModel->add("Unknown Pleasures and Closer");
	
    mItemsInfo = new FFContainer;
    mItemsInfo->setDimension(gcn::Rectangle(0, 0, 320, 50));
    mItemsInfo->setVisible(false);
	
    mItemsInfoInfo = new gcn::TextBox();
    mItemsInfoInfo->setOpaque(false);
    mItemsInfoInfo->setEditable(false);
    mItemsInfoInfo->setFocusable(false);
    mItemsInfoInfo->setDimension(gcn::Rectangle(5, 5, 310, 40));
    mItemsInfoInfo->setBorderSize(0);
    mItemsInfo->add(mItemsInfoInfo);
	
    mItemsList = new FFListBox();
    mItemsList->setActionEventId("items");	
    mItemsList->addKeyListener(this);
    mItemsList->setWidth(300);
    mItemsList->setListModel(mItemsListModel);
    mItemsScrollArea = new FFScrollArea();
    mItemsScrollArea->setContent(mItemsList);
    mItemsScrollArea->setDimension(gcn::Rectangle(5, 5, 310, 180));
    mItems = new FFContainer();
    mItems->setDimension(gcn::Rectangle(0, 50, 320, 190));
    mItems->setVisible(false);
    mItems->add(mItemsScrollArea);
    mTop->add(mItems);	
    mTop->add(mItemsInfo);
}

void FFDemo::cleanItems()
{
    delete mItems;
    delete mItemsInfo;
    delete mItemsInfoInfo;
    delete mItemsList;
    delete mItemsScrollArea;
}	

void FFDemo::initAbout()
{
    mAbout = new FFContainer();
    mAbout->setDimension(gcn::Rectangle(0, 0, 320, 240));
    mAbout->setVisible(false);
    mTop->add(mAbout);
 
    mAboutInfo = new gcn::TextBox();
    mAboutInfo->setOpaque(false);
    mAboutInfo->setEditable(false);
    mAboutInfo->setFocusable(false);
    mAboutInfo->setText("Welcome to Guisan FF Demo!\n\n"
                        "What is this, you wonder?\n"
                        "Well, this is a little proof of\n"
                        "concept demo for the Guisan\n"
                        "GUI library.\n"
                        "This demo demonstrates the\n"
                        "flexibility of the library,\n"
                        "how to overload widgets to get a\n"
                        "custom look and feel.\n\n"
                        "Guisan has a modular, object\n"
                        "oriented API. The back-end is\n"
                        "replaceable, so it can work\n"
                        "on any platform. It is bundled\n"
                        "with graphics back-ends for\n"
                        "SDL, and OpenGL and an input-\n"
                        "backend for SDL.\n"
                        "Don't be fooled by this demo,\n"
                        "it does support mouse input!\n"
                        "Guisan developed by:\n"
                        " - Alexander von Gluck (kallisti5)\n"
                        "Guichan originally developed by:\n"
                        " - Per Larsson (finalman)\n"
                        " - Olof Naessen (yakslem)\n\n"
                        "Demo developed by:\n"
                        " - Per Larsson (finalman)\n"
                        "       code\n\n"
                        " - Olof Naessen (yakslem)\n"
                        "       code, character art\n\n"
                        " - Tomas Almgren (peak)\n"
                        "       font\n\n"
                        );
	
    mAboutScrollArea = new FFScrollArea();
    mAboutScrollArea->setContent(mAboutInfo);
    mAboutScrollArea->setFocusable(true);
    mAboutScrollArea->setDimension(gcn::Rectangle(5, 5, 310, 230));
    mAboutScrollArea->setBorderSize(0);
    mAbout->add(mAboutScrollArea);
    mAbout->setBorderSize(0);
}

void FFDemo::cleanAbout()
{
    delete mAboutInfo;
    delete mAboutScrollArea;
    delete mAbout;
}


void FFDemo::run()
{
    while(mRunning)
    {		
        input();

        int sec = SDL_GetTicks() / 1000;
        int min = sec / 60;
        sec = sec % 60;
        std::string str;
        std::ostringstream os(str);

        if (min < 10)
        {
            os << " " << min << ":";
        }
        else
        {
            os << min << ":";			
        }

        if (sec < 10)
        {
            os << "0" << sec;
        }
        else
        {
            os << sec;
        }

        mTimeLabel2->setCaption(os.str());
        mTimeLabel2->adjustSize();
		
        if (SDL_GetTicks() < 3000)
        {
            SDL_Rect src, dst;
            src.x = src.y = 0;
            src.w = dst.w = mSplashImage->getWidth();
            src.h = dst.h = mSplashImage->getHeight();
            dst.x = 10;
            dst.y = 50;
            gcn::SDLImage* image = (gcn::SDLImage*) mSplashImage;
            SDL_BlitSurface(image->getSurface(), &src, mScreen, &dst);
        }
        else		
        {
            mGui->logic();
            mGui->draw();
        }

	SDL_UpdateWindowSurface(mWindow);
        SDL_Delay(10);
    }		
}

void FFDemo::action(const gcn::ActionEvent& actionEvent)
{
    if (actionEvent.getId() == "menu")		
    {
        switch (mMenuList->getSelected())
        {
          case 0:
              mItems->setVisible(true);
              mItemsList->setSelected(0);
              mItemsList->requestFocus();
              mItemsInfo->setVisible(true);
              mItemsInfoInfo->setText(mItemsInfoListModel->getElementAt(mItemsList->getSelected()));
              break;

          case 1:
          case 2:
          case 3:
              mCharacterChooser->setSelected(0);
              mCharacterChooser->requestFocus();
              break;
          case 4:
              mAbout->setVisible(true);
              mAboutScrollArea->setVerticalScrollAmount(0);
              mAboutScrollArea->requestFocus();
              break;
				
          case 6:
              mRunning = false;
              break;
				
          default:
              break;
        }
    }

    if (actionEvent.getId() == "escape")
    {
        mAbout->setVisible(false);
        mItems->setVisible(false);
        mItemsInfo->setVisible(false);
        mMenu->setVisible(true);
        mTime->setVisible(true);
        mGoldFootsteps->setVisible(true);
        mMenuList->requestFocus();
        mMain->slideContentTo(0);
        mStatus->setVisible(false);
        mPerStatus1->setVisible(false);
        mPerStatus2->setVisible(false);
        mOlofStatus1->setVisible(false);
        mOlofStatus2->setVisible(false);
        mTomasStatus1->setVisible(false);
        mTomasStatus2->setVisible(false);
        mMagicSkills->setVisible(false);
        mNavigationLabel->setVisible(false);
    }

    if (actionEvent.getId() == "character")
    {
        mMain->slideContentTo(-76*mCharacterChooser->getSelected());
        mMenu->setVisible(false);
        mTime->setVisible(false);
        mGoldFootsteps->setVisible(false);

        mGui->focusNone();

        mNavigationLabel->setVisible(true);
        mNavigationLabel->setY(mCharacterChooser->getSelected()*76 + 30);
			
        switch(mMenuList->getSelected())
        {			
          case 1:
              mNavigationLabel->setCaption("STATUS");
											
              if (mCharacterChooser->getSelected() == 0)
              {
                  mPerStatus1->setVisible(true);
                  mPerStatus2->setVisible(true);					
              }
              else if (mCharacterChooser->getSelected() == 1)
              {
                  mOlofStatus1->setVisible(true);
                  mOlofStatus2->setVisible(true);
              }
              else if (mCharacterChooser->getSelected() == 2)
              {
                  mTomasStatus1->setVisible(true);
                  mTomasStatus2->setVisible(true);
              }
              mStatus->setVisible(true);
              break;

          case 2:
              mNavigationLabel->setCaption("SKILLS");
											
              if (mCharacterChooser->getSelected() == 0)
              {
                  mMagicSkillsList->setListModel(mPerSkills);
              }
              else if (mCharacterChooser->getSelected() == 1)
              {
                  mMagicSkillsList->setListModel(mOlofSkills);
              }
              else if (mCharacterChooser->getSelected() == 2)
              {
                  mMagicSkillsList->setListModel(mTomasSkills);
              }
              mMagicSkillsList->setSelected(0);
              mMagicSkills->setVisible(true);
              mMagicSkillsList->requestFocus();
              break;

          case 3:
              mNavigationLabel->setCaption("MAGIC");			
				
              if (mCharacterChooser->getSelected() == 0)
              {
                  mMagicSkillsList->setListModel(mPerMagic);
              }
              else if (mCharacterChooser->getSelected() == 1)
              {
                  mMagicSkillsList->setListModel(mOlofMagic);
              }
              else if (mCharacterChooser->getSelected() == 2)
              {
                  mMagicSkillsList->setListModel(mTomasMagic);
              }
              mMagicSkillsList->setSelected(0);
              mMagicSkills->setVisible(true);
              mMagicSkillsList->requestFocus();
              break;

				
        }
    }
}

void FFDemo::input()
{
    while(SDL_PollEvent(&mEvent))
    {
        if (mEvent.type == SDL_KEYDOWN)
        {
            if (mEvent.key.keysym.sym == SDLK_ESCAPE)
            {  
                Mix_PlayChannel(-1, mEscapeSound, 0);
				
                action(gcn::ActionEvent(NULL, "escape"));
            }
            else if (mEvent.key.keysym.sym == SDLK_RETURN
                     || mEvent.key.keysym.sym == SDLK_UP
                     || mEvent.key.keysym.sym == SDLK_DOWN)
            {  
                Mix_PlayChannel(-1, mChooseSound, 0);
            }
            else if (mEvent.key.keysym.sym == SDLK_f)
            {
                // TODO: Fullscreen
                // Works with X11 only
                //SDL_WM_ToggleFullScreen(mScreen);
            }
            mSDLInput->pushInput(mEvent);			
        }
        else if (mEvent.type == SDL_KEYUP)
        {
            mSDLInput->pushInput(mEvent);
        }
        else if (mEvent.type == SDL_QUIT)
        {
            mRunning = false;
        }
    }
}

void FFDemo::keyPressed(gcn::KeyEvent& keyEvent)
{		
    mItemsInfoInfo->setText(mItemsInfoListModel->getElementAt(mItemsList->getSelected()));		
}
