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

#include "ffcharacterchooser.hpp"

FFCharacterChooser::FFCharacterChooser()
{
    setWidth(20);
    setHeight(240);
    mSelected = 0;
    mDistance = 76;
    mHand = gcn::Image::load("images/hand.png");
    setFocusable(true);
    addKeyListener(this);
    setBorderSize(0);
}

FFCharacterChooser::~FFCharacterChooser()
{
    delete mHand;
}

void FFCharacterChooser::draw(gcn::Graphics* graphics)
{
    if (isFocused())
    {
        graphics->drawImage(mHand, 0, mDistance*mSelected);
    }
}

int FFCharacterChooser::getSelected()
{
    return mSelected;
}

void FFCharacterChooser::setSelected(int selected)
{
    mSelected = selected;
}

void FFCharacterChooser::setDistance(int distance)
{
    mDistance = distance;
}

void FFCharacterChooser::keyPressed(gcn::KeyEvent& keyEvent)
{
    if (keyEvent.getKey().getValue() == gcn::Key::UP)
    {
        mSelected--;
        if (mSelected < 0)
        {
            mSelected = 0;
        }
    }
    else if (keyEvent.getKey().getValue() == gcn::Key::DOWN)
    {
        mSelected++;
        if (mSelected > 2)
        {
            mSelected = 2;
        }
    }
    else if (keyEvent.getKey().getValue() == gcn::Key::ENTER)
    {
		// TODO: fix this
        //distributeActionEvent();
    }
}
