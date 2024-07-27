/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pauldos- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 18:23:23 by pauldos-          #+#    #+#             */
/*   Updated: 2024/07/24 09:25:00 by pauldos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"


int	key_press(int keycode, t_game *game)
{
	if (keycode == 65307)
	{
		mlx_destroy_window(game->mlx, game->window);
//		cleanup_mlx(game);
		exit(0);
	}
	return (0);
}

// Function to render images
void	render_game(t_game *game)
{
	int	x;
	int	y;
	char	tile;

	y = 0;
	while (y < game->line_count)
	{
		x = 0;
		while (x < game->max_line_length)
		{
			tile = game->map[y][x];
			if (tile == '1')
				mlx_put_image_to_window(game->mlx, game->window, game->img_wall, x * TILE_SIZE, y * TILE_SIZE);
			else if (tile == '0')
				mlx_put_image_to_window(game->mlx, game->window, game->img_road, x * TILE_SIZE, y * TILE_SIZE);
			else if (tile == 'P')
				mlx_put_image_to_window(game->mlx, game->window, game->img_player, x * TILE_SIZE, y * TILE_SIZE);
			else if (tile == 'E')
				mlx_put_image_to_window(game->mlx, game->window, game->img_exit, x * TILE_SIZE, y * TILE_SIZE);
			else if (tile == 'C')
				mlx_put_image_to_window(game->mlx, game->window, game->img_collectible, x * TILE_SIZE, y * TILE_SIZE);
			x++;
		}
		y++;
	}
}

void	update_and_render(t_game *game)
{
	mlx_clear_window(game->mlx, game->window);
	render_game(game);
}

int	loop_hook(t_game *game)
{
	update_and_render(game);
	return (0);
}

// Function to load images
void load_image(t_game *game) {
    game->img_player = mlx_xpm_file_to_image(game->mlx, "./images/player.xpm", &game->img_width, &game->img_height);
    game->img_wall = mlx_xpm_file_to_image(game->mlx, "./images/wall.xpm", &game->img_width, &game->img_height);
    game->img_collectible = mlx_xpm_file_to_image(game->mlx, "./images/collectible.xpm", &game->img_width, &game->img_height);
    game->img_exit = mlx_xpm_file_to_image(game->mlx, "./images/exit.xpm", &game->img_width, &game->img_height);
    game->img_road = mlx_xpm_file_to_image(game->mlx, "./images/road.xpm", &game->img_width, &game->img_height);

    if (!game->img_player) {
        ft_printf("Failed to load player image\n");
	exit(1);
    }
    if (!game->img_wall) {
        ft_printf("Failed to load wall image\n");
	exit(1);
    }
    if (!game->img_collectible) {
        ft_printf("Failed to load collectible image\n");
	exit(1);
    }
    if (!game->img_exit) {
        ft_printf("Failed to load exit image\n");
	exit(1);
    }
    if (!game->img_road) {
        ft_printf("Failed to load road image\n");
	exit(1);
    }
}

// Function to cleanup MLX images and window
void cleanup_mlx(t_game *game) {
    if (game->img_player) {
        mlx_destroy_image(game->mlx, game->img_player);
        game->img_player = NULL;
    }
    if (game->img_wall) {
        mlx_destroy_image(game->mlx, game->img_wall);
        game->img_wall = NULL;
    }
    if (game->img_collectible) {
        mlx_destroy_image(game->mlx, game->img_collectible);
        game->img_collectible = NULL;
    }
    if (game->img_exit) {
        mlx_destroy_image(game->mlx, game->img_exit);
        game->img_exit = NULL;
    }
    if (game->img_road) {
        mlx_destroy_image(game->mlx, game->img_road);
        game->img_road = NULL;
    }
    if (game->window) {
        mlx_destroy_window(game->mlx, game->window);
        game->window = NULL;
    }
    if (game->mlx) {
        mlx_destroy_display(game->mlx);
        free(game->mlx);
        game->mlx = NULL;
    }
}

void	init_mlx(t_game *game)
{
	game->mlx = mlx_init();
	if (!game->mlx)
	{
		ft_printf("Failed to initialize MLX\n");
		exit(1);
	}
	game->window = mlx_new_window(game->mlx, game->max_line_length * TILE_SIZE, \
			game->line_count * TILE_SIZE, "so_long");
	if (!game->window)
	{
		ft_printf("Failed to create window\n");
		mlx_destroy_display(game->mlx);
		free(game->mlx);
		exit(1);
	}
}

static void	map_read(int fd, int *line_count, int *max_line_length)
{
	char	*line;
	int		line_length;

	line = get_next_line(fd);
	while (line != NULL)
	{
		(*line_count)++;
		line_length = ft_strlen(line);
		if (line_length > *max_line_length)
			*max_line_length = line_length;
		free (line);
		line = get_next_line(fd);
	}
}

void	init_game(t_game *game)
{
	game->line_count = 0;
	game->max_line_length = 0;
	game->map = NULL;
	game->player = 0;
	game->consumable = 0;
	game->exit_map = 0;
	game->mlx = NULL;
	game->window = NULL;
	game->img_player = NULL;
	game->img_wall = NULL;
	game->img_exit = NULL;
	game->img_road = NULL;
	game->img_collectible = NULL;
	game->img_width = 0;
	game->img_height = 0;
}

int	main(int argc, char *argv[])
{
	int		fd;
	t_game	game;	

	if (argc != 2)
		return (1);
	init_game(&game);
	fd = open(argv[1], O_RDONLY);
	if (fd == -1)
		return (1);
	map_read(fd, &game.line_count, &game.max_line_length);
	lseek(fd, 0, SEEK_SET);
	if (map_mem_allocate(&game.map, fd, game.line_count, \
				game.max_line_length) != 0)
		return (1);
	add_print_lines(&game.map, fd);
	close (fd);
	if (!validate_map(game.map, game.line_count))
		return (1);
	init_mlx(&game);
	load_image(&game);

	mlx_loop_hook(game.mlx, loop_hook, &game);
	mlx_key_hook(game.window, key_press, &game);
	mlx_loop(game.mlx);

	mem_free(&game.map, game.line_count);
	cleanup_mlx(&game);
	return (0);
}
