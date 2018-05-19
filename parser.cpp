/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: justasze <justasze@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/02 14:00:54 by bcozic            #+#    #+#             */
/*   Updated: 2018/05/19 12:28:14 by justasze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expert_system.hpp"

// static void		aff_token_list(std::vector <std::vector <Token>> tokens)
// {
// 	std::vector <std::vector <Token>> :: iterator line;
// 	for (line = tokens.begin(); line != tokens.end(); ++line)
// 	{
// 		for (std::vector <Token> :: iterator i = (*line).begin(); i != (*line).end(); ++i)
// 		{
// 			std::cout << *i << '\n';
// 		}
// 		std::cout << "end line\n";
// 	}
// }

// static void		aff_token_line(std::vector <Token> tokens)
// {
// 	for (std::vector <Token> :: iterator i = tokens.begin(); i != tokens.end(); ++i)
// 	{
// 		std::cout << *i << '\n';
// 	}
// }

static int		fact_queried(char symbol, Hub *hub)
{
	int	ret = 0;
	for (std::vector <Fact> :: iterator i = (*hub).facts.begin(); i != (*hub).facts.end(); i++)
	{
		if ((*i).symbol == symbol)
		{
			(*i).queried = true;
			ret = 1;
			break ;
		}
	}
	return (ret);
}

static void		get_queries(std::vector <std::vector <Token>> :: iterator line, Hub *hub)
{
	std::vector <Token> :: iterator i = (*line).begin();
	i++;
	for (; i != (*line).end(); i++)
	{
		if ((*i).type != FACT || !fact_queried((*i).symbol, hub))
			error_n_exit("Querying an undefined fact");
	}
}

static void		fact_set_true(char symbol, Hub *hub)
{
	for (std::vector <Fact> :: iterator i = (*hub).facts.begin(); i != (*hub).facts.end(); i++)
	{
		if ((*i).symbol == symbol)
		{
			(*i).set_status(F_TRUE);
			return ;
		}
	}
}

static void		get_truth(std::vector <std::vector <Token>> :: iterator line, Hub *hub)
{
	std::vector <Token> :: iterator i = (*line).begin();
	i++;
	for (; i != (*line).end(); i++)
	{
		if ((*i).type != FACT)
			error_n_exit(" an undefined fact");
		fact_set_true((*i).symbol, hub);
	}
}

static int		get_end_parenthesis(Hub *hub, std::vector <Token> line, int i, int end)
{
	i++;
	while (line[i].symbol != ')')
	{
		if (line[i].symbol == '(')
			i = get_end_parenthesis(hub, line, i, end);
		i++;
		if (i >= end || i == 0)
			return (-1);
	}
	return (i);
}

static Fact	*get_formula(Hub *hub, std::vector <Token> line, int begin, int end)
{
	(void)hub;
	int	index = -1;
	int	priority = -1;

	for (int i = begin; i < end; i++)
	{
		if (line[i].symbol == ')')
			error_n_exit("Parenthesis don't match1");
		if (line[i].symbol == '(')
		{
			int tmp = i;
			if ((i = get_end_parenthesis(hub, line, i, end)) == -1)
				error_n_exit("Parenthesis don't match2");
			//i++;
			//std::cout << "get parenthesis" << i << std::endl;
			if (i >= end - 1 && tmp == begin)
			{
				i = begin;
				begin++;
				end--;
				continue ;
			}
			continue ;
			//else if (i >= end)
			//	break ;
		}
		if (line[i].operator_type > priority)
		{
			index = i;
			priority = line[i].operator_type;
		}
	}
	if (begin == end - 1)
		return &hub->facts[line[begin].symbol - 'A'];
	if (priority == -1)
		error_n_exit("Error in formula");
	return new Formula(1, get_formula(hub, line, begin, index), get_formula(hub, line, index + 1, end), priority);
}

static void		get_axioms(std::vector <Token> line, Hub *hub)
{
	(void)hub;
	int relation = -1;
	for (size_t i = 0; i < line.size(); i++)
	{
		if (line[i].type == RELATION)
		{
			relation = static_cast<int>(i);
			break ;
		}
	}
	if (relation == -1)
		error_n_exit("Missing relation");
	bool bicond = (line[relation].symbol == '=') ? 1 : 0;
	//Formula test = *static_cast<Formula*>(get_formula(hub, line, 0, line.size()));
	Axiom axiom(get_formula(hub, line, 0, relation), get_formula(hub, line, relation + 1, line.size()), bicond);
	axiom.compute_axiom();
	hub->axioms.push_back(axiom);

	//test.compute_status();
	//aff_token_line(line);
}

void			parse_system(std::vector <std::vector <Token>> tokens, Hub *hub)
{
	for (std::vector <std::vector <Token>> :: iterator i = tokens.begin(); i != tokens.end(); ++i)
	{
		if ((*(*i).begin()).type == QUERY)
			get_queries(i, hub);
		else if ((*(*i).begin()).type == TRUTH)
			get_truth(i, hub);
		else
			get_axioms(*i, hub);
	}
	//aff_token_list(tokens);
}