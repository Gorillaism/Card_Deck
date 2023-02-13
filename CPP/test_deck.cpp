#include "deck.h"

#include "gtest/gtest.h"

TEST(Card, init)
{
    Card *c = new Card(4, Suit::Diamonds);
    EXPECT_EQ(c->get_rank(), 4);
    EXPECT_EQ(c->get_suit(), Suit::Diamonds);
}

TEST(Deck, init)
{
    Deck *d = new Deck();
    EXPECT_EQ(d->size(), 55);
}

TEST(Card, operators)
{
    Card c1(5, Suit::Clubs);
    Card c2(6, Suit::Diamonds);
    Card c3(5, Suit::Hearts);
    EXPECT_TRUE(c3 == c1);
    EXPECT_FALSE(c2 == c1);
    EXPECT_TRUE(c1 < c2);
    EXPECT_FALSE(c3 < c1);
    EXPECT_TRUE(c2 > c3);
    EXPECT_FALSE(c3 > c1);
}

TEST(Deck, size)
{
    Deck *d = new Deck();
    EXPECT_EQ(d->size(), 55);
}

TEST(Deck, sort)
{
    Deck *d = new Deck();
    d->sort();
    Card c = d->get_cards()[4];
    EXPECT_EQ(c.get_rank(), 1);
    c = d->get_cards()[19];
    EXPECT_EQ(c.get_rank(), 5);
    c = d->get_cards()[52];
    EXPECT_EQ(c.get_rank(), 13);
}

TEST(Deck, take)
{
    Deck *d = new Deck();
    EXPECT_EQ(d->take().get_rank(), 0);
    d->sort();
    EXPECT_EQ(d->take().get_rank(), 13);
}

TEST(Deck, put)
{
    Deck *d = new Deck();
    Card c1(5, Suit::Clubs);
    Card c2(6, Suit::Diamonds);
    Card c3(13, Suit::Hearts);
    d->put(c3);
    d->put(c2);
    d->put(c1);
    EXPECT_EQ(d->take().get_rank(), 5);
    EXPECT_EQ(d->take().get_rank(), 6);
    EXPECT_EQ(d->take().get_rank(), 13);
}

TEST(Deck, pick_by_random)
{
    Deck *d = new Deck();
    Card c1 = d->pick_by_random();
    EXPECT_TRUE(c1.get_rank() >= 0);
}

TEST(Deck, sort_by_value)
{
    Deck *d = new Deck();
    d->sort_by_value();
    Card c1 = d->get_cards()[3];
    EXPECT_EQ(c1.get_rank(), 1);
    EXPECT_EQ(c1.get_suit(), Suit::Hearts);
    c1 = d->get_cards()[4];
    EXPECT_EQ(c1.get_rank(), 1);
    EXPECT_EQ(c1.get_suit(), Suit::Diamonds);
    c1 = d->get_cards()[19];
    EXPECT_EQ(c1.get_rank(), 5);
    EXPECT_EQ(c1.get_suit(), Suit::Hearts);
}

TEST(Deck, sort_by_suit)
{
    Deck *d = new Deck();
    d->sort_by_suit();
    Card c1 = d->get_cards()[0];
    EXPECT_EQ(c1.get_rank(), 1);
    EXPECT_EQ(c1.get_suit(), Suit::Hearts);
    c1 = d->get_cards()[14];
    EXPECT_EQ(c1.get_rank(), 2);
    EXPECT_EQ(c1.get_suit(), Suit::Diamonds);
    c1 = d->get_cards()[29];
    EXPECT_EQ(c1.get_rank(), 4);
    EXPECT_EQ(c1.get_suit(), Suit::Spades);
}

TEST(Deck, remove_jokers)
{
    Deck *d = new Deck();
    d->remove_jokers();
    EXPECT_TRUE(d->take().get_rank() != 0);
    Deck *d2 = new Deck();
    d2->sort();
    d2->remove_jokers();
    Card c1 = d2->get_cards()[0];
    EXPECT_TRUE(c1.get_rank() != 0);
}

TEST(Deck, remove_duplicates)
{
    Deck *d = new Deck();
    vector<int> temp = d->remove_duplicates();
    EXPECT_TRUE(temp.size() == 0);
    Card c1(1, Suit::Diamonds);
    d->put(c1);
    temp = d->remove_duplicates();
    EXPECT_FALSE(temp.size() == 0);
}

TEST(Deck, insert)
{
    vector<Card> temp;
    Deck d;
    Deck *d2 = new Deck();
    d.insert(temp, d2->take());
    d.insert(temp, d2->take());
    d.insert(temp, d2->take());
    d.insert(temp, d2->take());
    d.insert(temp, d2->take());
    d.set_cards(temp);
    EXPECT_EQ(d.get_cards()[0].get_rank(), 0);
    EXPECT_EQ(d.get_cards()[3].get_rank(), 12);
}

TEST(Deck, deal)
{
    Deck *d = new Deck();
    Deck *d2 = new Deck();
    d->deal(4);
    EXPECT_EQ(d->size(), 3);
    d2->deal(5);
    EXPECT_EQ(d2->size(), 0);
}
