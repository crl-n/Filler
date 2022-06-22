from subprocess import PIPE, run
import sys
import os
import time
import pandas as pd

games_per_opponent = 5
opponents = ['champely.filler',
             'carli.filler',
             'abanlin.filler',
             'grati.filler',
             'hcao.filler',
             'superjeannot.filler']
maps = ['map00', 'map01', 'map02']
resources_path = './resources'
BOLD = '\033[1m'
RESET = '\033[0m'

def main():

    if len(sys.argv) == 1:
        print('Usage: python3 {} [filler.player]'.format(sys.argv[0]))
        return

    player_binary = sys.argv[1]
    if player_binary.startswith('./') is False:
        player_binary = './' + player_binary
    player = player_binary.lstrip('./')

    if not os.path.exists(player_binary):
        print('Error: The player binary does not exist')
        return

    if not os.path.exists(resources_path):
        print('Error: Resources folder does not exists')
        return

    verbose = False
    if len(sys.argv) == 3:
        if sys.argv[2] == '-v':
            verbose = True

    total_time_start = time.time()

    main_df = pd.DataFrame(columns = ['Player', 'Opponent', 'Player Score', 'Opponent Score', 'Map', 'Time'])

    print(BOLD + 'Running matches... Please wait.\n' + RESET)

    for opponent in opponents:
        opponent_binary = '{}/players/{}'.format(resources_path, opponent)
        for m in maps:
            mapfile = '{}/maps/{}'.format(resources_path, m)

            print(BOLD + '{} vs. {} on {}.'.format(player, opponent,  mapfile) + RESET)

            for i in range(games_per_opponent):
                command = ['{}/filler_vm'.format(resources_path),
                           '-q',
                           '-p1', '{}'.format(player_binary),
                           '-p2', '{}'.format(opponent_binary),
                           '-f', '{}'.format(mapfile)]

                start = time.time()
                result = run(command, stdout = PIPE, stderr = PIPE, universal_newlines = True)
                end = time.time()

                player_score = int(result.stdout.split('\n')[-3].split(':')[1])
                opponent_score = int(result.stdout.split('\n')[-2].split(':')[1])

                duration = end - start

                round_data = {'Player' : player,
                              'Opponent' : opponent,
                              'Player Score' : player_score,
                              'Opponent Score' : opponent_score,
                              'Map':m,
                              'Time' : duration}

                main_df = pd.concat([main_df, pd.DataFrame([round_data])], ignore_index=True, axis = 0)

                if verbose:
                    print('{}:\t{} {}\n\t{} {}\n\ttime: {:.3f} s'.format(i + 1, player, player_score, opponent, opponent_score, duration))

            if verbose: print('\n')

    total_time_end = time.time()

    print('Execution time: {:.3f} seconds'.format(total_time_end - total_time_start))
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

if __name__ == "__main__":
    main()
