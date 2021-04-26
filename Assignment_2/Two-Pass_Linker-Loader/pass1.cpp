#include"handler.cpp"
#include<bits/stdc++.h>
using namespace std;

bool mypass1(){
	string address,currline; // can be in hex

	fin.open(Input_file);
	fout.open("intermediate_loadmap.txt");

	while(getline(fin,currline))
    {
		char rectype=currline[0];
        switch(rectype)
        {
            case 'H':
            {
                handle_H(currline);
                break;
            }
            case 'D':
            {
                handle_D(currline);
                break;
            }
            case 'R':
            {
                break;
            }
            case 'T':
            {
                handle_T(currline);
            }
            case 'E':
            {
                break;
            }
            
        }

    }

	fin.close();
	fout.close();
	return 1;
}