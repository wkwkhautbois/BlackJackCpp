#pragma once
#include <vector>
#include "Card.h"

class Hand
{
	std::vector<Card> _cards;
public:
	Hand();
	virtual ~Hand();
	void add(const Card& card);
	const int calcPoint() const;
	const Card& getCard(int n) const;
	const int number() const;
};

