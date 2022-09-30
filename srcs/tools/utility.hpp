/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utility.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cberganz <cberganz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/16 17:12:48 by cberganz          #+#    #+#             */
/*   Updated: 2022/09/30 04:18:36 by cberganz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILITY_HPP
# define UTILITY_HPP

# include <sstream>

namespace ft {

/*
**	@brief Perform type conversion from any type to the type specified as T1.
**	@usage lexical_cast<out_type>(in_type)
*/

template <typename T1, typename T2>
inline T1 lexical_cast(const T2 &to_cast)
{
	T1 ret;
	std::stringstream oss(to_cast);
	oss >> ret;
	return ret;
}

}; // NAMESPACE FT

#endif // UTILITY_HPP
