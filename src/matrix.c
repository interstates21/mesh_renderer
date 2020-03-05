#include "scop.h"

void	m_cp(t_m *a, t_m b)
{
	register size_t			i;
	register size_t			size;

	i = 0;
	size = MATRIX_FULL_SIZE;
	while (i < size)
	{
		a->data[i] = b.data[i];
		i++;
	}
}

t_m	m_iden()
{
	register size_t		i;
	t_m					temp;

	i = 0;
	while (i < MATRIX_FULL_SIZE) {
		temp.data[i] = (i % 5 == 0 ? 1 : 0);
		i++;
	}
	return (temp);
}

t_m	m_zero()
{
	register size_t		i;
	t_m					temp;

	i = 0;
	while (i < MATRIX_FULL_SIZE) {
		temp.data[i] = 0;
		i++;
	}
	return (temp);
}



t_m		mat4_mul(t_m a, t_m b)
{
	register size_t		x;
	register size_t		y;
	register size_t		z;
	t_m					mat;

	y = 0;
	while (y < MATRIX_SIZE)
	{
		x = 0;
		while (x < MATRIX_SIZE)
		{
			z = -1;
			mat.data[y * MATRIX_SIZE + x] = 0;
			while (++z < MATRIX_SIZE)
				mat.data[y * MATRIX_SIZE + x]
				+= a.data[y * MATRIX_SIZE + z] * b.data[z * MATRIX_SIZE + x];
			x++;
		}
		y++;
	}
	return (mat);
}

void	m4_fast_mult(t_m *a, t_m b)
{
	register size_t		x;
	register size_t		y;
	register size_t		z;
	t_m					mat;

	y = 0;
	while (y < MATRIX_SIZE)
	{
		x = 0;
		while (x < MATRIX_SIZE)
		{
			z = -1;
			mat.data[y * MATRIX_SIZE + x] = 0;
			while (++z < MATRIX_SIZE)
				mat.data[y * MATRIX_SIZE + x]
				+= a->data[y * MATRIX_SIZE + z] * b.data[z * MATRIX_SIZE + x];
			x++;
		}
		y++;
	}
	m_cp(a, mat);
}

void	m_rotate_x(t_m *m, float angle)
{
	t_m		r;
	float	theta;

	r = m_iden();
	theta = angle * (M_PI / 180);
	r.data[5] = cos(theta);
	r.data[6] = sin(theta);
	r.data[9] = -sin(theta);
	r.data[10] = cos(theta);
	m4_fast_mult(m, r);
}

void	m_rotate_y(t_m *m, float angle)
{
	t_m	r;
	float	theta;

	r = m_iden();
	theta = angle * (M_PI / 180);
	r.data[0] = cos(theta);
	r.data[2] = -sin(theta);
	r.data[8] = sin(theta);
	r.data[10] = cos(theta);
	m4_fast_mult(m, r);
}

void	m_rotate_z(t_m *m, float angle)
{
	t_m	r;
	float	theta;

	r = m_iden();
	theta = angle * (M_PI / 180);
	r.data[0] = cos(theta);
	r.data[1] = sin(theta);
	r.data[4] = -sin(theta);
	r.data[5] = cos(theta);
	m4_fast_mult(m, r);
}


t_m	mat4_transpose(t_m m)
{
	register size_t	y;
	register size_t	x;
	t_m	t;

	y = 0;
	x = 0;
	while (y < MATRIX_SIZE)
	{
		x = 0;
		while (x < MATRIX_SIZE) {
			t.data[x * MATRIX_SIZE + y] = m.data[y * MATRIX_SIZE + x];
			x++;
		}
		y++;
	}
	m_cp(&m, t);
	return (m);
}
