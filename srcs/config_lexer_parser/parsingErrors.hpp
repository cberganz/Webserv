/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsingErrors.hpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cberganz <cberganz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/16 17:12:41 by cberganz          #+#    #+#             */
/*   Updated: 2022/09/22 22:02:16 by charles          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSINGERRORS_HPP
# define PARSINGERRORS_HPP

# define UNEXPECTED_EOF "Reached unexpected EOF while looking for bloc closing bracket inside bloc"
# define MANDATORY_DIRECTIVE_NOT_FOUND "Context mandatory directive not found"
# define MANDATORY_CONTEXT_NOT_FOUND "Context mandatory child context not found"
# define UNAVAILABLE_DIRECTIVE "Directive does not exists in this context"
# define NO_SPECIFIED_LOCATION "Bloc starts without specified path"
# define NO_BLOC_OPEN "Bloc starts without opening bracket"
# define NO_SEMICOLON "Directive ends without semicolon"
# define UNSPECIFIED_URI "URI not specified while context requires it"
# define PARSERCONFIG_MISUSE "Misuse of ParserConfig constructor. See @warning for more details."
# define DUPLICATE_BLOC "Duplicate bloc reached"
# define DUPLICATE_DIRECTIVE "Duplicate directive reached"

#endif // PARSINGERRORS_HPP
