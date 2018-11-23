/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.struct.hpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: justasze <justasze@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/02 16:09:11 by bcozic            #+#    #+#             */
/*   Updated: 2018/05/01 17:06:00 by justasze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKEN_STRUCT_HPP
# define TOKEN_STRUCT_HPP

#include "expert_system.hpp"

struct Token
{
	char			symbol;
	int				operator_type;
	e_token_type	type;
	Token(char symbol, e_token_type type, int operator_type);
	~Token(void);
};

std::ostream & operator<<(std::ostream & o, const Token & rep);

#endif