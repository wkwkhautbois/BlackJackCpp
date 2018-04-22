#pragma once
#include <ostream>
#include <string>

enum class Mark {
	Heart,
	Diamond,
	Club,
	Spade
};

class Card
{
	int _num;
	Mark _mark;

public:
	Card();
	Card(Mark mark, int number);
	virtual ~Card();
	const int number() const;
	const Mark& mark() const;
};

std::ostream& operator<<(std::ostream& os, const Mark& mark);
std::ostream& operator<<(std::ostream& os, const Card& card);

