#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <stdio.h>

int		line_length(int fd)
{
	int counter;
	char buffer;

	counter = 0;
	while (read(fd, &buffer, 1))
	{
		counter++;
		if (buffer == '\n')
		{
			return (counter);
		}
	}
	return (counter);
}

int		map_height(int fd)
{
	int counter;
	char buffer;

	counter = 0;
	while (read(fd, &buffer, 1))
	{
		if (buffer == '\n')
		{	
			printf("%d", counter);
			counter++;
		}
	}
	return (counter);
}

void	bsq(int **map, int fd)
{
	int i;
	int cur_x;
	int cur_y;

	cur_x = 0;
	cur_y = 0;
	map[0][0] = 0;
	i = 1;
	while (i < map_height(fd) * line_length(fd))
	{
		//algorithm goes here -> :)

		i++;
	}
}

void	load_array(char *filename)
{
	unsigned long counter;
	int fd;
	int i;
	char buffer;
	int **map;
	int x;
	int y;

	x = 0;
	y = 0;
	i = 0;
	counter = 0;
	fd = open(filename, O_RDONLY); //should probably check if a directory
	if (fd >= 0)
	{
		//convert chars to ints, put them in an array
		map = malloc(sizeof(int) * line_length(fd));
		write(1, "loop entered", 12);
		while (i < line_length(fd))
		{
			map[i] = malloc(sizeof(int) * map_height(fd));
			i++;
		}
		while (counter < sizeof(map))
		{
			read(fd, &buffer, 1);
			if (buffer == 'o')
				map[x][y] = 1;
			if (buffer == '.')
				map[x][y] = 1;
			else if (buffer != '\n')
			{
				write(1, "\nInvalid map.", 12);
				return;
			}
			x++;
			y++;
			counter++;
		}
	}
}

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
			c = 49;
			write(fd, &c, 1);
		}
		if (c == '.')
		{
			c = 48;
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

int		main(int argc, char **argv)
{
	int i;

	if (argc > 1)
	{
		i = 1;
		while (argv[i])
		{
			load_array(argv[i]);
			write(1, "\n", 1);
			i++;
		}
	}
	//take map from standard input if no file is given as argument
	else
		stdinput();
}
