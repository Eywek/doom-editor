/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtouffet <vtouffet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/05 15:00:21 by vtouffet          #+#    #+#             */
/*   Updated: 2019/08/15 17:49:34 by vtouffet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/editor.h"

void		ft_load_texture(t_env *env, int id, char *path, int mode)
{
	t_texture	*texture;
	t_xmp		*image;

	if (access(path, F_OK) == -1)
		return (void)(env);
	texture = ft_malloc_or_throw(env, sizeof(t_texture));
	texture->id = id;
	ft_push_texture(env, texture, mode);
	image = ft_malloc_or_throw(env, sizeof(t_xmp));
	image->image = ft_malloc_or_throw(env, sizeof(t_image));
	image->image->id = mlx_xpm_file_to_image(env->mlx.mlx_id, path,
		&image->width, &image->height);
	image->image->str = mlx_get_data_addr(image->image->id,
		&image->image->bpp, &image->image->size, &image->image->endian);
	texture->image = image;
	return ;
}

void		ft_put_texture(t_env *env, int x, int y, t_texture *texture)
{
	t_point	*point;

	if (!texture)
		return ;
	point = &(env->points[y][x]);
	if (!point->image->id)
	{
		point->image->id = mlx_new_image(env->mlx.mlx_id,
			BOX_WIDTH - 1, BOX_HEIGHT - 1);
		point->image->str = mlx_get_data_addr(point->image->id,
			&point->image->bpp, &point->image->size, &point->image->endian);
	}
	point->value = texture->id;
	ft_copy_texture(texture, point->image, (BOX_WIDTH) - 1, (BOX_HEIGHT) - 1);
	mlx_put_image_to_window(env->mlx.mlx_id, env->mlx.window_id,
		point->image->id, (int)(x * (BOX_WIDTH) + 1),
		(int)(y * (BOX_HEIGHT) + 1));
}

t_texture	*ft_find_in_texture(t_env *env, int id, t_texture *find_in)
{
	t_texture	*texture;

	(void)env;
	texture = find_in;
	if (!texture)
		return (NULL);
	while (texture->id != id)
	{
		texture = texture->next;
		if (texture == find_in)
			return (NULL);
	}
	return (texture);
}

t_texture	*ft_find_texture(t_env *env, int id)
{
	t_texture	*texture;

	texture = ft_find_in_texture(env, id, env->wall_texture);
	if (!texture)
		texture = ft_find_in_texture(env, id, env->sprite_texture);
	return (texture);
}

void		ft_copy_texture(t_texture *texture, t_image *image,
	int desired_width, int desired_height)
{
	if (texture->image->width < desired_width ||
		texture->image->height < desired_height)
		return (ft_resize_down(texture, image, desired_width, desired_height));
	return (ft_resize_up(texture, image, desired_width, desired_height));
}
