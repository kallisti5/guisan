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

#include <guichan.hpp>

#include "ffscrollarea.hpp"

FFScrollArea::FFScrollArea()
{
    setScrollPolicy(ShowNever,
                    ShowNever);
    addKeyListener(this);
    setFocusable(false);
    setFrameSize(0);
}

void FFScrollArea::draw(gcn::Graphics *graphics)
{
    graphics->pushClipArea(getContent()->getDimension());
    getContent()->draw(graphics);
    graphics->popClipArea();

    if (getVerticalMaxScroll() != 0)
    {
        int y = ((getHeight() - 32) * getVerticalScrollAmount()) /
            getVerticalMaxScroll();

        graphics->setColor(0x000000);
        graphics->drawRectangle(getWidth()-11, y, 8, 32);
        graphics->drawRectangle(getWidth()-10, y+1, 8, 32);

        graphics->setColor(0xffffff);

        graphics->fillRectangle(getWidth()-10, y+1, 6, 30);
    }
}

void FFScrollArea::keyPressed(gcn::KeyEvent &keyEvent)
{
    if (keyEvent.isConsumed())
    {
        return;
    }
    
    if (keyEvent.getKey().getValue() == gcn::Key::Down)
    {
        setVerticalScrollAmount(getVerticalScrollAmount() + 16);
    }
    else if (keyEvent.getKey().getValue() == gcn::Key::Up)
    {
        setVerticalScrollAmount(getVerticalScrollAmount() - 16);
    }
}
