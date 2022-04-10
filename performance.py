import sys
import os
import time
import multiprocessing as mp
from subprocess import Popen
import pandas as pd

def get_result(p):
    for i in range(7):
        p.readline()
    o_result = int(p.readline().split(':')[1])
    x_result = int(p.readline().split(':')[1])
    return (o_result, x_result)

def main():
    if len(sys.argv) != 2:
        print('Usage: python3 {} [filler.player]'.format(sys.argv[0]))
        return
    player_binary = sys.argv[1]
    if player_binary.startswith('./') is False:
        player_binary = './' + player_binary
    player = player_binary.lstrip('./')

    print('Player: ' + player_binary)

    opponents = ['champely.filler',
                 'hcao.filler',
                 'grati.filler']
    maps = ['map00', 'map01']

    resources_path = '../resources_filler'
    filler_vm = '{}/filler_vm'.format(resources_path)

    # TODO: Create better system for temp files.
    #matchlog = 'matchlog_{}'.format(time.strftime('%d%m%Y-%H%M', time.localtime()))
    #os.system('{} -q -p1 {} -p2 {} -f {}'.format(filler_vm, player_binary, opponent_binary, mapfile, matchlog))

    df = pd.DataFrame(columns = ['Player', 'Opponent', 'Player Score', 'Opponent Score'])

    start = time.time()
    for opponent in opponents:
        opponent_binary = '{}/players/{}'.format(resources_path, opponent)
        for m in maps:
            mapfile = '{}/maps/{}'.format(resources_path, m)
            processes = []
            for i in range(5):
                processes.append(os.popen('{} -q -p1 {} -p2 {} -f {}'.format(filler_vm, player_binary, opponent_binary, mapfile)))

            for p in processes:
                o, x = get_result(p)
                print('O: {}'.format(o))
                print('X: {}'.format(x))
                df = pd.concat([df, pd.DataFrame([{'Player' : player, 'Opponent' : opponent, 'Player Score' : o, 'Opponent Score' : x}])], ignore_index=True, axis = 0)

    end = time.time()
    print(df)
    print('Execution time: {}'.format(end - start))
    
    # TODO: Make a function that extracts the match result and other relevant metrics from temp output
    # TODO: Figure out if virtual machine can be modified to speed up games
    # TODO: Plot/report results

if __name__ == '__main__':
    main()
