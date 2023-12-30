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

#ifndef GCN_OPENGL3GRAPHICS_HPP
#define GCN_OPENGL3GRAPHICS_HPP

#if defined (_WIN32)
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#endif

#if defined (__amigaos4__)
#include <mgl/gl.h>
#elif defined (__APPLE__)
#include <OpenGL/gl.h>
#else
#include <GL/gl.h>
#endif

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "guisan/color.hpp"
#include "guisan/graphics.hpp"
#include "guisan/platform.hpp"

namespace gcn
{
	/**
	 * OpenGL3 implementation of the Graphics.
	 */
	class GCN_EXTENSION_DECLSPEC OpenGL3Graphics: public Graphics
	{
	public:

		// Needed so that drawImage(gcn::Image *, int, int) is visible.
		using Graphics::drawImage;

		/**
		 * Constructor.
		 */
		OpenGL3Graphics();

		/**
		 * Constructor.
		 *
		 * @param width the width of the logical drawing surface. Should be the
		 *              same as the screen resolution.
		 *
		 * @param height the height ot the logical drawing surface. Should be
		 *               the same as the screen resolution.
		 */
		OpenGL3Graphics(int width, int height);

		/**
		 * Destructor.
		 */
		virtual ~OpenGL3Graphics();

		/**
		 * Sets the target plane on where to draw.
		 *
		 * @param width the width of the logical drawing surface. Should be the
		 *              same as the screen resolution.
		 * @param height the height ot the logical drawing surface. Should be
		 *               the same as the screen resolution.
		 */
		virtual void setTargetPlane(int width, int height);

		/**
		 * Gets the target plane width.
		 *
		 * @return The target plane width.
		 */
		virtual int getTargetPlaneWidth() const;

		/**
		 * Gets the target plane height.
		 *
		 * @return The target plane height.
		 */
		virtual int getTargetPlaneHeight() const;


		// Inherited from Graphics

		virtual void _beginDraw();

		virtual void _endDraw();

		virtual bool pushClipArea(Rectangle area);

		virtual void popClipArea();

		virtual void drawImage(const Image* image,
							   int srcX,
							   int srcY,
							   int dstX,
							   int dstY,
							   int width,
							   int height);

		virtual void drawPoint(int x, int y);

		virtual void drawLine(int x1, int y1, int x2, int y2);

		virtual void drawRectangle(const Rectangle& rectangle);

		virtual void fillRectangle(const Rectangle& rectangle);

		virtual void setColor(const Color& color);

		virtual const Color& getColor() const;

	protected:
		int mWidth, mHeight;
		bool mAlpha;
		Color mColor;

		GLuint mVBO;

		GLuint mImageShader;
		GLuint mLineShader;

		glm::mat4 mProjection;

		mutable bool mInitialize;

	private:

		GLuint createShaderProgram(const std::string& vs, const std::string& fs);
	};
}

#endif // end GCN_OPENGL3GRAPHICS_HPP