/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   callback.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wwatkins <wwatkins@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/30 13:51:00 by wwatkins          #+#    #+#             */
/*   Updated: 2016/12/10 12:13:35 by wwatkins         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"

void	key_handle(t_env *env)
{
	register int	i;

	if (glfwGetKey(env->window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(env->window, GL_TRUE);
	i = -1;
	while (++i < MAX_KEYS)
		env->key[i].code = glfwGetKey(env->window, i) == GLFW_PRESS ? 1 : 0;
	key_toggle(&env->key[MW], &env->wireframe, GL_FILL, GL_LINE);
	key_toggle(&env->key[MF], &env->focus, 0, 1);
	key_toggle(&env->key[MS], &env->shading, 0, 1);
	key_toggle(&env->key[MC], &env->color, 0, 1);
	key_toggle(&env->key[MG], &env->greyscale, 0, 1);
	key_toggle(&env->key[MM], &env->mapping, 0, 1);
	key_toggle(&env->key[MT], &env->textured, 0, 1);
	key_action(env);
}

void	key_action(t_env *env)
{
	if (env->key[MW].code)
		glPolygonMode(GL_FRONT_AND_BACK, env->wireframe);
	if (env->key[ZP].code || env->key[ZM].code)
		camera_zoom(env);
	if (env->focus)
		camera_center(env);
	model_move_demo(env);
	model_move_inertia(env, 0.9);
	camera_move_inertia(env, 0.93, FREE);
	camera_look_at_target(env);
}

void	key_toggle(t_key *key, int *var, int v0, int v1)
{
	key->cooldown > 1 ? key->cooldown -= 1 : 0;
	if (key->code && key->cooldown <= 1)
	{
		if (*var == v1)
			*var = v0;
		else if (*var == v0)
			*var = v1;
		key->cooldown = COOLDOWN;
	}
}
