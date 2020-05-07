/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operations.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ftrujill <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/07 17:42:28 by ftrujill          #+#    #+#             */
/*   Updated: 2020/05/07 17:42:51 by ftrujill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef OPERATIONS_H
# define OPERATIONS_H

typedef struct s_cw			t_cw;
typedef struct s_process	t_process;
typedef struct s_op			t_op;
void						ft_live(t_cw *cw, t_process *prcs, int i, t_op op);
void						ft_ld(t_cw *cw, t_process *prcs, int i, t_op op);
void						ft_st(t_cw *cw, t_process *prcs, int i, t_op op);
void						ft_add(t_cw *cw, t_process *prcs, int i, t_op op);
void						ft_sub(t_cw *cw, t_process *prcs, int i, t_op op);
void						ft_and(t_cw *cw, t_process *prcs, int i, t_op op);
void						ft_or(t_cw *cw, t_process *prcs, int i, t_op op);
void						ft_xor(t_cw *cw, t_process *prcs, int i, t_op op);
void						ft_zjmp(t_cw *cw, t_process *prcs, int i, t_op op);
void						ft_ldi(t_cw *cw, t_process *prcs, int i, t_op op);
void						ft_sti(t_cw *cw, t_process *prcs, int i, t_op op);
void						ft_fork(t_cw *cw, t_process *prcs, int i, t_op op);
void						ft_lld(t_cw *cw, t_process *prcs, int i, t_op op);
void						ft_lldi(t_cw *cw, t_process *prcs, int i, t_op op);
void						ft_lfork(t_cw *cw, t_process *prcs, int i, t_op op);
void						ft_aff(t_cw *cw, t_process *prcs, int i, t_op op);

#endif
