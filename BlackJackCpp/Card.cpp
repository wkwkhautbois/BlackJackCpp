#include <string>
#include "Card.h"


Card::Card()
{
}

Card::Card(Mark mark, int number)
	:_mark(mark), _num(number)
{
}


Card::~Card()
{
}

const int Card::number() const
{
	return _num;
}

const Mark& Card::mark() const
{
	return _mark;
}


std::ostream & operator<<(std::ostream & os, const Mark & mark)
{
	std::string markStr;
	switch (mark)
	{
	case Mark::Club:
		markStr = "Club";
		break;
	case Mark::Diamond:
		markStr = "Diamond";
		break;
	case Mark::Heart:
		markStr = "Heart";
		break;
	case Mark::Spade:
		markStr = "Spade";
		break;
	}

	os << markStr;
	return os;
}



std::ostream & operator<<(std::ostream & os, const Card & card)
{
	std::string numberDisplay;
	switch (card.number()) {
	case 1:
		numberDisplay = "A";
		break;
	case 11:
		numberDisplay = "J";
		break;
	case 12:
		numberDisplay = "Q";
		break;
	case 13:
		numberDisplay = "K";
		break;
	default:
		numberDisplay = std::to_string(card.number());
	}

	os << "[" << card.mark() << ", " << numberDisplay << "]";
	return os;
}
