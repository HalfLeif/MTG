import cardlist
import order
import save

def join_cards(cards, ordinals):
    d = {}
    for c in cards:
        d[c.name] = c

    for name, ordinal in ordinals:
        assert name in d, name
        d[name].order = ordinal

DEBUG=True
SEASON='vow'

def main():
    cards = list(cardlist.read_cards(f'data/{SEASON}/cards.html'))
    print(f'Found {len(cards)} cards')
    ordinals = order.read_order(f'data/{SEASON}/order.html')
    join_cards(cards, ordinals)
    filtered = filter(lambda x: x.mana, cards)
    save.save_cards(filtered, f'data/{SEASON}/cards.csv')

main()
