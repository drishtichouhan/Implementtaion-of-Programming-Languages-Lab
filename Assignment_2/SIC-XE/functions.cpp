/*This file contains function helpfull for functioningof other files
Function declared here rarelly changes
This file also contains important files to #include*/

#include<bits/stdc++.h>

using namespace std;


class EvaluateString{
public:
  int getResult();
  EvaluateString(string data);
private:
  string storedData;
  int index;
  char peek();
  char get();
  int term();
  int factor();
  int number();
};

EvaluateString::EvaluateString(string data){
  index=0;
  storedData = data;
  
}
int EvaluateString::term(){
  int result = factor();
  while(peek() == '*' || peek() == '/'){
    if(get()!='*'){
      result /= factor();
    }
    else{
      result *= factor();
    }
  }
  return result;
}

int EvaluateString::getResult(){
  int result = term();
  while(peek()=='+' || peek() == '-')
  {
    if(get() != '+'){
      result -= term();
    }else{
      result += term();
    }
  }
  return result;
}

char EvaluateString::get(){
  return storedData[index++];
}


int EvaluateString::factor(){
  if(peek() >= '0' && peek() <= '9'){
    return number();
  }
  else if(peek() == '('){
    get();
    int result = getResult();
    get();
    return result;
  }
  else if(peek()=='-'){
    get();
    return -factor();
  }
  return 0;
}




char EvaluateString::peek(){
  return storedData[index];
}


string getString(char c){
  string s(1,c) ;
  return s ;
}

string intToStringHex(int x,int fill = 5){
  stringstream s;
  s << setfill('0') << setw(fill) << hex << x;
  string temp = s.str();
  temp = temp.substr(temp.size()-fill,fill);
  transform(temp.begin(), temp.end(),temp.begin(),::toupper);
  return temp;
}

int EvaluateString::number(){
  int result = get() - '0';
  while(peek() >= '0' && peek() <= '9'){
    result = 10*result + get()-'0';
  }
  return result;
}


string expandString(string data,int length,char fillChar,bool back=false){
  if(back){
    if(length<=data.size()){
      return data.substr(0,length);
    }
    else{
      for(int i = length-data.size();i>0;i--){
        data += fillChar;
      }
    }
  }
  else{
    if(length<=data.size()){
      return data.substr(data.size()-length,length);
    }
    else{
      for(int i = length-data.size();i>0;i--){
        data = fillChar + data;
      }
    }
  }
  return data;
}
int stringHexToInt(string x){
  return stoul(x,nullptr,16);
}

string stringToHexString(const string& input){
    static const char* const lut = "0123456789ABCDEF";
    size_t len = input.size();

    string output;
    output.reserve(2 * len);
    for (size_t i = 0; i < len; ++i)
    {
        const unsigned char c = input[i];
        output.push_back(lut[c >> 4]);
        output.push_back(lut[c & 15]);
    }
    return output;
}

bool checkWhiteSpace(char x){
  if(x==' ' || x=='\t'){
    return true;
  }
  return false;
}



bool if_all_num(string x){
  bool all_num = true;
  int i = 0;
  while(all_num && (i<x.size())){
    all_num &= isdigit(x[i++]);
  }
  return all_num;
}

void readFirstBlank(string line,int& index,bool& status,string& data,bool readTillEnd=false){
  
  status = true;
  data = "";
  if(readTillEnd){
    data = line.substr(index,line.size() - index);
    if(data==""){
      status = false;
    }
    return;
  }
  while(!checkWhiteSpace(line[index]) && index<line.size()){//If no whitespace then data
    data += line[index];
    index++;
  }

  if(data==""){
    status = false;
  }

  while(index<line.size()&&checkWhiteSpace(line[index])){//Increase index to pass all whitespace
    index++;
  }
}

bool checkCommentLine(string line){
  if(line[0]!='.'){
    return false;
  }
  return true;
}

void readByteOperand(string line,int& index,bool& status,string& data){
  data = "";
  status = true;
  if(line[index]!='C'){
    while(index<line.size()&&!checkWhiteSpace(line[index])){//In no whitespace then data
      data += line[index];
      index++;
    }

    
  }
  else{
    
    data = data + line[index++];
    char identifier = line[index++];
    data = data + identifier;
    while(index<line.size() && line[index]!=identifier){//Copy all data until next identifier regardless of whitespace
      data += line[index];
      index++;
    }
    index++;
    data += identifier;
    //Shift to next of identifier
  }

  if(data==""){
    status = false;
  }

  while(checkWhiteSpace(line[index])&& index<line.size()){//Increase index to pass all whitespace
    index++;
  }
}

void writeToFile(ofstream& file,string data,bool newline=true){
  if(!newline){
    file<<data;
  }else{
    file<<data<<endl;
  }
}

string getRealOpcode(string opcode){
  if(opcode[0] == '@' || opcode[0] == '+'){
    return opcode.substr(1,opcode.size() - 1);
  }
  return opcode;
}

char getFlagFormat(string data){
  if( data[0] == '@' || data[0] == '#' || data[0] == '+' || data[0] == '='){
    return data[0];
  }
  return ' ';
}



