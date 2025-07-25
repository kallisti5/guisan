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

#include "guisan/widget.hpp"

#include "guisan/actionevent.hpp"
#include "guisan/actionlistener.hpp"
#include "guisan/deathlistener.hpp"
#include "guisan/defaultfont.hpp"
#include "guisan/event.hpp"
#include "guisan/exception.hpp"
#include "guisan/focushandler.hpp"
#include "guisan/graphics.hpp"
#include "guisan/keyinput.hpp"
#include "guisan/keylistener.hpp"
#include "guisan/mouseinput.hpp"
#include "guisan/mouselistener.hpp"
#include "guisan/widgetlistener.hpp"

#include <algorithm>

namespace gcn
{
    Font* Widget::mGlobalFont = nullptr;
    DefaultFont Widget::mDefaultFont;
    std::list<Widget*> Widget::mWidgetInstances;

    Widget::Widget()
    {
        mWidgetInstances.push_back(this);
    }

    Widget::~Widget()
    {
        if (mParent != nullptr)
        {
            mParent->remove(this);
        }

        for (Widget* w : mChildren)
        {
            w->_setParent(nullptr);
        }

        for (DeathListener* deathListener : mDeathListeners)
        {
            const Event event(this);
            deathListener->death(event);
        }

        _setFocusHandler(nullptr);

        mWidgetInstances.remove(this);
    }

    void Widget::drawFrame(Graphics* graphics)
    {
        Color faceColor = getBaseColor();
        Color highlightColor, shadowColor;
        int alpha = getBaseColor().a;
        int width = getWidth() + getFrameSize() * 2 - 1;
        int height = getHeight() + getFrameSize() * 2 - 1;
        highlightColor = faceColor + 0x303030;
        highlightColor.a = alpha;
        shadowColor = faceColor - 0x303030;
        shadowColor.a = alpha;

        unsigned int i;
        for (i = 0; i < getFrameSize(); ++i)
        {
            graphics->setColor(shadowColor);
            graphics->drawLine(i,i, width - i, i);
            graphics->drawLine(i,i + 1, i, height - i - 1);
            graphics->setColor(highlightColor);
            graphics->drawLine(width - i,i + 1, width - i, height - i);
            graphics->drawLine(i,height - i, width - i - 1, height - i);
        }
    }

    void Widget::_setParent(Widget* parent)
    {
        mParent = parent;
    }

    Widget* Widget::getParent() const
    {
        return mParent;
    }

    void Widget::setWidth(int width)
    {
        Rectangle newDimension = mDimension;
        newDimension.width = width;

        setDimension(newDimension);
    }

    int Widget::getWidth() const
    {
        return mDimension.width;
    }

    void Widget::setHeight(int height)
    {
        Rectangle newDimension = mDimension;
        newDimension.height = height;

        setDimension(newDimension);
    }

    int Widget::getHeight() const
    {
        return mDimension.height;
    }

    void Widget::setX(int x)
    {
        Rectangle newDimension = mDimension;
        newDimension.x = x;

        setDimension(newDimension);
    }

    int Widget::getX() const
    {
        return mDimension.x;
    }

    void Widget::setY(int y)
    {
        Rectangle newDimension = mDimension;
        newDimension.y = y;

        setDimension(newDimension);
    }

    int Widget::getY() const
    {
        return mDimension.y;
    }

    void Widget::setPosition(int x, int y)
    {
        Rectangle newDimension = mDimension;
        newDimension.x = x;
        newDimension.y = y;
        
        setDimension(newDimension);
    }

    void Widget::setDimension(const Rectangle& dimension)
    { 
        Rectangle oldDimension = mDimension;
        mDimension = dimension;

        if (mDimension.width != oldDimension.width
            || mDimension.height != oldDimension.height)
        {
            distributeResizedEvent();
        }

        if (mDimension.x != oldDimension.x
            || mDimension.y != oldDimension.y)
        {
            distributeMovedEvent();
        }
    }

    void Widget::setFrameSize(unsigned int borderSize)
    {
        mBorderSize = borderSize;
    }

    unsigned int Widget::getFrameSize() const
    {
        return mBorderSize;
    }

    const Rectangle& Widget::getDimension() const
    {
        return mDimension;
    }

    const std::string& Widget::getActionEventId() const
    {
        return mActionEventId;
    }

    void Widget::setActionEventId(const std::string& actionEventId)
    {
        mActionEventId = actionEventId;
    }

