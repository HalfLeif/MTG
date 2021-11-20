import cardlist
import order


def join_cards(cards, ordinals):
    d = {}
    for c in cards:
        d[c.name] = c

    for name, ordinal in ordinals:
        assert name in d, name
        d[name].order = ordinal


def main():
    cards = list(cardlist.read_cards())
    ordinals = order.read_order()
    join_cards(cards, ordinals)
    filtered = filter(lambda x: x.mana, cards)
    for c in filtered:
        print(c)

main()
