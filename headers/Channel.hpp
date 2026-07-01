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

// trouver comment gérer les membres à partir du Client
// (ex: ajouter un membre, peut-il rejoindre le channel, ajouter un opérateur, etc..)

class Channel
{
    private:
        std::string _name;
        std::string _topic;
        std::string _key;
        // trouver comment mettre les membres à partir du Client
        // trouver comment mettre les opérateurs à partir du Client
        bool        _inviteOnly; // +i
        bool        _topicRestricted; // +t
        bool        _hasKey;
        bool        _hasLimit;
        size_t      _limit; // nombre max de membres quand +l actif
        
    public:
        Channel();
        Channel(const std::string &name);
        Channel(const Channel &other);
        Channel &operator=(const Channel &other);
        ~Channel();

        const   std::string &getName()  const;
        const   std::string &getTopic()  const;
        const   std::string &getKey()  const;
        bool                isInviteOnly()  const;
        bool                isTopicRestricted()  const;
        bool                hasKey()  const;
        bool                hasLimit()  const;
        size_t              getLimit()  const;
        size_t              getMemberCount()    const;
        void                setTopic(const std::string &topic);
        void                setInviteOnly(bool value);
        void                setTopicRestricted(bool value);
        void                setKey(const std::string &key);
        void                removeKey();
        void                setLimit(size_t limit);
        void                removeLimit();     
};

#endif