    bool Widget::isFocused() const
    {
        if (!mFocusHandler)
        {
            return false;
        }

        return (mFocusHandler->isFocused(this));
    }

    void Widget::setFocusable(bool focusable)
    {
        if (!focusable && isFocused())
        {
            mFocusHandler->focusNone();
        }

        mFocusable = focusable;
    }

    bool Widget::isFocusable() const
    {
        return mFocusable && isVisible() && isEnabled();
    }

    void Widget::requestFocus()
    {
        if (mFocusHandler == nullptr)
        {
            throw GCN_EXCEPTION("No focushandler set (did you add the widget to the gui?).");
        }

        if (isFocusable())
        {
            mFocusHandler->requestFocus(this);
        }
    }

    void Widget::requestMoveToTop()
    {
        if (mParent)
        {
            mParent->moveToTop(this);
        }
    }

    void Widget::requestMoveToBottom()
    {
        if (mParent)
        {
            mParent->moveToBottom(this);
        }
    }

    void Widget::setVisible(bool visible)
    {
        if (!visible && isFocused())
        {
            mFocusHandler->focusNone();
        }
        
        if (visible)
        {
            distributeShownEvent();
        }
        else if(!visible)
        {
            distributeHiddenEvent();
        }

        mVisible = visible;
    }

    bool Widget::isVisible() const
    {
        if (getParent() == nullptr)
        {
            return mVisible;
        }
        else
        {
            return mVisible && getParent()->isVisible();
        }
    }

    void Widget::setBaseColor(const Color& color)
    {
        mBaseColor = color;
    }

    const Color& Widget::getBaseColor() const
    {
        return mBaseColor;
    }

    void Widget::setForegroundColor(const Color& color)
    {
        mForegroundColor = color;
    }

    const Color& Widget::getForegroundColor() const
    {
        return mForegroundColor;
    }

    void Widget::setBackgroundColor(const Color& color)
    {
        mBackgroundColor = color;
    }

    const Color& Widget::getBackgroundColor() const
    {
        return mBackgroundColor;
    }

    void Widget::setSelectionColor(const Color& color)
    {
        mSelectionColor = color;
    }

    const Color& Widget::getSelectionColor() const
    {
        return mSelectionColor;
    }    
    
    void Widget::_setFocusHandler(FocusHandler* focusHandler)
    {
        if (mFocusHandler)
        {
            releaseModalFocus();
            mFocusHandler->remove(this);
        }

        if (focusHandler)
        {
            focusHandler->add(this);
        }

        mFocusHandler = focusHandler;

        if (mInternalFocusHandler != nullptr)
        {
            return;
        }

        for (Widget* w : mChildren)
        {
            if (widgetExists(w))
            {
                w->_setFocusHandler(focusHandler);
            }
        }
    }

    FocusHandler* Widget::_getFocusHandler()
    {
        return mFocusHandler;
    }

    void Widget::addActionListener(ActionListener* actionListener)
    {
        mActionListeners.push_back(actionListener);
    }

    void Widget::removeActionListener(ActionListener* actionListener)
    {
        mActionListeners.remove(actionListener);
    }

    void Widget::addDeathListener(DeathListener* deathListener)
    {
        mDeathListeners.push_back(deathListener);
    }

    void Widget::removeDeathListener(DeathListener* deathListener)
    {
        mDeathListeners.remove(deathListener);
    }

    void Widget::addKeyListener(KeyListener* keyListener)
    {
        mKeyListeners.push_back(keyListener);
    }

    void Widget::removeKeyListener(KeyListener* keyListener)
    {
        mKeyListeners.remove(keyListener);
    }

    void Widget::addFocusListener(FocusListener* focusListener)
    {
        mFocusListeners.push_back(focusListener);
    }

    void Widget::removeFocusListener(FocusListener* focusListener)
    {
        mFocusListeners.remove(focusListener);
    }

    void Widget::addMouseListener(MouseListener* mouseListener)
    {
        mMouseListeners.push_back(mouseListener);
    }

    void Widget::removeMouseListener(MouseListener* mouseListener)
    {
        mMouseListeners.remove(mouseListener);
    }

    void Widget::addWidgetListener(WidgetListener* widgetListener)
    {
        mWidgetListeners.push_back(widgetListener);
    }

    void Widget::removeWidgetListener(WidgetListener* widgetListener)
    {
        mWidgetListeners.remove(widgetListener);
    }

