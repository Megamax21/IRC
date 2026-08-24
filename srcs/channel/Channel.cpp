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
        _members(),
        _operators(),
        _invited(),
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
        _members(),
        _operators(),
        _invited(),
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
        _members = other._members;
        _operators = other._operators;
        _invited = other._invited;
        _inviteOnly = other._inviteOnly;
        _topicRestricted = other._topicRestricted;
        _hasKey = other._hasKey;
        _hasLimit = other._hasLimit;
        _limit = other._limit;
    }
    return (*this);
}

Channel::~Channel() {}

const   std::string &Channel::getName()  const
{
    return (_name);
}

const   std::string &Channel::getTopic()  const
{
    return (_topic);
}

const   std::string &Channel::getKey()  const
{
    return (_key);
}

const   std::vector<Client*> &Channel::getMembers() const
{
    return (_members);
}

const   std::vector<Client*> &Channel::getOperators() const
{
    return (_operators);
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

bool    Channel::isInVector(const std::vector<Client*> &vec, Client *client) const
{
    return (std::find(vec.begin(), vec.end(), client) != vec.end());
}

void    Channel::removeFromVector(std::vector<Client*> &vec, Client *client)
{
    std::vector<Client*>::iterator  it = std::find(vec.begin(), vec.end(), client);
    if (it != vec.end())
        vec.erase(it);
}

bool    Channel::isMember(Client *client) const
{
    return (isInVector(_members, client));
}

bool    Channel::isOperator(Client *client) const
{
    return (isInVector(_operators, client));
}

bool    Channel::isInvited(Client *client) const
{
    return (isInVector(_invited, client));
}

bool    Channel::canJoin(Client *client) const
{
    if (!client)
        return (false);
    if (_hasLimit && _members.size() >= _limit)
        return (false);
    if (_inviteOnly && !isInvited(client))
        return (false);
    return (true);
}

void    Channel::addMember(Client *client)
{
    if (!client || isMember(client))
        return ;
    _members.push_back(client);
}

void    Channel::removeMember(Client *client)
{
    if (!client)
        return ;
    removeFromVector(_members, client);
    removeFromVector(_operators, client);
    removeFromVector(_invited, client);
}

void    Channel::addOperator(Client *client)
{
    if (!client || isOperator(client) || !isMember(client))
        return ;
    _operators.push_back(client);
}

void    Channel::removeOperator(Client *client)
{
    if (!client)
        return ;
    removeFromVector(_operators, client);
}

void    Channel::invite(Client *client)
{
    if (client && !isInvited(client))
        _invited.push_back(client);
}

void    Channel::removeInvite(Client *client)
{
    if (client)
        removeFromVector(_invited, client);
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