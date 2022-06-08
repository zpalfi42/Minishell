/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ealonso- <ealonso-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/08 15:59:29 by ealonso-          #+#    #+#             */
/*   Updated: 2022/06/08 16:37:27 by ealonso-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	do_env_bis(t_data *data, t_ast *ast)
{
	(void) data;
	(void) ast;
	printf("LC_TERMINAL : %s\n", getenv("LC_TERMINAL"));
	printf("COLORTERM : %s\n", getenv("COLORTERM"));
	printf("TERM : %s\n", getenv("TERM"));
	printf("HOME : %s\n", getenv("HOME"));
	printf("TMPDIR : %s\n", getenv("TMPDIR"));
	printf("USER : %s\n", getenv("USER"));
	printf("XPC_SERVICE_NAME : %s\n", getenv("XPC_SERVICE_NAME"));
	printf("LOGNAME : %s\n", getenv("LOGNAME"));
	printf("ITERM_SESSION_ID : %s\n", getenv("ITERM_SESSION_ID"));
	printf("__CF_USER_TEXT_ENCODING : %s\n", getenv("__CF_USER_TEXT_ENCODING"));
	printf("SHLVL : %s\n", getenv("SHLVL"));
	printf("OLDPWD : %s\n", getenv("OLDPWD"));
	printf("MAIL : %s\n", getenv("MAIL"));
	printf("ZSH : %s\n", getenv("ZSH"));
	printf("PAGER : %s\n", getenv("PAGER"));
	printf("LESS : %s\n", getenv("LESS"));
	printf("LSCOLORS : %s\n", getenv("TERM_SESSION_ID"));
	printf("_ : %s\n", getenv("_"));
}	

void	do_env(t_data *data, t_ast *ast)
{
	(void) data;
	(void) ast;
	printf("TERM_SESSION_ID : %s\n", getenv("TERM_SESSION_ID"));
	printf("SSH_AUTH_SOCK : %s\n", getenv("SSH_AUTH_SOCK"));
	printf("LC_TERMINAL_VERSION : %s\n", getenv("LC_TERMINAL_VERSION"));
	printf("COLORFGBG : %s\n", getenv("COLORFGBG"));
	printf("ITERM_PROFILE : %s\n", getenv("ITERM_PROFILE"));
	printf("XPC_FLAGS : %s\n", getenv("XPC_FLAGS"));
	printf("PWD : %s\n", getenv("PWD"));
	printf("SHELL : %s\n", getenv("SHELL"));
	printf("LC_CTYPE : %s\n", getenv("LC_CTYPE"));
	printf("TERM_PROGRAM_VERSION : %s\n", getenv("TERM_PROGRAM_VERSION"));
	printf("TERM_PROGRAM : %s\n", getenv("TERM_PROGRAM"));
	printf("PATH : %s\n", getenv("PATH"));
	do_env_bis(data, ast);
}
