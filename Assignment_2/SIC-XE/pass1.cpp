/*Code for pass1*/
#include "functions.cpp" /*conatins all important headers*/
#include "tables.cpp"

using namespace std;

/*Variable to keep persisted*/
bool error_flag = false;
string fileName;
string *BLocksNumToName;
int program_length;
int lineNumber=0;

int currentBlockNumber;
int cheems;
string firstExecutable_Sec;

void handle_LTORG(string &litPrefix, int &lineNumberDelta, int lineNumber, int &LOCCTR, int &lastDeltaLOCCTR, int currentBlockNumber);
void evaluateExpression(string expression, bool &relative, string &tempOperand, int lineNumber, ofstream &errorFile, bool &error_flag);
int string_to_int(string str)
{
  return stoi(str);
}
void pass1()
{
  ifstream sourceFile; //begin
  ofstream intermediateFile;
  ofstream errorFile;

  sourceFile.open("INPUT.txt");
  if (!sourceFile)
  {
    cout << "Cannot open source file" << fileName << endl;
    exit(1);
  }

  intermediateFile.open("intermediate_" + fileName);
  if (!intermediateFile)
  {
    cout << "Cannot open intermediate file" << fileName << endl;
    exit(1);
  }
  writeToFile(intermediateFile, "Line\tAddress\tLabel\tOPCODE\tOPERAND\tComment");
  errorFile.open("error_file.txt");
  if (!errorFile)
  {
    cout << "Unable to open file: error_" << fileName << endl;
    exit(1);
  }
  writeToFile(errorFile, "-------------------------PASS1-------------------------");

  string fileLine;
  
  string writeData;
  string writeDataSuffix = "";
  string writeDataPrefix = "";

  
  
  int totalBlocks = 1;
  int index = 0;
  string currentBlockName = "DEFAULT";
  

  bool statusCode;
  string label;
  string opcode;
  string operand;
  string comment;
  string tempOperand;

  int startAddress;
  int LOCCTR;
  int saveLOCCTR;
  int lastDeltaLOCCTR;
  int lineNumberDelta = 0;
  
  lastDeltaLOCCTR = 0;

  getline(sourceFile, fileLine);

  lineNumber =lineNumber + 5;

  while (checkCommentLine(fileLine))
  {
    writeData = to_string(lineNumber);
    writeData+= "\t";
    writeData+= fileLine;
    writeToFile(intermediateFile, writeData);
    getline(sourceFile, fileLine); //read first input line
    lineNumber =
    index = 0;
  }

  readFirstNonWhiteSpace(fileLine, index, statusCode, label);
  readFirstNonWhiteSpace(fileLine, index, statusCode, opcode);

  if (opcode == "START")
  {
    readFirstNonWhiteSpace(fileLine, index, statusCode, operand);
    readFirstNonWhiteSpace(fileLine, index, statusCode, comment, true);
    startAddress = stringHexToInt(operand);
    
    LOCCTR = startAddress;
    writeData = to_string(lineNumber);
    writeData +="\t";
    writeData+=intToStringHex(LOCCTR - lastDeltaLOCCTR);
    writeData+="\t";
    writeData+=to_string(currentBlockNumber);
    writeData+="\t" + label + "\t";
    writeData+= opcode + "\t" + operand + "\t";
    writeData+=comment;

    writeToFile(intermediateFile, writeData); // Write file to intermediate file

    getline(sourceFile, fileLine); //Read next line
    lineNumber = lineNumber+5;
    index = 0;
    readFirstNonWhiteSpace(fileLine, index, statusCode, label);  //Parse label
    readFirstNonWhiteSpace(fileLine, index, statusCode, opcode); //Parse OPCODE
  }
  else
  {
    LOCCTR = 0;
    startAddress = 0;
    
  }
  //*************************************************************
  int sectionCounter = 0;
  string currentSectName = "DEFAULT";
  
  //**********************************************************************
  while (opcode.compare("END")!=0)
  {
    //****************************************************************

    while ((opcode.compare("END")!=0) && (opcode.compare("CSECT")!=0) )
    {

      //****************************************************************
      if (!checkCommentLine(fileLine))
      {
        if (label != "")
        { //Label found
          //string templabel
          if (SYMTAB[make_pair(label, "*")].exists ==true)
          {
            writeData = "Line: " + to_string(lineNumber) + " : Duplicate symbol for '" + label + "'. Previously defined at " + SYMTAB[make_pair(label, "*")].address;
            writeToFile(errorFile, writeData);
            error_flag = true;

            
            //****************************************************************************
          }
          else
          {
            SYMTAB[make_pair(label, "*")].name = label;
            SYMTAB[make_pair(label, "*")].exists = true;
            SYMTAB[make_pair(label, "*")].blockNumber = currentBlockNumber;
            SYMTAB[make_pair(label, "*")].relative = 1;
            SYMTAB[make_pair(label, "*")].address = intToStringHex(LOCCTR);

            //***************************************************************************
            if (CSECT_TAB[currentSectName].EXTDEF_TAB[label].exists != false)
            {
              CSECT_TAB[currentSectName].EXTDEF_TAB[label].address = SYMTAB[make_pair(label, "*")].address;
            }
          }
        }
        if (OPTAB[getRealOpcode(opcode)].exists == true)
        { //Search for opcode in OPTAB
          if (OPTAB[getRealOpcode(opcode)].format == 3)
          {
            LOCCTR = LOCCTR+3;
            lastDeltaLOCCTR =  lastDeltaLOCCTR+3;
            if (getFlagFormat(opcode) == '+')
            {
              LOCCTR = LOCCTR+1;
              lastDeltaLOCCTR = lastDeltaLOCCTR+1;
            }
            if (getRealOpcode(opcode) != "RSUB")
            {
              readFirstNonWhiteSpace(fileLine, index, statusCode, operand);
              if (operand[operand.size() - 1] == ',')
              {
                readFirstNonWhiteSpace(fileLine, index, statusCode, tempOperand);
                operand =operand + tempOperand;
              }
              
            }
            else
            {
              operand = " ";
            }

            if (getFlagFormat(operand) == '=')
            {
              tempOperand = operand.substr(1, operand.size() - 1);
              if (tempOperand == "*")
              {
                tempOperand = "X'" + intToStringHex(LOCCTR - lastDeltaLOCCTR, 6) + "'";
              }
              if (LITTAB[tempOperand].exists != true)
              {
                LITTAB[tempOperand].exists = true;
                LITTAB[tempOperand].value = tempOperand;
                LITTAB[tempOperand].blockNumber = -1;
                LITTAB[tempOperand].address = "?";
                
              }
            }
          }
          else if (OPTAB[getRealOpcode(opcode)].format == 1)
          {
            operand = " ";
            LOCCTR = LOCCTR + OPTAB[getRealOpcode(opcode)].format;
            lastDeltaLOCCTR = lastDeltaLOCCTR + OPTAB[getRealOpcode(opcode)].format;
          }
          else
          {
            LOCCTR = LOCCTR + OPTAB[getRealOpcode(opcode)].format;
            lastDeltaLOCCTR = lastDeltaLOCCTR + OPTAB[getRealOpcode(opcode)].format;
            readFirstNonWhiteSpace(fileLine, index, statusCode, operand);
            if (operand[operand.size() - 1] == ',')
            {
              readFirstNonWhiteSpace(fileLine, index, statusCode, tempOperand);
              operand = operand+ tempOperand;
            }
          }
        }
        //*************************************************************************************************
        else if (opcode == "EXTREF")
        {
          readFirstNonWhiteSpace(fileLine, index, statusCode, operand);
          int length = operand.size();
          string inp = "";
          int i=0;
          while(i<length)
          {
            for(; i < length  && operand[i] != ',';i++)
            {
              inp += operand[i];
              
            }
            CSECT_TAB[currentSectName].EXTREF_TAB[inp].name = inp;
            CSECT_TAB[currentSectName].EXTREF_TAB[inp].exists = true;
            inp = "";
            i++;
          }
          
        }
        else if (opcode == "EXTDEF")
        {
          readFirstNonWhiteSpace(fileLine, index, statusCode, operand);
          int length = operand.size();
          string inp = "";
          int i=0;
          while(i<length)
          {
            for(;operand[i] != ',' && i < length;i++)
            {
              inp += operand[i];
              i++;
            }
            CSECT_TAB[currentSectName].EXTDEF_TAB[inp].name = inp;
            CSECT_TAB[currentSectName].EXTDEF_TAB[inp].exists = true;
            inp = "";
            i++;
          }

          
        }
        //****************************************************************************************
        else if (opcode == "RESB")
        {
          readFirstNonWhiteSpace(fileLine, index, statusCode, operand);
          LOCCTR += string_to_int(operand);
          lastDeltaLOCCTR += string_to_int(operand);
        }
        else if (opcode == "LTORG")
        {
          operand = " ";
          handle_LTORG(writeDataSuffix, lineNumberDelta, lineNumber, LOCCTR, lastDeltaLOCCTR, currentBlockNumber);
        }
        else if (opcode == "WORD")
        {
          readFirstNonWhiteSpace(fileLine, index, statusCode, operand);
          LOCCTR += 3;
          lastDeltaLOCCTR += 3;
        }
        else if (opcode == "BYTE")
        {
          readByteOperand(fileLine, index, statusCode, operand);
          if (operand[0] == 'X')
          {
            LOCCTR += (operand.size() - 3) / 2;
            lastDeltaLOCCTR += (operand.size() - 3) / 2;
          }
          else if (operand[0] == 'C')
          {
            LOCCTR += operand.size() - 3;
            lastDeltaLOCCTR += operand.size() - 3;
          }
          // else{
          //   writeData = "Line: "+to_string(line)+" : Invalid operand for BYTE. Found " + operand;
          //   writeToFile(errorFile,writeData);
          // }
        }
        else if (opcode == "BASE")
        {
          readFirstNonWhiteSpace(fileLine, index, statusCode, operand);
        }
        else if (opcode == "EQU")
        {
          readFirstNonWhiteSpace(fileLine, index, statusCode, operand);
          tempOperand = "";
          bool relative;

          if (operand == "*")
          {
            tempOperand = intToStringHex(LOCCTR - lastDeltaLOCCTR, 6);
            relative = 1;
          }
          else if (if_all_num(operand))
          {
            tempOperand = intToStringHex(string_to_int(operand), 6);
            relative = 0;
          }
          else
          {
            char lastByte = operand[operand.size() - 1];

            while ( lastByte == '/' || lastByte == '*' || lastByte == '+' || lastByte == '-')
            {
              readFirstNonWhiteSpace(fileLine, index, statusCode, tempOperand);
              operand = operand+ tempOperand;
              lastByte = operand[operand.size() - 1];
            }

            //Code for reading whole operand
            evaluateExpression(operand, relative, tempOperand, lineNumber, errorFile, error_flag);
          }

          SYMTAB[make_pair(label, "*")].name = label;
          SYMTAB[make_pair(label, "*")].address = tempOperand;
          SYMTAB[make_pair(label, "*")].relative = relative;
          SYMTAB[make_pair(label, "*")].blockNumber = currentBlockNumber;
          lastDeltaLOCCTR = LOCCTR - stringHexToInt(tempOperand);
        }
        else if (opcode == "USE")
        {
          // cout<<"Changing block"<<endl;
          // for(auto const& it: BLOCKS){
          //   cout<<it.second.name<<":"<<it.second.LOCCTR<<endl;
          // }
          //
          // cout<<"Current block number: "<<currentBlockNumber<<endl;
          // cout<<"Current LOCCTR: "<<LOCCTR<<endl;

          readFirstNonWhiteSpace(fileLine, index, statusCode, operand);
          BLOCKS[currentBlockName].LOCCTR = intToStringHex(LOCCTR);

          if (BLOCKS[operand].exists != true)
          {
            // cout<<"Creating block: "<<operand<<endl;
            BLOCKS[operand].exists = true;
            BLOCKS[operand].name = operand;
            BLOCKS[operand].number = totalBlocks++;
            BLOCKS[operand].LOCCTR = "0";
          }

          // cout<<"Changing to: "<<operand<<endl;
          // for(auto const& it: BLOCKS){
          //   cout<<it.second.name<<":"<<it.second.LOCCTR<<endl;
          // }

          currentBlockNumber = BLOCKS[operand].number;
          currentBlockName = BLOCKS[operand].name;
          LOCCTR = stringHexToInt(BLOCKS[operand].LOCCTR);

          // cout<<"Current block number: "<<currentBlockNumber<<endl;
          // cout<<"Current LOCCTR: "<<LOCCTR<<endl;
        }
        else if (opcode == "RESW")
        {
          readFirstNonWhiteSpace(fileLine, index, statusCode, operand);
          LOCCTR += 3 * string_to_int(operand);
          lastDeltaLOCCTR += 3 * string_to_int(operand);
        }

        
        
        
        
        else if (opcode == "ORG")
        {
          readFirstNonWhiteSpace(fileLine, index, statusCode, operand);

          char lastByte = operand[operand.size() - 1];
          while (lastByte == '+' || lastByte == '-' || lastByte == '/' || lastByte == '*')
          {
            readFirstNonWhiteSpace(fileLine, index, statusCode, tempOperand);
            operand += tempOperand;
            lastByte = operand[operand.size() - 1];
          }

          int tempVariable;
          tempVariable = saveLOCCTR;
          saveLOCCTR = LOCCTR;
          LOCCTR = tempVariable;

          if (SYMTAB[make_pair(operand, "*")].exists == true)
          {
            LOCCTR = stringHexToInt(SYMTAB[make_pair(operand, "*")].address);
          }
          else
          {
            bool relative;
            //set error_flag to false
            error_flag = false;
            evaluateExpression(operand, relative, tempOperand, lineNumber, errorFile, error_flag);
            if (!error_flag)
            {
              LOCCTR = stringHexToInt(tempOperand);
            }
            error_flag = false; //reset error_flag
          }
        }
        
        
        else
        {
          readFirstNonWhiteSpace(fileLine, index, statusCode, operand);
          writeData = "Line: " + to_string(lineNumber) + " : Invalid OPCODE. Found " + opcode;
          writeToFile(errorFile, writeData);
          error_flag = true;
        }
        readFirstNonWhiteSpace(fileLine, index, statusCode, comment, true);
        if (SYMTAB[make_pair(label, "*")].relative == 0 && opcode == "EQU")
        {
          writeData = writeDataPrefix + to_string(lineNumber) + "\t" + intToStringHex(LOCCTR - lastDeltaLOCCTR) + "\t" + " " + "\t" + label + "\t" + opcode + "\t" + operand + "\t" + comment + writeDataSuffix;
        }
        //*********************************************************************************
        else if ( opcode == "EXTREF"|| opcode == "EXTDEF")
        {
          writeData = writeDataPrefix + to_string(lineNumber) + "\t" + " " + "\t" + " " + "\t" + " " + "\t" + opcode + "\t" + operand + "\t" + comment + writeDataSuffix;
       /* writeData = writeDataPrefix + to_string(lineNumber) + "\t" + intToStringHex(LOCCTR-lastDeltaLOCCTR) + "\t" + blockNumberstr + "\t" + label + "\t" + opcode + "\t" + operand + "\t" + comment + writeDataSuffix;   
      }*/ }
       else if (opcode == "CSECT")
       {
         cheems++;
         writeData = writeDataPrefix + to_string(lineNumber) + "\t" + intToStringHex(LOCCTR - lastDeltaLOCCTR) + "\t" + " " + "\t" + label + "\t" + opcode + "\t" + " " + "\t" + " " + writeDataSuffix;
       }
       //*******************************************************************************
       else
       {
         writeData = writeDataPrefix + to_string(lineNumber) + "\t" + intToStringHex(LOCCTR - lastDeltaLOCCTR) + "\t" + to_string(currentBlockNumber) + "\t" + label + "\t" + opcode + "\t" + operand + "\t" + comment + writeDataSuffix;
       }
       writeDataPrefix = "";
       writeDataSuffix = "";
      }
      else
      {
        writeData = to_string(lineNumber) + "\t" + fileLine;
      }
      writeToFile(intermediateFile, writeData);

      BLOCKS[currentBlockName].LOCCTR = intToStringHex(LOCCTR); //Update LOCCTR of block after every instruction
      getline(sourceFile, fileLine);                            //Read next line
      lineNumber += 5 + lineNumberDelta;
      lineNumberDelta = 0;
      index = 0;
      lastDeltaLOCCTR = 0;
      readFirstNonWhiteSpace(fileLine, index, statusCode, label);  //Parse label
      readFirstNonWhiteSpace(fileLine, index, statusCode, opcode); //Parse OPCODE
    }
    //*****************************************************************************************

    if (opcode != "END")
    {

      if (SYMTAB[make_pair(label, "*")].exists == false)
      {
        cout<<opcode<<endl;
        if (opcode == "EQU" && label == "MAXLEN")
        {
          cout<<"hI"<<endl;
          label += "*";
        }
        SYMTAB[make_pair(label, "*")].name = label;
        SYMTAB[make_pair(label, "*")].address = intToStringHex(LOCCTR);
        SYMTAB[make_pair(label, "*")].relative = 1;
        SYMTAB[make_pair(label, "*")].exists = true;
        SYMTAB[make_pair(label, "*")].blockNumber = currentBlockNumber;
      }

      CSECT_TAB[currentSectName].LOCCTR = intToStringHex(LOCCTR - lastDeltaLOCCTR, 6);
      CSECT_TAB[currentSectName].length = (LOCCTR - lastDeltaLOCCTR);
      LOCCTR = lastDeltaLOCCTR = 0;
      currentSectName = label;
      CSECT_TAB[currentSectName].name = currentSectName;
      sectionCounter++;
      CSECT_TAB[currentSectName].section_number = sectionCounter;

      writeToFile(intermediateFile, writeDataPrefix + to_string(lineNumber) + "\t" + intToStringHex(LOCCTR - lastDeltaLOCCTR) + "\t" + to_string(currentBlockNumber) + "\t" + label + "\t" + opcode);

      getline(sourceFile, fileLine); //Read next line
      lineNumber += 5;

      readFirstNonWhiteSpace(fileLine, index, statusCode, label);  //Parse label
      readFirstNonWhiteSpace(fileLine, index, statusCode, opcode); //Parse OPCODE
    }
    else
    {
      CSECT_TAB[currentSectName].LOCCTR = intToStringHex(LOCCTR - lastDeltaLOCCTR, 6);
      CSECT_TAB[currentSectName].length = (LOCCTR - lastDeltaLOCCTR);

      CSECT_TAB[currentSectName].name = currentSectName;

      CSECT_TAB[currentSectName].section_number = sectionCounter;
    }
    //*******************************************************************************************
  }

  if (opcode == "END")
  {
    firstExecutable_Sec = SYMTAB[make_pair(label, "*")].address;
    SYMTAB[make_pair(firstExecutable_Sec, "*")].name = label;
    SYMTAB[make_pair(firstExecutable_Sec, "*")].address = firstExecutable_Sec;
  }

  readFirstNonWhiteSpace(fileLine, index, statusCode, operand);
  readFirstNonWhiteSpace(fileLine, index, statusCode, comment, true);

  /*Change to deafult before dumping literals*/
  currentBlockName = "DEFAULT";
  currentBlockNumber = 0;
  LOCCTR = stringHexToInt(BLOCKS[currentBlockName].LOCCTR);

  handle_LTORG(writeDataSuffix, lineNumberDelta, lineNumber, LOCCTR, lastDeltaLOCCTR, currentBlockNumber);

  writeDataSuffix.erase(writeDataSuffix.begin());
  writeToFile(intermediateFile, writeDataSuffix);
  writeData = to_string(lineNumber) + "\t" + intToStringHex(LOCCTR - lastDeltaLOCCTR) + "\t" + " " + "\t" + label + "\t" + opcode + "\t" + operand + "\t" + comment;
  writeToFile(intermediateFile, writeData);

  int LocctrArr[totalBlocks];
  BLocksNumToName = new string[totalBlocks];
  for (auto const &it : BLOCKS)
  {
    LocctrArr[it.second.number] = stringHexToInt(it.second.LOCCTR);
    BLocksNumToName[it.second.number] = it.first;
  }

  for (int i = 1; i < totalBlocks; i++)
  {
    LocctrArr[i] += LocctrArr[i - 1];
  }

  for (auto const &it : BLOCKS)
  {
    if (it.second.startAddress == "?")
    {
      BLOCKS[it.first].startAddress = intToStringHex(LocctrArr[it.second.number - 1]);
    }
  }

  program_length = LocctrArr[totalBlocks - 1] - startAddress;

  sourceFile.close();
  intermediateFile.close();
  errorFile.close();
}


