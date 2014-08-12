#pragma once

#include <vector>
#include <cassert>
#include <GL/glew.h>
#include <gpc/fonts/RasterizedFont.hpp>
#include <OpenGL/error.hpp>

class TextRenderer {
public:

	void setViewportSize(GLint width, GLint height) { vp_width = width, vp_height = height; }

	void setFont(const gpc::fonts::RasterizedFont &rfont_) { rfont = &rfont_; }

	void init();

	void drawText(const uint32_t *text, GLint x, GLint y, size_t variant = 0);

	void cleanup();

private:

	void uploadFont();
	void prepareShaderProgram();
	void prepareGlyphVertices();

	GLint vp_width, vp_height;
	const gpc::fonts::RasterizedFont *rfont;
	std::vector<GLuint> texture_buffers;
	std::vector<GLuint> buffer_textures;
	GLuint vertex_buffer;
	GLuint shader_program;
	GLuint vertex_shader, fragment_shader;

};