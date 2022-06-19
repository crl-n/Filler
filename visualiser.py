# This Python file uses the following encoding: utf-8
import sys
import os
import termios
from select import select
from time import sleep

ESC = '\033'
GOTO = ESC + "[{row};{col}H" + ESC + "[{row};{col}f"
ALTERNATE_SCREEN_BUFFER = ESC + '[?1049h'
NORMAL_SCREEN_BUFFER = ESC + '[?1049l'
HIDE_CURSOR = ESC + '[?25l'
SHOW_CURSOR = ESC + '[?12l' + ESC + '[?25h'
GOTO_ORIGIN = ESC + '[H'
NEXTLINE = ESC + '[1E'
CLEAR = ESC + '[2J' + GOTO_ORIGIN
BOLD = '\033[1m'
RESET = '\033[0m'

# Color-related constants
FG = ESC + '[38;5;{0}m'
BG = ESC + '[48;5;{0}m'
RESET_BG = ESC + '[m'
P1_COLOR_1 = 27
P1_COLOR_2 = 20
EMPTY_TILE_COLOR = 237
P2_COLOR_1 = 160
P2_COLOR_2 = 124

#BLOCK = FG + '⬛︎' 
BLOCK = BG + ' '

banner_thin = ['███ █ █  █  ███ ███',
               '█   █ █  █  █   █ █',
               '█▅  █ █  █  █▅  ██ ',
               '█   █ █  █  █   █ █',
               '█   █ █▅ █▅ █▅▅ █ █']

banner = ['████ ██ ██  ██  ████ ████',
          '██   ██ ██  ██  ██   ██ █',
          '███  ██ ██  ██  ███  ███▀ ',
          '██   ██ ██  ██  ██   ██ █',
          '██   ██ ███ ███ ████ ██ █']

out = sys.stdout
speeds = [20.0, 0.75, 0.3, 0.2, 0.15, 0.1, 0.05, 0.04, 0.03, 0.02, 0.005]

def itorgb(i):
    r = (i & 0xe0) >> 5
    g = (i & 0x1c) >> 2
    b = i & 0x3
    return (r, g, b)


def rgbtoi(r, g, b):
    i = r << 5
    i += g << 2
    i += b
    return i


# ISSUE: Too big l-values cause flicker
# ISSUE: b has to be bigger than a
def gradient(a, b, l):
    r1, g1, b1 = itorgb(a)
    r2, g2, b2 = itorgb(b)
    sr = r2 - r1 // l
    sg = g2 - g1 // l
    sb = b2 - b1 // l
    colors = []
    for i in range(l):
        r = r1 + i * sr
        g = g1 + i * sg
        b = b1 + i * sb
        colors.append(rgbtoi(r, g, b))
    return colors


def get_player_numbers():
    '''Gets the player numbers, returns them as strings.'''

    p1 = 'Player 1: '
    p2 = 'Player 2: '

    # Skip filler_vm banner
    for _ in range(5):
        sys.stdin.readline()

    # Build p1
    p1_split = sys.stdin.readline().rsplit('/')
    p1 += p1_split[-1].rstrip('\n')

    # Skip 'launched' line
    sys.stdin.readline()

    # Build p2
    p2_split = sys.stdin.readline().rsplit('/')
    p2 += p2_split[-1].rstrip('\n')

    # Skip 'launched' line
    sys.stdin.readline()

    return (p1, p2)


def get_dims():
    '''Gets the dimensions of the filler board.'''

    parts = sys.stdin.readline().rstrip(':\n').split(' ')
    rows = int(parts[1])
    cols = int(parts[2])
    return (rows, cols)


def get_frames(rows):
    '''Gets filler_vm output from sys.stdin.'''

    i = 0
    frames = []
    frame = []
    for line in sys.stdin:
        if 'Plateau' in line:
            i = 0
            continue
        if i == 0:
            i += 1
            continue
        if i <= rows:
            line = line.split(' ')[1]
            
            # line = line.replace('.', BLOCK.format(EMPTY_TILE_COLOR))
            # line = line.replace('X', BLOCK.format(P2_COLOR_1))
            # line = line.replace('x', BLOCK.format(P2_COLOR_2))
            # line = line.replace('O', BLOCK.format(P1_COLOR_1))
            # line = line.replace('o', BLOCK.format(P1_COLOR_2))

            frame.append(line.rstrip('\n'))

        if i == rows:
            frames.append(frame)
            frame = []
        i += 1
    return frames


def print_banner():
    '''Prints FILLER ascii banner.'''

    for row in banner:
        out.write(row)
        out.write(NEXTLINE)


