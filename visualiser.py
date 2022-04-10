# This Python file uses the following encoding: utf-8
import sys
from time import sleep

ESC = '\033'
HIDE_CURSOR = ESC + '[?25l'
SHOW_CURSOR = ESC + '[?12l' + ESC + '[?25h'
GOTO_ORIGIN = ESC + '[H'
NEXTLINE = ESC + '[1E'
SET_COLOR = ESC + '[38;5;{0}m'
CLEAR = ESC + '[2J' + GOTO_ORIGIN

RED = 0xe0
GREEN = 0x1c
BLUE = 0x3

BLOCK = SET_COLOR + '⬛︎' 

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
            line = line.replace('.', BLOCK.format(237))
            line = line.replace('X', BLOCK.format(160))
            line = line.replace('x', BLOCK.format(124))
            line = line.replace('O', BLOCK.format(27))
            line = line.replace('o', BLOCK.format(20))
            frame.append(line.rstrip('\n'))
        if i == rows:
            frames.append(frame)
            frame = []
        i += 1
    return frames

def main():
    out = sys.stdout
    p1, p2 = get_player_numbers()
    rows, cols = get_dims()
    frames = get_frames(rows)
    out.write(HIDE_CURSOR)
    for color in gradient(0, 255, 20):
        out.write(SET_COLOR.format(color))
        for row in banner:
            out.write(row)
            out.write(NEXTLINE)
        out.flush()
        sleep(0.01)
        out.write(CLEAR)
    for frame in frames:
        out.write(CLEAR)
        out.write(SET_COLOR.format(231))
        for row in banner:
            out.write(row)
            out.write(NEXTLINE)
        out.write(NEXTLINE)
        out.write(NEXTLINE)
        out.write(p1)
        out.write(NEXTLINE)
        out.write(p2)
        out.write(NEXTLINE)
        out.write(NEXTLINE)
        for line in frame:
            out.write(line)
            out.write(NEXTLINE)
        out.flush()
        sleep(0.035)
    out.write(SHOW_CURSOR)

if __name__ == '__main__':
    main()
