/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbehar <sbehar@student.42nice.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/30 17:31:50 by sbehar            #+#    #+#             */
/*   Updated: 2026/06/30 17:31:50 by sbehar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/Channel.hpp"

Channel::Channel()
    :   _name(""),
        _topic(""),
        _key(""),
        _inviteOnly(false),
        _topicRestricted(false),
        _hasKey(false),
        _hasLimit(false),
        _limit(0)
{}

Channel::Channel(const std::string &name)
    :   _name(name),
        _topic(""),
        _key(""),
        _inviteOnly(false),
        _topicRestricted(false),
        _hasKey(false),
        _hasLimit(false),
        _limit(0)
{}

Channel::Channel(const Channel &other)
{
    *this = other;
}

Channel &Channel::operator=(const Channel &other)
{
    if (this != &other)
    {
        _name = other._name;
        _topic = other._topic;
        _key = other._key;
        _inviteOnly = other._inviteOnly;
        _topicRestricted = other._topicRestricted;
        _hasKey = other._hasKey;
        _hasLimit = other._hasLimit;
        _limit = other._limit;
    }
    return (*this);
}

Channel::~Channel() {}

const   std::string &Channel:getName()  const
{
    return (_name);
}

const   std::string &Channel:getTopic()  const
{
    return (_topic);
}

const   std::string &Channel:getKey()  const
{
    return (_key);
}

bool    Channel::isInviteOnly() const
{
    return (_inviteOnly);
}

bool    Channel::isTopicRestricted() const
{
    return (_topicRestricted);
}

bool    Channel::hasKey() const
{
    return (_hasKey);
}

bool    Channel::hasLimit() const
{
    return (_hasLimit);
}

size_t  Channel::getLimit() const
{
    return (_limit);
}

size_t  Channel::getMemberCount() const
{
    return (_members.size());
}

void    Channel::setTopic(const std::string &topic)
{
    _topic = topic;
}

void    Channel::setInviteOnly(bool value)
{
    _inviteOnly = value;
}

void    Channel::setTopicRestricted(bool value)
{
    _topicRestricted = value;
}

void    Channel::setKey(const std::string &key)
{
    _key = key;
    _hasKey = true;
}

void    Channel::removeKey()
{
    _key.clear(); // ft qui remets la str à "" sans la détruire
    _hasKey = false;
}

void    Channel::setLimit(size_t limit)
{
    _limit = limit;
    _hasLimit = true;
}

void    Channel::removeLimit()
{
    _limit = 0;
    _hasLimit = false;
}
