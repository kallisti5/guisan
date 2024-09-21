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

#include "ffcontainer.hpp"

#include <cmath>
#include <memory>

#ifndef _MSC_VER
#include <SDL2/SDL.h>
#else
#include <SDL.h>
#endif // !_MSC_

namespace
{
    int mInstances = 0;
    std::unique_ptr<gcn::Image> mCornerUL;
    std::unique_ptr<gcn::Image> mCornerUR;
    std::unique_ptr<gcn::Image> mCornerDL;
    std::unique_ptr<gcn::Image> mCornerDR;
    std::unique_ptr<gcn::Image> mHorizontal;
    std::unique_ptr<gcn::Image> mVertical;
} // namespace

FFContainer::FFContainer()
{
    if (mInstances == 0)
    {
        mCornerUL.reset(gcn::Image::load("images/cornerul.png"));
        mCornerUR.reset(gcn::Image::load("images/cornerur.png"));
        mCornerDL.reset(gcn::Image::load("images/cornerdl.png"));
        mCornerDR.reset(gcn::Image::load("images/cornerdr.png"));
        mHorizontal.reset(gcn::Image::load("images/horizontal.png"));
        mVertical.reset(gcn::Image::load("images/vertical.png"));
    }

    mInstances++;

    Container::setWidth(0);
    Container::setHeight(0);

    setFrameSize(0);
}

FFContainer::~FFContainer()
{
    mInstances--;

    if (mInstances == 0)
    {
        mCornerUL = nullptr;
        mCornerUR = nullptr;
        mCornerDL = nullptr;
        mCornerDR = nullptr;
        mHorizontal = nullptr;
        mVertical = nullptr;
    }
}

void FFContainer::draw(gcn::Graphics* graphics)
{
    int i;

    if (isOpaque())
    {
        double height = (mRealHeight - 8) / 16.0;
        gcn::Color c(0x7070FF);

        for (i = 0; i<16; ++i)
        {
            graphics->setColor(c * (1.0 - i / 18.0));
            graphics->fillRectangle(gcn::Rectangle(4, (i * height + 4),
            getWidth()-8, (i * height ) + height));
        }
    }

    for (i = 5; i < getHeight()-10; i+=5)
    {
        graphics->drawImage(mVertical.get(), 0, i);
        graphics->drawImage(mVertical.get(), getWidth() - 4, i);
    }
    graphics->drawImage(mVertical.get(), 0, 0, 0, i, 4, getHeight() - 5 - i);
    graphics->drawImage(mVertical.get(), 0, 0, getWidth() - 4, i, 4, getHeight() - 5 - i);

    for (i = 5; i < getWidth()-10; i+=5)
    {
        graphics->drawImage(mHorizontal.get(), i, 0);
        graphics->drawImage(mHorizontal.get(), i, getHeight() - 4);
    }
    graphics->drawImage(mHorizontal.get(), 0, 0, i, 0, getWidth() - 5 - i, 4);
    graphics->drawImage(mHorizontal.get(), 0, 0, i, getHeight() - 4, getWidth() - 5 - i, 4);

    graphics->drawImage(mCornerUL.get(), 0, 0);
    graphics->drawImage(mCornerUR.get(), getWidth() - 5, 0);
    graphics->drawImage(mCornerDL.get(), 0, getHeight() - 5);
    graphics->drawImage(mCornerDR.get(), getWidth() - 5, getHeight() - 5);
}

void FFContainer::logic()
{
    if (mTime < 0)
    {
        mTime = SDL_GetTicks();
    }

    int deltaTime = SDL_GetTicks() - mTime;
    mTime = SDL_GetTicks();

    if (!mShow)
    {
        Container::setWidth(getWidth() - deltaTime);

        if (getWidth() < 0)
        {
            Container::setWidth(0);
        }

        Container::setHeight(getHeight() - deltaTime);

        if (getHeight() < 0)
        {
            Container::setHeight(0);
        }

        if (getHeight() == 0 && getWidth() == 0)
        {
            Container::setVisible(false);
        }
    }
    else
    {
        if (getWidth() < mRealWidth)
        {
            Container::setWidth(getWidth() + deltaTime);

            if (getWidth() > mRealWidth)
            {
                Container::setWidth(mRealWidth);
            }
        }
        else if (getWidth() > mRealWidth)
        {
            Container::setWidth(getWidth() - deltaTime);

            if (getWidth() < mRealWidth)
            {
                Container::setWidth(mRealWidth);
            }
        }

        if (getHeight() < mRealHeight)
        {
            Container::setHeight(getHeight() + deltaTime);

            if (getHeight() > mRealHeight)
            {
                Container::setHeight(mRealHeight);
            }
        }
        else if (getHeight() > mRealHeight)
        {
            Container::setHeight(getHeight() - deltaTime);

            if (getHeight() < mRealHeight)
            {
                Container::setHeight(mRealHeight);
            }
        }
    }

    if (mCurrentSlide < mSlideTarget)
    {
        mCurrentSlide += deltaTime;
        if (mCurrentSlide > mSlideTarget)
        {
            mCurrentSlide = mSlideTarget;
        }
    }

    if (mCurrentSlide > mSlideTarget)
    {
        mCurrentSlide -= deltaTime;
        if (mCurrentSlide < mSlideTarget)
        {
            mCurrentSlide = mSlideTarget;
        }
    }

    Container::logic();
}

void FFContainer::setDimension(const gcn::Rectangle &dimension)
{
    setPosition(dimension.x, dimension.y);
    setWidth(dimension.width);
    setHeight(dimension.height);
}

void FFContainer::setVisible(bool visible)
{
    mShow = visible;

    if (visible)
    {
        Container::setVisible(true);
    }
}

void FFContainer::setWidth(int width)
{
    mRealWidth = width;
}

void FFContainer::setHeight(int height)
{
    mRealHeight = height;
}

void FFContainer::slideContentTo(int y)
{
    mSlideTarget = y;
}

gcn::Rectangle FFContainer::getChildrenArea()
{
    return gcn::Rectangle(0, 0, mRealWidth, mRealHeight);
}
