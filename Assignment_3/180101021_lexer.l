
%{
  #include<bits/stdc++.h>
  using namespace std;

//definitions and declerations as per the token coding scheme
#define PROGRAMnumber 1
#define VARnumber 2
#define BEGINnumber 3
#define ENDnumber 4
#define EOFnumber 5
#define INTEGERnumber 6
#define FORnumber 7
#define READnumber 8
#define WRITEnumber 9
#define TOnumber 10
#define DOnumber 11
#define SEMInumber 12
#define COLONnumber 13
#define COMMAnumber 14
#define COLEQnumber 15
#define PLUSnumber 16
#define MINUSnumber 17
#define TIMESnumber 18
#define DIVnumber 19
#define LPARENnumber 20
#define RPARENnumber 21
#define IDnumber 22
#define INTnumber 23




//extern declerations of parameters used in lex program 

extern int install_id(char* str,bool upper);
extern int install_num(int x,bool upper);
extern void lex_error(string msg);

//map for hashed symbol table organization
//the float stores the index, the string in the pair stores the id/int specifier, and the int stores the Token ID
map<float,pair<string,int>> mp;

//variables corressponding to the yy.c file
int yycolumn = 1; 
float yylval; 
int yyline = 1;
int starting_ind = 0;

int cnt=1; //keeps count of the line number
%}

delim   [ \t]
ws      {delim}+
letter [a-zA-Z]
digit  [0-9]
id     {letter}({letter}|{digit})*
number {digit}+



%%
\\translation_part

\n						{yyline++; yycolumn = 1;cnt=cnt+1;}
[ \t]+					{yycolumn += yyleng;}

(BEGIN|begin)					{yycolumn += yyleng; return BEGINnumber;}
(END|end)						{yycolumn += yyleng; return ENDnumber;}
(DIV|div)						{yycolumn += yyleng; return DIVnumber;}
(READ|read)					{yycolumn += yyleng; return READnumber;}
(WRITE|write)					{yycolumn += yyleng; return WRITEnumber;}
(DO|do)					{yycolumn += yyleng; return DOnumber;}
(TO|to)						{yycolumn += yyleng; return TOnumber;}
(INTEGER|integer)					{yycolumn += yyleng; return INTEGERnumber;}
(FOR|for)						{yycolumn += yyleng; return FORnumber;}
(VAR|var)						{yycolumn += yyleng; return VARnumber;}
(PROGRAM|program)					{yycolumn += yyleng; return PROGRAMnumber;}



[a-zA-Z]+[0-9]*			{yylval = install_id(yytext, true); return IDnumber;}
[0-9]+					{yylval = install_num(atoi(yytext), true); yycolumn += yyleng; return INTnumber;}



"("						{yycolumn += yyleng; return LPARENnumber;}
")"						{yycolumn += yyleng; return RPARENnumber;}
"."						{yycolumn += yyleng; return EOFnumber;}
":"						{yycolumn += yyleng; return COLONnumber;}
"-"						{yycolumn += yyleng; return MINUSnumber;}
"+"						{yycolumn += yyleng; return PLUSnumber;}
","						{yycolumn += yyleng; return COMMAnumber;}
"*"						{yycolumn += yyleng; return TIMESnumber;}
";"						{yycolumn += yyleng; return SEMInumber;}
":="						{yycolumn += yyleng; return COLEQnumber;}
.						{string s(yytext); lex_error("improper character \'" + s + "\'"); yycolumn += yyleng;}



%%
//functional part

int yywrap()
{  if (feof(stdin)) return 1;
   return 0;
}
//utility function to convert string to uppercase
string toUpper(string x){
	for (auto &c : x)
		c = toupper(c);
	return x;
}


//this function is called when the specifier is an identifier
int install_id(char* str,bool upper)
{
	string s(str);
	if(upper)toUpper(s);
	mp.insert({starting_ind,{s,22}});
	
	starting_ind++;
	return starting_ind-1;
}
//this function is called when the specifier is a number
int install_num(int x,bool upper)
{
	string s;
	stringstream ss;
	ss << x;
	ss>>s;
    if(upper)toUpper(s);
	mp.insert({starting_ind,{s,23}});
	starting_ind++;
	return (starting_ind-1);

}

void lex_error(string msg)
{
  cout << msg << ", line=" << yyline << " column=" << yycolumn << endl;
}