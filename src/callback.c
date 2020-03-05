// /* ************************************************************************** */
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

void	set_key(t_key *key, t_modes *target, int src)
{
	key->cooldown > 1 ? key->cooldown -= 1 : 0;
	if (key->code && key->cooldown <= 1)
	{
		*target = src;
		key->cooldown = COOLDOWN;
	}
}

int		get_next_mode(t_world *world)
{
	int		modulo;

	modulo = world->modes_len;
	return ((world->mode + 1) % modulo);
}

void	key_handle(t_world *world)
{
	register int	i;

	if (glfwGetKey(world->window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(world->window, GL_TRUE);
	i = -1;
	while (++i < MAX_KEYS)
		world->key[i].code = glfwGetKey(world->window, i) == GLFW_PRESS ? 1 : 0;
	set_key(&world->key[NEXT_MODE_KEY], &world->mode, get_next_mode(world));
	// key_toggle(&world->key[NEXT_MODE_KEY], &world->wireframe, GL_FILL, GL_LINE);
	// key_toggle(&world->key[MS], &world->shading, 0, 1);
	// key_toggle(&world->key[MC], &world->color, 0, 1);
	// key_toggle(&world->key[MG], &world->greyscale, 0, 1);
	// key_toggle(&world->key[MM], &world->mapping, 0, 1);
	// key_toggle(&world->key[MT], &world->textured, 0, 1);
	key_action(world);
}

void	key_action(t_world *world)
{
	if (world->key[MW].code)
		glPolygonMode(GL_FRONT_AND_BACK, world->wireframe);
	if (world->key[ZP].code || world->key[ZM].code)
		camera_zoom(world);
	camera_center(world);
	model_move_demo(world);
	model_move_inertia(world, 0.9);
	camera_move_inertia(world, 0.93, FREE);
	camera_look_at_target(world);
}

