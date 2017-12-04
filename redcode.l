%{

#include "instruction.h"
#include "process.h"
#include "redcode.tab.h"

#include <stdio.h>

%}

NUMBER      -?[0-9]+
WS          [ \r\n\t]*
DAT         [dD][aA][tT]
MOV         [mM][oO][vV]
ADD         [aA][dD][dD]
SUB         [sS][uU][bB]
JMP         [jJ][mM][pP]
JMZ         [jJ][mM][zZ]
DJZ         [dD][jJ][zZ]
CMP         [cC][mM][pP]

%%

{WS}        { /* Skip blanks */ }
{NUMBER}    { yylval.integer = atoi(yytext); return TOK_NUMBER; }
{DAT}       { return TOK_DAT; }
{MOV}       { return TOK_MOV; }
{ADD}       { return TOK_ADD; }
{SUB}       { return TOK_SUB; }
{JMP}       { return TOK_JMP; }
{JMZ}       { return TOK_JMZ; }
{DJZ}       { return TOK_DJZ; }
{CMP}       { return TOK_CMP; }
#           { return TOK_IMMEDIATE; }
@           { return TOK_INDIRECT; }
.           {}

%%
