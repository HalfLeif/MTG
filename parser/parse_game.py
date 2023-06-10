import collections
import csv
import sys

import cardlist
import save

class Counts:

    def __init__(self):
        self.wins = collections.defaultdict(int)
        self.total_played = collections.defaultdict(int)
        self.num_games = 0
        self.num_wins = 0

    def add_game(self, row):
        self.num_games += 1
        won = row['won'] == 'True'
        if won:
            self.num_wins += 1

        for k in row:
            if k.startswith('drawn_'):
                drawn = int(row[k])
                if drawn < 1:
                    continue

                cardname = cardlist.normalize_name(k.removeprefix('drawn_'))
                self.total_played[cardname] += drawn
                if won:
                    self.wins[cardname] += drawn


def ReadCounts(filename):
    counts = Counts()
    with open(filename, 'r') as f:
        reader = csv.DictReader(f)
        for row in reader:
            counts.add_game(row)
            # if counts.num_games > 500: break

        print(f'#games: {counts.num_games}')
        for cardname in counts.total_played:
            print(f'win rate: {cardname} {counts.wins[cardname]} / {counts.total_played[cardname]}')
            break
    return counts

def SaveCounts(counts, filename):
    num_written = 0
    with open(filename, 'w') as f:
        writer = csv.writer(f, dialect=save.SemiColonDialect())
        writer.writerow(['cardname','wins_when_played','num_played'])
        for cardname in counts.total_played:
            writer.writerow([cardname, counts.wins[cardname], counts.total_played[cardname]])
            num_written += 1
    print('')
    print(f'Successfully wrote {num_written} counts to {filename}')


def main():
    args = sys.argv[1:]
    if len(args) > 1:
      print(f'Got more arguments than expected: {len(args)}')
    if len(args) > 0:
      file = args[0]

    counts = ReadCounts('data/mom/TradSealed.csv')
    SaveCounts(counts, 'data/mom/counts.csv')


main()
