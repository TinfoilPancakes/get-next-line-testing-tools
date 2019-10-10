/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppatil <ppatil@student.42.us.org>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/05 22:39:37 by ppatil            #+#    #+#             */
/*   Updated: 2019/10/27 22:39:51 by cacharle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include GNL_HEADER_CPY
#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include "ft_ansi.h"

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
		printf(ANSI_F_RED "Error opening %s.\n" ANSI_RESET, "test_basic_dino.txt");
		return ;
	}
	printf("Done.\n");
	printf(ANSI_F_YELLOW "Reading Lines...\n" ANSI_RESET);
	while (get_next_line(fd, &line))
	{
		line_count++;
		printf(ANSI_F_CYAN "%zu" ANSI_RESET "\t|%s" ANSI_F_CYAN "$\n" ANSI_RESET, line_count, line);
		free(line);
	}
	if (line_count != 12)
		printf(ANSI_F_RED "ERROR: test_basic(...) failed.\n" ANSI_RESET);
	else
		printf(ANSI_F_GREEN "Done.\n" ANSI_RESET);
	printf(ANSI_F_YELLOW "[ Lines Expected: 12, Lines Read: %zu ]\n" ANSI_RESET, line_count);
	fd = close(fd);
	if (fd < 0)
	{
		printf(ANSI_F_BRED "Fatal Error: Could not close open file.\n" ANSI_RESET);
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
		printf(ANSI_F_RED "Error opening files.\n" ANSI_RESET);
		return ;
	}
	printf(ANSI_F_YELLOW "Starting interleaved file read test...\n\n" ANSI_RESET);
	line_count = 0;
	while (line_count < 4)
	{
		line_count++;
		get_next_line(fd_i, &line);
		printf(ANSI_F_CYAN "%zu" ANSI_RESET "\t|%s" ANSI_F_CYAN "$\n" ANSI_RESET, line_count, line);
		free(line);
	}
	while (get_next_line(fd_a, &line))
	{
		line_count++;
		printf(ANSI_F_CYAN "%zu" ANSI_RESET "\t|%s" ANSI_F_CYAN "$\n" ANSI_RESET, line_count, line);
		free(line);
	}
	line_count++;
	get_next_line(fd_i, &line);
	printf(ANSI_F_CYAN "%zu" ANSI_RESET "\t|%s" ANSI_F_CYAN "$\n" ANSI_RESET, line_count, line);
	free(line);
	while (get_next_line(fd_b, &line))
	{
		line_count++;
		printf(ANSI_F_CYAN "%zu" ANSI_RESET "\t|%s" ANSI_F_CYAN "$\n" ANSI_RESET, line_count, line);
		free(line);
	}
	while (get_next_line(fd_i, &line))
	{
		line_count++;
		printf(ANSI_F_CYAN "%zu" ANSI_RESET "\t|%s" ANSI_F_CYAN "$\n" ANSI_RESET, line_count, line);
		free(line);
	}
	if (line_count != 45)
		printf(ANSI_F_RED "\nERROR: Interleaved files test failed! [ test_poems(...); ]\n" ANSI_RESET);
	else
		printf(ANSI_F_GREEN "\nDone.\n" ANSI_RESET);
	printf(ANSI_F_YELLOW "[ Lines Expected: 45, Lines Read: %zu ]\n" ANSI_RESET, line_count);
	fd_i = close(fd_i);
	fd_a = close(fd_a);
	fd_b = close(fd_b);
	if (fd_i < 0 || fd_a < 0 || fd_b < 0)
	{
		printf(ANSI_F_BRED "Fatal Error: Could not close open files!\n" ANSI_RESET);
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
	printf(ANSI_F_GREEN "Done.\n" ANSI_RESET "As a prize here is some text:\n\n");
	if (temp_fd < 0)
	{
		printf(ANSI_F_RED "Nevermind. The file couln't be opened so you get nothing :C\n" ANSI_RESET);
		return ;
	}
	while (get_next_line(temp_fd, &line))
	{
		line_count++;
		printf(ANSI_F_CYAN "%zu" ANSI_RESET "\t|%s" ANSI_F_CYAN "$\n" ANSI_RESET, line_count, line);
		free(line);
	}
	if (line_count == 16)
		printf("\nDid you enjoy your prize? Yes? Okay let's move on.\n");
	else
		printf(ANSI_F_RED "Hey! Your prize isn't working properly! What's going on?\n" ANSI_RESET);
	printf(ANSI_F_YELLOW "[ Prize lines read: %zu, Prize lines expected: 16 ]\n" ANSI_RESET, line_count);
	temp_fd = close(temp_fd);
	if (temp_fd < 0)
	{
		printf("Fatal Error: Could not close open file!\n");
		exit(EXIT_FAILURE);
	}
}

int		main(void)
{
	printf(ANSI_F_BCYAN "[ Testing get_next_line(...): ]\n");
	printf("[ Current Buffer Size: %.4d   ]\n\n" ANSI_RESET, BUFFER_SIZE);
	test_basic();
	test_poems();
	test_null_cases();
	printf(ANSI_F_BCYAN "[ Test complete. ]\n" ANSI_RESET);
	return (0);
}
