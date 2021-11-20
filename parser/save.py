import csv

import cardlist

class SemiColonDialect(csv.Dialect):
    def __init__(self):
        self.delimiter = ';'
        self.quoting = csv.QUOTE_MINIMAL
        self.quotechar = '"'
        self.lineterminator = '\n'

def save_cards(cards):
    fname = 'data/mid/cards.csv'
    count = 0
    with open(fname, 'w') as f:
        writer = csv.writer(f, dialect=SemiColonDialect())
        writer.writerow(cardlist.Card.header())
        for c in cards:
            print(c)
            writer.writerow(c.fields())
            count += 1
    print('')
    print(f'Successfully wrote {count} cards to {fname}')