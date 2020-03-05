#include "scop.h"

void	clean_glfw(t_world *world)
{
	glDeleteVertexArrays(1, &world->buffer.vao);
	glDeleteBuffers(1, &world->buffer.vbo);
	glDeleteBuffers(1, &world->buffer.ebo);
	glfwTerminate();
}

GLuint	*gluint_array_copy(GLuint *array, int length, int m)
{
	int		i;
	GLuint	*new;

	i = -1;
	new = (GLuint*)malloc(sizeof(GLuint) * length);
	while (++i < length - m)
		new[i] = array[i];
	free(array);
	array = new;
	return (new);
}
