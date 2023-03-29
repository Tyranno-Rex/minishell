/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_set_pipe_n_redi.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: MJKim <zinnnn37@gmail.com>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/29 14:56:11 by MJKim             #+#    #+#             */
/*   Updated: 2023/03/29 14:56:11 by MJKim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/*
** check if type is pipe or redirection
*/
void	check_type(t_token *cur)
{
	int	len;

	len = ft_strlen(cur->data);
	if (len > 2 || (*(cur->data)) == PIPE && len > 1)
		cur->type = ERROR;
	else if (*(cur->data) == LREDI)
	{
		if (len == 1)
			cur->type = LREDI;
		else if (len == 2)
			cur->type = HEREDOC;
	}
	else if (*(cur->data) = RREDI)
	{
		if (len == 1)
			cur->type = RREDI;
		else if (len == 2)
			cur->type = RRREDI;
	}
	else if (*(cur->data) == PIPE)
		if (len == 1)
			cur->type = PIPE;
}

t_bool	deal_lredis(char *redi)
{
	// check_error if문 내에 있는 내용 여기로 빼기
	// length에 따라서 60할 지 6060할 지 조건으로 넣기
}

/*
** check if type ERROR is |< or |<< -> should be splited as | < and | <<
*/
t_bool	check_error(t_token *cur)
{
	char	*tmp;
	char	*type;
	t_token	*new;

	tmp = cur->data;
	if (ft_strcmp(cur->data, "|<"))
	{
		cur->data = ft_strdup("|");
		if (!(cur->data))
			return (ft_free(tmp));
		type = ft_strdup("<");
		if (!type)
			return (ft_free(tmp));
		new = ft_lstnew(LREDI, type);
		if (!new)
		{
			free(type);
			return (ft_free(tmp));
		}
	}
	else if (ft_strcmp(cur->data, "|<<"))
	{
		// same as upper condition
		// 함수로 빼서 s로 "<"나 "<<" 넘겨주기
		// 한 함수로 두 개 다 커버하기
	}
	free(tmp);
}

t_bool	set_pipe_n_redi(void)
{
	t_token	*cur;

	cur = g_glob.tok;
	while (cur)
	{
		if (cur->type == TMP)
			check_type(cur);
		else if (cur->type == ERROR)
			if (!check_error(cur))
				return (FALSE);
		cur = cur->next;
	}
	return (TRUE);
}