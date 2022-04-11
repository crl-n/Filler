# This Python file uses the following encoding: utf-8
import sys
import select
from time import sleep

ESC = '\033'
HIDE_CURSOR = ESC + '[?25l'
SHOW_CURSOR = ESC + '[?12l' + ESC + '[?25h'
GOTO_ORIGIN = ESC + '[H'
NEXTLINE = ESC + '[1E'
CLEAR = ESC + '[2J' + GOTO_ORIGIN

# Color-related constants
FG = ESC + '[38;5;{0}m'
BG = ESC + '[48;5;{0}m'
RESET_BG = ESC + '[m'
P1_COLOR_1 = 27
P1_COLOR_2 = 20
EMPTY_TILE_COLOR = 237
P2_COLOR_1 = 160
P2_COLOR_2 = 124

BLOCK = FG + '⬛︎' 

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
    for _ in range(5):
        sys.stdin.readline()
    p1 = 'Player 1: '
    p2 = 'Player 2: '
    p1_split = sys.stdin.readline().rsplit('/')
    p1 += p1_split[-1].rstrip('\n')
    sys.stdin.readline()
    p2_split = sys.stdin.readline().rsplit('/')
    p2 += p2_split[-1].rstrip('\n')
    sys.stdin.readline()
    print(p1, p2)
    return (p1, p2)

def get_dims():
    parts = sys.stdin.readline().rstrip(':\n').split(' ')
    rows = int(parts[1])
    cols = int(parts[2])
    return (rows, cols)

# TODO: Optimise get_frames
def get_frames(rows):
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
            line = line.replace('.', BLOCK.format(EMPTY_TILE_COLOR))
            line = line.replace('X', BLOCK.format(P2_COLOR_1))
            line = line.replace('x', BLOCK.format(P2_COLOR_2))
            line = line.replace('O', BLOCK.format(P1_COLOR_1))
            line = line.replace('o', BLOCK.format(P1_COLOR_2))
            frame.append(line.rstrip('\n'))
        if i == rows:
            frames.append(frame)
            frame = []
        i += 1
    return frames

# TODO: clean up and split into functions
# TODO: write map dimensions
# TODO: declare winner, show turn and result
# TODO: center banner
# TODO: fade in banner
# TODO: make speed adjustable (by flag or by keystroke?)
# TODO: compatibility with map02
def main():
    out = sys.stdout
    p1, p2 = get_player_numbers()
    rows, cols = get_dims()
    frames = get_frames(rows)
    out.write(HIDE_CURSOR)
    for color in gradient(0, 255, 20):
        out.write(FG.format(color))
        for row in banner:
            out.write(row)
            out.write(NEXTLINE)
        out.flush()
        sleep(0.01)
        out.write(CLEAR)
    for frame in frames:
        out.write(CLEAR)
        out.write(FG.format(231))
        for row in banner:
            out.write(row)
            out.write(NEXTLINE)
        out.write(NEXTLINE)
        out.write(BG.format(P1_COLOR_1))
        out.write(p1)
        out.write(NEXTLINE)
        out.write(BG.format(P2_COLOR_1))
        out.write(p2)
        out.write(RESET_BG)
        out.write(NEXTLINE)
        out.write(NEXTLINE)
        for line in frame:
            out.write(line)
            out.write(NEXTLINE)
        out.flush()
        sleep(0.035)
    out.write(SHOW_CURSOR)

if __name__ == '__main__':
    if sys.stdin.isatty():
        print('Usage: You have to pipe a filler_vm process to this script.')
        print('E.g. ./filler_vm -p1 ./champely.filler -p2 ./grati.filler -f map00 | py visualiser.py')
    else:
        main()
