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

#ifndef __FFDEMO_HPP
#define __FFDEMO_HPP

#include <SDL/SDL.h>
#include <SDL/SDL_mixer.h>
#include <guichan.hpp>
#include <guichan/sdl.hpp>

#include "ffcharacterchooser.hpp"
#include "ffcontainer.hpp"
#include "fflistbox.hpp"
#include "ffscrollarea.hpp"
#include "stringlistmodel.hpp"

class FFDemo : public gcn::ActionListener, public gcn::KeyListener
{
public:
    FFDemo();
    ~FFDemo();
    void run();
    void action(const gcn::ActionEvent& actionEvent);
    void keyPressed(gcn::KeyEvent& keyEvent);

private:
    void input();
    void initMain();
    void cleanMain();
    void initStatus();
    void cleanStatus();
    void initMagicSkills();
    void cleanMagicSkills();
    void initItems();
    void cleanItems();
    void initAbout();
    void cleanAbout();

    bool mRunning;

    SDL_Surface* mScreen;
    SDL_Event mEvent;
    Mix_Chunk* mChooseSound;
    Mix_Chunk* mEscapeSound;

    gcn::SDLGraphics* mSDLGraphics;
    gcn::SDLInput* mSDLInput;
    gcn::SDLImageLoader* mSDLImageLoader;
    gcn::Gui* mGui;

    gcn::Container* mTop;
    FFContainer* mMain;
    FFContainer* mStatus;
    FFContainer* mItems;
    FFContainer* mMagicSkills;
    FFContainer* mTime;
    FFContainer* mGoldFootsteps;
    FFContainer* mMenu;
    FFContainer* mAbout;
    FFContainer* mItemsInfo;

    gcn::Icon* mPerIcon;
    gcn::Icon* mOlofIcon;
    gcn::Icon* mTomasIcon;
    gcn::Image* mPerImage;
    gcn::Image* mOlofImage;
    gcn::Image* mTomasImage;
    gcn::Image* mSplashImage;
    gcn::Font* mFontWhite;
    gcn::Font* mFontCyan;

    FFListBox *mMenuList;

    FFListBox *mMagicSkillsList;
    FFScrollArea *mMagicSkillsScroll;

    StringListModel *mPerSkills;
    StringListModel *mPerMagic;
    StringListModel *mOlofSkills;
    StringListModel *mOlofMagic;
    StringListModel *mTomasSkills;
    StringListModel *mTomasMagic;

    gcn::TextBox* mPerInfo1;
    gcn::TextBox* mOlofInfo1;
    gcn::TextBox* mTomasInfo1;
    gcn::TextBox* mPerInfo2;
    gcn::TextBox* mOlofInfo2;
    gcn::TextBox* mTomasInfo2;
    gcn::TextBox* mItemsInfoInfo;
    gcn::TextBox* mOlofStatus1;
    gcn::TextBox* mOlofStatus2;
    gcn::TextBox* mPerStatus1;
    gcn::TextBox* mPerStatus2;
    gcn::TextBox* mTomasStatus1;
    gcn::TextBox* mTomasStatus2;

    gcn::TextBox* mGoldFootstepsInfo1;
    gcn::TextBox* mGoldFootstepsInfo2;
    gcn::Label* mTimeLabel1;
    gcn::Label* mTimeLabel2;

    gcn::Label* mNavigationLabel;

    gcn::TextBox* mAboutInfo;
    FFScrollArea *mAboutScrollArea;

    FFListBox *mItemsList;
    FFScrollArea *mItemsScrollArea;
    StringListModel *mItemsListModel;
    StringListModel *mItemsInfoListModel;
    StringListModel *mMenuListModel;

    FFCharacterChooser* mCharacterChooser;
};

#endif
