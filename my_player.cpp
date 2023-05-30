#include <string>
#include "my_player.h"
#include "card.h"
using namespace std;
#pragma warning(disable:4996)
SimplePlayer::SimplePlayer(std::string const & name)
{
	this->m_name = name;
}

SimplePlayer::~SimplePlayer()
{
}

string SimplePlayer::name() const
{
	return this->m_name;
}

void SimplePlayer::receiveCards(const std::vector<const Card*>& cards)
{
    if (cards.size() == 7)
    { 
        this->cards.clear(); //чистим чтобы снова заполнить новыми картами
    }
    for (const Card* card : cards)
    {
        this->cards.push_back(card); //заполняем cards картами (каждая новая помещается в конец)
    }
}

const Card* SimplePlayer::playCard()
{
	const Card* current_card = game()->topCard();
	const Card* card = nullptr;

	if (!current_card->is_wild())
	{
		for (const Card* cur_card : this->cards)
		{
			if (haveColour(cur_card) or haveScale(cur_card))
			{
				card = cur_card;
				break;
			}
			else if (cur_card->is_wild())
			{
				if (Draw4(cur_card))
				{
					card = cur_card; break;
				}
			}
		}
	}
	else if (current_card->is_wild())
	{
		const CardColor currentcolor = this->game()->currentColor();
		for (const Card* cur_card : this->cards)
		{
			if (haveColour(cur_card))
			{
				card = cur_card;
			}
			else if (cur_card->is_wild())
			{
				if (Draw4(cur_card))
				{
					card = cur_card; break;
				}
			}
		}
	}
	int i = 0;
	auto iter = this->cards.cbegin();
	for (const Card* cur_card : this->cards)
	{
		if (card != nullptr and cur_card->color == card->color and cur_card->value == card->value)
		{
			this->cards.erase(iter + i);
			break;
		}
		i++;
	}


	return card;
}

bool SimplePlayer::haveColour(const Card* current_card) const // смотрим есть ли карты цвета
{

		if (!(current_card->is_wild()) and (current_card->color == game()->currentColor())) return true;
	return false;
}

bool SimplePlayer::haveScale(const Card* current_card) const // смотрим есть ли карты цифр
{

		if (!(current_card->is_wild()) and (current_card->value == game()->topCard()->value)) return true;
	return false;
}
//
//bool SimplePlayer::haveActives(const Card* current_card)  const //смотрим карты действий нужного цвета
//{
//
//		if ((current_card->color == game()->currentColor()) and (current_card->is_action())) return true;
//	return false;
//}
//
//bool SimplePlayer::haveOrdinary(const Card* current_card) const // смотрим есть ли в руке цвета циферок
//{
//
//		if ((current_card->color == game()->currentColor()) and (!current_card->is_action()) and (!current_card->is_wild())) return true;
//	return false;
//}

bool SimplePlayer::Draw4(const Card* current_card) const
{

		if (current_card->value == WildDraw4)
		{
			for (const Card* cr : this->cards)
			{
				if (cr->color == this->game()->currentColor() and !cr->is_wild()) { return false; }
			}
		}
		return true;
}
bool SimplePlayer::drawAdditionalCard(const Card* additionalCard)
{
	const Card* current_card = this->game()->topCard();
	if (haveColour(additionalCard) or haveScale(additionalCard)) {
		return true;
	}

	else if (additionalCard->is_wild())
	{
		if (Draw4(additionalCard))
		{
			return true;
		}
	}

	this->cards.push_back(additionalCard);
	return false;
}


CardColor SimplePlayer::changeColor()
{
	srand(time(NULL));

	int min = 0;
	int max = 3;
	int num = min + rand() % (max);

	return CardColor(num);

}

Player::Player(std::string const& name)
{
	this->m_name = name;
}
Player::~Player()
{
}

string Player::name() const
{
	return this->m_name;
}

