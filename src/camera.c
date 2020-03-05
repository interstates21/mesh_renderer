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

void	camera_zoom(t_env *env)
{
	if (env->key[ZP].code)
		set_projection_matrix(env, FOV);
	if (env->key[ZM].code)
		set_projection_matrix(env, FOV);
}

void	camera_move_inertia(t_env *e, float inertia, int mode)
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

void	camera_center(t_env *env)
{
	t_v3f	model_pos;

	model_pos.x = env->translation.data[3];
	model_pos.y = env->translation.data[7];
	model_pos.z = env->translation.data[11];
	env->cam.target = v3_plus(env->axis, model_pos);
}

void	camera_look_at_target(t_env *env)
{
	t_v3f	tmp;
	t_m	view;

	tmp = env->cam.up;
	env->cam.front = v3_norm(v3_min(env->cam.pos, env->cam.target));
	env->cam.right = v3_norm(v3_cross(env->cam.up, env->cam.front));
	tmp = v3_cross(env->cam.front, env->cam.right);
	view = m_iden();
	view.data[0] = env->cam.right.x;
	view.data[1] = tmp.x;
	view.data[2] = env->cam.front.x;
	view.data[4] = env->cam.right.y;
	view.data[5] = tmp.y;
	view.data[6] = env->cam.front.y;
	view.data[8] = env->cam.right.z;
	view.data[9] = tmp.z;
	view.data[10] = env->cam.front.z;
	view.data[12] = -v3_dot(env->cam.right, env->cam.pos);
	view.data[13] = -v3_dot(tmp, env->cam.pos);
	view.data[14] = -v3_dot(env->cam.front, env->cam.pos);
	env->sim.view = view;
}
