/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wwatkins <wwatkins@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/06 12:13:45 by wwatkins          #+#    #+#             */
/*   Updated: 2016/12/10 18:44:10 by wwatkins         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"

void	camera_zoom(t_world *world)
{
	if (world->key[ZP].code)
		set_projection_matrix(world, FOV);
	if (world->key[ZM].code)
		set_projection_matrix(world, FOV);
}

void	camera_move_inertia(t_world *e, float inertia, int mode)
{
	t_v3f	temp;

	e->cam.inertia = v3_scale(e->cam.inertia, inertia);
	temp = v(e->cam.pos.x, e->cam.pos.y, e->cam.pos.z);
	if (e->key[CF].code)
		e->cam.inertia = v3_min(e->cam.inertia,
		v3_scale(e->cam.front, e->cam.velocity));
	if (e->key[CB].code)
		e->cam.inertia = v3_plus(e->cam.inertia,
		v3_scale(e->cam.front, e->cam.velocity));
	if (e->key[CL].code)
		e->cam.inertia = v3_min(e->cam.inertia,
		v3_scale(e->cam.right, e->cam.velocity));
	if (e->key[CR].code)
		e->cam.inertia = v3_plus(e->cam.inertia,
		v3_scale(e->cam.right, e->cam.velocity));
	if (e->key[CU].code)
		e->cam.inertia = v3_plus(e->cam.inertia,
		v3_scale(e->cam.up, e->cam.velocity));
	if (e->key[CD].code)
		e->cam.inertia = v3_min(e->cam.inertia,
		v3_scale(e->cam.up, e->cam.velocity));
	e->cam.pos = v3_plus(e->cam.pos, e->cam.inertia);
	if (mode == FREE)
		e->cam.target = v3_plus(e->cam.target, v3_min(e->cam.pos, temp));
}

void	camera_center(t_world *world)
{
	t_v3f	model_pos;

	model_pos.x = world->translation.data[3];
	model_pos.y = world->translation.data[7];
	model_pos.z = world->translation.data[11];
	world->cam.target = v3_plus(world->axis, model_pos);
}

void	camera_look_at_target(t_world *world)
{
	t_v3f	tmp;
	t_m	view;

	tmp = world->cam.up;
	world->cam.front = v3_norm(v3_min(world->cam.pos, world->cam.target));
	world->cam.right = v3_norm(v3_cross(world->cam.up, world->cam.front));
	tmp = v3_cross(world->cam.front, world->cam.right);
	view = m_iden();
	view.data[0] = world->cam.right.x;
	view.data[1] = tmp.x;
	view.data[2] = world->cam.front.x;
	view.data[4] = world->cam.right.y;
	view.data[5] = tmp.y;
	view.data[6] = world->cam.front.y;
	view.data[8] = world->cam.right.z;
	view.data[9] = tmp.z;
	view.data[10] = world->cam.front.z;
	view.data[12] = -v3_dot(world->cam.right, world->cam.pos);
	view.data[13] = -v3_dot(tmp, world->cam.pos);
	view.data[14] = -v3_dot(world->cam.front, world->cam.pos);
	world->view = view;
}
