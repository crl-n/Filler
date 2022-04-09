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

out = sys.stdout

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

out.write(HIDE_CURSOR)
while (1):
    for i in range(168, 228):
        out.write(SET_COLOR.format(i))
        for row in banner:
            out.write(row)
            out.write(NEXTLINE)
        out.flush()
        sleep(0.001)
        out.write(CLEAR)
out.write(SHOW_CURSOR)
