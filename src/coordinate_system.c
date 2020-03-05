#include "scop.h"

void	set_projection_matrix(t_world *world, float fov)
{
	float	s;
	float	far;
	float	near;

	far = CAMERA_FAR;
	near = CAMERA_NEAR;
	s = 1 / (tan(fov * 0.5 * M_PI / 180.0));
	world->projection = m_zero();
	world->projection.data[0] = s / ASPECT_RATIO;
	world->projection.data[5] = s;
	world->projection.data[10] = -(far + near) / (far - near);
	world->projection.data[11] = -1;
	world->projection.data[14] = -2 * far * near / (far - near);
}

void	compute_mvp_matrix(t_world *world)
{
	world->mvp = m_mult(m4_trans(world->model),
		m_mult(world->view, world->projection));
}
