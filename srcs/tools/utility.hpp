/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utility.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbicanic <rbicanic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/16 17:12:48 by cberganz          #+#    #+#             */
/*   Updated: 2022/10/16 00:14:09 by charles          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILITY_HPP
# define UTILITY_HPP

# include <sstream>
# include <stdio.h>
# include <time.h>
# include <sys/stat.h>
# include <unistd.h>
# include <algorithm>
# include <sstream>
# include <iterator>
# include <cstring>

namespace ft {

/*
**	@brief Perform type conversion from any type to the type specified as T1.
**	@usage lexical_cast<out_type>(in_type)
*/

template <typename T1, typename T2>
inline T1 lexical_cast(const T2 &to_cast)
{
	T1 ret;
	std::stringstream ss(to_cast);
	ss >> ret;
	return ret;
}

inline std::string itostr(const int &n)
{
	std::ostringstream oss;
	oss << n;
	return oss.str();
}

inline std::string getTimeFormated()
{
	char buf[1000];
	time_t now = time(0);
	struct tm tm = *gmtime(&now);
	strftime(buf, sizeof buf, "%a, %d %b %Y %H:%M:%S %Z", &tm);
	return buf;
}

}; // NAMESPACE FT

#endif // UTILITY_HPP
