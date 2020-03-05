#include "scop.h"

void	glfw_loop(void)
{
	glfwPollEvents();
	glClearColor(0.09f, 0.08f, 0.15f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}


int	run(char *filename)
{
	t_world	world;
	world = init_manager(filename);
	load_obj(&world);
	get_textures(&world);
	build_shader_program(&world);
	create_buffers(&world, GL_DYNAMIC_DRAW);
	glBindVertexArray(0);
	glEnable(GL_DEPTH_TEST);
	while (!glfwWindowShouldClose(world.window))
	{
		glfw_loop();
		key_handle(&world);
		world.model = m_mult(world.translation, world.rotation);
		glUseProgram(world.shader.program);
		compute_mvp_matrix(&world);
		update_shader_uniforms(&world);
		glBindTexture(GL_TEXTURE_2D, world.buffer.texture);
		glBindVertexArray(world.buffer.vao);
		glDrawElements(GL_TRIANGLES, world.num_indices, GL_UNSIGNED_INT, 0);
		glBindVertexArray(0);
		glfwSwapBuffers(world.window);
	}
	clean_glfw(&world);
	system("leaks --quiet scop");
	return (0);
}


int main(int argc, char **argv)
{
	if (argc != 2)
		return (1);
	if (!ft_strstr(argv[1], ".obj"))
		return (1);
	return (run(argv[1]));
}
