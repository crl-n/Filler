import sys
import os
import random

def main():
    player_binary = sys.argv[1]
    if player_binary.startswith('./') is False:
        player_binary = './' + player_binary

    print('Player: ' + player_binary)

    resources_path = '../resources_filler'
    filler_vm = '{}/filler_vm'.format(resources_path)
    opponent_binary = '{}/players/champely.filler'.format(resources_path)
    mapfile = '{}/maps/map00'.format(resources_path)

    # TODO: Create better system for temp files.
    tempfile = 'temp_{}'.format(random.randint(10, 99))


    os.system('{} -p1 {} -p2 {} -f {} > {}'.format(filler_vm, player_binary, opponent_binary, mapfile, tempfile))
    
    # TODO: Make a function that extracts the match result and other relevant metrics from temp output
    # TODO: Figure out if virtual machine can be modified to speed up games
    # TODO: Plot/report results

if __name__ == '__main__':
    main()
