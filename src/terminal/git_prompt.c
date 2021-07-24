/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   git_prompt.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ciglesia <ciglesia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/24 21:22:50 by ciglesia          #+#    #+#             */
/*   Updated: 2021/07/24 21:52:57 by ciglesia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "msh.h"

static void	print_porcelain(char *branch, int types[])
{
	ioctl(STDIN_FILENO, TIOCGWINSZ, &g_sh->events->ws);

	ft_putstr(BOLD""CYAN"      "WORRA" ");
	if (types[0])
	{
		ft_putchar('+');
		ft_putnbr(types[0]);
	}
	if (types[1])
	{
		ft_putchar('!');
		ft_putnbr(types[1]);
	}
	if (types[2])
	{
		ft_putchar('?');
		ft_putnbr(types[2]);
	}
	if (types[0] + types[1] + types[2])
		ft_putstr(" "TRIANG" ");
	ft_putstr(branch);
	ft_putstr("\n"E0M);
}

/*

  # ⇣42 if behind the remote.
  (( VCS_STATUS_COMMITS_BEHIND )) && p+=" ${clean}⇣${VCS_STATUS_COMMITS_BEHIND}"
  # ⇡42 if ahead of the remote; no leading space if also behind the remote: ⇣42⇡42.
  (( VCS_STATUS_COMMITS_AHEAD && !VCS_STATUS_COMMITS_BEHIND )) && p+=" "
  (( VCS_STATUS_COMMITS_AHEAD  )) && p+="${clean}⇡${VCS_STATUS_COMMITS_AHEAD}"
  # ⇠42 if behind the push remote.
  (( VCS_STATUS_PUSH_COMMITS_BEHIND )) && p+=" ${clean}⇠${VCS_STATUS_PUSH_COMMITS_BEHIND}"
  (( VCS_STATUS_PUSH_COMMITS_AHEAD && !VCS_STATUS_PUSH_COMMITS_BEHIND )) && p+=" "
  # ⇢42 if ahead of the push remote; no leading space if also behind: ⇠42⇢42.
  (( VCS_STATUS_PUSH_COMMITS_AHEAD  )) && p+="${clean}⇢${VCS_STATUS_PUSH_COMMITS_AHEAD}"
  # *42 if have stashes.
  (( VCS_STATUS_STASHES        )) && p+=" ${clean}*${VCS_STATUS_STASHES}"
  # 'merge' if the repo is in an unusual state.
  [[ -n "$VCS_STATUS_ACTION"   ]] && p+=" ${conflicted}${VCS_STATUS_ACTION}"
  # ~42 if have merge conflicts.
  (( VCS_STATUS_NUM_CONFLICTED )) && p+=" ${conflicted}~${VCS_STATUS_NUM_CONFLICTED}"
  # +42 if have staged changes.
  (( VCS_STATUS_NUM_STAGED     )) && p+=" ${modified}+${VCS_STATUS_NUM_STAGED}"
  # !42 if have unstaged changes.
  (( VCS_STATUS_NUM_UNSTAGED   )) && p+=" ${modified}!${VCS_STATUS_NUM_UNSTAGED}"
  # ?42 if have untracked files. It's really a question mark, your font isn't broken.
  (( VCS_STATUS_NUM_UNTRACKED  )) && p+=" ${untracked}?${VCS_STATUS_NUM_UNTRACKED}"


*/

/*
**	types:
**		0 : M  (added)
**		1 :  M (modified)
**		2 : ?  (untracked)
*/

void	porcelain_prompt(char *branch)
{
	static char	*cmd2[] = {"/usr/bin/git", "status", "--porcelain", NULL};
	static int	types[3];
	int			fd;
	char		*line;

	ft_bzero(types, sizeof(types));
	fd = xcmdfd(cmd2);
	line = NULL;
	while (get_next_line(fd, &line) > 0)
	{
		if (line[0] == 'M' || line[0] == 'A')
			types[0]++;
		if (line[0] && line[1] == 'M')
			types[1]++;
		if (line[0] == '?')
			types[2]++;
		free(line);
	}
	close(fd);
	print_porcelain(branch, types);
}
