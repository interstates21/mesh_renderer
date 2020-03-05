#include "scop.h"

void	glfw_loop(void)
{
	glfwPollEvents();
	glClearColor(0.09f, 0.08f, 0.15f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}


void	init_matrices(t_env *env)
{
	env->sim.model = m_iden();
	env->sim.view = m_iden();
	set_projection_matrix(env, FOV);
	env->model.rotation = m_iden();
	env->model.translation = m_iden();
	env->model.inertia = v(0, 0, 0);
	env->model.center_axis = v(0, 0, 0);
}

void	init_cam(t_env *env)
{
	t_v3f	up;

	up = v(0, 1, 0);
	env->cam.pos = v(0, 0, 3);
	env->cam.target = v(0, 0, 0);
	env->cam.dir = v3_norm(v3_min(env->cam.pos, env->cam.target));
	env->cam.right = v3_norm(v3_cross(up, env->cam.dir));
	env->cam.up = v3_cross(env->cam.dir, env->cam.right);
	env->cam.front = v3_cross(env->cam.up, env->cam.right);
	env->cam.inertia = v(0, 0, 0);
	env->cam.velocity = 0.005;
}

void	init(t_env *env)
{

	init_gl(env);
	init_cam(env);
	init_matrices(env);
	env->mod.wireframe = GL_FILL;
	env->mod.shading = 0;
	env->mod.focus = 1;
	env->mod.color = 0;
	env->mod.greyscale = 0;
	env->mod.mapping = 0;
	env->mod.texture = 0;
	env->model.velocity = 0.33;
}


void	run(char *filename)
{
	t_env	env;

	register size_t	i;

	i = -1;
	while (++i < MAX_KEYS)
		env.key[i].cooldown = 0;
	env.model.filename = filename;
	init(&env);
	load_obj(&env, env.model.filename);
	load_bmp(&env, "./resources/pony.bmp");
	build_shader_program(&env);
	create_buffers(&env, GL_DYNAMIC_DRAW);
	glBindVertexArray(0);
	glEnable(GL_DEPTH_TEST);
	while (!glfwWindowShouldClose(env.window))
	{
		glfw_loop();
		key_handle(&env);
		env.sim.model = mat4_mul(env.model.translation, env.model.rotation);
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
}


int main(int argc, char **argv)
{
	if (argc != 2)
		return (1);
	if (!ft_strstr(argv[1], ".obj"))
		return (1);
	run(argv[1]);
	return (0);
}
