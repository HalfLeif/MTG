import collections
import csv
import sys

import cardlist
import save

# Data from https://www.17lands.com/public_datasets


class CountsFilter:

    def __init__(self):
        self.header = []
        self.indexes = []
        self.num_games = 0


    def set_header(self, row):
        for i, field in enumerate(row):
            if field in ['won']:
                self.header.append(field)
                self.indexes.append(i)
            elif field.startswith('drawn_'):
                cardname = cardlist.normalize_name(field.removeprefix('drawn_'))
                self.header.append(cardname)
                self.indexes.append(i)
        return self.header


    def generate(self, rows):
        for row in rows:
            # if self.num_games > 100: break
            if len(self.header) == 0:
                yield self.set_header(row)
            else:
                yield self.add_game(row)


    def add_game(self, row):
        self.num_games += 1
        if self.num_games % 1000 == 0:
            print(f'Processed {self.num_games}...', flush=True)

        return [row[x] for x in self.indexes]


def WriteRows(rows, filename):
    with open(filename, 'w') as ofile:
        writer = csv.writer(ofile, dialect=save.SemiColonDialect())
        num_written = 0
        for row in rows:
            writer.writerow(row)
            num_written += 1
        print('')
        print(f'Successfully wrote {num_written} rows to {filename}')


def main():
    for filename in [
        'data/mom/inputcsv/TradSealed.csv',
        'data/mom/inputcsv/Sealed.csv',
        'data/mom/inputcsv/TradDraft.csv',
        'data/mom/inputcsv/PremierDraft.csv',
    ]:
        with open(filename, 'r') as f:
            counts = CountsFilter()
            reader = csv.reader(f)
            rows = counts.generate(reader)
            ofilename = filename.replace('inputcsv', 'outputcsv')
            WriteRows(rows, ofilename)

    # rows = CleanCounts()
    # ReadCounts(counts, )
    # ReadCounts(counts, 'data/mom/inputcsv/Sealed.csv')




main()
