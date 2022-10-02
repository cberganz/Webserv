/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BodyMaker.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cberganz <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/02 18:55:06 by cberganz          #+#    #+#             */
/*   Updated: 2022/10/02 19:48:27 by cberganz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "BodyMaker.hpp"

BodyMaker::BodyMaker()
{}

BodyMaker::BodyMaker(const BodyMaker &src)
{ *this = src; }

BodyMaker::~BodyMaker()
{}

BodyMaker &BodyMaker::operator=(const BodyMaker &rhs)
{
	if (this != &rhs)
		this->m_body = rhs.m_body;
	return *this;
}

const std::string &BodyMaker::createBody(const std::string &path)
{
	m_body.clear();
	std::ifstream fs(path);
	m_body = std::string((std::istreambuf_iterator<char>(fs)), std::istreambuf_iterator<char>());
	return m_body;
}
