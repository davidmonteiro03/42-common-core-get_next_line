/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bonus.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcaetano <dcaetano@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/14 11:10:10 by dcaetano          #+#    #+#             */
/*   Updated: 2025/02/14 15:17:53 by dcaetano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"
#include <fcntl.h>
#include <stdbool.h>

static void	open_fds_and_init_lines(int *fds, char **lines, int argc,
		char **argv)
{
	int	i;

	i = 0;
	while (++i < argc)
	{
		lines[i - 1] = NULL;
		fds[i - 1] = open(argv[i], O_RDONLY);
		if (fds[i - 1] == -1)
		{
			perror(argv[i]);
			continue ;
		}
	}
	lines[i - 1] = NULL;
}

static void	read_fds_and_show_lines(int *fds, char **lines, int argc,
		char **argv)
{
	int		i[2];
	bool	readed;

	i[1] = 0;
	while (1)
	{
		readed = false;
		i[0] = 0;
		while (++i[0] < argc)
		{
			if (fds[i[0] - 1] == -1)
				continue ;
			lines[i[0] - 1] = get_next_line(fds[i[0] - 1]);
			if (lines[i[0] - 1] == NULL)
				continue ;
			readed = true;
			printf("%s[%d]: %s", argv[i[0]], i[1], lines[i[0] - 1]);
			free(lines[i[0] - 1]);
		}
		if (readed == false)
			break ;
		i[1]++;
	}
}

static void	close_fds_and_clean_lines(int *fds, char **lines, int argc)
{
	int	i;

	i = 0;
	while (++i < argc)
		if (fds[i - 1] != -1)
			close(fds[i - 1]);
	if (fds != NULL)
		free(fds);
	if (lines != NULL)
		free(lines);
}

int	main(int argc, char **argv)
{
	int		*fds;
	char	**lines;

	fds = (int *)malloc(sizeof(int) * (argc - 1));
	if (fds == NULL)
		return (1);
	lines = (char **)malloc(sizeof(char *) * argc);
	if (lines == NULL)
		return (free(fds), 1);
	open_fds_and_init_lines(fds, lines, argc, argv);
	read_fds_and_show_lines(fds, lines, argc, argv);
	close_fds_and_clean_lines(fds, lines, argc);
	return (0);
}
