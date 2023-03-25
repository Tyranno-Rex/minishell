/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   l_make_tree.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minjinki <minjinki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/24 14:19:43 by MJKim             #+#    #+#             */
/*   Updated: 2023/03/25 17:29:49 by minjinki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

t_bool	make_ast_tree(void)
{
	if (!init_root())
		return (print_error("Fail to initialize root\n"));
	if (!lexer())
		return (print_error("Lexical analysis failed\n"));
}
