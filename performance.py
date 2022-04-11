import sys
import os
import time
from multiprocessing.pool import ThreadPool
import multiprocessing as mp
import pandas as pd

# TODO: Add error handling for when players fail to finish a game.
             #'grati.filler',
opponents = ['champely.filler',
             'hcao.filler',
             'carli.filler',
             'abanlin.filler',
             'superjeannot.filler']
maps = ['map00', 'map01', 'map02']
GAMES_PER_OPPONENT = 5
N_OF_TESTS = len(maps) * len(opponents) * GAMES_PER_OPPONENT
BOLD = '\033[1m'
RESET = '\033[0m'

def get_result(p):
    for i in range(7):
        p.readline()
    o_result = int(p.readline().split(':')[1])
    x_result = int(p.readline().split(':')[1])
    return (o_result, x_result)

def call_proc(args):
    filler_vm, player_binary, opponent_binary, opponent, mapfile, m = args
    p = os.popen('{} -q -p1 {} -p2 {} -f {}'.format(filler_vm, player_binary, opponent_binary, mapfile))
    return (p, (opponent, m))

def main():

    if len(sys.argv) != 2:
        print('Usage: python3 {} [filler.player]'.format(sys.argv[0]))
        return

    player_binary = sys.argv[1]
    if player_binary.startswith('./') is False:
        player_binary = './' + player_binary
    player = player_binary.lstrip('./')

    resources_path = '../resources_filler'
    filler_vm = '{}/filler_vm'.format(resources_path)

    df = pd.DataFrame(columns = ['Player', 'Opponent', 'Player Score', 'Opponent Score', 'Map'])

    start = time.time()
    print(BOLD + 'Running matches... Please wait.' + RESET)
    pool = ThreadPool(mp.cpu_count())
    tests = []
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
        d = {'Player' : player, 'Opponent' : opponent, 'Player Score' : o, 'Opponent Score' : x, 'Map':m}
        df = pd.concat([df, pd.DataFrame([d])], ignore_index=True, axis = 0)

    end = time.time()

    print(df)
    print('Execution time: {}'.format(end - start))
    
    # TODO: Figure out if virtual machine can be modified to speed up games
    # TODO: Plot/report results
    # TODO: Create folder for log files and implement logging of dataframe.
    #log = 'performance_log_{}'.format(time.strftime('%d%m%Y-%H%M', time.localtime()))

if __name__ == '__main__':
    main()
