#include "uno_game.h"
#pragma once
class SimplePlayer: public UnoPlayer
{
	std::string m_name;
	std::vector<const Card*> cards;
	bool haveColour(const Card* current_card) const;
	bool haveScale(const Card* current_card) const;
	//bool haveActives(const Card* current_card) const;
	//bool haveOrdinary(const Card* current_card) const;
	bool Draw4(const Card* current_card) const;
	
public:
	SimplePlayer(std::string const & name);
	~SimplePlayer();
	virtual std::string name() const;
	virtual void receiveCards(const std::vector<const Card*>& cards);
	virtual const Card* playCard();
	virtual bool drawAdditionalCard(const Card* additionalCard);
	virtual CardColor changeColor();
	

};

class Player : public UnoPlayer
{
	std::string m_name;
	std::vector<const Card*> cards;
	bool haveColour(const Card* current_card) const;
	bool haveScale(const Card* current_card) const;
	bool haveNull(const Card* current_card) const;
	//bool haveActives(const Card* current_card) const;
	//bool haveOrdinary(const Card* current_card) const;
	bool Draw4(const Card* current_card) const;

public:
	Player(std::string const& name);
	~Player();
	virtual std::string name() const;
	virtual void receiveCards(const std::vector<const Card*>& cards);
	virtual const Card* playCard();
	virtual bool drawAdditionalCard(const Card* additionalCard);
	virtual CardColor changeColor();


};