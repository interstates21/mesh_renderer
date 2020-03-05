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

void	translate(t_mat4 *m, t_v3f v)
{
	m->m[3] += v.x;
	m->m[7] += v.y;
	m->m[11] += v.z;
}

void	rotate(t_mat4 *m, t_v3f v)
{
	if (v.x != 0.0)
		m_rotate_x(m, v.x);
	if (v.y != 0.0)
		m_rotate_y(m, v.y);
	if (v.z != 0.0)
		m_rotate_z(m, v.z);
}

void	model_move_inertia(t_env *env, float inertia)
{
	env->model.inertia = v3_scale(env->model.inertia, inertia);
	if (env->key[TF].code)
		env->model.inertia = v3_min(env->model.inertia,
		v3_scale(v(env->cam.front.x, 0, env->cam.front.z), 0.01));
	if (env->key[TB].code)
		env->model.inertia = v3_plus(env->model.inertia,
		v3_scale(v(env->cam.front.x, 0, env->cam.front.z), 0.01));
	if (env->key[TL].code)
		env->model.inertia = v3_min(env->model.inertia,
		v3_scale(env->cam.right, 0.01));
	if (env->key[TR].code)
		env->model.inertia = v3_plus(env->model.inertia,
		v3_scale(env->cam.right, 0.01));
	if (env->key[TU].code)
		env->model.inertia = v3_plus(env->model.inertia,
		v3_scale(env->cam.up, 0.01));
	if (env->key[TD].code)
		env->model.inertia = v3_min(env->model.inertia,
		v3_scale(env->cam.up, 0.01));
	translate(&env->model.translation, env->model.inertia);
}

void	model_move_demo(t_env *env)
{
	if (env->key[RM].code)
		env->model.velocity -= 0.05;
	if (env->key[RP].code)
		env->model.velocity += 0.05;
	rotate(&env->model.rotation, v(0, env->model.velocity, 0));
}
