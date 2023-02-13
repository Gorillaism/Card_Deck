from deck import Deck, Card


def test_card_init():
    # Test creating a card to see if the card is correctly created
    c = Card(5, 'Hearts')
    assert c.rank == 5
    assert c.suite == 'Hearts'

    print('Passed card init test')


def test_card_operators():
    # Test comparing card rank to see if the operators are functioning correctly
    c1 = Card(5, 'Hearts')
    c2 = Card(5, 'Spades')
    c3 = Card(4, 'Clubs')
    assert c1 == c2
    assert c3 < c1
    assert c1 != c3
    assert c2 > c3

    print('Passed card operators test')


def test_deck_init_len():
    # Test creating card deck to see if the right amount of cards are created
    # and if len function returns the right amount of cards
    d = Deck()
    assert len(d) == 55

    print('Passed deck init and len test')


def test_deck_sort():
    # Test sorting the card deck to see if the deck is sorted successfully
    d = Deck()
    d.sort()
    assert d.cards[1].rank == 0
    assert d.cards[4].rank == 1
    assert d.cards[53].rank == 13

    print('Passed deck sort test')


def test_deck_take():
    # Test taking cards from the top of the card deck to see if it is taking the correct card
    d = Deck()
    assert d.take().rank == 0
    d.sort()
    assert d.take().rank == 13
    assert len(d) == 53

    print('Passed deck take test')


def test_deck_put():
    # Test putting cards on top of the card deck to see if it is putting in the right cards
    d = Deck()
    c1 = Card(5, 'Hearts')
    c2 = Card(5, 'Spades')
    c3 = Card(4, 'Clubs')
    d.put(c1)
    d.put(c2)
    d.put(c3)
    assert d.take().rank == 4
    assert d.take().rank == 5
    assert d.take().rank == 5
    assert len(d) == 55

    print('Passed deck put test')


def test_deck_insert():
    # Test inserting cards in to a list
    test = []
    d = Deck()
    d.insert(test, d.take())
    assert len(test) == 1
    assert test[0].rank == 0
    d.sort()
    d.insert(test, d.take())
    assert len(test) == 2
    assert test[1].rank == 13

    print('Passed deck insert test')


def test_deck_remove_joker():
    # Test removing jokers to see if the jokers at the end of the decks are removed successfully
    d = Deck()
    assert len(d) == 55
    d.remove_jokers()
    assert len(d) == 52
    assert d.take().rank != 0

    print('Passed deck remove joker test')


def test_deck_remove_duplicates():
    # Test removing duplicates to see if any duplicates is found and removed successfully
    d = Deck()
    test = d.remove_duplicates()
    assert len(d) == 55
    assert len(test) == 0
    c = Card(5, 'Hearts')
    d.put(c)
    assert len(d) == 56
    test = d.remove_duplicates()
    assert len(d) == 55
    assert len(test) > 0

    print('Passed deck remove duplicates test')


def test_deck_pick_by_random():
    # Test picking a random card out of the deck and check if the card is picked out successfully
    d = Deck()
    assert len(d) == 55
    c1 = d.pick_by_random()
    assert len(d) == 54
    assert c1.rank >= 0
    c2 = d.pick_by_random()
    assert len(d) == 53
    assert c2.rank >= 0

    print('Passed deck pick by random test')


def test_deck_sort_by_value():
    # Test sorting the deck by value and checking if the deck is sorted successfully
    d = Deck()
    d.sort_by_value()
    c = d.cards[3]
    assert c.rank == 1
    assert c.suite == 'Hearts'
    c = d.cards[7]
    assert c.rank == 2
    assert c.suite == 'Hearts'
    c = d.cards[19]
    assert c.rank == 5
    assert c.suite == 'Hearts'

    print('Passed deck sort by value test')


def test_deck_sort_by_suit():
    # Test sorting the deck by suit and checking if the deck is sorted successfully
    d = Deck()
    d.sort_by_suit()
    c = d.cards[0]
    assert c.rank == 1
    assert c.suite == 'Hearts'
    c = d.cards[2]
    assert c.rank == 3
    assert c.suite == 'Hearts'
    c = d.cards[13]
    assert c.rank == 1
    assert c.suite == 'Diamonds'

    print('Passed deck sort by suit test')


def test_deck_deal():
    # Test dealing out cards to players to see if the cards are dealt out equally
    d1 = Deck()
    d1.deal(5)
    assert len(d1) == 0
    d2 = Deck()
    d2.deal(4)
    assert len(d2) > 0

    print('Passed deck deal test')


def run_all_card_test():
    # Run all test functions for Card
    print('---------------------\nTesting Card\n---------------------')
    test_card_init()
    test_card_operators()
    print('---------------------\nAll card test passed\n---------------------')


def run_all_deck_test():
    # Run all test functions for Deck
    print('---------------------\nTesting Deck\n---------------------')
    test_deck_init_len()
    test_deck_sort()
    test_deck_take()
    test_deck_put()
    test_deck_insert()
    test_deck_remove_joker()
    test_deck_remove_duplicates()
    test_deck_pick_by_random()
    test_deck_sort_by_value()
    test_deck_sort_by_suit()
    test_deck_deal()
    print('---------------------\nAll deck test passed\n---------------------')


def run_all_test():
    # Run all test functions
    run_all_card_test()
    run_all_deck_test()


if __name__ == '__main__':
    # Run all the test and if it passes, print out that it passes
    # if any test does not pass, it will not print out the test that fails and will stop the whole process
    run_all_test()
