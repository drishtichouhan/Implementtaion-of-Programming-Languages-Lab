#include<bits/stdc++.h>
#include"pass1.cpp"
#include"pass2.cpp"
using namespace std;

int main(){

	programAddress ="4000"; // default
	cout<<"PLEASE ENTER THE NAME OF INPUT FILE:\n";
	cin>>Input_file;
	cout<<endl;
	cout<<"PLEASE ENTER STARTING ADDRESS";
	cout<<endl;
	cin>> programAddress; 
	mypass1();
	cout<<endl;
	cout<<"Intermediate loadmap file has been generated\n\n";
	mypass2();
	cout<<endl;
	cout<<"Output file has been generated\n";


}