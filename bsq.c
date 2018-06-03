#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>

int		line_length(int fd)
{
	int counter;
	char buffer;

	counter = 0;
	while (read(fd, &buffer, 1) != '\n')
	{
		counter++;
		if (counter > 2147483647)
		{
			write(1, "\nInvalid map.", 12);
			return (-1);
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
		if (read(fd, &buffer, 1) == '\n')
			counter++;
	}
	return (counter);
}

void	bsq(int *map, int fd)
{
	int i;
	int open_space;

	i = 1;
	open_space = 0;
	while (i < map_height(fd) * line_length(fd))
	{
		//algorithm goes here -> :)

		//maybe something like this?
		if (map[i] == 0 && map[i + line_length(fd)] == 0)
		{
			open_space++;
			i += line_length(fd);
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
	char buffer;
	int *map;
	int i;
	int fd;
	unsigned long counter;

	if (argc > 1)
	{
		i = 1;
		while (argv[i])
		{
			counter = 0;
			fd = open(argv[i], O_RDONLY); //should probably check if a directory
			if (fd >= 0)
			{
				//convert chars to ints, put them in an array
				map = (int*)malloc(sizeof(char) * ((line_length(fd) * map_height(fd)) + map_height(fd)));
				while (counter < sizeof(map))
				{
					if (read(fd, &buffer, 1) == 'o')
						map[counter] = 1;
					if (read(fd, &buffer, 1) == '.')
						map[counter] = 0;
					if (read(fd, &buffer, 1) == '\n')
						map[counter] = 4;
					else
					{
						write(1, "\nInvalid map.", 12);
						return(1);
					}
					counter++;
				}
			}
			bsq(map, fd);
			write(1, "\n", 1);
			i++;
		}
	}
	//take map from standard input if no file is given as argument
	else
		stdinput();
}
