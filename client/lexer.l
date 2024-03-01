%option noyywrap caseless yylineno nounput noinput batch debug

%{
    #include <stdio.h>
    #include <stdbool.h>
    #include <string.h>
    #include <math.h>
    #include "parser.tab.h"

    void print_tokenizer_error(char*);
%}

alpha   [A-Za-z_0-9 \t\r]
id      [a-zA-Z][a-zA-Z_0-9]*
int     ([-+]?[0-9])+
float   [+-]?([0-9]*[.])?[0-9]+
blank   [ \t\r]
word    ([a-zA-Z_][a-zA-Z0-9_]*)
quoted_string \"{word}*\"

%%

"V"                     {return VERTEX;}
"has"                   {return HAS;}
"out"                   {return OUT;}

"open_file"                  {return OPEN;}
"delete_file"                {return DELETE;}
"create_file"            {return CREATE;}
"close_file"             {return CLOSE;}
"create_schema"          {return CREATE_SCHEMA;}
"delete_schema"          {return DELETE_SCHEMA;}
"add_vertex"             {return ADD_VERTEX;}

"eq"                    {return EQUALS;}
"gt"                    {return GREATER;}
"gte"                   {return GREATER_EQUALS;}
"lt"                    {return LESS;}
"lte"                   {return LESS_EQUALS;}
"neq"                   {return NOT_EQUALS;}
"contains"              {return CONTAINS;}

"integer"               {return MY_INTEGER;}
"float"                 {return MY_FLOAT;}
"string"                {return MY_STRING;}
"boolean"               {return MY_BOOLEAN;}
"reference"             {return MY_REF;}

"values"                {return VALUES;}

"true"|"false"          {yylval.boolean = !strcmp(yytext, "true"); return BOOLEAN;}

"("                     {return LEFT_BRACE;}
")"                     {return RIGHT_BRACE;}
\'                      {return QUOTE;}
"."                     {return DOT;}
","                     {return COMMA;}
";"                     {return SEMICOLON;}

[a-zA-Z0-9_]+\.[A-Za-z]{1,3}    {yylval.string = strdup(yytext); return FILENAME;}
[a-zA-Z][a-zA-Z0-9_]*   {yylval.string = strdup(yytext); return WORD;}
(\.[0-9]+)|([0-9]+(\.[0-9]*)?([eE][+-]?[0-9]+)?)   {
      double f = atof(yytext);
      if (ceil(f) == f) {
        yylval.integer = atoi(yytext);
        return INTEGER;
      } else {
        yylval.decimal = f;
        return DECIMAL;
      }
}

[\n]                      {/* ignore */;}
[ \t]+                    {/* ignore */;}
.                         {
    print_tokenizer_error(yytext);
    return (OTHER);
}
%%

void print_tokenizer_error(char* token) {
    printf("Error in tokenizer while reading token = %s \n", token);
}