/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_00.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbehar <sbehar@student.42nice.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/16 13:40:38 by ml-hote           #+#    #+#             */
/*   Updated: 2026/08/26 21:47:24 by sbehar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_00_HPP
#define UTILS_00_HPP

#include <string>
#include <vector>
#include <map>
#include <algorithm>
#include <sstream>
#include <iostream>
#include <cctype>
#include <cstring>
#include <cstdlib>
#include <cstddef>
#include <poll.h>
#include <sys/socket.h>
#include <memory>
#include <cstdio>
#include <sys/types.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <unistd.h>

bool	argsParsing(int ac, char **av);

#endif