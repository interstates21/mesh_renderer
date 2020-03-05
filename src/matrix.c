#include "scop.h"

t_mat4	mat4_add(t_mat4 a, t_mat4 b)
{
	int		i;

	i = -1;
	while (++i < 16)
		a.m[i] += b.m[i];
	return (a);
}


t_mat4	mat4_copy(t_mat4 *a, t_mat4 b)
{
	int i;

	i = -1;
	while (++i < 16)
		a->m[i] = b.m[i];
	return (*a);
}

t_mat4	m_iden()
{
	int		i;
	t_mat4	temp;

	i = 0;
	while (i < 16) {
		temp.m[i] = (i % 5 == 0 ? 1 : 0);
		i++;
	}
	return (temp);
}

t_mat4	m_zero()
{
	int		i;
	t_mat4	temp;

	i = 0;
	while (i < 16) {
		temp.m[i] = 0;
		i++;
	}
	return (temp);
}



t_mat4	mat4_mul(t_mat4 a, t_mat4 b)
{
	int		h;
	int		w;
	int		z;
	t_mat4	m;

	h = -1;
	while (++h < 4)
	{
		w = -1;
		while (++w < 4)
		{
			z = -1;
			m.m[h * 4 + w] = 0;
			while (++z < 4)
				m.m[h * 4 + w] += a.m[h * 4 + z] * b.m[z * 4 + w];
		}
	}
	return (m);
}

void	get_axis_x_rotation_matrix(t_mat4 *m, float theta)
{
	m->m[5] = cos(theta);
	m->m[6] = sin(theta);
	m->m[9] = -sin(theta);
	m->m[10] = cos(theta);
}

void	get_axis_y_rotation_matrix(t_mat4 *m, float theta)
{
	m->m[0] = cos(theta);
	m->m[2] = -sin(theta);
	m->m[8] = sin(theta);
	m->m[10] = cos(theta);
}

void	get_axis_z_rotation_matrix(t_mat4 *m, float theta)
{
	m->m[0] = cos(theta);
	m->m[1] = sin(theta);
	m->m[4] = -sin(theta);
	m->m[5] = cos(theta);
}

t_mat4	mat4_rotate_axis(t_mat4 m, int axis, float angle)
{
	t_mat4	r;
	float	theta;

	r = m_iden();
	theta = angle * (M_PI / 180);
	if (axis == AXIS_X)
	{
		get_axis_x_rotation_matrix(&r, theta);
		m = mat4_mul(m, r);
	}
	else if (axis == AXIS_Y)
	{
		get_axis_y_rotation_matrix(&r, theta);
		m = mat4_mul(m, r);
	}
	else if (axis == AXIS_Z)
	{
		get_axis_z_rotation_matrix(&r, theta);
		m = mat4_mul(m, r);
	}
	return (m);
}

t_mat4	mat4_scale(t_mat4 m, float f)
{
	int	i;

	i = -1;
	while (++i < 16)
		m.m[i] *= f;
	return (m);
}

t_mat4	mat4_sub(t_mat4 a, t_mat4 b)
{
	int		i;

	i = -1;
	while (++i < 16)
		a.m[i] -= b.m[i];
	return (a);
}

t_mat4	mat4_transpose(t_mat4 m)
{
	int		h;
	int		w;
	t_mat4	t;

	h = -1;
	while (++h < 4)
	{
		w = -1;
		while (++w < 4)
			t.m[w * 4 + h] = m.m[h * 4 + w];
	}
	m = mat4_copy(&m, t);
	return (m);
}
