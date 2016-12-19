from ply import *
import wdm_lex
import sys

output_file = '../User/main.c'

sys.path.insert(0, "../..")

if sys.version_info[0] >= 3:
    raw_input = input

tokens = wdm_lex.tokens


def p_program(p):
    '''program : prog_body'''

def p_prog_body(p):
    '''prog_body : prog_body state
                 | state'''

def p_state(p):
    '''state : state_id timeout  param_block next_state
             | state_id timeout  next_state'''

def p_state_id(p):
    '''state_id : STATEID EQUALS INTEGER SEMI'''
    f2 = open(output_file, 'a')
    f2.write("case " + str(p[3]) + ":\n")
    f2.write("{\n")
    f2.close()

def p_timeout(p):
    '''timeout : TIMEOUT EQUALS INTEGER SEMI'''
    f2 = open(output_file, 'a')
    f2.write("delay = %d;\n" %p[3])
    f2.close()

def p_param_block(p):
    '''param_block : param_block param
                   | param'''

def p_param(p):
    '''param : PARAM INTEGER COLON statement SEMI'''
    f2 = open(output_file, 'a')
    f2.write("while (receive_count < 2);\n")
    f2.write("read_bufer();\n")
    f2.write("if (!(command == %d && (%s)))\n" %(p[2], p[4]))
    f2.write("{\n")
    f2.write(" error();\n")
    f2.write(" break;\n")
    f2.write("}\n")
    f2.write("blink_LED();\n")
    f2.close()

def p_statement(p):
    '''statement : compare INTEGER
                 | compare INTEGER AND compare INTEGER
                 | compare INTEGER OR compare INTEGER'''
    if len(p) > 3:
        if p[3] == '&':
            p[0] = "data " + str(p[1]) + " " + str(p[2]) + " && data " + str(p[4]) + " " + str(p[5])
        elif p[3] == '|':
            p[0] = "data " + str(p[1]) + " " + str(p[2]) + " || data " + str(p[4]) + " " + str(p[5])
    else:
        p[0] = "data " + str(p[1]) + " " + str(p[2])


def p_compare(p):
    '''compare : EQUALS
               | NE
               | LT
               | LE
               | GT
               | GE '''
    if p[1] == '=':
        p[0] = "=="
    elif p[1] == '!=':
        p[0] = "!="
    elif p[1] == '<':
        p[0] = "<"
    elif p[1] == '<=':
        p[0] = "<="
    elif p[1] == '>':
        p[0] = ">"
    elif p[1] == '>=':
        p[0] = ">="

def p_next_state(p):
    '''next_state : NEXTSTATE COLON numer SEMI'''
    f2 = open(output_file, 'a')
    f2.write("while (receive_count < 2);\n")
    f2.write("read_bufer();\n")
    f2.write("if (!(command == 0xFF && (%s)))\n" %(p[3]))
    f2.write("{\n")
    f2.write(" error();\n")
    f2.write(" break;\n")
    f2.write("}\n")
    f2.write("state = data;\n")
    f2.write("break;\n")
    f2.write("}\n")
    f2.close()

def p_numer(p):
    '''numer : INTEGER COMMA numer
             | INTEGER'''
    if len(p) == 2:
        p[0] = "data == " + str(p[1])
    else:
        p[0] = "data == " + str(p[1]) + " || " + str(p[3])



# Обработка синтаксических ошибок
def p_error(p):
    print ("Syntax error!")

wparser = yacc.yacc()

def parse(data, debug=0):
    wparser.error = 0
    p = wparser.parse(data, debug=debug)
    if wparser.error:
        return None
    return p

if __name__=="__main__":
    while 1:
       try:
           s = raw_input('enter > ')
       except EOFError:
           break
       if not s: continue

       yacc.parse(s)