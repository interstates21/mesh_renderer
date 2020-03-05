#include "scop.h"

static void	get_bpp(int fd, t_texture *texture)
{
	size_t		bpp;

	lseek(fd, 2, SEEK_CUR);
	read(fd, &bpp, 2);
	texture->resolution = texture->w * (bpp / 8);
	texture->size = texture->resolution * texture->h;
}

static void	get_size(int fd, t_texture *texture)
{
	lseek(fd, 18, SEEK_SET);
	read(fd, &texture->w, 4);
	read(fd,&texture->h, 4);
	texture->w < 0 ? texture->w = -texture->w : 0;
	texture->h < 0 ? texture->h = -texture->h : 0;
}

static void	update_texture_image(t_texture *texture, char *buffer, int i, int b)
{
	texture->img[i] = (unsigned char)buffer[b + 2];
	texture->img[i + 1] = (unsigned char)buffer[b + 1];
	texture->img[i + 2] = (unsigned char)buffer[b];
}

static void	parse_picture(t_texture *texture, char *buffer, int i)
{
	int	y;
	int	x;

	y = 0;
	texture->img = (unsigned char*)malloc(sizeof(unsigned char) * texture->size * 2);
	while (i >= 0)
	{
		x = 0;
		i = i - texture->resolution;
		while (x < texture->resolution)
		{
			update_texture_image(texture, buffer, y + x, i + x);
			x += 3;
		}
		y = texture->resolution + y;
	}
}

void	get_textures(t_world *world)
{
	int					fd;
	register size_t		i;
	char				*b;

	i = 0;
	if ((fd = open("./resources/poney.bmp", O_RDWR)) < 0)
		print_err("cannot read texture");
	get_size(fd, &world->texture);
	get_bpp(fd, &world->texture);
	b = malloc(sizeof(char) * world->texture.size + 1);
	if (!b)
		print_err("cannot allocate");
	lseek(fd, 54, SEEK_SET);
	i = read(fd, b, world->texture.size);
	parse_picture(&world->texture, b, i);
	free(b);
	close(fd);
}
