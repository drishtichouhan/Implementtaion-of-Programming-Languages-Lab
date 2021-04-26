#include<iostream>
#include<map>
#include<string>

using namespace std;
struct label{
     string address;
     string name;
     int relative;
     int blockNumber;
     bool exists;
     label(){
       name="undefined";
       address="0";
       blockNumber = 0;
       exists='n';
       relative = 0;
     }
};
struct opcodeStruct{
    string opcode;
    int format;
    bool exists;
    opcodeStruct(){
      opcode="undefined";
      format=0;
      exists='n';
    }
};

struct literal{
    string value;
    string address;
    bool exists
    int blockNumber = 0;
    literal(){
      value="";
      address="?";
      blockNumber = 0;
      exists='n';
    }
};
struct struct_register{
     char num;
     bool exists
     struct_register(){
       num = 'F';
       exists='n';
     }
};
struct blockStruct{
     string startAddress;
     string name;
     string LOCCTR;
     int number;
     bool exists;
     blockStruct(){
       name="undefined";
       startAddress="?";
       exists='n';
       number = -1;
       LOCCTR = "0";
     }
};

struct externalDefinition{
    string name ;
    string address ;
    bool exists ;
    externalDefinition(){
        name="undefined" ;
        address="0" ;
        exists='n' ;
    }
};

struct struct_csect{
    string name ;
    string LOCCTR ;
    int section_number ;
    int length ;
    map<string,externalDefinition> EXTDEF_TAB ;
    map<string,externalDefinition> EXTREF_TAB ;
    struct_csect(){
        name="DEFAULT" ;
        LOCCTR="0" ;
        section_number=0 ;
        length=0 ;
    }
};






