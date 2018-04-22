#pragma once
#include <deque>
#include "Card.h"

class Deck
{
	std::deque<Card> _cardList;
public:
	Deck();
	~Deck();
	Card draw();
};

