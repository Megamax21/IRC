/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbehar <sbehar@student.42nice.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/30 17:33:04 by sbehar            #+#    #+#             */
/*   Updated: 2026/06/30 17:33:04 by sbehar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CHANNEL_HPP
#define CHANNEL_HPP

#include "../headers/utils_00.hpp"

class Client;

class Channel
{
    private:
        std::string             _name;
        std::string             _topic;
        std::string             _key;
        std::vector<Client*>    _members;
        std::vector<Client*>    _operators;
        bool                    _inviteOnly; // +i
        bool                    _topicRestricted; // +t
        bool                    _hasKey;
        bool                    _hasLimit;
        size_t                  _limit; // nombre max de membres quand +l actif
        
        // permets de trouver membre/operateur dans le vecteur client
        // afin de pouvoir faire les actions (add, remove, etc...)
        bool    isInVector(const std::vector<Client*> &vec, Client *client) const;
        void    removeFromVector(std::vector<Client*> &vec, Client *client);

    public:
        Channel();
        Channel(const std::string &name);
        Channel(const Channel &other);
        Channel &operator=(const Channel &other);
        ~Channel();

        const   std::string             &getName()  const;
        const   std::string             &getTopic()  const;
        const   std::string             &getKey()  const;
        const   std::vector<Client*>    &getMembers() const;
        const   std::vector<Client*>    &getOperators() const;
        bool                            isInviteOnly()  const;
        bool                            isTopicRestricted()  const;
        bool                            hasKey()  const;
        bool                            hasLimit()  const;
        size_t                          getLimit()  const;
        size_t                          getMemberCount()    const;
        bool                            isMember(Client *client) const;
        bool                            isOperator(Client *client) const;
        bool                            canJoin(Client *client) const;
        void                            addMember(Client *client);
        void                            removeMember(Client *client);
        void                            addOperator(Client *client);
        void                            removeOperator(Client *client);
        void                            setTopic(const std::string &topic);
        void                            setInviteOnly(bool value);
        void                            setTopicRestricted(bool value);
        void                            setKey(const std::string &key);
        void                            removeKey();
        void                            setLimit(size_t limit);
        void                            removeLimit();     
};

#endif