/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abluis-m <abluis-m@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/26 19:11:26 by abluis-m          #+#    #+#             */
/*   Updated: 2024/05/27 19:10:14 by abluis-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef REDIRECTIONS_H
# define REDIRECTIONS_H

int	handle_redir_in(t_minishell *shell, t_cmd_set *cmd_set, int pos);
int	clean_fd(t_minishell *shell, t_cmd_set *cmd_set, int pos);

#endif
