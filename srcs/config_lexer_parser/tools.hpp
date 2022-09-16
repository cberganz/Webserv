/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cberganz <cberganz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/16 17:12:48 by cberganz          #+#    #+#             */
/*   Updated: 2022/09/16 17:12:50 by cberganz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOOLS_HPP
# define TOOLS_HPP

# include <sstream>

namespace ft {

template <typename T1, typename T2>
inline T1 lexical_cast(const T2 &to_cast)
{
	std::ostringstream oss;
	oss << to_cast;
	return oss.str();
}

}; // NAMESPACE FT

#endif
