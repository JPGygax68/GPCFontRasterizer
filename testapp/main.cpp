#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdexcept>
#include <sstream>

#include <SDL.h>
#include <SDL_main.h>
#include <SDL_opengl.h>
#include <GL/GLU.h>

#include <cereal/archives/binary.hpp>
#include <gpc/fonts/cereal.hpp>

#include <OpenGL/error.hpp>

#include "embedded.hpp"

void initGL()
{
	/* Enable smooth shading */
	GL(glShadeModel, (GL_SMOOTH));

	/* Set the background black */
	GL(glClearColor, (0.0f, 0.0f, 0.0f, 0.0f));

	/* Depth buffer setup */
	GL(glClearDepth, (1.0f));

	/* Enables Depth Testing */
	GL(glEnable, (GL_DEPTH_TEST));

	/* The Type Of Depth Test To Do */
	GL(glDepthFunc, (GL_LEQUAL));

	/* Really Nice Perspective Calculations */
	GL(glHint, (GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST));
}

/* function to reset our viewport after a window resize
 */
int setViewport(int width, int height)
{
	/* Height / width ration */
	GLfloat ratio;

	/* Protect against a divide by zero */
	if (height == 0) height = 1;

	ratio = (GLfloat)width / (GLfloat)height;

	/* Setup our viewport. */
	GL(glViewport, (0, 0, (GLsizei)width, (GLsizei)height));

	/* change to the projection matrix and set our viewing volume. */
	GL(glMatrixMode, (GL_PROJECTION));
	GL(glLoadIdentity, ());

	/* Set our perspective */
	GL(gluPerspective, (45.0f, ratio, 0.1f, 100.0f));

	/* Make sure we're chaning the model view and not the projection */
	GL(glMatrixMode, (GL_MODELVIEW));

	/* Reset The View */
	GL(glLoadIdentity, ());

	return 1;
}

void render(SDL_Window *window)
{
	/* Set the background black */
	GL(glClearColor, (0.0f, 0.0f, 0.0f, 0.0f));
	/* Clear The Screen And The Depth Buffer */
	GL(glClear, (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));

	/* Move Left 1.5 Units And Into The Screen 6.0 */
	GL(glLoadIdentity, ());
	GL(glTranslatef, (-1.5f, 0.0f, -6.0f));

	GL(glBegin, (GL_TRIANGLES));			/* Drawing Using Triangles */
	GL(glVertex3f, (0.0f, 1.0f, 0.0f));		/* Top */
	GL(glVertex3f, (-1.0f, -1.0f, 0.0f));	/* Bottom Left */
	GL(glVertex3f, (1.0f, -1.0f, 0.0f));	/* Bottom Right */
	GLI(glEnd, ());							/* Finished Drawing The Triangle */

	/* Move Right 3 Units */
	GL(glTranslatef, (3.0f, 0.0f, 0.0f));

	GL(glBegin, (GL_QUADS));				/* Draw A Quad */
	GL(glVertex3f, (-1.0f,  1.0f, 0.0f));	/* Top Left */
	GL(glVertex3f, ( 1.0f,  1.0f, 0.0f));	/* Top Right */
	GL(glVertex3f, ( 1.0f, -1.0f, 0.0f));	/* Bottom Right */
	GL(glVertex3f, (-1.0f, -1.0f, 0.0f));	/* Bottom Left */
	GLI( glEnd, ());							/* Done Drawing The Quad */

	SDL_GL_SwapWindow(window);
}


int
main(int argc, char *argv[])
{
	gpc::fonts::RasterizedFont rfont;
	{
		auto &file = embeds["arial-14.15.bin"];
		std::stringstream is(std::string(file.data<char>(), file.size()));
		cereal::BinaryInputArchive archive(is);
		archive(rfont);
	}

	SDL_Init(SDL_INIT_VIDEO);

	SDL_Window *window = SDL_CreateWindow("GPC Font Rasterizer Test App",
		SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
		800, 600, SDL_WINDOW_OPENGL);
	if (!window) throw std::runtime_error("Failed to open window");

	SDL_GLContext glctx = SDL_GL_CreateContext(window);
	if (!glctx) throw std::runtime_error("Failed to create an OpenGL context for the window");

	SDL_GL_MakeCurrent(window, glctx);

	initGL();

	setViewport(800, 600);

	render(window);

	SDL_Event event;

	while (SDL_WaitEvent(&event)) {
		
		bool exit = false, must_render = false;

		switch (event.type){

		case SDL_KEYDOWN:
			if (event.key.keysym.sym == 27)
				exit = true;
			break;

		case SDL_KEYUP:
			break;

		case SDL_QUIT:
			exit = true;
			break;

		default:
			break;
		}

		if (exit) break;

		if (must_render) {
			render(window);
			must_render = false;
		}
	}

	SDL_Quit();

	return 0;
}