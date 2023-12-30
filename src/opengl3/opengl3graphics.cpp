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

/*
 * For comments regarding functions please see the header file.
 */

#include <GL/glew.h>

#include "guisan/opengl3/opengl3graphics.hpp"

#include "guisan/exception.hpp"
#include "guisan/image.hpp"
#include "guisan/opengl3/opengl3image.hpp"

namespace gcn
{
	OpenGL3Graphics::OpenGL3Graphics() : mInitialize (true), mVBO (0), mImageShader (0), mLineShader (0)
	{
		setTargetPlane(640, 480);
		mAlpha = false;

		glewExperimental = GL_TRUE;
	}

	OpenGL3Graphics::OpenGL3Graphics(int width, int height)
	{
		setTargetPlane(width, height);
	}

	OpenGL3Graphics::~OpenGL3Graphics()
	{
		if (mVBO != 0)
		{
			glDeleteBuffers(1, &mVBO);
		}
	}

	void OpenGL3Graphics::_beginDraw()
	{
		if (mInitialize)
		{
			GLenum error = glewInit();
			if (GLEW_OK != error)
			{
				//std::cout << std::string(reinterpret_cast <const char *>(glewGetErrorString(error))) << std::endl;

				throw gcn::Exception("GLEW failed to init: " + std::string(reinterpret_cast <const char *>(glewGetErrorString(error))));
			}

			mImageShader = createShaderProgram(

				"attribute vec3 vPosition;"
				"attribute vec2 vTexUV0;"
				"varying vec2 fTexUV;"
				"uniform mat4 uMVP;"
				"void main() {"
				"gl_Position = uMVP * vec4(vPosition, 1.0); fTexUV = vTexUV0;"
				"}",

				"varying vec2 fTexUV;"
				"uniform sampler2D uTex;"
				"void main() {"
				"gl_FragColor = texture2D(uTex, fTexUV);"
				"}"
			);

			mLineShader = createShaderProgram(

				"attribute vec3 vPosition;"
				"uniform mat4 uMVP;"
				"void main() {"
				"gl_Position = uMVP * vec4(vPosition, 1.0);"
				"}",

				"uniform vec4 uColor;"
				"void main() {"
				"gl_FragColor = uColor;"
				"}"
			);

			mProjection = glm::ortho<float>(0.0f, static_cast<float>(mWidth), static_cast<float>(mHeight), 0.0f, -1.0f, 1.0f);

			glUseProgram(mImageShader);
			glUniformMatrix4fv(glGetUniformLocation(mImageShader, "uMVP"), 1, GL_FALSE, glm::value_ptr(mProjection));

			glUseProgram(mLineShader);
			glUniformMatrix4fv(glGetUniformLocation(mLineShader, "uMVP"), 1, GL_FALSE, glm::value_ptr(mProjection));
			glUniform4f(glGetUniformLocation(mLineShader, "uColor"), 0.0f, 0.0f, 0.0f, 0.0f);

			glGenBuffers(1, &mVBO);

			mInitialize = false;
		}

		glBindBuffer(GL_ARRAY_BUFFER, mVBO);

		glDisable(GL_LIGHTING);
		glDisable(GL_CULL_FACE);
		glDisable(GL_DEPTH_TEST);
		glDisable(GL_TEXTURE_2D);

		glEnable(GL_SCISSOR_TEST);
		glPointSize(1.0);
		glLineWidth(1.0);

		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

		glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);

