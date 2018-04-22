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

void init(Deck &deck, Hand &playerHand, Hand &dealerHand);
void playDealer(Hand &dealerHand, Deck &deck);
bool doesBust(Hand hand);
MatchResult checkResult(Hand &playerHand, Hand &dealerHand);

int main(int argc, char* argv[])
{
	Deck deck;
	Hand playerHand;
	Hand dealerHand;
	bool isPlayerBurst = false;
	bool isDealerBurst = false;

	// カード配布
	init(deck, playerHand, dealerHand);

	// プレイヤーの動作
	char c;
	while (true) {
		std::cout << "今のあなたの得点は" << playerHand.calcPoint() << "です。カードを引きますか?[y/n]" << std::endl;


		std::cin >> c;
		if (c == 'y' || c == 'Y') {
			Card drawnCard = deck.draw();
			playerHand.add(drawnCard);
			std::cout << "あなたがカードを引きました" << std::endl;
			std::cout << "あなたの引いたカードは" << drawnCard << "です" << std::endl;

			if (doesBust(playerHand)) {
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
	std::cout << "ディーラーの2枚目のカードは" << dealerHand.getList().back() << "です" << std::endl;
	playDealer(dealerHand, deck);
	std::cout << "ディーラーの得点は" << dealerHand.calcPoint() << "です" << std::endl;
	if (doesBust(dealerHand)) {
		std::cout << "ディーラーはバストしました" << std::endl;
	}

	// 結果表示
	MatchResult result = checkResult(playerHand, dealerHand);
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



void init(Deck &deck, Hand &playerHand, Hand &dealerHand)
{
	Card drawnCard;

	// プレイヤーに2枚配る
	for (int i = 0; i < 2; i++) {
		drawnCard = deck.draw();
		playerHand.add(drawnCard);
		std::cout << "あなたがカードを引きました" << std::endl;
		std::cout << "あなたの引いたカードは" << drawnCard << "です" << std::endl;
	}

	// ディーラーに2枚配る(1枚目だけ表示する)
	for (int i = 0; i < 2; i++) {
		drawnCard = deck.draw();
		dealerHand.add(drawnCard);
		std::cout << "ディーラーがカードを引きました" << std::endl;
		if (i == 0) {
			std::cout << "ディーラーの引いたカードは" << drawnCard << "です" << std::endl;
		}
		else {
			std::cout << "ディーラーの2枚目のカードは分かりません" << std::endl;
		}
	}
}


void playDealer(Hand &dealerHand, Deck &deck)
{
	Card drawnCard;
	while (dealerHand.calcPoint() < 17) {
		drawnCard = deck.draw();
		dealerHand.add(drawnCard);
		std::cout << "ディーラーの引いたカードは" << drawnCard << "です" << std::endl;
	}
}

bool doesBust(Hand hand)
{
	return hand.calcPoint() > 21;
}

MatchResult checkResult(Hand &playerHand, Hand &dealerHand)
{
	// 自分がバーストした場合は、ディーラーの得点によらず負け
	if (doesBust(playerHand)) {
		return MatchResult::Lose;
	}

	// (自分がバーストせず)ディーラーがバストした場合は、ディーラーの得点によらず勝ち
	if (doesBust(dealerHand)) {
		return MatchResult::Win;
	}

	// 自分もディーラーもバートしていない場合は、
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