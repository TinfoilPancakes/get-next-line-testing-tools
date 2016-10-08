/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppatil <ppatil@student.42.us.org>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/05 22:39:37 by ppatil            #+#    #+#             */
/*   Updated: 2016/10/05 22:39:37 by ppatil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include GNL_HEADER_CPY
#include <fcntl.h>
#include <stdio.h>

void	test_basic(void)
{
	size_t	line_count;
	char	*line;
	int		fd;

	line_count = 0;
	line = NULL;
	printf("Opening file... ");
	fd = open("test_basic_dino.txt", O_RDONLY);
	if (fd < 0)
	{
		printf("Error opening %s.\n", "test_basic.txt");
		return ;
	}
	printf("Done.\n");
	printf("Reading Lines [12 expected]...\n");
	while (get_next_line(fd, &line))
	{
		line_count++;
		printf("%zu\t|%s$\n", line_count, line);
	}
	if (line_count != 12)
		printf("ERROR: test_basic(...) failed.\n");
	else
		printf("Done.\n");	
	printf("[ Lines Expected: 12, Lines Read: %zu ]\n", line_count);
	fd = close(fd);
	if (fd < 0)
	{
		printf("Fatal Error: Could not close open file.\n");
		exit(EXIT_FAILURE);
	}
}

void	test_poems(void)
{
	size_t	line_count;
	char	*line;
	int		fd_i;
	int		fd_a;
	int		fd_b;

	line = NULL;
	line_count = 0;
	fd_i = open("timmy_test_interleave.txt", O_RDONLY);
	fd_a = open("timmy_test_a.txt", O_RDONLY);
	fd_b = open("timmy_test_b.txt", O_RDONLY);
	if (fd_i < 0 || fd_a < 0 || fd_b < 0)
	{
		printf("Error opening files.\n");
		return ;
	}
	printf("Starting interleaved file read test...\n\n");
	line_count = 0;
	while (line_count < 4)
	{
		line_count++;
		get_next_line(fd_i, &line);
		printf("%zu\t|%s$\n", line_count, line);
	}
	while (get_next_line(fd_a, &line))
	{
		line_count++;
		printf("%zu\t|%s$\n", line_count, line);
	}
	line_count++;
	get_next_line(fd_i, &line);
	printf("%zu\t|%s$\n", line_count, line);
	while (get_next_line(fd_b, &line))
	{
		line_count++;
		printf("%zu\t|%s$\n", line_count, line);
	}
	while (get_next_line(fd_i, &line))
	{
		line_count++;
		printf("%zu\t|%s$\n", line_count, line);
	}
	printf("\nDone.\n");
	fd_i = close(fd_i);
	fd_a = close(fd_a);
	fd_b = close(fd_b);
	if (fd_i < 0 || fd_a < 0 || fd_b < 0)
	{
		printf("Fatal Error: Could not close open files!\n");
		exit(EXIT_FAILURE);
	}
}

void	test_null_cases(void)
{
	char	*line;
	int		temp_fd;
	size_t	line_count;

	line = NULL;
	line_count = 0;
	temp_fd = open("test_null_cases.txt", O_RDONLY);
	printf("Testing failure cases...\n");
	printf("Passing NULL pointer to line parameter of get_next_line(...)\n");
	get_next_line(temp_fd, NULL);
	printf("Passing invalid file descriptor (fd = -1)...\n");
	get_next_line(-1, &line);
	printf("Passing invalid file descriptor and line pointer...\n");
	printf("Done.\nAs a prize here is some text:\n\n");
	if (temp_fd < 0)
	{
		printf("Nevermind. The file couln't be opened so you get nothing :C\n");
		return ;
	}
	while (get_next_line(temp_fd, &line))
	{
		line_count++;
		printf("%zu\t|%s$\n", line_count, line);
	}
	printf("\nDid you enjoy your prize? Yes? Okay let's move on.\n");
	temp_fd = close(temp_fd);
	if (temp_fd < 0)
	{
		printf("Fatal Error: Could not close open file!\n");
		exit(EXIT_FAILURE);
	}
}

int		main(void)
{
	printf("[ Testing get_next_line(...): ]\n");
	printf("[ Current Buffer Size: %.4d   ]\n\n", BUFF_SIZE);
	test_basic();
	test_poems();
	test_null_cases();
	return (0);
}
