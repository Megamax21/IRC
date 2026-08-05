#include "../headers/GambleBot.hpp"

GambleBot::GambleBot()
{
	fillCards();
	std::cout << "Gamblebot constructor called !" << std::endl;
}

GambleBot::~GambleBot()
{
	std::cout << "Gamblebot destructor called !" << std::endl;
}

void GambleBot::fillCards(void)
{
	std::ifstream file("./bonus/cards.txt");
	std::string line;
	if (file.is_open())
	{
			while (getline(file, line))
					cards_names.push_back(line);
			file.close();
	}
	else
			std::cerr << "Unable to open file!" << std::endl;
	for (int i = 0; i < 4; i++)
	{
		for (int j = 1; j <= 13 ; j++)
		{
			if (j >= 10 && j <= 13)
				cards_values.push_back(10);
			else
				cards_values.push_back(j);
		}
	}
}

void GambleBot::pickCards(int n)
{
	(void)n;
	std::vector<std::string>copyName = this->cards_names;
	std::vector<int>copyValue = this->cards_values;
	int	indexValue;
	int	totalCardValue = 0;
	// std::cout << "rand is " << rand()%52 << std::endl;	
	for (int i = 0; i < n; i++)
	{
		indexValue = rand()%(int)copyName.size();
		std::cout << '[' << cards_names[indexValue] << "]";
		totalCardValue += cards_values[indexValue];
		copyName.erase(copyName.begin() + indexValue);
		copyValue.erase(copyValue.begin() + indexValue);
	}
	std::cout << std::endl;
	std::cout << "Total cards value is : " << totalCardValue << std::endl;
}