    void Widget::getAbsolutePosition(int& x, int& y) const
    {
        if (getParent() == nullptr)
        {
            x = mDimension.x;
            y = mDimension.y;
            return;
        }

        int parentX;
        int parentY;

        getParent()->getAbsolutePosition(parentX, parentY);

        x = parentX + mDimension.x + getParent()->getChildrenArea().x;
        y = parentY + mDimension.y + getParent()->getChildrenArea().y;
    }

    Font* Widget::getFont() const
    {
        if (mCurrentFont == nullptr)
        {
            if (mGlobalFont == nullptr)
            {
                return &mDefaultFont;
            }

            return mGlobalFont;
        }

        return mCurrentFont;
    }

    void Widget::setGlobalFont(Font* font)
    {
        mGlobalFont = font;

        for (Widget* w : mWidgetInstances)
        {
            if (w->mCurrentFont == nullptr)
            {
                w->fontChanged();
            }
        }
    }

    Font* Widget::getGlobalFont()
    {
        return mGlobalFont;
    }

    void Widget::setWidgetsBaseColor(Color color)
    {
        for (Widget* w : mWidgetInstances)
        {
            w->setBaseColor(color);
        }
    }

    void Widget::setWidgetsForegroundColor(Color color)
    {
        for (Widget* w : mWidgetInstances)
        {
            w->setForegroundColor(color);
        }
    }

    void Widget::setWidgetsBackgroundColor(Color color)
    {
        for (Widget* w : mWidgetInstances)
        {
            w->setBackgroundColor(color);
        }
    }

    void Widget::setWidgetsSelectionColor(Color color)
    {
        for (Widget* w : mWidgetInstances)
        {
            w->setSelectionColor(color);
        }
    }

    void Widget::setFont(Font* font)
    {
        mCurrentFont = font;
        fontChanged();
    }

    bool Widget::widgetExists(const Widget* widget)
    {
        return std::find(mWidgetInstances.begin(), mWidgetInstances.end(), widget) != mWidgetInstances.end();
    }

    bool Widget::isTabInEnabled() const
    {
        return mTabIn;
    }

    void Widget::setTabInEnabled(bool enabled)
    {
        mTabIn = enabled;
    }

    bool Widget::isTabOutEnabled() const
    {
        return mTabOut;
    }

    void Widget::setTabOutEnabled(bool enabled)
    {
        mTabOut = enabled;
    }

    void Widget::setSize(int width, int height)
    {
        Rectangle newDimension = mDimension;
        newDimension.width = width;
        newDimension.height = height;

        setDimension(newDimension);
    }

    void Widget::setEnabled(bool enabled)
    {
        mEnabled = enabled;
    }

    bool Widget::isEnabled() const
    {
        return mEnabled && isVisible();
    }

    void Widget::requestModalFocus()
    {
        if (mFocusHandler == nullptr)
        {
            throw GCN_EXCEPTION("No focushandler set (did you add the widget to the gui?).");
        }

        mFocusHandler->requestModalFocus(this);
    }

    void Widget::requestModalMouseInputFocus()
    {
        if (mFocusHandler == nullptr)
        {
            throw GCN_EXCEPTION("No focushandler set (did you add the widget to the gui?).");
        }

        mFocusHandler->requestModalMouseInputFocus(this);
    }

    void Widget::releaseModalFocus()
    {
        if (mFocusHandler == nullptr)
        {
            return;
        }

        mFocusHandler->releaseModalFocus(this);
    }

    void Widget::releaseModalMouseInputFocus()
    {
        if (mFocusHandler == nullptr)
        {
            return;
        }

        mFocusHandler->releaseModalMouseInputFocus(this);
    }

    bool Widget::isModalFocused() const
    {
        if (mFocusHandler == nullptr)
        {
            throw GCN_EXCEPTION("No focushandler set (did you add the widget to the gui?).");
        }

        if (getParent() != nullptr)
        {
            return (mFocusHandler->getModalFocused() == this) || getParent()->isModalFocused();
        }

        return mFocusHandler->getModalFocused() == this;
    }

    bool Widget::isModalMouseInputFocused() const
    {
        if (mFocusHandler == nullptr)
        {
            throw GCN_EXCEPTION("No focushandler set (did you add the widget to the gui?).");
        }

        if (getParent() != nullptr)
        {
            return (mFocusHandler->getModalMouseInputFocused() == this) || getParent()->isModalMouseInputFocused();
        }

        return mFocusHandler->getModalMouseInputFocused() == this;
    }

