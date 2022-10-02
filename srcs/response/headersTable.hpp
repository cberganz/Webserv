/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   headersTable.hpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cberganz <cberganz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/01 03:34:41 by cberganz          #+#    #+#             */
/*   Updated: 2022/10/02 00:05:19 by cberganz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HEADERSTABLE_HPP
# define HEADERSTABLE_HPP

# define NEWLINE "\r\n"

typedef struct s_headerRow {
	std::string	rowTitle;
	bool		required;
}	t_headerRow;

# define MAX_ROWS 12

const t_headerRow headersTable[MAX_ROWS] = {
	{ "date",				true },
	{ "server",				true },
	{ "location",			false },
	{ "connection",			false },
	{ "retry-after",		true },
	{ "last-modified",		false },
	{ "www-authenticate",	false },
	{ "transfer-encoding",	false },
	{ "content-type",		false },
	{ "content-length",		false },
	{ "content-location",	false },
	{ "content-language",	false },
};

#endif // HEADERMAKER_HPP
