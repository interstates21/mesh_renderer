/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wwatkins <wwatkins@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/29 17:20:21 by wwatkins          #+#    #+#             */
/*   Updated: 2016/12/12 11:38:18 by wwatkins         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"

void	glfw_loop(void)
{
	glfwPollEvents();
	glClearColor(0.09f, 0.08f, 0.15f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}


void	init_matrices(t_env *env)
{
	mat4_set(&env->sim.model, IDENTITY);
	mat4_set(&env->sim.view, IDENTITY);
	set_projection_matrix(env, env->cam.fov);
	mat4_set(&env->model.rotation, IDENTITY);
	mat4_set(&env->model.translation, IDENTITY);
	vec3_set(&env->model.inertia, 0);
	vec3_set(&env->model.center_axis, 0);
}

void	init_cam(t_env *env)
{
	t_vec3	up;

	up = vec3(0, 1, 0);
	env->cam.pos = vec3(0, 0, 3);
	env->cam.target = vec3(0, 0, 0);
	env->cam.dir = vec3_normalize(vec3_sub(env->cam.pos, env->cam.target));
	env->cam.right = vec3_normalize(vec3_cross(up, env->cam.dir));
	env->cam.up = vec3_cross(env->cam.dir, env->cam.right);
	env->cam.front = vec3_cross(env->cam.up, env->cam.right);
	vec3_set(&env->cam.inertia, 0);
	env->cam.velocity = 0.005;
}

void	init(t_env *env)
{

	env->cam.fov = CAMERA_FOV;
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

	int	i;

	i = -1;
	while (++i < MAX_KEYS)
		env.key[i].cooldown = 0;
	env.model.filename = filename;
	init(&env);
	load_obj(&env, env.model.filename);
	load_bmp(&env, "./resources/chaton.bmp");
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