void evaluateExpression(string expression, bool &relative, string &tempOperand, int lineNumber, ofstream &errorFile, bool &error_flag)
{
  string singleOperand = "?", singleOperator = "?", valueString = "", valueTemp = "", writeData = "";
  int lastOperand = 0, lastOperator = 0, pairCount = 0;
  char lastByte = ' ';
  bool Illegal = false;

  for (int i = 0; i < expression.size();)
  {
    singleOperand = "";

    lastByte = expression[i];
    while ((lastByte != '+' && lastByte != '-' && lastByte != '/' && lastByte != '*') && i < expression.size())
    {
      singleOperand += lastByte;
      lastByte = expression[++i];
    }

    if (SYMTAB[make_pair(singleOperand, "*")].exists == true)
    { //Check operand existence
      lastOperand = SYMTAB[make_pair(singleOperand, "*")].relative;
      valueTemp = to_string(stringHexToInt(SYMTAB[make_pair(singleOperand, "*")].address));
    }
    else if ((singleOperand != "" || singleOperand != "?") && if_all_num(singleOperand))
    {
      lastOperand = 0;
      valueTemp = singleOperand;
    }
    else
    {
      writeData = "Line: " + to_string(lineNumber) + " : Can't find symbol. Found " + singleOperand;
      writeToFile(errorFile, writeData);
      Illegal = true;
      break;
    }

    if (lastOperand * lastOperator == 1)
    { //Check expressions legallity
      writeData = "Line: " + to_string(lineNumber) + " : Illegal expression";
      writeToFile(errorFile, writeData);
      error_flag = true;
      Illegal = true;
      break;
    }
    else if ((singleOperator == "-" || singleOperator == "+" || singleOperator == "?") && lastOperand == 1)
    {
      if (singleOperator == "-")
      {
        pairCount--;
      }
      else
      {
        pairCount++;
      }
    }

    valueString += valueTemp;

    singleOperator = "";
    while (i < expression.size() && (lastByte == '+' || lastByte == '-' || lastByte == '/' || lastByte == '*'))
    {
      singleOperator += lastByte;
      lastByte = expression[++i];
    }

    if (singleOperator.size() > 1)
    {
      writeData = "Line: " + to_string(lineNumber) + " : Illegal operator in expression. Found " + singleOperator;
      writeToFile(errorFile, writeData);
      error_flag = true;
      Illegal = true;
      break;
    }

    if (singleOperator == "*" || singleOperator == "/")
    {
      lastOperator = 1;
    }
    else
    {
      lastOperator = 0;
    }

    valueString += singleOperator;
  }

  if (!Illegal)
  {
    if (pairCount == 1)
    {
      /*relative*/
      relative = 1;
      EvaluateString tempOBJ(valueString);
      tempOperand = intToStringHex(tempOBJ.getResult());
    }
    else if (pairCount == 0)
    {
      /*absolute*/
      relative = 0;
      cout << valueString << endl;
      EvaluateString tempOBJ(valueString);
      tempOperand = intToStringHex(tempOBJ.getResult());
    }
    else
    {
      writeData = "Line: ";
      writeData += to_string(lineNumber);
      writeData+= " : Illegal expression";
      writeToFile(errorFile, writeData);
      error_flag = true;
      tempOperand = "00000";
      relative = 0;
    }
  }
  else
  {
    tempOperand = "00000";
    error_flag = true;
    relative = 0;
  }
}

