#include "scop.h"

static void	init_cam(t_world *world)
{
	t_v3f	up;

	up = v(0, 1, 0);
	world->cam.velocity = 0.007;
	world->cam.target = v(0, 0, 0);
	world->cam.pos = v(0, 0, 3);
	world->cam.dir = v3_norm(v3_min(world->cam.pos, world->cam.target));
	world->cam.right = v3_norm(v3_cross(up, world->cam.dir));
	world->cam.up = v3_cross(world->cam.dir, world->cam.right);
	world->cam.front = v3_cross(world->cam.up, world->cam.right);
	world->cam.inertia = v(0, 0, 0);
	world->model = m_iden();
	world->view = m_iden();
	set_projection_matrix(world, FOV);
	world->translation = m_iden();
	world->inertia = v(0, 0, 0);
	world->rotation = m_iden();
	world->axis = v(0, 0, 0);
}

static void	init_modes(t_world *world)
{
	world->wireframe = GL_FILL;
	world->mode = BASIC;
	world->modes_len = 3;
	// world->shading = 0;
	// world->greyscale = 0;
	// world->mapping = 0;
	// world->textured = 0;
	// world->color = 0;
	world->velocity = 0.8;
}

static void	init_keys(t_world *world)
{
	register size_t	i;

	i = 0;
	while (i < MAX_KEYS) {
		world->key[i].cooldown = 0;
		i++;
	}
}

t_world	init_manager(char *filename)
{
	t_world			world;

	world.filename = filename;
	init_keys(&world);
	init_gl(&world);
	init_cam(&world);
	init_modes(&world);
	return (world);
}
