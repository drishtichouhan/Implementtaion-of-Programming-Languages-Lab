#include "structs.cpp"
typedef map<pair<string,string>,label> SYMBOL_TABLE_TYPE;
typedef map<string,opcodeStruct> OPCODE_TABLE_TYPE;
typedef map<string,struct_register> REG_TABLE_TYPE;
typedef map<string,literal> LIT_TABLE_TYPE;
typedef map<string,blockStruct> BLOCK_TABLE_TYPE;
typedef map<string,struct_csect> CSECT_TABLE_TYPE;

SYMBOL_TABLE_TYPE SYMTAB;
OPCODE_TABLE_TYPE OPTAB;
REG_TABLE_TYPE REGTAB;
LIT_TABLE_TYPE LITTAB;
BLOCK_TABLE_TYPE BLOCKS;
CSECT_TABLE_TYPE CSECT_TAB;

void load_REGTAB(){
  REGTAB["A"].num='0';
  REGTAB["A"].exists=true;

  REGTAB["X"].num='1';
  REGTAB["X"].exists=true;

  REGTAB["L"].num='2';
  REGTAB["L"].exists=true;

  REGTAB["B"].num='3';
  REGTAB["B"].exists=true;

  REGTAB["S"].num='4';
  REGTAB["S"].exists=true;

  REGTAB["T"].num='5';
  REGTAB["T"].exists=true;

  REGTAB["F"].num='6';
  REGTAB["F"].exists=true;

  REGTAB["PC"].num='8';
  REGTAB["PC"].exists=true;

  REGTAB["SW"].num='9';
  REGTAB["SW"].exists=true;
}
void load_OPTAB(){
  OPTAB["ADD"].opcode="18";
  OPTAB["ADD"].format=3;
  OPTAB["ADD"].exists=true;

  OPTAB["ADDF"].opcode="58";
  OPTAB["ADDF"].format=3;
  OPTAB["ADDF"].exists=true;

  OPTAB["ADDR"].opcode="90";
  OPTAB["ADDR"].format=2;
  OPTAB["ADDR"].exists=true;

  OPTAB["AND"].opcode="40";
  OPTAB["AND"].format=3;
  OPTAB["AND"].exists=true;

  OPTAB["CLEAR"].opcode="B4";
  OPTAB["CLEAR"].format=2;
  OPTAB["CLEAR"].exists=true;

  OPTAB["COMP"].opcode="28";
  OPTAB["COMP"].format=3;
  OPTAB["COMP"].exists=true;

  OPTAB["COMPF"].opcode="88";
  OPTAB["COMPF"].format=3;
  OPTAB["COMPF"].exists=true;

  OPTAB["COMPR"].opcode="A0";
  OPTAB["COMPR"].format=2;
  OPTAB["COMPR"].exists=true;

  OPTAB["DIV"].opcode="24";
  OPTAB["DIV"].format=3;
  OPTAB["DIV"].exists=true;

  OPTAB["DIVF"].opcode="64";
  OPTAB["DIVF"].format=3;
  OPTAB["DIVF"].exists=true;

  OPTAB["DIVR"].opcode="9C";
  OPTAB["DIVR"].format=2;
  OPTAB["DIVR"].exists=true;

  OPTAB["FIX"].opcode="C4";
  OPTAB["FIX"].format=1;
  OPTAB["FIX"].exists=true;

  OPTAB["FLOAT"].opcode="C0";
  OPTAB["FLOAT"].format=1;
  OPTAB["FLOAT"].exists=true;

  OPTAB["HIO"].opcode="F4";
  OPTAB["HIO"].format=1;
  OPTAB["HIO"].exists=true;

  OPTAB["J"].opcode="3C";
  OPTAB["J"].format=3;
  OPTAB["J"].exists=true;

  OPTAB["JEQ"].opcode="30";
  OPTAB["JEQ"].format=3;
  OPTAB["JEQ"].exists=true;

  OPTAB["JGT"].opcode="34";
  OPTAB["JGT"].format=3;
  OPTAB["JGT"].exists=true;

  OPTAB["JLT"].opcode="38";
  OPTAB["JLT"].format=3;
  OPTAB["JLT"].exists=true;

  OPTAB["JSUB"].opcode="48";
  OPTAB["JSUB"].format=3;
  OPTAB["JSUB"].exists=true;

  OPTAB["LDA"].opcode="00";
  OPTAB["LDA"].format=3;
  OPTAB["LDA"].exists=true;

  OPTAB["LDB"].opcode="68";
  OPTAB["LDB"].format=3;
  OPTAB["LDB"].exists=true;

  OPTAB["LDCH"].opcode="50";
  OPTAB["LDCH"].format=3;
  OPTAB["LDCH"].exists=true;

  OPTAB["LDF"].opcode="70";
  OPTAB["LDF"].format=3;
  OPTAB["LDF"].exists=true;

  OPTAB["LDL"].opcode="08";
  OPTAB["LDL"].format=3;
  OPTAB["LDL"].exists=true;

  OPTAB["LDS"].opcode="6C";
  OPTAB["LDS"].format=3;
  OPTAB["LDS"].exists=true;

  OPTAB["LDT"].opcode="74";
  OPTAB["LDT"].format=3;
  OPTAB["LDT"].exists=true;

  OPTAB["LDX"].opcode="04";
  OPTAB["LDX"].format=3;
  OPTAB["LDX"].exists=true;

  OPTAB["LPS"].opcode="D0";
  OPTAB["LPS"].format=3;
  OPTAB["LPS"].exists=true;

  OPTAB["MUL"].opcode="20";
  OPTAB["MUL"].format=3;
  OPTAB["MUL"].exists=true;

  OPTAB["MULF"].opcode="60";
  OPTAB["MULF"].format=3;
  OPTAB["MULF"].exists=true;

  OPTAB["MULR"].opcode="98";
  OPTAB["MULR"].format=2;
  OPTAB["MULR"].exists=true;

  OPTAB["NORM"].opcode="C8";
  OPTAB["NORM"].format=1;
  OPTAB["NORM"].exists=true;

  OPTAB["OR"].opcode="44";
  OPTAB["OR"].format=3;
  OPTAB["OR"].exists=true;

  OPTAB["RD"].opcode="D8";
  OPTAB["RD"].format=3;
  OPTAB["RD"].exists=true;

  OPTAB["RMO"].opcode="AC";
  OPTAB["RMO"].format=2;
  OPTAB["RMO"].exists=true;

  OPTAB["RSUB"].opcode="4F";
  OPTAB["RSUB"].format=3;
  OPTAB["RSUB"].exists=true;

  OPTAB["SHIFTL"].opcode="A4";
  OPTAB["SHIFTL"].format=2;
  OPTAB["SHIFTL"].exists=true;

  OPTAB["SHIFTR"].opcode="A8";
  OPTAB["SHIFTR"].format=2;
  OPTAB["SHIFTR"].exists=true;

  OPTAB["SIO"].opcode="F0";
  OPTAB["SIO"].format=1;
  OPTAB["SIO"].exists=true;

  OPTAB["SSK"].opcode="EC";
  OPTAB["SSK"].format=3;
  OPTAB["SSK"].exists=true;

  OPTAB["STA"].opcode="0C";
  OPTAB["STA"].format=3;
  OPTAB["STA"].exists=true;

  OPTAB["STB"].opcode="78";
  OPTAB["STB"].format=3;
  OPTAB["STB"].exists=true;

  OPTAB["STCH"].opcode="54";
  OPTAB["STCH"].format=3;
  OPTAB["STCH"].exists=true;

  OPTAB["STF"].opcode="80";
  OPTAB["STF"].format=3;
  OPTAB["STF"].exists=true;

  OPTAB["STI"].opcode="D4";
  OPTAB["STI"].format=3;
  OPTAB["STI"].exists=true;

  OPTAB["STL"].opcode="14";
  OPTAB["STL"].format=3;
  OPTAB["STL"].exists=true;

  OPTAB["STS"].opcode="7C";
  OPTAB["STS"].format=3;
  OPTAB["STS"].exists=true;

  OPTAB["STSW"].opcode="E8";
  OPTAB["STSW"].format=3;
  OPTAB["STSW"].exists=true;

  OPTAB["STT"].opcode="84";
  OPTAB["STT"].format=3;
  OPTAB["STT"].exists=true;

  OPTAB["STX"].opcode="10";
  OPTAB["STX"].format=3;
  OPTAB["STX"].exists=true;

  OPTAB["SUB"].opcode="1C";
  OPTAB["SUB"].format=3;
  OPTAB["SUB"].exists=true;

  OPTAB["SUBF"].opcode="5C";
  OPTAB["SUBF"].format=3;
  OPTAB["SUBF"].exists=true;

  OPTAB["SUBR"].opcode="94";
  OPTAB["SUBR"].format=2;
  OPTAB["SUBR"].exists=true;

  OPTAB["SVC"].opcode="B0";
  OPTAB["SVC"].format=2;
  OPTAB["SVC"].exists=true;

  OPTAB["TD"].opcode="E0";
  OPTAB["TD"].format=3;
  OPTAB["TD"].exists=true;

  OPTAB["TIO"].opcode="F8";
  OPTAB["TIO"].format=1;
  OPTAB["TIO"].exists=true;

  OPTAB["TIX"].opcode="2C";
  OPTAB["TIX"].format=3;
  OPTAB["TIX"].exists=true;

  OPTAB["TIXR"].opcode="B8";
  OPTAB["TIXR"].format=2;
  OPTAB["TIXR"].exists=true;

  OPTAB["WD"].opcode="DC";
  OPTAB["WD"].format=3;
  OPTAB["WD"].exists=true;
}

void load_BLOCKS(){
  BLOCKS["DEFAULT"].exists = true;
  BLOCKS["DEFAULT"].name = "DEFAULT";
  BLOCKS["DEFAULT"].startAddress = "00000";
  BLOCKS["DEFAULT"].number=0;
  BLOCKS["DEFAULT"].LOCCTR = "0";
}
void load_tables(){
  load_BLOCKS();
  load_OPTAB();
  load_REGTAB();
}