void handle_LTORG(string &litPrefix, int &lineNumberDelta, int lineNumber, int &LOCCTR, int &lastDeltaLOCCTR, int currentBlockNumber)
{
  string litAddress;
  string litValue;
  litPrefix = "";
  
  
  for (auto const &it : LITTAB)
  {
    litAddress = it.second.address;
    litValue = it.second.value;
    if (litAddress == "?")
    {
      lineNumber = lineNumber+5;
      lineNumberDelta =lineNumberDelta+ 5;
      LITTAB[it.first].blockNumber = currentBlockNumber;
      LITTAB[it.first].address = intToStringHex(LOCCTR);
      
      litPrefix += "\n";
      litPrefix += to_string(lineNumber)+"\t";
      litPrefix += intToStringHex(LOCCTR);
      litPrefix += "\t" + to_string(currentBlockNumber) + "\t" + "*" + "\t" + "=";
      litPrefix += litValue + "\t" + " " + "\t" + " ";
      if (litValue[0] == 'C')
      {
        int x = (litValue.size() - 3);
        LOCCTR += x;
        lastDeltaLOCCTR += x;
      }
      else if (litValue[0] == 'X')
      {
        int x = (litValue.size() - 3) / 2;
        LOCCTR += x;
        lastDeltaLOCCTR += x;
      }
    }
    else
    {
      //Pass as already assigned
    }
  }
}