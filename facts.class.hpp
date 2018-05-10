/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   facts.class.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: justasze <justasze@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/01 12:36:02 by bcozic            #+#    #+#             */
/*   Updated: 2018/05/10 14:21:59 by justasze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FACTS_CLASS_HPP
# define FACTS_CLASS_HPP

#include "expert_system.hpp"
#include "hub.class.hpp"

class Facts : public Hub
{
	public:

		int			type;
		const char	symbol;
		bool		queried;
		
		e_status	get_status(void);
		void		set_status(e_status);

		Facts(int type, const char);
		Facts(void);
		~Facts(void);
		//to do: add operator overload

		void	compute_status(void);

	private:

		e_status	_status;
};

std::ostream & operator<<(std::ostream & o, const Facts & fact);

#endif
