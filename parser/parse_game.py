import collections
import csv
import sys

import cardlist
import save

# Data from https://www.17lands.com/public_datasets


class Counts:

    def __init__(self):
        self.wins = collections.defaultdict(int)
        self.total_played = collections.defaultdict(int)
        self.num_games = 0
        self.num_wins = 0


    def add_game(self, row, primary_card=None):
        self.num_games += 1
        if self.num_games % 1000 == 0:
            print(f'Processed {self.num_games}...')

        won = row['won'] == 'True'
        if won:
            self.num_wins += 1

        for k in row:
            if k.startswith('drawn_'):
                drawn = int(row[k])
                if drawn < 1: continue

                cardname = cardlist.normalize_name(k.removeprefix('drawn_'))
                if cardname == primary_card: continue

                joined_key = cardname
                if primary_card:
                    # Only capture a && b, not also b && a
                    if cardname < primary_card: continue
                    joined_key = ''.join(['_2 ', cardname, ' && ', primary_card])
                else:
                    # One level of recursion to capture Count(a & b)
                    self.add_game(row, primary_card=cardname)

                self.total_played[joined_key] += drawn
                if won:
                    self.wins[joined_key] += drawn


    def as_sorted(self):
        items = []
        for cardname in self.total_played:
            items.append([cardname, self.wins[cardname], self.total_played[cardname]])
        yield ['cardname','wins_when_played','num_played']
        for item in sorted(items):
            yield item


def ReadCounts(counts, filename):
    with open(filename, 'r') as f:
        reader = csv.DictReader(f)
        for row in reader:
            counts.add_game(row)
            # if counts.num_games > 500: break

        print(f'#games: {counts.num_games}')
        for cardname in counts.total_played:
            print(f'win rate: {cardname} {counts.wins[cardname]} / {counts.total_played[cardname]}')
            break


def SaveCounts(counts, filename):
    num_written = 0
    with open(filename, 'w') as f:
        writer = csv.writer(f, dialect=save.SemiColonDialect())
        for row in counts.as_sorted():
            writer.writerow(row)
            num_written += 1
    print('')
    print(f'Successfully wrote {num_written} counts to {filename}')


def main():
    args = sys.argv[1:]
    if len(args) > 1:
      print(f'Got more arguments than expected: {len(args)}')
    if len(args) > 0:
      file = args[0]

    counts = Counts()
    ReadCounts(counts, 'data/mom/Sealed.csv')
    ReadCounts(counts, 'data/mom/TradSealed.csv')

    SaveCounts(counts, 'data/mom/counts.csv')


main()