		pushClipArea(Rectangle(0, 0, mWidth, mHeight));
	}

	void OpenGL3Graphics::_endDraw()
	{
		glBindBuffer(GL_ARRAY_BUFFER, 0);

		glEnable(GL_CULL_FACE);
		glEnable(GL_DEPTH_TEST);

		glDisable(GL_SCISSOR_TEST);

		popClipArea();
	}

	bool OpenGL3Graphics::pushClipArea(Rectangle area)
	{
		bool result = Graphics::pushClipArea(area);

		glScissor(mClipStack.top().x,
				  mHeight - mClipStack.top().y - mClipStack.top().height,
				  mClipStack.top().width,
				  mClipStack.top().height);

		return result;
	}

	void OpenGL3Graphics::popClipArea()
	{
		Graphics::popClipArea();

		if (mClipStack.empty())
		{
			return;
		}

		glScissor(mClipStack.top().x,
				  mHeight - mClipStack.top().y - mClipStack.top().height,
				  mClipStack.top().width,
				  mClipStack.top().height);
	}

	void OpenGL3Graphics::setTargetPlane(int width, int height)
	{
		mWidth = width;
		mHeight = height;
	}

	void OpenGL3Graphics::drawImage(const Image* image,
								   int srcX,
								   int srcY,
								   int dstX,
								   int dstY,
								   int width,
								   int height)
	{
		const OpenGL3Image* srcImage = dynamic_cast<const OpenGL3Image*>(image);

		if (srcImage == NULL)
		{
			throw GCN_EXCEPTION("Trying to draw an image of unknown format, must be an OpenGLImage.");
		}

		if (mClipStack.empty())
		{
			throw GCN_EXCEPTION("Clip stack is empty, perhaps you called a draw funtion outside of _beginDraw() and _endDraw()?");
		}

		const ClipRectangle& top = mClipStack.top();

		dstX += top.xOffset;
		dstY += top.yOffset;

		// Find OpenGL texture coordinates
		float texX1 = srcX / (float)srcImage->getTextureWidth();
		float texY1 = srcY / (float)srcImage->getTextureHeight();
		float texX2 = (srcX+width) / (float)srcImage->getTextureWidth();
		float texY2 = (srcY+height) / (float)srcImage->getTextureHeight();

		glBindTexture(GL_TEXTURE_2D, srcImage->getTextureHandle());

		glEnable(GL_TEXTURE_2D);

		// Check if blending already is enabled
		if (!mAlpha)
		{
			glEnable(GL_BLEND);
		}

		// Draw a textured quad -- the image
		GLfloat box[4][5] = {
			{ static_cast<float>(dstX), static_cast<float>(dstY + height), 0.0f, static_cast<float>(texX1), static_cast<float>(texY2) },
			{ static_cast<float>(dstX), static_cast<float>(dstY), 0.0f, static_cast<float>(texX1), static_cast<float>(texY1) },
			{ static_cast<float>(dstX + width), static_cast<float>(dstY + height), 0.0f, static_cast<float>(texX2), static_cast<float>(texY2) },
			{ static_cast<float>(dstX + width), static_cast<float>(dstY), 0.0f, static_cast<float>(texX2), static_cast<float>(texY1) },
		};

		glBufferData(GL_ARRAY_BUFFER, sizeof box, box, GL_DYNAMIC_DRAW);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(GLfloat) * 5, 0);   // Position
		glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(GLfloat) * 5, ((char*)NULL + 12));     // TexUVs
		glEnableVertexAttribArray(0);
		glEnableVertexAttribArray(1);

		glUseProgram(mImageShader);
		glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

		// Don't disable blending if the color has alpha
		if (!mAlpha)
		{
			glDisable(GL_BLEND);
		}
	}

	void OpenGL3Graphics::drawPoint(int x, int y)
	{
		if (mClipStack.empty())
		{
			throw GCN_EXCEPTION("Clip stack is empty, perhaps you called a draw funtion outside of _beginDraw() and _endDraw()?");
		}

		const ClipRectangle& top = mClipStack.top();

		x += top.xOffset;
		y += top.yOffset;

		GLfloat point[3] = { static_cast<float>(x), static_cast<float>(y), 0.0f };

		glBufferData(GL_ARRAY_BUFFER, sizeof point, point, GL_DYNAMIC_DRAW);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
		glEnableVertexAttribArray(0);

		glUseProgram(mLineShader);
		glDrawArrays(GL_POINTS, 0, 1);
	}

	void OpenGL3Graphics::drawLine(int x1, int y1, int x2, int y2)
	{
		if (mClipStack.empty())
		{
			throw GCN_EXCEPTION("Clip stack is empty, perhaps you called a draw funtion outside of _beginDraw() and _endDraw()?");
		}

		const ClipRectangle& top = mClipStack.top();

		x1 += top.xOffset;
		y1 += top.yOffset;
		x2 += top.xOffset;
		y2 += top.yOffset;

		GLfloat line[2][3] =
		{
			{ x1 + 0.375f, y1 + 0.375f, 0.0f },
			{ x2 + 1.0f - 0.375f, y2 + 1.0f - 0.375f, 0.0f }
		};

		glBufferData(GL_ARRAY_BUFFER, sizeof(line), line, GL_DYNAMIC_DRAW);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
		glEnableVertexAttribArray(0);

		glUseProgram(mLineShader);
		glDrawArrays(GL_LINES, 0, 2);
	}

	void OpenGL3Graphics::drawRectangle(const Rectangle& rectangle)
	{
		if (mClipStack.empty())
		{
			throw GCN_EXCEPTION("Clip stack is empty, perhaps you called a draw funtion outside of _beginDraw() and _endDraw()?");
		}

		const ClipRectangle& top = mClipStack.top();

		GLfloat box[4][3] = {
			{ static_cast<float>(rectangle.x + top.xOffset), static_cast<float>(rectangle.y + top.yOffset), 0.0f },
			{ static_cast<float>(rectangle.x + rectangle.width + top.xOffset) - 1.0f, static_cast<float>(rectangle.y + top.yOffset) + 0.375f, 0.0f },
			{ static_cast<float>(rectangle.x + rectangle.width + top.xOffset) - 1.0f, static_cast<float>(rectangle.y + rectangle.height + top.yOffset), 0.0f },
			{ static_cast<float>(rectangle.x + top.xOffset), static_cast<float>(rectangle.y + rectangle.height + top.yOffset), 0.0f },
		};

		glBufferData(GL_ARRAY_BUFFER, sizeof box, box, GL_DYNAMIC_DRAW);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
		glEnableVertexAttribArray(0);

		glUseProgram(mLineShader);
		glDrawArrays(GL_LINE_LOOP, 0, 4);
	}

	void OpenGL3Graphics::fillRectangle(const Rectangle& rectangle)
	{
		if (mClipStack.empty())
		{
			throw GCN_EXCEPTION("Clip stack is empty, perhaps you called a draw funtion outside of _beginDraw() and _endDraw()?");
		}

		const ClipRectangle& top = mClipStack.top();

		GLfloat box[4][3] = {
			{ static_cast<float>(rectangle.x + top.xOffset), static_cast<float>(rectangle.y + top.yOffset), 0.0f },
			{ static_cast<float>(rectangle.x + rectangle.width + top.xOffset), static_cast<float>(rectangle.y + top.yOffset), 0.0f },
			{ static_cast<float>(rectangle.x + top.xOffset), static_cast<float>(rectangle.y + rectangle.height + top.yOffset), 0.0f },
			{ static_cast<float>(rectangle.x + rectangle.width + top.xOffset), static_cast<float>(rectangle.y + rectangle.height + top.yOffset), 0.0f },
		};

		glBufferData(GL_ARRAY_BUFFER, sizeof (box), box, GL_DYNAMIC_DRAW);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
		glEnableVertexAttribArray(0);

		glUseProgram(mLineShader);
		glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
	}

	void OpenGL3Graphics::setColor(const Color& color)
	{
		mColor = color;
		glUseProgram(mLineShader);
		glUniform4f(glGetUniformLocation(mLineShader, "uColor"), color.r / 255.0f, color.g / 255.0f, color.b / 255.0f, color.a / 255.0f);

		mAlpha = color.a != 255;

		if (mAlpha)
		{
			glEnable(GL_BLEND);
		}
	}

	const Color& OpenGL3Graphics::getColor() const
	{
		return mColor;
	}

	int OpenGL3Graphics::getTargetPlaneWidth() const
	{
		return mWidth;
	}

	int OpenGL3Graphics::getTargetPlaneHeight() const
	{
		return mHeight;
	}

	GLuint OpenGL3Graphics::createShaderProgram(const std::string& vs, const std::string& fs)
	{
		GLint success;

		GLuint program = glCreateProgram();

		GLuint vertShader = glCreateShader(GL_VERTEX_SHADER);
		GLuint fragShader = glCreateShader(GL_FRAGMENT_SHADER);

		GLint length = strlen(vs.c_str());
		const char *c_str = vs.c_str();

		glShaderSource(vertShader, 1, &c_str, &length);
		glCompileShader(vertShader);
		glAttachShader(program, vertShader);

		glGetShaderiv(vertShader, GL_COMPILE_STATUS, &success);

		if (!success)
		{
			GLchar infolog[256];
			glGetShaderInfoLog(vertShader, 256, NULL, infolog);

			throw Exception("Vertex shader failed to compile: " + std::string(infolog));
		}

		length = strlen(fs.c_str());
		c_str = fs.c_str();

		glShaderSource(fragShader, 1, &c_str, &length);
		glCompileShader(fragShader);
		glAttachShader(program, fragShader);

		glGetShaderiv(fragShader, GL_COMPILE_STATUS, &success);

		if (!success)
		{
			GLchar infolog[256];
			glGetShaderInfoLog(fragShader, 256, NULL, infolog);

			throw Exception("Fragment shader failed to compile: " + std::string(infolog));
		}

		glBindAttribLocation(program, 0, "vPosition");
		glBindAttribLocation(program, 1, "vTexUV0");

		glLinkProgram(program);
		glDeleteShader(vertShader);
		glDeleteShader(fragShader);

		glGetProgramiv(program, GL_LINK_STATUS, &success);
		if (!success)
		{
			GLchar infolog[1024];
			glGetProgramInfoLog(program, 1024, NULL, infolog);

			throw Exception("Shader program failed to link: " + std::string(infolog));
		}

		return program;
	}
}