    Widget *Widget::getWidgetAt(int x, int y)
    {
        Rectangle r = getChildrenArea();

        if (!r.isContaining(x, y))
        {
            return nullptr;
        }

        x -= r.x;
        y -= r.y;

        for (auto iter = mChildren.rbegin(); iter != mChildren.rend(); ++iter)
        {
            Widget* widget = (*iter);
            if (widget->isVisible() && widget->getDimension().isContaining(x, y))
            {
                return widget;
            }
        }
        return nullptr;
    }

    const std::list<MouseListener*>& Widget::_getMouseListeners()
    {
        return mMouseListeners;
    }

    const std::list<KeyListener*>& Widget::_getKeyListeners()
    {
        return mKeyListeners;
    }

    const std::list<FocusListener*>& Widget::_getFocusListeners()
    {
        return mFocusListeners;
    }

    Rectangle Widget::getChildrenArea()
    {
        return Rectangle(0, 0, 0, 0);
    }

    FocusHandler* Widget::_getInternalFocusHandler()
    {
        return mInternalFocusHandler;
    }

    void Widget::setInternalFocusHandler(FocusHandler* focusHandler)
    {
        mInternalFocusHandler = focusHandler;

        for (Widget* w : mChildren)
        {
            if (mInternalFocusHandler == nullptr)
            {
                w->_setFocusHandler(_getFocusHandler());
            }
            else
            {
                w->_setFocusHandler(mInternalFocusHandler);
            }
        }
    }

    void Widget::setId(const std::string& id)
    {
        mId = id;
    }

    const std::string& Widget::getId()
    {
        return mId;
    }

    void Widget::distributeResizedEvent()
    {
        const Event event(this);

        for (WidgetListener* widgetListener : mWidgetListeners)
        {
            widgetListener->widgetResized(event);
        }
    }

    void Widget::distributeMovedEvent()
    {
        const Event event(this);

        for (WidgetListener* widgetListener : mWidgetListeners)
        {
            widgetListener->widgetMoved(event);
        }
    }

    void Widget::distributeHiddenEvent()
    {
        const Event event(this);

        for (WidgetListener* widgetListener : mWidgetListeners)
        {
            widgetListener->widgetHidden(event);
        }
    }

    void Widget::distributeActionEvent()
    {
        const ActionEvent actionEvent(this, mActionEventId);

        for (ActionListener* actionListener : mActionListeners)
        {
            actionListener->action(actionEvent);
        }
    }

    void Widget::distributeShownEvent()
    {
        const Event event(this);

        for (WidgetListener* widgetListener : mWidgetListeners)
        {
            widgetListener->widgetShown(event);
        }
    }

    void Widget::showPart(Rectangle rectangle)
    {
        if (mParent != nullptr)
        {
            mParent->showWidgetPart(this, rectangle);
        }
    }

    Widget* Widget::getTop() const
    {
        if (getParent() == nullptr) return nullptr;

        Widget* widget = getParent();
        Widget* parent = getParent()->getParent();

        while (parent != nullptr)
        {
            widget = parent;
            parent = parent->getParent();
        }

        return widget;
    }

    std::list<Widget*> Widget::getWidgetsIn(const Rectangle& area, Widget* ignore)
    {
        std::list<Widget*> result;

        for (Widget* widget : mChildren)
        {
            if (ignore != widget && widget->getDimension().isIntersecting(area))
            {
                result.push_back(widget);
            }
        }

        return result;
    }

    void Widget::resizeToChildren()
    {
        int w = 0;
        int h = 0;
        for (Widget* widget : mChildren)
        {
            w = std::max(w, widget->getX() + widget->getWidth());
            h = std::max(h, widget->getY() + widget->getHeight());
        }

        setSize(w, h);
    }

    Widget* Widget::findWidgetById(const std::string& id)
    {
        for (Widget* widget : mChildren)
        {
            if (widget->getId() == id)
            {
                return widget;
            }
            if (Widget* child = widget->findWidgetById(id))
            {
                return child;
            }
        }
        return nullptr;
    }

