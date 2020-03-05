/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wwatkins <wwatkins@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/03 12:23:16 by wwatkins          #+#    #+#             */
/*   Updated: 2016/12/10 18:45:31 by wwatkins         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"

void	translate(t_m *m, t_v3f v)
{
	m->data[3] += v.x;
	m->data[7] += v.y;
	m->data[11] += v.z;
}

void	rotate(t_m *m, t_v3f v)
{
	if (v.x != 0.0)
		m_rotate_x(m, v.x);
	if (v.y != 0.0)
		m_rotate_y(m, v.y);
	if (v.z != 0.0)
		m_rotate_z(m, v.z);
}

void	model_move_inertia(t_world *world, float inertia)
{
	world->inertia = v3_scale(world->inertia, inertia);
	if (world->key[TF].code)
		world->inertia = v3_min(world->inertia,
		v3_scale(v(world->cam.front.x, 0, world->cam.front.z), 0.01));
	if (world->key[TB].code)
		world->inertia = v3_plus(world->inertia,
		v3_scale(v(world->cam.front.x, 0, world->cam.front.z), 0.01));
	if (world->key[TL].code)
		world->inertia = v3_min(world->inertia,
		v3_scale(world->cam.right, 0.01));
	if (world->key[TR].code)
		world->inertia = v3_plus(world->inertia,
		v3_scale(world->cam.right, 0.01));
	if (world->key[TU].code)
		world->inertia = v3_plus(world->inertia,
		v3_scale(world->cam.up, 0.01));
	if (world->key[TD].code)
		world->inertia = v3_min(world->inertia,
		v3_scale(world->cam.up, 0.01));
	translate(&world->translation, world->inertia);
}

void	model_move_demo(t_world *world)
{
	if (world->key[RM].code)
		world->velocity -= 0.05;
	if (world->key[RP].code)
		world->velocity += 0.05;
	rotate(&world->rotation, v(0, world->velocity, 0));
}
