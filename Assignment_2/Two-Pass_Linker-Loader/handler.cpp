
#include"utilities.cpp"
#include<bits/stdc++.h>
using namespace std;

void handle_H(string& templine){
			string csectname;
			string addr1;
			string length;
			int index = 2;

			while(1){
				if (templine[index]=='^')  break;
				csectname+=templine[index];
				index++;
			}
			while(templine[index]!='^')
			index+=2;
			
			while(templine[index]!='^'){
				addr1+=templine[index];
				index++;
			}
			index++;
			string x = "one";
			while(index<templine.length()){
				length+=templine[index];
				index++;
			}
			string z = "zero";
			if(isStarted==0){
				csaddress = programAddress;

				startingAddress = Add_2_hex_strings(addr1,csaddress);
				isStarted =1;
			}

			struct ESTAB_ENTRY ob;
			ob.address = Add_2_hex_strings(addr1,csaddress);
			ob.name = csectname;
			
			estab_map[csectname] = ob;
			ob.length = length;
			ob.isSymbol = 2;
			cslth = length;
			fout<<ob.name<<"\t"<<"*\t"<<ob.address<<"\t"<<ob.length<<endl;

}
void handle_T(string& currline){

	while(getline(fin,currline)){
		if(currline.length()>0&&currline[0]=='E'){
						csaddress = Add_2_hex_strings(csaddress,cslth);
						break;}
	}	

}
void handle_D(string& templine){


			int index = 2;

			while(index<templine.length()){

			string name;
			string addr1;
			string length ="0";

				while(templine[index]!='^'){
					name+=templine[index];
					index++;
				}
				index++;
				while(index<templine.length()&&templine[index]!='^'){
					addr1+=templine[index];
					index++;
				}
				index++;
				struct ESTAB_ENTRY ob;
				ob.address = Add_2_hex_strings(addr1,csaddress);
				ob.length = length;
				ob.name = name;
				ob.isSymbol = 0;
				estab_map[name] = ob;
				fout<<"*"<<"\t"<<name<<"\t"<<ob.address<<"\t"<<ob.length<<endl;

			}


}


