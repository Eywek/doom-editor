/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtouffet <vtouffet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/05 14:58:32 by vtouffet          #+#    #+#             */
/*   Updated: 2019/08/15 17:15:55 by vtouffet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/editor.h"

void	ft_init_env(t_env *env)
{
	int		x;
	int		y;

	ft_memset(env, 0, sizeof(env));
	env->life_level = 1;
	env->sky_mode = SKY_MODE_OPEN;
	env->hud = ft_malloc_or_throw(env, sizeof(t_xmp));
	env->hud->image = ft_malloc_or_throw(env, sizeof(t_image));
	y = -1;
	while (++y < BOX_COUNT)
	{
		x = -1;
		while (++x < BOX_COUNT)
		{
			env->points[y][x].image = ft_malloc_or_throw(env, sizeof(t_image));
			env->points[y][x].image->id = NULL;
			env->points[y][x].value = 0;
		}
	}
}

void	ft_init_texture(t_env *env, t_texture **texture, int color, int id)
{
	t_texture	*mtexture;
	int			x;
	int			y;

	mtexture = ft_malloc_or_throw(env, sizeof(t_texture));
	*texture = mtexture;
	mtexture->next = mtexture;
	mtexture->previous = mtexture;
	mtexture->id = id;
	mtexture->image = ft_malloc_or_throw(env, sizeof(t_xmp));
	mtexture->image->height = 64;
	mtexture->image->width = 64;
	mtexture->image->image = ft_malloc_or_throw(env, sizeof(t_image));
	mtexture->image->image->id = mlx_new_image(env->mlx.mlx_id,
		64, 64);
	mtexture->image->image->str = mlx_get_data_addr(
		mtexture->image->image->id, &mtexture->image->image->bpp,
		&mtexture->image->image->size, &mtexture->image->image->endian);
	y = -1;
	while (++y < 64)
	{
		x = -1;
		while (++x < 64)
			ft_putpixel(*mtexture->image->image, x, y, color);
	}
}

void	ft_init_window(t_env *env)
{
	env->mlx.mlx_id = mlx_init();
	env->mlx.window_id = mlx_new_window(env->mlx.mlx_id,
		WINDOW_WIDTH, WINDOW_HEIGHT, WINDOW_TITLE);
	ft_draw_grid(env);
	env->hud->image->id = mlx_xpm_file_to_image(env->mlx.mlx_id,
		"./texture/editor.xpm", &env->hud->width, &env->hud->height);
	mlx_put_image_to_window(env->mlx.mlx_id, env->mlx.window_id,
		env->hud->image->id, GRID_WIDTH + 1, 0);
}

void	ft_init_hooks(t_env *env)
{
	mlx_mouse_hook(env->mlx.window_id, ft_onmouseclick, env);
	mlx_key_hook(env->mlx.window_id, ft_onkeypress, env);
	mlx_hook(env->mlx.window_id, KEYPRESS, KEYPRESSMASK, ft_onkeypressl, env);
	mlx_hook(env->mlx.window_id, 17, (1L << 17), ft_quit, env);
	mlx_loop(env->mlx.mlx_id);
}

void	ft_init_text(t_env *env)
{
	mlx_string_put(env->mlx.mlx_id, env->mlx.window_id, 1116,
		250, 0xFFFFFF, HT1);
	mlx_string_put(env->mlx.mlx_id, env->mlx.window_id, 1116,
		300, 0xFFFFFF, HT2);
	mlx_string_put(env->mlx.mlx_id, env->mlx.window_id, 1116,
		350, 0xFFFFFF, HT3);
	mlx_string_put(env->mlx.mlx_id, env->mlx.window_id, 1116,
		400, 0xFFFFFF, HT4);
	mlx_string_put(env->mlx.mlx_id, env->mlx.window_id, 1116,
		450, 0xFFFFFF, HT5);
	mlx_string_put(env->mlx.mlx_id, env->mlx.window_id, 1116,
		500, 0xFFFFFF, HT6);
	mlx_string_put(env->mlx.mlx_id, env->mlx.window_id, 1116,
		550, 0xFFFFFF, HT7);
	mlx_string_put(env->mlx.mlx_id, env->mlx.window_id, 1160,
		720, 0xFFFFFF, TEXT_CURRENT_TEXTURE);
	mlx_string_put(env->mlx.mlx_id, env->mlx.window_id, 1625,
		640, 0xFFFFFF, TEXT_LIFE_LEVEL);
	mlx_string_put(env->mlx.mlx_id, env->mlx.window_id, 1615,
		660, 0xFFFFFF, TEXT_LIFE_LEVEL_2);
	mlx_string_put(env->mlx.mlx_id, env->mlx.window_id, 1290,
		934, 0xFFFFFF, TEXT_SKYMODE_OPEN);
	mlx_string_put(env->mlx.mlx_id, env->mlx.window_id, 1540,
		934, 0xFFFFFF, TEXT_SKYMODE_CLOSE);
}
