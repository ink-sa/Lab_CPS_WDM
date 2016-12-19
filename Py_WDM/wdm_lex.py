# An implementation of Dartmouth BASIC (1964)

from ply import *

keywords = (
    'STATEID', 'TIMEOUT', 'NEXTSTATE','PARAM'
)

tokens = keywords + (
    'EQUALS', 'PLUS', 'MINUS', 'TIMES', 'DIVIDE', 'POWER',
    'LPAREN', 'RPAREN', 'LT', 'LE', 'GT', 'GE', 'NE',
    'COMMA', 'SEMI', 'INTEGER',
    'ID', 'NEWLINE','COLON', 'OR', 'AND', 'NOT'
)

t_ignore = ' \t\n'



def t_ID(t):
    r'[A-Z][A-Z0-9]*'
    if t.value in keywords:
        t.type = t.value
    return t


t_EQUALS = r'='
t_PLUS = r'\+'
t_MINUS = r'-'
t_TIMES = r'\*'
t_POWER = r'\^'
t_DIVIDE = r'/'
t_LPAREN = r'\('
t_RPAREN = r'\)'
t_LT = r'<'
t_LE = r'<='
t_GT = r'>'
t_GE = r'>='
t_NE = r'!='
t_NOT = r'!'
t_OR = r'\|'
t_AND = r'&'
t_COMMA = r'\,'
t_SEMI = r';'
t_COLON = r':'



def t_INTEGER(t):
    r'\d+'
    try:
        t.value = int(t.value)
        #if  t.value < 0 or t.value > 255:
            #print ("Строка %d: Число %s слишком велико! Допустимый диапаазон - 0 - 255!" % (t.lineno, t.value))
            #t.value = 0
    except ValueError:
        print ("Строка %d: Число %s слишком велико!" % (t.lineno, t.value))
        t.value = 0

    return t




def t_NEWLINE(t):
    r'\n'
    t.lexer.lineno += 1
    return t


def t_error(t):
    print("Illegal character %s" % t.value[0])
    t.lexer.skip(1)

wdm_lex = lex.lex(debug=0)



if __name__=="__main__":
    data = '''STATEID = 1; TIMEOUT = 10; PARAM 1: >0 & <5; NEXTSTATE: 1;'''

    wdm_lex.input(data)

    while True:
        tok = wdm_lex.token()
        if not tok: break
        print (tok)