/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minjinki <minjinki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/16 16:24:44 by minjinki          #+#    #+#             */
/*   Updated: 2023/03/18 19:04:43 by minjinki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/*
** parsing phase 1: split by quotes
** 
** e.g. ls -al "hi"'hello' "take me home" TT
** >> `ls -al `(STR) / `hi`(DOUBLE) / `hello`(SINGLE) \
**	/ ` `(STR) / `take me home`(DOUBLE) / ` TT`(STR)
** string between ` saved. ` is not saved
*/

t_token	*malloc_node(int len)
{
	t_token	*new;

	new = ft_calloc(1, sizeof(t_token));
	if (!new)
	{
		ft_lstclear(&(g_glob.tok));
		print_error("Fail to allocate memory: g_glob.tok\n");
		return (NULL);
	}
	new->data = ft_calloc(len + 1, sizeof(char));
	if (!(new->data))
	{
		free(new);
		ft_lstclear(&(g_glob.tok));
		print_error("Fail to allocate memory: g_glob.tok->data\n");
		return (NULL);
	}
	return (new);
}

t_token	*add_node(int type, int len, char *start)
{
	t_token	*new;

	new = malloc_node(len);
	new->type = type;
	ft_strlcpy(new->data, start, len + 1);
	return (new);
}

int	quotes(int type, char *cmd)
{
	int	len;

	len = ft_strnlen(cmd + 1, type);
	if (len == -1)
	{
		ft_lstclear(&(g_glob.tok));
		print_error("syntax error: unclosed quotes\n");
		return (ERROR);
	}
	ft_lstadd_back(&(g_glob.tok), add_node(type, len, cmd + 1));
	return (len);
}

int	split_quote(int len, char *cmd, char *quote)
{
	int	end;	// save index of 2nd quote

	end = 0;
	if (cmd != quote)
		ft_lstadd_back(&(g_glob.tok), add_node(STR, len, cmd));
	if (*quote == SINGLE)
		end = quotes(SINGLE, quote);	// check till single quote appears
	else if (*quote == DOUBLE)
		end = quotes(DOUBLE, quote);	// check till double quote appears
	if (end == ERROR)
		return (ERROR);
	return (end);	// return index of closed quote
}

void	deal_quotes(char *cmd)
{
	int		i;
	int		gap;
	int		last;
	char	*start;

	i = -1;
	last = 0;
	start = cmd;
	while (cmd[++i])
	{
		if (cmd[i] == SINGLE || cmd[i] == DOUBLE)
		{
			gap = split_quote(i - last, start, cmd + i);
			if (gap == ERROR)
				return ;
			i += (gap + 1);
			start = cmd + i + 1;
			last = i + 1;
		}
	}
	if (*start)
		split_quote(i + 1, start, cmd);
	ft_lstprint(&(g_glob.tok));
}
