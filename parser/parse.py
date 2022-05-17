import cardlist
import order
import save
import sys

DEBUG = True
SEASON = 'snc'

def join_cards(cards, ordinals):
    d = {}
    for c in cards:
        d[c.name] = c

    for name, ordinal in ordinals:
        if name not in d:
            print(f'ERROR: Ordinal card not found in card list: {name}')
        else:
            d[name].order = ordinal

def main():
    global SEASON
    args = sys.argv[1:]
    if len(args) > 1:
      print(f'Got more arguments than expected: {len(args)}')
    if len(args) > 0:
      SEASON = args[0]

    cards = list(cardlist.read_cards(f'data/{SEASON}/cards.html'))
    print(f'Found {len(cards)} cards')
    ordinals = order.read_order(f'data/{SEASON}/order.html')
    join_cards(cards, ordinals)
    save.save_cards(cards, f'data/{SEASON}/cards.csv')

main()
