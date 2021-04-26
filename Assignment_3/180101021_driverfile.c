#include <bits/stdc++.h>
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

//map for hashed symbol table organization
//the float stores the index, the string in the pair stores the id/int specifier, and the int stores the Token ID
extern map<float,pair<string,int> > mp;

extern int yylex(); //runs the lex file when called
extern int cnt; //keeps count of the line number
extern char* yytext; //variables corressponding to the yy.c file
extern float yylval;





int main()
{	
	int i;
       //placeholders for the output
       cout << "Line Number" <<setw(12) << "Token ID"<< setw(20) << "Token Specifier"<<endl;
       // while the program has not ended
	while((i=yylex()) != EOFnumber)
	{
		
		//if the specifier is an identifier
              if(i==IDnumber )
              {
                     if(cnt<10)
                     {
                     cout << cnt<<setw(20) << i << setw(17) << "^" <<mp[yylval].first;
                     cout<<endl;
                     }
                     else
                     {
                     cout << cnt<<setw(19) << i << setw(17) << "^" <<mp[yylval].first;
                     cout<<endl;

                     }
              }
              //if the specifier is an integer
              else if(i==INTnumber)
              {
                     if(cnt<10)
                     {
                     cout << cnt<< setw(20) << i << setw(17) << "#" << mp[yylval].first;
                     cout<<endl;
                     }
                     else{
                     cout << cnt<< setw(19) << i << setw(17) << "#" << mp[yylval].first;
                     cout<<endl;

                     }
              }
              
              else
              {
                     if(cnt<10)
                     {cout << cnt<< setw(20) << i;
                     cout<<endl;
                     }
                     else{
                     
                     if(cnt!=16)
                     {
                            cout << cnt<< setw(19) << i;
                            cout<<endl;
                     }

                     }
              }
		
	}
       cout << cnt <<setw(19) <<5;
       cout<<endl;
	
}
