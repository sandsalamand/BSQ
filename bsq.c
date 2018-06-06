/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bsq.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgrindhe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/06 02:42:23 by sgrindhe          #+#    #+#             */
/*   Updated: 2018/06/06 06:39:14 by sgrindhe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <stdio.h>

int		line_length(int fd)
{
	int counter;
	int i;
	char buffer;

	counter = 0;
	i = 0;
	while (read(fd, &buffer, 1))
	{
		if (i > 0)
		{
			if (buffer == '\n')
			{
				return counter;
			}
			counter++;
		}
		if (buffer == '\n')
		{
			i++;
		}
	}
	return (counter);
}

int		map_height(int fd)
{
	int counter;
	char buffer;

	counter = 1;
	while (read(fd, &buffer, 1))
	{
		if (buffer == '\n')
		{
			counter++;
		}
	}
	return (counter);
}

void	print_array(int **arr, int m_height, int line_len)
{
	int		x;
	int		y;
	y = 0;

	while (y < m_height)
	{
		x = 0;
		while (x < line_len)
		{
			printf("%d", arr[y][x]);
			x++;
		}
		printf("\n");
		y++;
	}
}

void	map_clear(int **map, int m_height, int line_len)
{
	int y;
	int x;

	y = 0;
	x = 0;
	while (y < m_height)
	{
		x = 0;
		while (x < line_len)
		{
			if (map[y][x] == 3)
				map[y][x] = 0;
			x++;
		}
		y++;
	}
}

void	map_redraw(int **map, int size, int xcorner, int ycorner)
{
	int x;
	int y;

	x = xcorner;
	y = ycorner;
	while (y < ycorner + size)
	{
		x = 0;
		while (x < xcorner + size)
		{	
			map[y][x] = 3;
			x++;
		}
		y++;
	}
}

void	bsq(int **arr,  int m_height, int line_len)
{
	int		**square_holder_map;
	int		x;
	int		y;
	int		cur_x;
	int		cur_y;
	int		starting_x;
	int 	starting_y;
	int		biggest_size;
	int		size;
	int		i;

	x = 0;
	y = 0;
	i = 0;
	square_holder_map = malloc(sizeof(int*) * line_len);
	while (i < line_len)
	{
		square_holder_map[i] = malloc(sizeof(int) * m_height);
		i++;
	}

	while (y < m_height)
	{
		x = 0;
		while (x < line_len)
		{
			square_holder_map[x][y] = arr[x][y];
			x++;
		}
		y++;
	}

	y = 0;
	//print_array(arr, m_height, line_len);
	starting_x = 0;
	starting_y = 0;
	biggest_size = 1;
	size = 2;
	while (starting_y < m_height)
	{
		while (starting_x < line_len)
		{
			//this condition checks to make sure the square hasn't grown out of the bounds of the map
			cur_x = starting_x;
			cur_y = starting_y;
			//this condition is never called hmmmmm
			while (size <= m_height && size <= line_len && starting_x + size <= line_len && starting_y + size <= m_height && arr[cur_y][cur_x] != 1)
			{
				cur_y = starting_y;
				while (cur_y < (starting_y + size) && cur_y < m_height && arr[cur_y][cur_x] != 1)
				{
					cur_x = starting_x;
					while (cur_x < (starting_x + size) && cur_x < line_len && arr[cur_y][cur_x] != 1)
					{
						printf("cur_x = %d, cur_y = %d, biggest_size = %d, starting_x = %d, starting_y = %d\n", cur_x, cur_y, biggest_size, starting_x, starting_y);
						if (size > biggest_size && arr[cur_y][cur_x] != 1)
						{
							biggest_size = size;
							map_clear(square_holder_map, m_height, line_len);
							map_redraw(square_holder_map, biggest_size, cur_x, cur_y);
							square_holder_map[cur_y][cur_x] = 3;
						}
						cur_x++;
					}
					cur_y++;
				}
				size++;
			}
			starting_x++;
			size = 2;
		}
		starting_x = 0;
		starting_y++;
		size = 2;
	}
	print_array(square_holder_map, m_height, line_len);
}

void	load_array(char *filename)
{
	int		fd;
	char	buf;
	int		**map;
	int		x;
	int		y;
	int		i;
	int		len;
	int		hei;

	x = 0;
	y = 0;
	i = 0;

	fd = open(filename, O_RDONLY); //should probably check if a directory
	len = line_length(fd);
	hei = map_height(fd);
	close(fd);
	fd = open(filename, O_RDONLY);
	if (fd >= 0)
	{
		map = malloc(sizeof(int*) * hei);
		while (i < hei)
		{
			map[i] = malloc(sizeof(int) * len);
			i++;
		}
		i = 0;

		while (read(fd, &buf, 1) != 0)
		{
			if(i > 0)
			{
				if (buf == 'o')
				{
					map[y][x] = 1;
					//print_array(map);
					x++;
				}
				else if (buf == '.')
				{
					map[y][x] = 0;
					//print_array(map);
					x++;
				}
				else if(buf == '\n')
				{
					y++;
				}
				else if(buf != 'o' && buf != '.' && buf != 'n')
				{
					write(1, "\nInvalid map.", 12);
				}
			}
			if (buf == '\n' && i < 10)
				i++;
		}
		bsq(map, hei, len);
	}
}

/*
void	stdinput(void)
{
	int i;
	char c;
	int fd;

	fd = open("temp.txt", O_WRONLY);
	i = 0;
	//for some reason you can't just write chars directly to the file, but this solution sucks cause it's > 25 lines
	while (read(0, &c, 1) != 0)
	{
		if (c == 'o')
		{
			c = '1';
			write(fd, &c, 1);
		}
		if (c == '.')
		{
			c = '0';
			write(fd, &c, 1);
		}
		if (c == '\n')
		{
			c = '\n';
			write(fd, &c, 1);
		}
		else
			write(1, "\nInvalid map character entered\n", 31);
		i++;
	}
	//main(2, "output.txt");
}
*/
int		main(int argc, char **argv)
{
	int i;

	if (argc > 1)
	{
		i = 1;
		while (argv[i])
		{
			load_array(argv[i]);
//			write(1, "\n", 1);
			i++;
		}
	}
	//take map from standard input if no file is given as argument
//	else
//		stdinput();
	return (0);
}
