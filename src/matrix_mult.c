#include "scop.h"

t_m		m_mult(t_m a, t_m b)
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

void	m_fast_mult(t_m *a, t_m b)
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
