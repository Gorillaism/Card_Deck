import random


class Card:
    def __init__(self, rank: int, suite: str):
        self.rank = rank  # 1-13
        self.suite = suite  # Hearts, Diamonds, Spades, Clubs

    def __str__(self):
        """ Make a string from the card's rank and suite. E.g. 5 of Clubs will be '5C'"""
        r = self.rank
        str_r = None

        if r == 1:
            str_r = 'A'
        elif r == 11:
            str_r = 'J'
        elif r == 12:
            str_r = 'Q'
        elif r == 13:
            str_r = 'K'
        else:
            str_r = str(r)

        if self.suite == 'Joker':
            return self.suite
        else:
            return f'{str_r}{self.suite[0].upper()}'

    def __repr__(self):
        return self.__str__()

    def __eq__(self, other):
        """ Compare if this card and 'other' card has the same rank """
        if not isinstance(other, Card):
            return False
        return self.rank == other.rank

    def __lt__(self, other):
        """ Compare if the rank of this card is lower than 'other' """
        if not isinstance(other, Card):
            return False
        return self.rank < other.rank

    def __gt__(self, other):
        """ Compare if the rank of this card is higher than 'other' """
        return other.rank < self.rank  # Just invert the check


class Deck:
    def __init__(self):
        """ Create a deck of 52 cards """

        self.cards = []

        for suite in ['Hearts', 'Diamonds', 'Spades', 'Clubs']:
            for rank in range(1, 14):
                self.cards.append(Card(rank, suite))

        jokes = 0

        while jokes < 3:
            self.cards.append(Card(0, 'Joker'))
            jokes = jokes + 1

    def __str__(self):
        return str(self.cards)

    def __repr__(self):
        return self.__str__()

    def __len__(self):
        return len(self.cards)

    def shuffle(self):
        random.shuffle(self.cards)

    @staticmethod
    def insert(card_list, card):
        """ Inserts a 'card' in the correct spot in the deck 'card_list' """

        added = False
        i = 0
        if len(card_list) == 0:
            card_list.append(card)
            added = True
        else:
            while i < len(card_list):
                if (card > card_list[i]):
                    i = i + 1
                    continue
                card_list.insert(i, card)
                added = True
                break
        if added is False:
            card_list.append(card)

        return card_list

    def sort(self):
        """ Sort the deck according to card rank. All aces, the all two's, then all threes, ... """

        sorted_deck = []  # Create a temporary deck

        while len(self.cards) > 0:
            # Go through the deck from left to right, insert the deck in the appropriate spot
            # Take a card from the old deck, insert it into the new one
            self.insert(sorted_deck, self.take())

        # Replace the old (empty) deck with the new (sorted) one
        self.cards = sorted_deck

    def take(self):
        """ Take the top card from the deck """
        return self.cards.pop()

    def put(self, card):
        """ Put a card on top of the deck """
        self.cards.append(card)

    def python_sort(self):
        self.cards.sort()

    def remove_jokers(self):
        joker = Card(0, 'Joker')
        joker_count = self.cards.count(joker)

        while joker_count != 0:
            self.cards.remove(joker)
            joker_count = joker_count - 1

    def remove_duplicates(self):
        tracker = []

        for x in range(len(self.cards)):
            for y in range(x+1, len(self.cards)):
                if self.cards[x] == self.cards[y] and self.cards[x].suite == self.cards[y].suite and self.cards[x].suite != 'Joker':
                    tracker.append(y)
                    break

        tracker.reverse()
        for x in range(len(tracker)):
            self.cards.pop(tracker[x])

        return tracker

    def sort_by_suit(self):
        sorted_suit = []

        for suite in ['Hearts', 'Diamonds', 'Spades', 'Clubs', 'Joker']:
            for rank in range(0, 14):
                for x in range(len(self.cards)):
                    if self.cards[x].rank == rank and self.cards[x].suite == suite:
                        sorted_suit.append(self.cards[x])

        self.cards = sorted_suit

    def sort_by_value(self):
        sorted_value = []

        for rank in range(0, 14):
            for suite in ['Joker', 'Hearts', 'Diamonds', 'Spades', 'Clubs']:
                for x in range(len(self.cards)):
                    if self.cards[x].rank == rank and self.cards[x].suite == suite:
                        sorted_value.append(self.cards[x])

        self.cards = sorted_value

    def pick_by_random(self):
        random_pick = random.randint(0, len(self.cards))
        return self.cards.pop(random_pick)

    def deal(self, players):
        piles = []
        for i in range(players):
            piles.append([])
        while len(self.cards) >= players:
            for j in range(players):
                piles[j].append(self.take())

        # Commented for testing purposes
        # Uncomment lines below to see the players hands and what was dealt to them

        #for x in range(len(piles)):
        #    print('Player', x+1, ':', str(piles[x]))


if __name__ == '__main__':
    deck = Deck()
    print('Fresh deck:', deck)
    deck.shuffle()
    print('Shuffled deck:', deck)
    deck.sort_by_suit()
    print('Sorted deck:', deck)
    deck.put(Card(5, 'Hearts'))
    deck.put(Card(5, 'Hearts'))
    deck.put(Card(5, 'Hearts'))
    deck.put(Card(7, 'Hearts'))
    deck.sort_by_value()
    print('Sorted deck:', deck)
    deck.remove_duplicates()
    deck.shuffle()
    print('Shuffled deck:', deck)
    deck.python_sort()
    print('Python Sorted deck:', deck)
    deck.deal(5)