void Player::receiveCards(const std::vector<const Card*>& cards)
{
	if (cards.size() == 7)
	{
		this->cards.clear(); //чистим чтобы снова заполнить новыми картами
	}
	for (const Card* card : cards)
	{
		this->cards.push_back(card); //заполняем cards картами (каждая новая помещается в конец)
	}
}

const Card* Player::playCard()
{
	const Card* current_card = game()->topCard();
	const Card* card = nullptr;

	if (!current_card->is_wild())
	{
		int maxcard = 0;
		for (const Card* cur_card : this->cards)
		{
			if (haveColour(cur_card) or haveScale(cur_card))
			{
				if (haveColour(cur_card) and haveNull(cur_card)) { card = cur_card; break; }
				else { 
					if (cur_card->value > maxcard) {
						maxcard = cur_card->value;
						card = cur_card;
					}
				}
			}
			else if (cur_card->is_wild())
			{
				if (Draw4(cur_card))
				{
					card = cur_card; break;
				}
			}
		}
	}
	else if (current_card->is_wild())
	{
		const CardColor currentcolor = this->game()->currentColor();
		for (const Card* cur_card : this->cards)
		{
			if (haveColour(cur_card))
			{
				card = cur_card;
			}
			else if (cur_card->is_wild())
			{
				if (Draw4(cur_card))
				{
					card = cur_card; break;
				}
			}
		}
	}
	int i = 0;
	auto iter = this->cards.cbegin();
	for (const Card* cur_card : this->cards)
	{
		if (card != nullptr and cur_card->color == card->color and cur_card->value == card->value)
		{
			this->cards.erase(iter + i);
			break;
		}
		i++;
	}


	return card;
}

bool Player::haveColour(const Card* current_card) const // смотрим есть ли карты цвета
{

	if (!(current_card->is_wild()) and (current_card->color == game()->currentColor())) return true;
	return false;
}

bool Player::haveScale(const Card* current_card) const // смотрим есть ли карты цифр
{

	if (!(current_card->is_wild()) and (current_card->value == game()->topCard()->value)) return true;
	return false;
}

bool Player::haveNull(const Card* current_card) const // смотрим есть ли карты цифр
{

	if (!(current_card->is_wild()) and (current_card->value == 0)) return true;
	return false;
}

//
//bool SimplePlayer::haveActives(const Card* current_card)  const //смотрим карты действий нужного цвета
//{
//
//		if ((current_card->color == game()->currentColor()) and (current_card->is_action())) return true;
//	return false;
//}
//
//bool SimplePlayer::haveOrdinary(const Card* current_card) const // смотрим есть ли в руке цвета циферок
//{
//
//		if ((current_card->color == game()->currentColor()) and (!current_card->is_action()) and (!current_card->is_wild())) return true;
//	return false;
//}

bool Player::Draw4(const Card* current_card) const
{

	if (current_card->value == WildDraw4)
	{
		for (const Card* cr : this->cards)
		{
			if (cr->color == this->game()->currentColor() and !cr->is_wild()) { return false; }
		}
	}
	return true;
}

bool Player::drawAdditionalCard(const Card* additionalCard)
{
	const Card* current_card = this->game()->topCard();
	if (haveColour(additionalCard) or haveScale(additionalCard)) {
		return true;
	}

	else if (additionalCard->is_wild())
	{
		if (Draw4(additionalCard))
		{
			return true;
		}
	}

	this->cards.push_back(additionalCard);
	return false;
}


CardColor Player::changeColor()
{
	int red = 0;
	int blue = 0;
	int green = 0;
	int yellow = 0;
	for (const Card* cur_card : this->cards)
		{
		int num = cur_card->color;
		switch (num) {
		case 0:
			red++;
			break;
		case 1:
			green++;
			break;
		case 2:
			blue++;
			break;
		default:
			yellow++;
			break;
		}

	}
	int col = std::max({ red, blue, green, yellow });
	if (col = red) {
		return CardColor(0);
	}
	else if (col = green) {
		return CardColor(1);
	}
	else if (col = blue) {
		return CardColor(2);
	}
	else {
		return CardColor(3);
	}

}
