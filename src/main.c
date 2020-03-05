#include "scop.h"

void	glfw_loop(void)
{
	glfwPollEvents();
	glClearColor(0.09f, 0.08f, 0.15f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}


int	run(char *filename)
{
	t_env	env;
	env = init_manager(filename);
	load_obj(&env, filename);
	load_bmp(&env, "./resources/poney.bmp");
	build_shader_program(&env);
	create_buffers(&env, GL_DYNAMIC_DRAW);
	glBindVertexArray(0);
	glEnable(GL_DEPTH_TEST);
	while (!glfwWindowShouldClose(env.window))
	{
		glfw_loop();
		key_handle(&env);
		env.sim.model = m_mult(env.model.translation, env.model.rotation);
		glUseProgram(env.shader.program);
		compute_mvp_matrix(&env);
		update_shader_uniforms(&env);
		glBindTexture(GL_TEXTURE_2D, env.buffer.texture);
		glBindVertexArray(env.buffer.vao);
		glDrawElements(GL_TRIANGLES, env.model.num_indices, GL_UNSIGNED_INT, 0);
		glBindVertexArray(0);
		glfwSwapBuffers(env.window);
	}
	clean_glfw(&env);
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