def termios_setting_off(setting, fd):
    '''Turns OFF a termios driver setting.'''

    settings = termios.tcgetattr(fd)
    oflags = settings[3]
    oflags = oflags & ~setting
    settings[3] = oflags
    termios.tcsetattr(fd, termios.TCSADRAIN, settings)


def termios_setting_on(setting, fd):
    '''Turns ON a termios driver setting.'''

    settings = termios.tcgetattr(fd)
    oflags = settings[3]
    oflags = oflags | setting
    settings[3] = oflags
    termios.tcsetattr(fd, termios.TCSADRAIN, settings)


def info_str(speed, p1, p2):
    '''Creates a string containing player and speed info.'''

    info = ""
    info += NEXTLINE
    info += BOLD
    info += BG.format(P1_COLOR_1)
    info += p1
    info += NEXTLINE
    info += BG.format(P2_COLOR_1)
    info += p2
    info += RESET_BG
    info += NEXTLINE
    info += BOLD + 'Speed: {} '.format(speed) + RESET
    info += NEXTLINE
    info += FG.format(231)

    return info


def update_cell(row, col, character):
    out.write(GOTO.format(row = row, col = col) + character)


def update_board(frame, rows, cols):
    '''Modifies the displayed board.'''

    for i in range(rows):
        for j in range(cols):
            if frame[i][j] == '.':
                update_cell(i, j, BLOCK.format(EMPTY_TILE_COLOR))
                continue
            if frame[i][j] == 'X':
                update_cell(i, j, BLOCK.format(P2_COLOR_1))
                continue
            if frame[i][j] == 'x':
                update_cell(i, j, BLOCK.format(P2_COLOR_2))
                continue
            if frame[i][j] == 'O':
                update_cell(i, j, BLOCK.format(P1_COLOR_1))
                continue
            if frame[i][j] == 'o':
                update_cell(i, j, BLOCK.format(P1_COLOR_2))
                continue


def print_frames(frames, speed, p1, p2, rows, cols):

    # Turn off the terminal's canonical mode. See man termios for description.
    f = open('/dev/tty')
    fd = f.fileno()
    termios_setting_off(termios.ICANON, fd)

    # Create info string. It contains player and speed info.
    info = info_str(speed, p1, p2)

    # Print banner and info.
    print_banner()
    out.write(info)

    out.write(CLEAR)

    # Print out the first frame.
    for line in frames[0]:

        # Replace characters of filler_vm output with pretty blocks.
        line = line.replace('.', BLOCK.format(EMPTY_TILE_COLOR))
        line = line.replace('X', BLOCK.format(P2_COLOR_1))
        line = line.replace('x', BLOCK.format(P2_COLOR_2))
        line = line.replace('O', BLOCK.format(P1_COLOR_1))
        line = line.replace('o', BLOCK.format(P1_COLOR_2))

        out.write(line)
        out.write(NEXTLINE)

    out.flush()

    # Animate remaining frames.
    for frame in frames[1:]:

        # While animating, check for keystrokes.
        if select([f], (), (), 0)[0]:
            keystroke = f.read(1)
            if keystroke == 'k' and speed < 10:
                speed += 1
            elif keystroke == 'j' and speed > 1:
                speed -= 1

        update_board(frame, rows, cols)
        out.flush()
        sleep(speeds[speed])

    # Turn canonical mode back on.
    termios_setting_on(termios.ICANON, fd)


def check_terminal_size(rows, cols):
    term_width, term_height = os.get_terminal_size()

    if (term_width < cols or term_height < rows):
        print("The terminal font size is too big. Press ⌘- to make the font smaller".format(term_width, cols))

        while (term_width < cols or term_height < rows):
            sleep(0.5)
            term_width, term_height = os.get_terminal_size()

    out.write(CLEAR)
    out.flush()


def main():
    speed = 6
    p1, p2 = get_player_numbers()
    rows, cols = get_dims()

    check_terminal_size(rows, cols)

    frames = get_frames(rows)

    # out.write(ALTERNATE_SCREEN_BUFFER)
    out.write(HIDE_CURSOR)

    # Fade in banner
    for color in gradient(0, 255, 20):
        out.write(FG.format(color))
        print_banner()
        out.flush()
        sleep(0.01)
        out.write(CLEAR)

    print_frames(frames, speed, p1, p2, rows, cols)

    # TODO: declare winner, show turn and result

    out.write(SHOW_CURSOR)
    # out.write(NORMAL_SCREEN_BUFFER)

if __name__ == '__main__':
    if sys.stdin.isatty():
        print('Usage: You have to pipe a filler_vm process to this script.')
        print('E.g. ./filler_vm -p1 ./champely.filler -p2 ./grati.filler -f map00 | py visualiser.py')
    else:
        main()