    void Widget::showWidgetPart(Widget* widget, Rectangle area)
    {
        Rectangle widgetArea = getChildrenArea();

        area.x += widget->getX();
        area.y += widget->getY();

        if (area.x + area.width > widgetArea.width)
        {
            widget->setX(widget->getX() - area.x - area.width + widgetArea.width);
        }

        if (area.y + area.height > widgetArea.height)
        {
            widget->setY(widget->getY() - area.y - area.height + widgetArea.height);
        }

        if (area.x < 0)
        {
            widget->setX(widget->getX() - area.x);
        }

        if (area.y < 0)
        {
            widget->setY(widget->getY() - area.y);
        }
    }

    void Widget::clear()
    {
        for (Widget* widget : mChildren)
        {
            widget->_setFocusHandler(nullptr);
            widget->_setParent(nullptr);
        }
        mChildren.clear();
    }

    void Widget::remove(Widget* widget)
    {
        auto it = std::find(mChildren.begin(), mChildren.end(), widget);
        if (it == mChildren.end())
        {
            throw GCN_EXCEPTION("There is no such widget in this container.");
        }
        else
        {
            mChildren.erase(it);
            widget->_setFocusHandler(nullptr);
            widget->_setParent(nullptr);
        }
    }

    void Widget::add(Widget* widget)
    {
        mChildren.push_back(widget);

        if (mInternalFocusHandler == nullptr)
        {
            widget->_setFocusHandler(_getFocusHandler());
        }
        else
        {
            widget->_setFocusHandler(mInternalFocusHandler);
        }

        widget->_setParent(this);
    }

    void Widget::moveToTop(Widget* widget)
    {
        const auto iter = std::find(mChildren.begin(), mChildren.end(), widget);

        if (iter == mChildren.end())
        {
            throw GCN_EXCEPTION("There is no such widget in this widget.");
        }

        mChildren.remove(widget);
        mChildren.push_back(widget);
    }

    void Widget::moveToBottom(Widget* widget)
    {
        const auto iter = find(mChildren.begin(), mChildren.end(), widget);

        if (iter == mChildren.end())
        {
            throw GCN_EXCEPTION("There is no such widget in this widget.");
        }

        mChildren.remove(widget);
        mChildren.push_front(widget);
    }

    void Widget::focusNext()
    {
        const auto focusedIt = std::find_if(
            mChildren.begin(), mChildren.end(), [](auto* w) { return w->isFocused(); });

        const auto next = focusedIt == mChildren.end() ? mChildren.begin() : std::next(focusedIt);
        auto it = std::find_if(next, mChildren.end(), [](auto* w) { return w->isFocusable(); });

        if (it == mChildren.end())
        {
            it = std::find_if(mChildren.begin(), next, [](auto* w) { return w->isFocusable(); });
        }
        if (it != next)
        {
            (*it)->requestFocus();
        }
    }

    void Widget::focusPrevious()
    {
        const auto focusedRit = std::find_if(
            mChildren.rbegin(), mChildren.rend(), [](auto* w) { return w->isFocused(); });

        const auto next = focusedRit == mChildren.rend() ? mChildren.rbegin() : std::next(focusedRit);
        auto rit = std::find_if(next, mChildren.rend(), [](auto* w) { return w->isFocusable(); });

        if (rit == mChildren.rend())
        {
            rit = std::find_if(mChildren.rbegin(), next, [](auto* w) { return w->isFocusable(); });
        }
        if (rit != next)
        {
            (*rit)->requestFocus();
        }
    }

    void Widget::_draw(Graphics* graphics)
    {
        if (mBorderSize > 0)
        {
            Rectangle rec = mDimension;
            rec.x -= mBorderSize;
            rec.y -= mBorderSize;
            rec.width += 2 * mBorderSize;
            rec.height += 2 * mBorderSize;
            graphics->pushClipArea(rec);
            drawFrame(graphics);
            graphics->popClipArea();
        }

        graphics->pushClipArea(mDimension);
        draw(graphics);

        Rectangle childrenArea = getChildrenArea();
        graphics->pushClipArea(childrenArea);
        childrenArea.x = 0;
        childrenArea.y = 0;

        for (auto* widget : mChildren)
        {
            // Only draw a widget if it's visible
            // and if it visible inside the children area.
            if (widget->isVisible() && childrenArea.isIntersecting(widget->getDimension()))
            {
                widget->_draw(graphics);
            }
        }

        graphics->popClipArea();
        graphics->popClipArea();
    }

    void Widget::_logic()
    {
        logic();

        for (Widget* w : mChildren)
        {
            w->_logic();
        }
    }

    const std::list<Widget*>& Widget::getChildren() const
    {
        return mChildren;
    }
}
