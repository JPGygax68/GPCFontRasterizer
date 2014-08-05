#pragma once

#include <vector>
#include <cassert>
#include <GL/glew.h>
#include <gpc/fonts/RasterizedFont.hpp>
#include <OpenGL/error.hpp>

class TextRenderer {
public:

	void setFont(const gpc::fonts::RasterizedFont &rfont_) { rfont = &rfont_; }

	void init() {

		uploadFont();

		prepareShaderProgram();
	}

	void drawText(const uint32_t *text, size_t variant = 0) {

	}

	void cleanup() {
		// TODO: delete the buffers
	}

private:

	void uploadFont() {

		assert(rfont);

		buffers.resize(rfont->variants.size());
		GL(glGenBuffers, (buffers.size(), &buffers[0]));

		for (auto i_var = 0U; i_var < rfont->variants.size(); i_var++) {

			GL(glBindBuffer, (GL_TEXTURE_BUFFER, buffers[i_var]));

			auto &variant = rfont->variants[i_var];

			// Load the pixels into a buffer object
			GL(glBufferStorage, (GL_TEXTURE_BUFFER, variant.pixels.size(), &variant.pixels[0], 0)); // TODO: really no flags ?
		}
	}

	void prepareShaderProgram();

	const gpc::fonts::RasterizedFont *rfont;
	std::vector<GLuint> buffers;
	GLuint shader_program;
	GLuint vertex_shader, fragment_shader;

};