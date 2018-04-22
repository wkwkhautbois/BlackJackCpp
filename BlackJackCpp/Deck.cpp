#include <algorithm>
#include <random>
#include "Deck.h"


Deck::Deck()
{
	// カードを52枚セット
	for (int i = 1; i <= 13; i++) {
		_cardList.emplace_back(Mark::Club, i);
		_cardList.emplace_back(Mark::Diamond, i);
		_cardList.emplace_back(Mark::Heart, i);
		_cardList.emplace_back(Mark::Spade, i);
	}

	// デッキシャッフル
	std::random_device randd;
	std::mt19937 mt(randd());
	std::shuffle(_cardList.begin(), _cardList.end(), mt);

}


Deck::~Deck()
{
}


Card Deck::draw()
{
	// カードを後方から1枚引く
	Card back = _cardList.back();
	_cardList.pop_back();
	return back;
}