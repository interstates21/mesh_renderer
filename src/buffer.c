/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buffer.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wwatkins <wwatkins@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/01 11:32:58 by wwatkins          #+#    #+#             */
/*   Updated: 2016/12/10 13:21:12 by wwatkins         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"

void	create_texture(t_world *world)
{
	glGenTextures(1, &world->buffer.texture);
	glBindTexture(GL_TEXTURE_2D, world->buffer.texture);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, world->texture.w,
	world->texture.h, 0, GL_RGB, GL_UNSIGNED_BYTE, world->texture.img);
	glGenerateMipmap(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, 0);
}

void	create_buffers(t_world *world, int mode)
{
	glGenBuffers(1, &world->buffer.vbo);
	glGenBuffers(1, &world->buffer.ebo);
	glGenVertexArrays(1, &world->buffer.vao);
	glBindVertexArray(world->buffer.vao);
	glBindBuffer(GL_ARRAY_BUFFER, world->buffer.vbo);
	glBufferData(GL_ARRAY_BUFFER, world->size_vertices,
		world->vertices, mode);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, world->buffer.ebo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, world->size_indices,
		world->indices, mode);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat),
		(GLvoid*)0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat),
		(GLvoid*)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(1);
	create_texture(world);
}
