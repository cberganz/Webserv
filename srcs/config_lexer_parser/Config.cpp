/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Config.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cberganz <cberganz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/18 20:22:35 by cberganz          #+#    #+#             */
/*   Updated: 2022/09/30 05:11:58 by cberganz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Config.hpp"

Config::Config()
{}

Config::Config(const Config &src)
{ *this = src; }

Config::Config(const std::string &fileName)
	: m_parser(fileName)
{}

Config::~Config()
{}

Config &Config::operator=(const Config &rhs)
{
	if (this != &rhs)
		m_parser = rhs.m_parser;
	return *this;
}

const Parser &Config::getParser() const
{ return this->m_parser; }

const Config::contextsContainer &Config::getGlobalContextsContainer() const
{ return this->m_parser.getRoot().getContexts(); }
