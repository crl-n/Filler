import sys
import os
import time
from multiprocessing.pool import ThreadPool
import multiprocessing as mp
import pandas as pd

# TODO: 
# Add error handling for when players fail to finish a game.
# Figure out if virtual machine can be modified to speed up games
# Create folder for log files and implement logging of dataframe.

# Configurations
opponents = ['champely.filler',
             'carli.filler',
             'abanlin.filler',
             'grati.filler',
             'hcao.filler',
             'superjeannot.filler']
maps = ['map00', 'map01']                           # <-- Add map02 here if needed
resources_path = './resources'              # <-- Modify this to where your local resources_filler directory resides
timeout = 5                                         # <-- Filler_vm timeout can be set here
GAMES_PER_OPPONENT = 1                              # <-- The amount of games per opponent-map combination can be configured here

N_OF_TESTS = len(maps) * len(opponents) * GAMES_PER_OPPONENT
BOLD = '\033[1m'
RESET = '\033[0m'
filler_vm = '{}/filler_vm'.format(resources_path)

def get_result(p):
    for i in range(7):
        line = p.readline()
    line = p.readline()
    o_result = int(line.split(':')[1])
    line = p.readline()
    x_result = int(line.split(':')[1])
    return (o_result, x_result)

def call_proc(args):
    filler_vm, player_binary, opponent_binary, opponent, mapfile, m = args
    p = os.popen('{} -q -p1 {} -p2 {} -f {} -t {}'.format(filler_vm, player_binary, opponent_binary, mapfile, timeout))
    return (p, (opponent, m))

def main():

    if len(sys.argv) != 2:
        print('Usage: python3 {} [filler.player]'.format(sys.argv[0]))
        return

    player_binary = sys.argv[1]
    if player_binary.startswith('./') is False:
        player_binary = './' + player_binary
    player = player_binary.lstrip('./')

    if not os.path.exists(player_binary):
        print('Error: The player binary does not exist')
        return

    main_df = pd.DataFrame(columns = ['Player', 'Opponent', 'Player Score', 'Opponent Score', 'Map'])

    pool = ThreadPool(mp.cpu_count())
    tests = []

    start = time.time()

    print(BOLD + 'Running matches... Please wait.' + RESET)

    for opponent in opponents:
        opponent_binary = '{}/players/{}'.format(resources_path, opponent)
        for m in maps:
            mapfile = '{}/maps/{}'.format(resources_path, m)
            for i in range(GAMES_PER_OPPONENT):
                tests.append((filler_vm, player_binary, opponent_binary, opponent, mapfile, m))
                results = pool.map_async(call_proc, tests)

    pool.close()
    pool.join()

    for r in results.get():
        p, args = r
        o, x = get_result(p)
        opponent, m = args
        round_data = {'Player' : player, 'Opponent' : opponent, 'Player Score' : o, 'Opponent Score' : x, 'Map':m}
        main_df = pd.concat([main_df, pd.DataFrame([round_data])], ignore_index=True, axis = 0)

    end = time.time()

    print('Execution time: {:.3f} seconds'.format(end - start))
    print(BOLD + 'Aggregate results' + RESET)

    main_df['Win'] = (main_df['Player Score'] > main_df['Opponent Score'])

    aggregate_df = (main_df.groupby(['Opponent', 'Map'])
                            .agg({'Player Score':'mean', 'Opponent Score':'mean', 'Win':'sum'})
                            .rename(columns={'Player Score':'Avg. Player Score', 'Opponent Score':'Avg. Opponent Score', 'Win':'Matches Won'}))

    print(aggregate_df)

    print('Show more info? [y/n]', end='')

    if input() == 'y':
        print(BOLD + 'Full results' + RESET)
        print(main_df)
    

if __name__ == '__main__':
    main()
