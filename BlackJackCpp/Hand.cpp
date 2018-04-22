#include "Hand.h"
#include <numeric>

Hand::Hand()
{
}


Hand::~Hand()
{
}

void Hand::add(const Card & card)
{
	_cards.push_back(card);
}

const int Hand::calcPoint() const
{
	int point = std::accumulate(_cards.cbegin(), _cards.cend(), 0, [](int init, const Card& card) {
		if (card.number() <= 10) {
			return init + card.number();
		}
		else {
			return init + 10;
		}
	});

	return point;
}

const std::vector<Card>& Hand::getList() const
{
	return _cards;
}
