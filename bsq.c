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

void	print_array(int **arr)
{
	int		x;
	int		y;
	y = 0;

	while (y < 20)
	{
		x = 0;
		while (x < 20)
		{
			printf("%d", arr[y][x]);
			x++;
		}
		printf("\n");
		y++;
	}
}

/*
void	bsq(int **arr, int fd)
{
	int		**square_holder_map;
	int		x;
	int		y;
	int		cur_x;
	int		cur_y;
	int		starting_x;
	int 	starting_y;
	int		size;
	int		i;

	write(1, "break", 5);
	x = 0;
	y = 0;
	// fill a 4x4 array with 0's
	while (y < 4)
	{
		x = 0;
		while (x < 4)
		{
			arr[y][x] = 0;
			x++;
		}
		y++;
	}

	i = 0;
	square_holder_map = malloc(sizeof(int*) * line_length(fd));
	while (i < 10)
	{
		square_holder_map[i] = malloc(sizeof(int) * map_height(fd));
		i++;
	}

	while (y < 4)
	{
		x = 0;
		while (x < 4)
		{
			square_holder_map[x][y] = arr[x][y];
			x++;
		}
		y++;
	}

	y = 0;
	print_array(arr);
	starting_x = 0;
	starting_y = 0;
	size = 2;
	cur_y = 0;
	cur_x = 0;
	while (starting_y < 4)
	{
		while (starting_x < 4)
		{
			//this condition checks to make sure the square hasn't grown out of the bounds of the map
			while (size <= 4 && starting_x + size <= 4 && starting_y + size <= 4)
			{
				cur_y = starting_y;
				while (cur_y < (starting_y + size) && cur_y < 4 && arr[cur_x][cur_y] != 1)
				{
					cur_x = starting_x;
					while (cur_x < (starting_x + size) && cur_x < 4 && arr[cur_x][cur_y] != 1)
					{
						square_holder_map[cur_y][cur_x] = arr[cur_y][cur_x] + 1;
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
	print_array(square_holder_map);
}
*/
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
		//convert chars to ints, put them in an array
		map = malloc(sizeof(int*) * hei);
		while (i < hei)
		{
			map[i] = malloc(sizeof(int) * len);
			i++;
		}
		i = 0;

		while (read(fd, &buf, 1) != 0)
		{
			printf("%d\n", i);
			if(i > 0)
			{
				if (buf == 'o')
				{
					map[y][x] = 1;
					print_array(map);
					x++;
				}
				else if (buf == '.')
				{
					map[y][x] = 0;
					print_array(map);
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
