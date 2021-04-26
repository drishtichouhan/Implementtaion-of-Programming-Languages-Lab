#include<bits/stdc++.h>

string expandlen(int num, int len)
{
    char n[10];
    itoa(num, n, 16);
    string s = n;
    while(s.length() < len)
        s = "0" + s;

    return s;
}

string expandlen(string s, int len)
{
    while(s.length() < len)
        s = "0" + s;
    return s;
}
void mypass2_1(){

		string s = "XXXXXXXX";

		csaddress = programAddress;
        int firstsection = 0;
		execaddr = programAddress;
		string currline,beg,end;
        string addr_text_starts;
        string csectname;
		char linestartswith;
		

		string memloc_column;

		fin.open(Input_file);
		fout.open("loaderoutput.txt");

		char buffer[32];
        int i=0;
		while(i<32){
			buffer[i]='X';
            i++;
		}


		while(getline(fin,currline)){

			linestartswith = currline[0];

			if(linestartswith == 'H'){
	
			int i=2;
		
            csectname = "";

			while(i<currline.length()){
				if(currline[i]=='^') break;
				csectname+=currline[i];
                i++;
			}

				if(firstsection!=0){
csaddress = estab_map[csectname].address;
			beg = remove_preceeding_0s(nearest_addr_ending_in_0(csaddress));

					
				}
				else{
                    csaddress = programAddress;
					execaddr = programAddress;
					firstsection=1;
					beg = remove_preceeding_0s(nearest_addr_ending_in_0(csaddress));
				}
			cslth = "";
			cslth = estab_map[csectname].length;

			if(beg!=memloc_column)	
			fout<<beg<<"\t"<<s<<"\t"<<s<<"\t"<<s<<"\t"<<s<<"\n";
			
			beg = remove_preceeding_0s(Add_2_hex_strings(beg,"10"));

			}	
            else if (linestartswith=='M'){
				string operand_addr;
			}
			else if (linestartswith=='E'){}
            
			else if (linestartswith=='T'){



				int t; 
                t=2;
                addr_text_starts="";
					while(currline[t]!='^') {
						addr_text_starts+=currline[t];
						t++;
					}
					addr_text_starts = Add_2_hex_strings(csaddress,addr_text_starts);
					t++;

					memloc_column = remove_preceeding_0s (nearest_addr_ending_in_0(addr_text_starts));

					end = memloc_column;
					print_gap_lines(beg,end);

					fout<<memloc_column<<"\t";

					string hexdiff = subtract_2_hex_strings(addr_text_starts,memloc_column);
					int startIndex = calculate_start_index(hexdiff);

					while(currline[t]!='^') {
						t++;
					}// done with textlength
					t++;

					for(int j=0;j<startIndex;j++) {
						fout<<buffer[j];
						if((j+1)%8==0)
						fout<<"\t";
					}
					
					while(t!=currline.length()){
						int ft=0,fsi=0;
						while(startIndex<32&& t<currline.length() &&currline[t]!='^')
						{
							buffer[startIndex] = currline[t];
							fout<<buffer[startIndex];
							if((startIndex+1)%8==0){
								fout<<"\t";
							}
							startIndex++;
							t++;

						}
						if(!(t<currline.length())){
							break;
						}

						if(startIndex==32 && currline[t]!='^') {ft=0;fsi=1;}
						if(startIndex==32 && currline[t]=='^') {ft=1;fsi=1;}
						if(startIndex!=32 && currline[t]=='^') {ft=1;fsi=0;}
						
						if (!ft && fsi){
							startIndex=0;
							memloc_column = remove_preceeding_0s(Add_2_hex_strings(memloc_column,"10"));
							fout<<"\n"<<memloc_column<<"\t";
							reset_buffer(buffer);
						}
						if(ft && !fsi){
							t++;
						}
						if(ft && fsi){
							t++;
							startIndex=0;
							memloc_column = remove_preceeding_0s(Add_2_hex_strings(memloc_column,"10"));
							fout<<"\n"<<memloc_column<<"\t";
							reset_buffer(buffer);
						}
					}
					while(startIndex <32) {
						fout<<buffer[startIndex];
						if(startIndex==7||startIndex==15||startIndex==23) fout<<"\t";
						if(startIndex==31) fout<<endl;
						startIndex++;
						
					}
					reset_buffer(buffer);
					beg = Add_2_hex_strings(memloc_column,"10");			
			}
			
		}
		fin.close();
		fout.close();
//		cout<<"Exiting pass2\n";
}

