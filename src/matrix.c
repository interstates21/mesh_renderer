#include "scop.h"

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

void	m_rotate_x(t_mat4 *m, float angle)
{
	t_mat4	r;
	float	theta;

	r = m_iden();
	theta = angle * (M_PI / 180);
	r.m[5] = cos(theta);
	r.m[6] = sin(theta);
	r.m[9] = -sin(theta);
	r.m[10] = cos(theta);
	*m = mat4_mul(*m, r);
}

void	m_rotate_y(t_mat4 *m, float angle)
{
	t_mat4	r;
	float	theta;

	r = m_iden();
	theta = angle * (M_PI / 180);
	r.m[0] = cos(theta);
	r.m[2] = -sin(theta);
	r.m[8] = sin(theta);
	r.m[10] = cos(theta);
	*m = mat4_mul(*m, r);
}

void	m_rotate_z(t_mat4 *m, float angle)
{
	t_mat4	r;
	float	theta;

	r = m_iden();
	theta = angle * (M_PI / 180);
	r.m[0] = cos(theta);
	r.m[1] = sin(theta);
	r.m[4] = -sin(theta);
	r.m[5] = cos(theta);
	*m = mat4_mul(*m, r);
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
