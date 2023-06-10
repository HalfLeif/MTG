import collections
import csv
import sys

def main():
    file='data/mom/TradSealed.csv'
    args = sys.argv[1:]
    if len(args) > 1:
      print(f'Got more arguments than expected: {len(args)}')
    if len(args) > 0:
      file = args[0]

    with open(file, 'r') as f:
        reader = csv.DictReader(f)

        wins = collections.defaultdict(int)
        total_played = collections.defaultdict(int)
        num_games = 0
        for d in reader:
            won = d['won']
            for k in d:
                if k.startswith('drawn_') and int(d[k]) > 0:
                    cardname = k.removeprefix('drawn_')
                    total_played[cardname] += int(d[k])
                    if won == 'True':
                        wins[cardname] += int(d[k])

            num_games +=1

        print(f'#games: {num_games}')
        for cardname in total_played:
            print(f'win rate: {cardname} {wins[cardname]} / {total_played[cardname]}')
            break

main()