void mypass2(){
		vector<string> list_modified_addrs; 
		string currline;
		string csectname;
		string csaddr;
		mypass2_1();
		fin.open("loaderoutput.txt");
		while(getline(fin,currline)){

			int i=0;
			string saddr;
			string arr;

			while(currline[i]!='\t') {
				saddr+=currline[i];
			i++;}
			//cout<<"Out of loop 1\n";
			string zero;
			zero ="";
			while(i<currline.length()){
				if(currline[i]=='\t') i++;
				else{
					arr+=currline[i];
					i++;
				}
			}
			loader_primary[saddr] = arr;
				helpermap[counter_addr] = saddr;
				counter_addr++;
		}
		string one;
		one = "";
		fin.close();
		fin.open(Input_file);
		fin2.open("intermediate_loadmap.txt");

		while(getline(fin,currline)){

			char linestartswith = currline[0];
			if(linestartswith=='H'){
				
				int i=2; csectname="";
				while(currline[i]!='^') {
					csectname+=currline[i];
					i++;}
				csaddr = estab_map[csectname].address;
			}
			
			else if(linestartswith=='E'){
				// place correct values in map
				for(int i=0;i<list_modified_addrs.size();i++){
					string label_addr = remove_preceeding_0s( nearest_addr_ending_in_0(list_modified_addrs[i]));
					string offset = subtract_2_hex_strings(list_modified_addrs[i],label_addr);	
					int offset_ = HexStringToInt(offset)*2;
					string finaldata = final_val[list_modified_addrs[i]].val;
					int no_half_bytes = final_val[list_modified_addrs[i]].no_half_bytes;
					string temp="";
					if(finaldata.length()>no_half_bytes) 
					{
						temp=finaldata;
						reverse(temp.begin(),temp.end());
						temp = temp.substr(0,no_half_bytes);
						reverse(temp.begin(),temp.end());
						finaldata=temp;
					}

					if(finaldata.length()%2==1) offset_+=1;
					updateloaderPrimary(label_addr,finaldata.length(),finaldata,offset_);

				}
				list_modified_addrs.clear();
			}
			else if(linestartswith=='M'){
				int i=2; string addr_to_be_modified="";
				while(currline[i]!='^') 
				{ addr_to_be_modified+=currline[i];
				i++;}
				string temp = addr_to_be_modified;
				addr_to_be_modified=Add_2_hex_strings(addr_to_be_modified,csaddr);
				i++;
				string label_addr = remove_preceeding_0s( nearest_addr_ending_in_0(addr_to_be_modified));
				string offset = subtract_2_hex_strings(addr_to_be_modified,label_addr);
				string num_half_bytes="";

				while(currline[i]!='^') {
					num_half_bytes+=currline[i];
					i++;}
				int no_hb = HexStringToInt(num_half_bytes);
				i++;
				char operator_ = currline[i];
				string sym="";
				i++;
				while(i<currline.length()) {
					sym+=currline[i];
					i++;}
				int offset_ = HexStringToInt(offset)*2;

				string operand;
				
//				cout<<addr_to_be_modified<<" "<<label_addr<<" "<<offset_<<" "<<no_hb<<endl;


				operand = calculateOperand(offset_,no_hb,label_addr);

				final_val[addr_to_be_modified].no_half_bytes = no_hb;
				

				string ans;
				if(operator_=='+'){

					if(final_val[addr_to_be_modified].isPresent==1) {
						}
					else {
						final_val[addr_to_be_modified].val = operand;
						final_val[addr_to_be_modified].isPresent =1;
						}
				ans = Add_2_hex_strings(final_val[addr_to_be_modified].val, estab_map[sym].address);

				if(no_hb%2==1) ans=ans.substr(1,ans.length()-1);

//				cout<<temp<<" *** "<<label_addr<<" *** "<<offset_<<" *** "<<final_val[addr_to_be_modified].val<< " + "<< estab_map[sym].address<<" = "<<ans<<endl;

				final_val[addr_to_be_modified].val = ans;

				}
				else if(operator_=='-'){
					if(final_val[addr_to_be_modified].isPresent==1) {
						}
					else {
						final_val[addr_to_be_modified].val = operand;
						final_val[addr_to_be_modified].isPresent =1;
						}
				ans = subtract_2_hex_strings(final_val[addr_to_be_modified].val, estab_map[sym].address);
				if(no_hb%2==1) ans=ans.substr(1,ans.length()-1);

//				cout<<temp<<" *** "<<label_addr<<" *** "<<offset_<<" *** "<<final_val[addr_to_be_modified].val<< " - "<< estab_map[sym].address<<" = "<<ans<<endl;


				final_val[addr_to_be_modified].val = ans;
				}
				else{
					std::cout<<"Invalid operator\n";
				}
				list_modified_addrs.push_back(addr_to_be_modified);

			}

		}
		fin.close();
		fin2.close();
		fout.close();
		one += "hello";

		fout.open("output.txt");
		
		for(int t=0;t<helpermap.size();t++){
			string templine = loader_primary[helpermap[t]]; 
			fout<<helpermap[t]<<"\t"<< templine.substr(0,8)<<"\t"<<templine.substr(8,8)<< "\t" <<templine.substr(16,8)<<"\t"<<templine.substr(24,8)<<"\n";
		}
		fout.close();

}


//takes a string with decimal value and returns int equivalent
int strTOdec(string s)
{
    stringstream str;
    str << s;
    int value;
    str >> value;
    return value;
}