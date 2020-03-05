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

void	model_move_inertia(t_env *env, float inertia)
{
	env->inertia = v3_scale(env->inertia, inertia);
	if (env->key[TF].code)
		env->inertia = v3_min(env->inertia,
		v3_scale(v(env->cam.front.x, 0, env->cam.front.z), 0.01));
	if (env->key[TB].code)
		env->inertia = v3_plus(env->inertia,
		v3_scale(v(env->cam.front.x, 0, env->cam.front.z), 0.01));
	if (env->key[TL].code)
		env->inertia = v3_min(env->inertia,
		v3_scale(env->cam.right, 0.01));
	if (env->key[TR].code)
		env->inertia = v3_plus(env->inertia,
		v3_scale(env->cam.right, 0.01));
	if (env->key[TU].code)
		env->inertia = v3_plus(env->inertia,
		v3_scale(env->cam.up, 0.01));
	if (env->key[TD].code)
		env->inertia = v3_min(env->inertia,
		v3_scale(env->cam.up, 0.01));
	translate(&env->translation, env->inertia);
}

void	model_move_demo(t_env *env)
{
	if (env->key[RM].code)
		env->velocity -= 0.05;
	if (env->key[RP].code)
		env->velocity += 0.05;
	rotate(&env->rotation, v(0, env->velocity, 0));
}
