/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saalamoo <saalamoo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/03 18:50:28 by saalamoo          #+#    #+#             */
/*   Updated: 2023/09/03 18:51:21 by saalamoo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

int	main(int ac, char **av)
{
	t_prog	prog;

	if (ac > 4 && ac < 7)
	{
		if (char_parse(av))
			return (printf("ERROR ARG\n"), 1);
		if (parse(&prog, ac, av))
			return (printf("ERROR ARG\n"), 1);
		if (start_prog(&prog))
			return (printf("ERROR PROG\n"), 1);
	}
	else
		return (printf("error arg\n"), 1);
}
