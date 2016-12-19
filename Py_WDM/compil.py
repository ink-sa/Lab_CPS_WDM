import wdm_parse
import sys

output_file = '../User/main.c'

f1 = open('programm_sample_begin.txt', 'r')
try:
    f2 = open(output_file, 'w')
except FileNotFoundError:
    print("No file or directory '../User/main.c'!")
    exit(1)
bufer = f1.read()
f2.write(bufer + '\n')
f1.close()
f2.close()

if len(sys.argv) == 2:
    try:
        f = open(sys.argv[1], 'r')
        bufer = f.read()
        f.close()
    except FileNotFoundError:
        print("No file %s!" %str(sys.argv[1]))
        exit(1)
else:
    try:
        f = open("program.txt", 'r')
        bufer = f.read()
        f.close()
    except FileNotFoundError:
        print("No file program.txt!")
        exit(1)

wdm_parse.yacc.parse(bufer)

f1 = open('programm_sample_end.txt', 'r')
try:
    f2 = open(output_file, 'a')
except FileNotFoundError:
    print("No file or directory '../User/main.c'!")
    exit(1)
bufer = f1.read()
f2.write(bufer + '\n')
f1.close()
f2.close()

