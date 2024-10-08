/*      _______   __   __   __   ______   __   __   _______   __   __
 *     / _____/\ / /\ / /\ / /\ / ____/\ / /\ / /\ / ___  /\ /  |\/ /\
 *    / /\____\// / // / // / // /\___\// /_// / // /\_/ / // , |/ / /
 *   / / /__   / / // / // / // / /    / ___  / // ___  / // /| ' / /
 *  / /_// /\ / /_// / // / // /_/_   / / // / // /\_/ / // / |  / /
 * /______/ //______/ //_/ //_____/\ /_/ //_/ //_/ //_/ //_/ /|_/ /
 * \______\/ \______\/ \_\/ \_____\/ \_\/ \_\/ \_\/ \_\/ \_\/ \_\/
 *
 * Copyright (c) 2004, 2005, 2006, 2007 Olof Naess�n and Per Larsson
 *
 *                                                         Js_./
 * Per Larsson a.k.a finalman                          _RqZ{a<^_aa
 * Olof Naess�n a.k.a jansem/yakslem                _asww7!uY`>  )\a//
 *                                                 _Qhm`] _f "'c  1!5m
 * Visit: http://guichan.darkbits.org             )Qk<P ` _: :+' .'  "{[
 *                                               .)j(] .d_/ '-(  P .   S
 * License: (BSD)                                <Td/Z <fP"5(\"??"\a.  .L
 * Redistribution and use in source and          _dV>ws?a-?'      ._/L  #'
 * binary forms, with or without                 )4d[#7r, .   '     )d`)[
 * modification, are permitted provided         _Q-5'5W..j/?'   -?!\)cam'
 * that the following conditions are met:       j<<WP+k/);.        _W=j f
 * 1. Redistributions of source code must       .$%w\/]Q  . ."'  .  mj$
 *    retain the above copyright notice,        ]E.pYY(Q]>.   a     J@\
 *    this list of conditions and the           j(]1u<sE"L,. .   ./^ ]{a
 *    following disclaimer.                     4'_uomm\.  )L);-4     (3=
 * 2. Redistributions in binary form must        )_]X{Z('a_"a7'<a"a,  ]"[
 *    reproduce the above copyright notice,       #}<]m7`Za??4,P-"'7. ).m
 *    this list of conditions and the            ]d2e)Q(<Q(  ?94   b-  LQ/
 *    following disclaimer in the                <B!</]C)d_, '(<' .f. =C+m
 *    documentation and/or other materials      .Z!=J ]e []('-4f _ ) -.)m]'
 *    provided with the distribution.          .w[5]' _[ /.)_-"+?   _/ <W"
 * 3. Neither the name of Guichan nor the      :$we` _! + _/ .        j?
 *    names of its contributors may be used     =3)= _f  (_yQmWW$#(    "
 *    to endorse or promote products derived     -   W,  sQQQQmZQ#Wwa]..
 *    from this software without specific        (js, \[QQW$QWW#?!V"".
 *    prior written permission.                    ]y:.<\..          .
 *                                                 -]n w/ '         [.
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT       )/ )/           !
 * HOLDERS AND CONTRIBUTORS "AS IS" AND ANY         <  (; sac    ,    '
 * EXPRESS OR IMPLIED WARRANTIES, INCLUDING,               ]^ .-  %
 * BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF            c <   r
 * MERCHANTABILITY AND FITNESS FOR A PARTICULAR            aga<  <La
 * PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE          5%  )P'-3L
 * COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR        _bQf` y`..)a
 * ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,          ,J?4P'.P"_(\?d'.,
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES               _Pa,)!f/<[]/  ?"
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT      _2-..:. .r+_,.. .
 * OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,     ?a.<%"'  " -'.a_ _,
 * DATA, OR PROFITS; OR BUSINESS INTERRUPTION)                     ^
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN
 * ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN
 * IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

/*
 * For comments regarding functions please see the header file.
 */

#include "guisan/rectangle.hpp"

namespace gcn
{

    Rectangle::Rectangle(int x, int y, int width, int height) :
        x(x),
        y(y),
        width(width),
        height(height)
    {}

    void Rectangle::setAll(int x, int y, int width, int height)
    {
        this->x = x;
        this->y = y;
        this->width = width;
        this->height = height;
    }

    bool Rectangle::isIntersecting(const Rectangle& rectangle) const
    {
        if (isEmpty() || rectangle.isEmpty()) return false;
        int x_ = x;
        int y_ = y;
        int width_ = width;
        int height_ = height;

        x_ -= rectangle.x;
        y_ -= rectangle.y;

        if (x_ < 0)
        {
            width_ += x_;
            x_ = 0;
        }
        else if (x_ + width_ > rectangle.width)
        {
            width_ = rectangle.width - x_;
        }

        if (y_ < 0)
        {
            height_ += y_;
            y_ = 0;
        }
        else if (y_ + height_ > rectangle.height)
        {
            height_ = rectangle.height - y_;
        }

        if (width_ <= 0 || height_ <= 0)
        {
            return false;
        }

        return true;
    }

    bool Rectangle::isContaining(int x, int y) const
    {
        if (isEmpty()) return false;
        return ((x >= this->x) && (y >= this->y)
                && x < (this->x + this->width)
                && y < (this->y + this->height));
    }

    bool Rectangle::isContaining(const Rectangle& other) const
    {
        if (isEmpty() || other.isEmpty()) return false;
        return other.x >= x && other.y >= y && other.x + other.width <= x + width
            && other.y + other.height <= y + height;
    }

    bool Rectangle::isEmpty() const
    {
        return width <= 0 || height <= 0;
    }

    Rectangle Rectangle::operator+(const Rectangle& rh) const
    {
        if (isEmpty()) return rh;
        if (rh.isEmpty()) return *this;
        const int nx = x < rh.x ? x : rh.x;
        const int ny = y < rh.y ? y : rh.y;
        const int nx2 = x + width > rh.x + rh.width ? x + width : rh.x + rh.width;
        const int ny2 = y + height > rh.y + rh.height ? y + height : rh.y + rh.height;
        return Rectangle(nx, ny, nx2 - nx, ny2 - ny);
    }

    const Rectangle& Rectangle::operator+=(const Rectangle& rh)
    {
        if (rh.isEmpty()) return *this;
        if (isEmpty()) return *this = rh;
        x = x < rh.x ? x : rh.x;
        y = y < rh.y ? y : rh.y;
        const int x2 = x + width > rh.x + rh.width ? x + width : rh.x + rh.width;
        const int y2 = y + height > rh.y + rh.height ? y + height : rh.y + rh.height;
        width = x2 - x;
        height = y2 - y;
        return *(this);
    }

    Rectangle Rectangle::intersection(const Rectangle& rh) const
    {
        if (isEmpty() || rh.isEmpty()) return Rectangle();
        const int nx = x > rh.x ? x : rh.x;
        const int ny = y > rh.y ? y : rh.y;
        const int nx2 = x + width < rh.x + rh.width ? x + width : rh.x + rh.width;
        const int ny2 = y + height < rh.y + rh.height ? y + height : rh.y + rh.height;
        return Rectangle(nx, ny, nx2 - nx, ny2 - ny);
    }

    std::ostream& operator<<(std::ostream& out, const Rectangle& rectangle)
    {
        return out << "Rectangle [x = " << rectangle.x << ", y = " << rectangle.y
                   << ", width = " << rectangle.width << ", height = " << rectangle.height << "]";
    }
}
