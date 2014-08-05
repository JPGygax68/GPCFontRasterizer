static const unsigned char vertex_source[] = {
#include <TextRenderer_fragment_shader.h>
};

#include "TextRenderer.hpp"

void TextRenderer::prepareShaderProgram()
{
	shader_program = GLR(glCreateProgram, ());

	vertex_shader = GLR(glCreateShader, (GL_VERTEX_SHADER));
	fragment_shader = GLR(glCreateShader, (GL_FRAGMENT_SHADER));

	const char *sources[] = { reinterpret_cast<const char *>(vertex_source) };
	const GLint lengths[] = { sizeof(vertex_source) };
	GL(glShaderSource, (vertex_shader, 1, sources, lengths));
}
