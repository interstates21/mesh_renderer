#include "scop.h"

static void	read_size(int fd, t_texture *texture)
{
	int	pos;
	pos = 18;
	lseek(fd, pos, SEEK_SET);
	read(fd, &texture->w, 4);
	read(fd,&texture->h, 4);
	if (texture->w < 0)
		texture->w = -texture->w;
	if (texture->h < 0)
		texture->h = -texture->h;
}

static size_t	read_resolution(int fd, t_texture *texture)
{
	size_t		bpp;
	size_t		resolution;

	lseek(fd, 2, SEEK_CUR);
	read(fd, &bpp, 2);
	resolution = texture->w * (bpp / 8);
	texture->size = resolution * texture->h;
	return (resolution);
}


static void	get_image(t_texture *texture, char *buffer, int i)
{
	int	h;
	int	j;
	int	size;

	h = 0;
	size = texture->size * 2;
	texture->img = (unsigned char*)malloc(sizeof(unsigned char) * size);
	while (i >= 0)
	{
		i -= texture->sl;
		j = 0;
		while (j < texture->sl)
		{
			texture->img[h + j] = (unsigned char)buffer[i + j + 2];
			texture->img[h + j + 1] = (unsigned char)buffer[i + j + 1];
			texture->img[h + j + 2] = (unsigned char)buffer[i + j];
			j += 3;
		}
		h += texture->sl;
	}
}

void	load_bmp(t_env *env, char *filename)
{
	int					fd;
	register size_t		i;
	size_t				resolution;
	char				*buffer;

	i = 0;
	if ((fd = open(filename, O_RDWR)) < 0)
		print_err("bmp file opening failed.");
	read_size(fd, &env->model.texture);
	resolution = read_resolution(fd, &env->model.texture);
	buffer = (char*)malloc(sizeof(char) * env->model.texture.size + 1);
	lseek(fd, 54, SEEK_SET);
	i = read(fd, buffer, env->model.texture.size);
	get_image(&env->model.texture, buffer, i);
	ft_strdel((char**)&buffer);
	close(fd);
}
