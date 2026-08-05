/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   GambleBot.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ml-hote <ml-hote@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/10 11:58:47 by ml-hote           #+#    #+#             */
/*   Updated: 2026/07/12 17:37:12 by ml-hote          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils_00.hpp"

/** GambleBot
 * How is the class supposed to work ?
 * I'm planning on making a bot made for gamble with multiple fonctionnalities

 * $imfeelinglucky

Inspired by Google's **"I'm Feeling Lucky"** button, randomly joins the user to
a public channel.

 * $roulette

Pretty self-explanatory: spins a roulette wheel and returns a random slot.

 * $blackjack

Starts a small interactive game of Blackjack.

 * $hand
 * Accepts args ranging from 1 to 52 and returns that many cards at random

 * $dices

Accepts arguments for dice ranging from **d2** to **d20**, with the ability to
specify how many dice of each type to roll.

A bit of argument parsing is required to ensure that:

* Each die type is specified only once.
* A maximum of **10 dice per die type** can be rolled.

Example
$dices 2d3 4d6 3d4
This rolls 2 three-sided dice, 4 six-sided dice, and 3 four-sided dice.

For the card games I'll create a plain text file containing a card name by line
and it will pick up the cards from there
*/
class GambleBot {
private:
	std::vector<std::string> cards_names;
	std::vector<int> cards_values;

public:
	GambleBot();
	~GambleBot();
	
	void	fillCards(void);
	void	pickCards(int n);
};
