// BlackJackCpp.cpp : アプリケーションのエントリ ポイントを定義します。
//

#include <iostream>
#include "Deck.h"
#include "Hand.h"
#include "BlackJackCpp.h"

enum class MatchResult
{
	Win,
	Lose,
	Draw
};

class Player
{
	Hand _hand;
	Deck& deck;
public:
	Player() = delete;
	Player(Deck& deck)
		:deck(deck) {}
	~Player() {};
	
	void draw() {
		Card drawnCard = deck.draw();
		_hand.add(drawnCard);
		std::cout << "あなたがカードを引きました" << std::endl;
		this->showLast();
	}

	void show(int n) {
		std::cout << "あなたの引いたカードは" << _hand.getCard(n) << "です" << std::endl;
	}

	void showLast() {
		this->show(_hand.number());
	}

	Hand& hand() { return _hand; }
};


class Dealer
{
	Hand _hand;
	Deck& deck;
public:
	Dealer() = delete;
	Dealer(Deck& deck)
		:deck(deck) {}
	~Dealer() {};

	void draw() {
		Card drawnCard = deck.draw();
		_hand.add(drawnCard);
		std::cout << "ディーラーが" << _hand.number() << "枚目のカードを引きました" << std::endl;
	}

	void show(int n) {
		std::cout << "ディーラーの" << n << "枚目に引いたカードは" << _hand.getCard(n) << "です" << std::endl;
	}

	void showLast() {
		this->show(_hand.number());
	}

	Hand& hand() { return _hand; }
};

void init(Deck &deck, Player &player, Dealer &dealer);
bool doesBust(Hand hand);
MatchResult checkResult(Hand &playerHand, Hand &dealerHand);

int main(int argc, char* argv[])
{
	Deck deck;
	Player player(deck);
	Dealer dealer(deck);
	bool isPlayerBust = false;
	bool isDealerBust = false;

	// カード配布
	init(deck, player, dealer);

	// プレイヤーの動作
	char c;
	while (true) {
		std::cout << "今のあなたの得点は" << player.hand().calcPoint() << "です。カードを引きますか?[y/n]" << std::endl;


		std::cin >> c;
		if (c == 'y' || c == 'Y') {
			player.draw();

			if (doesBust(player.hand())) {
				std::cout << "あなたはバストしました" << std::endl;
				break;
			}
		}
		else if (c == 'n' || c == 'N') {
			break;
		}
		else {
			std::cout << "どちらかを選んでください[y/n]" << std::endl;
		}
	}

	// ディーラーの動作
	dealer.show(2);
	while (dealer.hand().calcPoint() < 17) {
		dealer.draw();
		dealer.showLast();
		std::cout << "ディーラーの得点は" << dealer.hand().calcPoint() << "です" << std::endl;
	}
	if (doesBust(dealer.hand())) {
		std::cout << "ディーラーはバストしました" << std::endl;
	}

	// 結果表示
	MatchResult result = checkResult(player.hand(), dealer.hand());
	switch (result)
	{
	case MatchResult::Win:
		std::cout << "★あなたの勝ち★" << std::endl;
		break;
	case MatchResult::Lose:
		std::cout << "▼あなたの負け▼" << std::endl;
		break;
	case MatchResult::Draw:
		std::cout << "=引き分けです=" << std::endl;
		break;
	}

    return 0;
}



void init(Deck &deck, Player &player, Dealer &dealer)
{
	Card drawnCard;

	// プレイヤーに2枚配る
	for (int i = 0; i < 2; i++) {
		player.draw();
	}

	// ディーラーに2枚配る(1枚目だけ表示する)
	// 1枚目
	dealer.draw();
	dealer.showLast();

	// 2枚目
	dealer.draw();
}

bool doesBust(Hand hand)
{
	return hand.calcPoint() > 21;
}

MatchResult checkResult(Hand &playerHand, Hand &dealerHand)
{
	// 自分がバストした場合は、ディーラーの得点によらず負け
	if (doesBust(playerHand)) {
		return MatchResult::Lose;
	}

	// (自分がバストせず)ディーラーがバストした場合は、ディーラーの得点によらず勝ち
	if (doesBust(dealerHand)) {
		return MatchResult::Win;
	}

	// 自分もディーラーもバストしていない場合は、
	// 自分の得点がディーラーより高ければ勝ち、低ければ負け、同じなら引き分け
	if (playerHand.calcPoint() > dealerHand.calcPoint()) {
		return MatchResult::Win;
	}
	else if (playerHand.calcPoint() < dealerHand.calcPoint()) {
		return MatchResult::Lose;
	}
	else {
		return MatchResult::Draw;
	}
}