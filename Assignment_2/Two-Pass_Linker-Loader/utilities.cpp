#include<bits/stdc++.h>
using namespace std;
string Input_file;
map<int, char> dec_to_hex{ { 0, '0' }, { 1, '1' },  
                      { 2, '2' }, { 3, '3' },  
                      { 4, '4' }, { 5, '5' },  
                      { 6, '6' }, { 7, '7' },  
                      { 8, '8' }, { 9, '9' },  
                      { 10, 'A' }, { 11, 'B' },  
                      { 12, 'C' }, { 13, 'D' },  
                      { 14, 'E' }, { 15, 'F' } };  

struct ESTAB_ENTRY{
	string name;
	string address;
	string length;
	int isSymbol;
};

map<char, int> hex_to_dec{ { '0', 0 }, { '1', 1 },  
                    { '2', 2 }, { '3', 3 },  
                    { '4', 4 }, { '5', 5 },  
                    { '6', 6 }, { '7', 7 },  
                    { '8', 8 }, { '9', 9 },  
                    { 'A', 10 }, { 'B', 11 },  
                    { 'C', 12 }, { 'D', 13 },  
                    { 'E', 14 }, { 'F', 15 } }; 


void reverse(char str[], int length) 
{ 
    int start = 0; 
    int end = length -1; 
    while (start < end) 
    { 
        swap(*(str+start), *(str+end)); 
        start++; 
        end--; 
    } 
} 
  
// Implementation of itoa() 
char* itoa(int num, char* str, int base) 
{ 
    int i = 0; 
    bool isNegative = false; 
  
    /* Handle 0 explicitely, otherwise empty string is printed for 0 */
    if (num == 0) 
    { 
        str[i++] = '0'; 
        str[i] = '\0'; 
        return str; 
    } 
  
    // In standard itoa(), negative numbers are handled only with  
    // base 10. Otherwise numbers are considered unsigned. 
    if (num < 0 && base == 10) 
    { 
        isNegative = true; 
        num = -num; 
    } 
  
    // Process individual digits 
    while (num != 0) 
    { 
        int rem = num % base; 
        str[i++] = (rem > 9)? (rem-10) + 'a' : rem + '0'; 
        num = num/base; 
    } 
  
    // If number is negative, append '-' 
    if (isNegative) 
        str[i++] = '-'; 
  
    str[i] = '\0'; // Append string terminator 
  
    // Reverse the string 
    reverse(str, i); 
  
    return str; 
} 
string Add_2_hex_strings(string a, string b) 
{ 
    if (a.length() < b.length()) 
        swap(a, b); 
    int l1 = a.length(), l2 = b.length(),s,bit_to_add;   
    string ans = ""; 
    int c = 0, i, j; 
    for (i = l1 - 1, j = l2 - 1; 
         j >= 0; i--, j--) { 
        s = hex_to_dec[a[i]] + hex_to_dec[b[j]] + c; 
        bit_to_add = dec_to_hex[s % 16]; 
        ans.push_back(bit_to_add); 
        c = s / 16; 
    } 
    while (i >= 0) { 
        s = hex_to_dec[a[i]] + c; 
        bit_to_add = dec_to_hex[s % 16]; 
        ans.push_back(bit_to_add); 
        c = s / 16; 
        i--; 
    } 
    if (c) { 
        ans.push_back(dec_to_hex[c]); 
    } 
    reverse(ans.begin(), ans.end()); 
    return ans; 
} 


ifstream fin,fin2;
ofstream fout;
string startingAddress,programAddress,csaddress,cslth,execaddr;
map<string,ESTAB_ENTRY> estab_map;
int isStarted = 0;

