#include "scop.h"

void	read_header(char *filename, t_texture *texture)
{
	int			fd;
	size_t		bpp;

	if ((fd = open(filename, O_RDONLY)) == -1)
		print_err("Read Header Failed");
	lseek(fd, 18, SEEK_SET);
	read(fd, &texture->w, 4);
	read(fd,&texture->h, 4);
	lseek(fd, 2, SEEK_CUR);
	read(fd, &bpp, 2);
	close(fd);
	texture->sl = texture->w * (bpp / 8);
	texture->w < 0 ? texture->w = -texture->w : 0;
	texture->h < 0 ? texture->h = -texture->h : 0;
	texture->size = texture->sl * texture->h;
}

void	get_image(t_texture *texture, char *buffer, int i)
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
	char				*buffer;

	i = 0;
	read_header(filename, &env->model.texture);
	buffer = (char*)malloc(sizeof(char) * env->model.texture.size + 1);
	if ((fd = open(filename, O_RDWR)) == -1)
		print_err("bmp file opening failed.");
	lseek(fd, 54, SEEK_SET);
	i = read(fd, buffer, env->model.texture.size);
	get_image(&env->model.texture, buffer, i);
	ft_strdel((char**)&buffer);
	close(fd);
}
