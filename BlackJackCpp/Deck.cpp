#include <algorithm>
#include <random>
#include "Deck.h"


Deck::Deck()
{
	// �J�[�h��52���Z�b�g
	for (int i = 1; i <= 13; i++) {
		_cardList.emplace_back(Mark::Club, i);
		_cardList.emplace_back(Mark::Diamond, i);
		_cardList.emplace_back(Mark::Heart, i);
		_cardList.emplace_back(Mark::Spade, i);
	}

	// �f�b�L�V���b�t��
	std::random_device randd;
	std::mt19937 mt(randd());
	std::shuffle(_cardList.begin(), _cardList.end(), mt);

}


Deck::~Deck()
{
}


Card Deck::draw()
{
	// �J�[�h���������1������
	Card back = _cardList.back();
	_cardList.pop_back();
	return back;
}