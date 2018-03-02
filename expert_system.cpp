/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expert_system.cpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcozic <bcozic@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/01 16:18:17 by justasze          #+#    #+#             */
/*   Updated: 2018/03/02 14:28:12 by bcozic           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expert_system.hpp"

static int	usage()
{
	std::cout << "usage: ./expert_system <file>" << std::endl;
	return (EXIT_FAILURE);
}

int		main(int ac, char **av)
{
	if (ac != 2)
		return (usage());
	Hub hub;
	get_system(&hub, av[1]);
	return 0;
}