void print_gap_lines(string beg, string end){
	string s = "XXXXXXXX";
	while(beg!=end){
		fout<<beg<<"\t"<<s<<"\t"<<s<<"\t"<<s<<"\t"<<s<<"\n";
		beg = Add_2_hex_strings(beg,"10");
	}

}
char *removeDuplicate(char str[], int n) 
{ 
   // Used as index in the modified string 
   int index = 0;    
     
   // Traverse through all characters 
   for (int i=0; i<n; i++) { 
         
     // Check if str[i] is present before it   
     int j;   
     for (j=0; j<i; j++)  
        if (str[i] == str[j]) 
           break; 
       
     // If not present, then add it to 
     // result. 
     if (j == i) 
        str[index++] = str[i]; 
   } 
     
   return str; 
}
int HexStringToInt(string x){
  return stoul(x,nullptr,16);
}
void permute(string a, int l, int r) 
{ 
    // Base case 
    if (l == r) 
        cout<<a<<endl; 
    else
    { 
        // Permutations made 
        for (int i = l; i <= r; i++) 
        { 
 
            // Swapping done 
            swap(a[l], a[i]); 
 
            // Recursion called 
            permute(a, l+1, r); 
 
            //backtrack 
            swap(a[l], a[i]); 
        } 
    } 
} 
string IntToHexString(int x,int fill = 6){
  stringstream s;
  s << setfill('0') << setw(fill) << hex << x;
  string ans = s.str();
  ans = ans.substr(ans.length()-fill,fill);
  transform(ans.begin(), ans.end(),ans.begin(),::toupper);
  return ans;
}


string subtract_2_hex_strings(string a, string b){
		int a1,b1;
		a1 = HexStringToInt(a);
		b1 = HexStringToInt(b);
		return IntToHexString(a1-b1);
}

string nearest_addr_ending_in_0(string s){
	if(s[s.length()-1]=='0'){}
	else{
		while(s[s.length()-1]!='0'){
			s = subtract_2_hex_strings(s,"1"); 
		}
		
	}
	return s;
}

string remove_preceeding_0s(string x){
	string temp="";
	int i=0;
	if(x.length()<=4){ return x;}

	while(i<x.length()&&x[i]=='0') i++;
	while(i<x.length()) {
		temp+=x[i];
		i++;}
	return temp;

}

int calculate_start_index(string hexdiff){
		string temp="";
		for(int j=0;j<hexdiff.length();j++){
			if(hexdiff[j]!='0') temp+=hexdiff[j];
		}
		hexdiff=temp;
		if(hexdiff.length()>1) return -1;
		char t = hexdiff[0];
		return 2*hex_to_dec[t];
}
int find_largest(int nums[], int n) {
  return *max_element(nums, nums + n);
}

void reset_buffer(char arr[],int n=32){
		for(int i=0;i<32;i++){
			arr[i]='X';
		}

}
int find_smallest(int nums[], int n) {
  return *min_element(nums, nums + n);
}

map<string, string> loader_primary;

static int counter_addr=0;

map<int,string> helpermap;
struct finalval{
	int isPresent = -1;
	string val;
	
	int no_half_bytes;

};

map<string,finalval> final_val;

string	calculateOperand(int offset,int len_data, string addr_label){
		string operand="";
		if(len_data%2==1) offset+=1;
		int StartIndex = offset;
		int counter=0;
		for(;StartIndex<32;StartIndex++){
			counter++;
			if(counter==len_data+1) break;
			operand+=loader_primary[addr_label][StartIndex];
			
		}
		if(!(counter==len_data+1)){
			addr_label = Add_2_hex_strings(addr_label,"10");
			StartIndex=0;
			while(StartIndex<32){
				counter++;
				if(counter==len_data+1) break;
				
				operand+=loader_primary[addr_label][StartIndex];
				StartIndex++;
			}	
		}
		return operand;
}

void updateloaderPrimary(string label_addr, int len_data, string newval, int offset){
	int j=0;
	int StartIndex;
	string temp="";
	
	if(newval=="1000004") cout<<"\n\n1000004 here "<<label_addr<<"\n";
	for(StartIndex=offset;StartIndex<32;StartIndex++){
		if (j==len_data) break;
		loader_primary[label_addr][StartIndex] = newval[j];
		if(newval=="1000004"){ cout<<StartIndex<<"  "<<loader_primary[label_addr][StartIndex]<<endl;}
		temp+=loader_primary[label_addr][StartIndex];
		j++;
		
	}
	if(!(j==len_data)){
		label_addr = Add_2_hex_strings(label_addr,"10");
		
		
		for(StartIndex=0;StartIndex<32;StartIndex++){
			if (j==len_data) break;
			loader_primary[label_addr][StartIndex] = newval[j];
			if(newval=="1000004"){ cout<<StartIndex<<"  "<<loader_primary[label_addr][StartIndex]<<endl;}
			temp+=loader_primary[label_addr][StartIndex];
			j++;
			
		}
	}

}