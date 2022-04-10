import sys
import os
import time
from multiprocessing.pool import ThreadPool
import multiprocessing as mp
from subprocess import Popen
import pandas as pd
from tqdm import tqdm

opponents = ['champely.filler',
             'hcao.filler',
             'grati.filler']
maps = ['map00', 'map01']
n_of_tests = len(maps) * len(opponents) * 5
#progress_bar = tqdm(total=n_of_tests)

def get_result(p):
    for i in range(7):
        p.readline()
    o_result = int(p.readline().split(':')[1])
    x_result = int(p.readline().split(':')[1])
    return (o_result, x_result)

def call_proc(filler_vm, player_binary, opponent_binary, opponent, mapfile, m):
    p = os.popen('{} -q -p1 {} -p2 {} -f {}'.format(filler_vm, player_binary, opponent_binary, mapfile))
    return (p, (opponent, m))

def update_prog_bar(_):
    progress_bar.update()

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
    print('Running matches... Please wait.')
    pool = ThreadPool(mp.cpu_count())
    results = []
    for opponent in opponents:
        opponent_binary = '{}/players/{}'.format(resources_path, opponent)
        for m in maps:
            mapfile = '{}/maps/{}'.format(resources_path, m)
            processes = []
            for i in range(5):
                results.append(pool.apply_async(call_proc, (filler_vm, player_binary, opponent_binary, opponent, mapfile, m)))

    pool.close()
    pool.join()

    for r in results:
        p, args = r.get()
        o, x = get_result(p)
        opponent, m = args
        d = {'Player' : player, 'Opponent' : opponent, 'Player Score' : o, 'Opponent Score' : x, 'Map':m}
        df = pd.concat([df, pd.DataFrame([d])], ignore_index=True, axis = 0)

    end = time.time()
    time.sleep(0.5)
    print(df)
    print('Execution time: {}'.format(end - start))
    
    # TODO: Make a function that extracts the match result and other relevant metrics from temp output
    # TODO: Figure out if virtual machine can be modified to speed up games
    # TODO: Plot/report results

    # TODO: Create folder for log files and implement logging of dataframe.
    #log = 'performance_log_{}'.format(time.strftime('%d%m%Y-%H%M', time.localtime()))

if __name__ == '__main__':
    main()
