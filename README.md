# Cub3d
static int	check_forward(t_game *game)
{
	float	x;
	float	y;

	if (cos(game->player.angle) < 0)
		game->player.corner_x = -10;
	else if (cos(game->player.angle) > 0)
		game->player.corner_x = 10;
	if (sin(game->player.angle) < 0)
		game->player.corner_y = -10;
	else if (sin(game->player.angle) > 0)
		game->player.corner_y = 10;
	x = game->player.x + cos(game->player.angle) * SPEED;
	if (!is_wall(game, x + game->player.corner_x, game->player.y
			+ game->player.corner_y))
	{
		y = game->player.y + sin(game->player.angle) * SPEED;
		if (!is_wall(game, game->player.x + game->player.corner_x, y
				+ game->player.corner_y))
			return (0);
	}
	return (1);
}

static int	check_backward(t_game *game)
{
	float	x;
	float	y;

	if (cos(game->player.angle) < 0)
		game->player.corner_x = 10;
	else if (cos(game->player.angle) > 0)
		game->player.corner_x = -10;
	if (sin(game->player.angle) < 0)
		game->player.corner_y = 10;
	else if (sin(game->player.angle) > 0)
		game->player.corner_y = -10;
	x = game->player.x - cos(game->player.angle) * SPEED;
	if (!is_wall(game, x + game->player.corner_x, game->player.y
			+ game->player.corner_y))
	{
		y = game->player.y - sin(game->player.angle) * SPEED;
		if (!is_wall(game, game->player.x + game->player.corner_x, y
				+ game->player.corner_y))
			return (0);
	}
	return (1);
}

int	cant_move_forward_backward(t_game *game, char key)
{
	if (key == 'w')
		return (check_forward(game));
	if (key == 's')
		return (check_backward(game));
	return (1);
}

static int	check_left(t_game *game)
{
	float	x;
	float	y;

	if (cos(game->player.angle - M_PI_2) < 0)
		game->player.corner_x = -10;
	else if (cos(game->player.angle - M_PI_2) > 0)
		game->player.corner_x = 10;
	if (sin(game->player.angle - M_PI_2) < 0)
		game->player.corner_y = -10;
	else if (sin(game->player.angle - M_PI_2) > 0)
		game->player.corner_y = 10;
	x = game->player.x + cos(game->player.angle - M_PI_2) * SPEED;
	if (!is_wall(game, x + game->player.corner_x, game->player.y
			+ game->player.corner_y))
	{
		y = game->player.y + sin(game->player.angle - M_PI_2) * SPEED;
		if (!is_wall(game, game->player.x + game->player.corner_x, y
				+ game->player.corner_y))
			return (0);
	}
	return (1);
}

static int	check_right(t_game *game)
{
	float	x;
	float	y;

	if (cos(game->player.angle + M_PI_2) < 0)
		game->player.corner_x = -10;
	else if (cos(game->player.angle + M_PI_2) > 0)
		game->player.corner_x = 10;
	if (sin(game->player.angle + M_PI_2) < 0)
		game->player.corner_y = -10;
	else if (sin(game->player.angle + M_PI_2) > 0)
		game->player.corner_y = 10;
	x = game->player.x + cos(game->player.angle + M_PI_2) * SPEED;
	if (!is_wall(game, x + game->player.corner_x, game->player.y
			+ game->player.corner_y))
	{
		y = game->player.y + sin(game->player.angle + M_PI_2) * SPEED;
		if (!is_wall(game, game->player.x + game->player.corner_x, y
				+ game->player.corner_y))
			return (0);
	}
	return (1);
}

int	cant_move_sidewalk(t_game *game, char key)
{
	if (key == 'a')
		return (check_left(game));
	if (key == 'd')
		return (check_right(game));
	return (1);
}