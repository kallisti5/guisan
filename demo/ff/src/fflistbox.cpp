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

#include <guisan.hpp>
#ifndef _MSC_VER
#include <SDL2/SDL.h>
#else
#include <SDL.h>
#endif

#include "fflistbox.hpp"

int FFListBox::mInstances = 0;
gcn::Image *FFListBox::mHand = NULL;

FFListBox::FFListBox()
{
    if (mInstances == 0)
    {
        mHand = gcn::Image::load("images/hand.png");
    }

    mInstances++;
    setBorderSize(0);
    setWrappingEnabled(true);
}

FFListBox::~FFListBox()
{
    mInstances--;

    if (mInstances == 0)
    {
        delete mHand;
    }
}

void FFListBox::draw(gcn::Graphics* graphics)
{
		if (mListModel == NULL)
		{
        return;
		}

		graphics->setColor(getForegroundColor());
		graphics->setFont(getFont());

		int i, fontHeight;
		int y = 0;

		fontHeight = getFont()->getHeight();

		/**
		 * @todo Check cliprects so we do not have to iterate over elements in the list model
		 */
		for (i = 0; i < mListModel->getNumberOfElements(); ++i)
		{
        graphics->drawText(mListModel->getElementAt(i), 16, y);

        if (i == mSelected)
        {
            if (isFocused())
            {
                graphics->drawImage(mHand, 0, y);
            }
            else if ((SDL_GetTicks() / 100) & 1)
            {
                graphics->drawImage(mHand, 0, y);
            }
        }

        y += fontHeight;
		}
}

void FFListBox::setSelected(int i)
{
    if (i >= 0 &&
        i < getListModel()->getNumberOfElements() &&
        getListModel()->getElementAt(i) == "")
    {
        if (i < getSelected())
        {
            i--;
        }
        else
        {
            i++;
        }
    }

    ListBox::setSelected(i);
}
