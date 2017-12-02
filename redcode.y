%{
#include <stdio.h>
#include <string.h>

#include "process.h"

extern int yylex();
extern void yyerror(Process *process, char *msg);

%}

%parse-param { Process *process }

%union {
    int integer;
    Arg arg;
    Instr *instr;
}

%token TOK_DAT TOK_MOV TOK_ADD TOK_SUB TOK_JMP TOK_JMZ TOK_DJZ TOK_CMP TOK_IMMEDIATE TOK_INDIRECT NEWLINE
%token <integer> TOK_NUMBER

%type <instr> instrs
%type <instr> instr
%type <integer> code dat mov add sub jmp jmz djz cmp
%type <arg> argument
%type <integer> mode

%%

instrs: /* empty */  { }
            | instrs instr { process_add_instr(process, $2); }
            ;

instr: code argument argument { $$ = instr_create($1, $2, $3); };

code: dat
    | mov
    | add
    | sub
    | jmp
    | jmz
    | djz
    | cmp
    ;

argument: TOK_NUMBER      { $$ = arg_create(REL, $1); }
        | mode TOK_NUMBER { $$ = arg_create($1, $2); }
        ;

mode: TOK_IMMEDIATE { $$ = IMD; }
    | TOK_INDIRECT  { $$ = IND; }
    ;

dat: TOK_DAT { $$ = DAT; };
mov: TOK_MOV { $$ = MOV; };
add: TOK_ADD { $$ = ADD; };
sub: TOK_SUB { $$ = SUB; };
jmp: TOK_JMP { $$ = JMP; };
jmz: TOK_JMZ { $$ = JMZ; };
djz: TOK_DJZ { $$ = DJZ; };
cmp: TOK_CMP { $$ = CMP; };
