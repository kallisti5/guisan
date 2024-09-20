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

#include <SDL.h>
#include <SDL_mixer.h>
#include <guisan.hpp>
#include <guisan/sdl.hpp>
#include <memory>

#include "ffcharacterchooser.hpp"
#include "ffcontainer.hpp"
#include "fflistbox.hpp"
#include "ffscrollarea.hpp"
#include "stringlistmodel.hpp"

class FFDemo : public gcn::ActionListener, public gcn::KeyListener
{
public:
    FFDemo();
    ~FFDemo() override;
    void action(const gcn::ActionEvent& actionEvent) override;
    void keyPressed(gcn::KeyEvent& keyEvent) override;

    void run();

private:
    void input();
    void initMain();
    void initStatus();
    void initMagicSkills();
    void initItems();
    void initAbout();

    bool mRunning = true;

    SDL_Surface* mScreen;
    SDL_Window* mWindow;
    SDL_Renderer* mRenderer;
    SDL_Event mEvent;

    Mix_Chunk* mChooseSound;
    Mix_Chunk* mEscapeSound;

    std::unique_ptr<gcn::SDLGraphics> mSDLGraphics;
    std::unique_ptr<gcn::SDLInput> mSDLInput;
    std::unique_ptr<gcn::SDLImageLoader> mSDLImageLoader;
    std::unique_ptr<gcn::Gui> mGui;

    std::unique_ptr<gcn::Container> mTop;
    std::unique_ptr<FFContainer> mMain;
    std::unique_ptr<FFContainer> mStatus;
    std::unique_ptr<FFContainer> mItems;
    std::unique_ptr<FFContainer> mMagicSkills;
    std::unique_ptr<FFContainer> mTime;
    std::unique_ptr<FFContainer> mGoldFootsteps;
    std::unique_ptr<FFContainer> mMenu;
    std::unique_ptr<FFContainer> mAbout;
    std::unique_ptr<FFContainer> mItemsInfo;

    std::unique_ptr<gcn::Icon> mPerIcon;
    std::unique_ptr<gcn::Icon> mOlofIcon;
    std::unique_ptr<gcn::Icon> mTomasIcon;
    std::unique_ptr<gcn::Image> mPerImage;
    std::unique_ptr<gcn::Image> mOlofImage;
    std::unique_ptr<gcn::Image> mTomasImage;
    std::unique_ptr<gcn::Image> mSplashImage;
    std::unique_ptr<gcn::Font> mFontWhite;
    std::unique_ptr<gcn::Font> mFontCyan;

    std::unique_ptr<FFListBox> mMenuList;

    std::unique_ptr<FFListBox> mMagicSkillsList;
    std::unique_ptr<FFScrollArea> mMagicSkillsScroll;

    std::unique_ptr<StringListModel> mPerSkills;
    std::unique_ptr<StringListModel> mPerMagic;
    std::unique_ptr<StringListModel> mOlofSkills;
    std::unique_ptr<StringListModel> mOlofMagic;
    std::unique_ptr<StringListModel> mTomasSkills;
    std::unique_ptr<StringListModel> mTomasMagic;

    std::unique_ptr<gcn::TextBox> mPerInfo1;
    std::unique_ptr<gcn::TextBox> mOlofInfo1;
    std::unique_ptr<gcn::TextBox> mTomasInfo1;
    std::unique_ptr<gcn::TextBox> mPerInfo2;
    std::unique_ptr<gcn::TextBox> mOlofInfo2;
    std::unique_ptr<gcn::TextBox> mTomasInfo2;
    std::unique_ptr<gcn::TextBox> mItemsInfoInfo;
    std::unique_ptr<gcn::TextBox> mOlofStatus1;
    std::unique_ptr<gcn::TextBox> mOlofStatus2;
    std::unique_ptr<gcn::TextBox> mPerStatus1;
    std::unique_ptr<gcn::TextBox> mPerStatus2;
    std::unique_ptr<gcn::TextBox> mTomasStatus1;
    std::unique_ptr<gcn::TextBox> mTomasStatus2;

    std::unique_ptr<gcn::TextBox> mGoldFootstepsInfo1;
    std::unique_ptr<gcn::TextBox> mGoldFootstepsInfo2;
    std::unique_ptr<gcn::Label> mTimeLabel1;
    std::unique_ptr<gcn::Label> mTimeLabel2;

    std::unique_ptr<gcn::Label> mNavigationLabel;

    std::unique_ptr<gcn::TextBox> mAboutInfo;
    std::unique_ptr<FFScrollArea> mAboutScrollArea;

    std::unique_ptr<FFListBox> mItemsList;
    std::unique_ptr<FFScrollArea> mItemsScrollArea;
    std::unique_ptr<StringListModel> mItemsListModel;
    std::unique_ptr<StringListModel> mItemsInfoListModel;
    std::unique_ptr<StringListModel> mMenuListModel;

    std::unique_ptr<FFCharacterChooser> mCharacterChooser;
};

#endif
