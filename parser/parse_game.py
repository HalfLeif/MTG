import collections
import csv
import sys

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

                cardname = k.removeprefix('drawn_')
                self.total_played[cardname] += drawn
                if won:
                    self.wins[cardname] += drawn

def main():
    file='data/mom/TradSealed.csv'
    args = sys.argv[1:]
    if len(args) > 1:
      print(f'Got more arguments than expected: {len(args)}')
    if len(args) > 0:
      file = args[0]

    counts = Counts()
    with open(file, 'r') as f:
        reader = csv.DictReader(f)
        for row in reader:
            counts.add_game(row)
            # if counts.num_games > 100: break

        print(f'#games: {counts.num_games}')
        for cardname in counts.total_played:
            print(f'win rate: {cardname} {counts.wins[cardname]} / {counts.total_played[cardname]}')
            break

main()
