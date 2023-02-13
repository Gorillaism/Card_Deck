#include "deck.h"
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <random>
#include <chrono>

using namespace std;

/**
 * Help function to convert Suit enum to string
 */
const string SuitToString(Suit s)
{
    switch (s)
    {
    case Suit::Hearts:
        return "H";
    case Suit::Diamonds:
        return "D";
    case Suit::Spades:
        return "S";
    case Suit::Clubs:
        return "C";
    case Suit::Joker:
        return "Joker";
    }
    return "";
}

Card::Card(int rank, Suit suit)
{
    this->rank = rank;
    this->suit = suit;
}

/**
 * Overload of << operator for Card class
 */
ostream &operator<<(ostream &out, const Card &c)
{
    string r;
    switch (c.rank)
    {
    case 0:
        r = "";
        break;
    case 1:
        r = 'A';
        break;
    case 11:
        r = 'J';
        break;
    case 12:
        r = 'Q';
        break;
    case 13:
        r = 'K';
        break;
    default:
        r = to_string(c.rank);
        break;
    }

    out << r << SuitToString(c.suit);

    return out;
}

/**
 * Create a deck of 55 cards
 */
Deck::Deck()
{
    for (Suit s = Suit::Hearts; s <= Suit::Clubs; s = Suit(s + 1))
    {
        for (int r = 1; r < 14; r++)
        {
            cards.push_back(Card(r, s));
        }
    }
    for (int i = 0; i < 3; i++)
    {
        cards.push_back(Card(0, Joker));
    }
}

/**
 * Overload of << operator for Deck class
 */
ostream &operator<<(ostream &out, const Deck &d)
{
    string separator;
    for (auto i : d.cards)
    {
        out << separator << i;
        separator = ", ";
    }

    return out;
}

/**
 * Return number of cards in deck
 */
int Deck::size()
{
    return this->cards.size();
}

/**
 * Shuffle all the cards in deck in ranom order.
 */
void Deck::shuffle()
{
    auto rng = std::default_random_engine(std::chrono::system_clock::now().time_since_epoch().count());
    std::shuffle(this->cards.begin(), this->cards.end(), rng);
}

/**
 * Sort the deck according to card rank. All aces, the all two's, then all threes, ...
 */
void Deck::sort()
{
    vector<Card> sorted_cards; // Empty temporary deck

    while (this->size() > 0)
    {
        // Go through the deck from left to right, insert the deck in the appropriate spot
        Deck::insert(sorted_cards, this->take()); // Take a card from the old deck, insert it into the new one
    }

    this->cards = sorted_cards;
}

/**
 * Take the top card from the deck
 */
Card Deck::take()
{
    Card c = this->cards.back();
    this->cards.pop_back();
    return c;
}

/**
 * Put a card on top of the deck
 */
void Deck::put(Card card)
{
    cards.push_back(card);
}

/**
 *  Insert Card in order
 */
void Deck::insert(vector<Card> &cardlist, Card card)
{
    bool added = false;
    if (cardlist.size() == 0)
    {
        cardlist.push_back(card);
        added = true;
    }
    else
    {
        for (int i = 0; i < cardlist.size(); i++)
        {
            if (card > cardlist[i])
            {
                continue;
            }
            cardlist.insert(cardlist.begin() + i, card);
            added = true;
            break;
        }
    }

    if (!added)
    {
        cardlist.push_back(card);
    }
    return;
}

/**
 * Remove Joker from deck
 */
void Deck::remove_jokers()
{
    Card temp(0, Joker);
    vector<int> tracker;
    int i = 0;
    for (auto c : this->cards)
    {
        if (c == temp)
        {
            tracker.push_back(i);
        }
        i++;
    }

    reverse(tracker.begin(), tracker.end());
    for (auto c : tracker)
    {
        this->cards.erase(this->cards.begin() + c);
    }
}

/**
 * Remove duplicates
 * @return vector<int>
 */
vector<int> Deck::remove_duplicates()
{
    vector<int> tracker;
    for (int i = 0; i < cards.size(); i++)
    {
        for (int j = i + 1; j < cards.size(); j++)
        {
            if (cards[i] == cards[j] && cards[i].get_suit() == cards[j].get_suit() && cards[i].get_suit() != Suit::Joker)
            {
                if (tracker.size() > 0)
                {
                    if (find(tracker.begin(), tracker.end(), j) != tracker.end())
                    {
                        tracker.push_back(j);
                    }
                }
                else
                {
                    tracker.push_back(j);
                }
            }
        }
    }
    reverse(tracker.begin(), tracker.end());
    for (auto t : tracker)
    {
        cards.erase(cards.begin() + t);
    }
    return tracker;
}

/**
 * Sort by Suit
 */
void Deck::sort_by_suit()
{
    vector<Card> sortedSuits;

    for (Suit s = Suit::Hearts; s <= Suit::Joker; s = Suit(s + 1))
    {
        for (int r = 0; r < 14; r++)
        {
            for (auto c : cards)
            {
                if (c.get_rank() == r && c.get_suit() == s)
                {
                    sortedSuits.push_back(c);
                }
            }
        }
    }
    this->cards = sortedSuits;
}

/**
 * Sort by Value
 */
void Deck::sort_by_value()
{
    vector<Card> sortedValue;

    for (int r = 0; r < 14; r++)
    {
        for (Suit s = Suit::Hearts; s <= Suit::Joker; s = Suit(s + 1))
        {
            for (auto c : cards)
            {
                if (c.get_rank() == r && c.get_suit() == s)
                {
                    sortedValue.push_back(c);
                }
            }
        }
    }
    this->cards = sortedValue;
}

/**
 * Pick a card out of the deck by random
 * @return Card that was picked out
 */
Card Deck::pick_by_random()
{
    srand(std::chrono::system_clock::now().time_since_epoch().count());
    int random = rand() % cards.size();
    Card temp = cards[random];
    cards.erase(cards.begin() + random);
    return temp;
}

/**
 * Getter for deck vector
 * @return Deck vector
 */
vector<Card> Deck::get_cards()
{
    return this->cards;
}

/**
 * Setter for deck vector
 * @param list Vector to be set
 */
void Deck::set_cards(vector<Card> list)
{
    this->cards = list;
}

/**
 * Deal out cards to players in equal amount
 * @param n Number of players
 */
void Deck::deal(int n)
{
    vector<vector<Card>> players(n);
    int count = 1;

    while (cards.size() >= n)
    {
        for (int i = 0; i < n; i++)
        {
            players[i].push_back(this->take());
        }
    }

    // Commented for testing purposes
    // Uncomment lines below to see the players hands and what was dealt to them
    /*
    for (vector<Card> vect1D : players)
    {
        string separator;
        cout << "Player " << count << ": ";
        for (auto i : vect1D)
        {
            cout << separator << i;
            separator = ", ";
        }
        cout << endl;
        count++;
    }*/
}
