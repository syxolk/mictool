#include <fstream>
#include <vector>
#include <iostream>
#include "html.h"
#include "io.h"
using namespace std;

int getInt(const bitset<80> bits, int fromBit, int toBit);

void writeHTML(const char* path, vector<micro_line>& lines) {
  ofstream file(path);
  if(file.is_open()) {
    
    file << "<!doctype html>" << endl 
      << "<html>" << endl
      << "<head>" << "<title>MI Program</title>" << endl
      << "<style type=\"text/css\">" << endl
      << ".bits {font-size: x-small;}" << endl
      << ".program, .program th, .program td {border: 1px solid black;}" << endl
      << ".program {border-collapse: collapse;}" << endl
      << "</style>" << endl
      << "</head>" << endl
      << "<body>" << endl;
    
    file << "<table class=\"program\">" << endl;
    
    // bit numbers from 79 to 0
    file << "<tr class=\"bits\"><td></td>";
    for(int i=79; i>=0; i--) {
      file << "<td>" << i << "</td>";
    }
    file << "</tr>" << endl;
    
    const char *MI_INTERRUPT[] = {"LDM", "RDM", "CLM", "STM", "BCLM", "BSTM", "LDST", 
      "RDST", "ENI", "DISI", "RDVC", "CLI", "CLMR", "CLMB", "CLVC", "MCL"};
    const char *MI_SRC[] = {"AQ", "AB", "ZQ", "ZB", "ZA", "DA", "DQ", "DZ"};
    const char *MI_FUNC[] = {"ADD", "SUBR", "SUBS", "OR", "AND", "NOTRS", "EXOR", "EXNOR"};
    const char *MI_DEST[] = {"QREG", "NOP", "RAMA", "RAMF", "RAMQD", "RAMD", "RAMQU", "RAMU"};
    const char *MI_CIN_MUX[] = {"CI0", "CI1", "CIX", "CIC"};
    const char *MI_TEST_WHAT[] = {"-", "&mu;SR", "MSR", "-"};
    const char *MI_TEST[] = {"signed >", "signed <=", "signed >=", "signed <", "!=", "==",
      "Not overflow", "Overflow", "&not; (C &or; Z)", "C &or; Z", "unsigned <", "unsigned >=",
      "unsigned >", "unsigned <=", "not N", "N"};
    
    // program lines
    for(auto& line : lines) {
      
      file << "<tr>";
      
      // Name and line number
      file << "<td>" << line.number;
      if(line.name.length() > 0) {
        file << " <tt>" << line.name << "</tt></td>";
      }
      
      // Interrupt
      file << "<td>";
      if(line.bits[79]) {
        file << "Dis";
      } else {
        file << "IE";
      }
      file << "</td>";
      
      file << "<td colspan=\"4\">" << MI_INTERRUPT[getInt(line.bits, 75, 78)] << "</td>";
      
      // Constant
      file << "<td>";
      if(line.bits[74]) {
        file << "D";
      } else {
        file << "K";
      }
      file << "</td>";
      
      file << "<td colspan=\"16\">" << getInt(line.bits, 58, 73) << "</td>";
    
      // Source
      file << "<td colspan=\"3\">" << MI_SRC[getInt(line.bits, 55, 57)] << "</td>";
    
      // Function
      file << "<td colspan=\"3\">" << MI_FUNC[getInt(line.bits, 52, 54)] << "</td>";
      
      // Destination
      file << "<td colspan=\"3\">" << MI_DEST[getInt(line.bits, 49, 51)] << "</td>";
    
      // RA Addr
      file << "<td colspan=\"4\">" << getInt(line.bits, 45, 48) << "</td>";      
      
      file << "<td>";
      if(line.bits[44]) {
        file << "MR";
      } else {
        file << "IR";
      }
      file << "</td>";
      
      // RB Addr
      file << "<td colspan=\"4\">" << getInt(line.bits, 40, 43) << "</td>";      
      
      file << "<td>";
      if(line.bits[39]) {
        file << "MR";
      } else {
        file << "IR";
      }
      file << "</td>";
      
      // Y-Mux
      file << "<td>";
      if(line.bits[38]) {
        file << "H";
      } else {
        file << "AB";
      }
      file << "</td>";
      
      file << "<td>";
      if(line.bits[37]) {
        file << "H";
      } else {
        file << "DB";
      }
      file << "</td>";
      
      // CIN-MUX
      file << "<td colspan=\"2\">" << MI_CIN_MUX[getInt(line.bits, 35, 36)] << "</td>";
      
      // Shifts
      // TODO unimplemented
      file << "<td colspan=\"4\"></td>";
      
      // Load status register
      file << "<td>";
      if(line.bits[30]) {
        file << "H";
      } else {
        file << "L";
      }
      file << "</td>";
      
      file << "<td>";
      if(line.bits[29]) {
        file << "H";
      } else {
        file << "L";
      }
      file << "</td>";
      
      // Test status register
      file << "<td colspan=\"2\">" << MI_TEST_WHAT[getInt(line.bits, 27, 28)] << "</td>";
      
      file << "<td colspan=\"4\">" << MI_TEST[getInt(line.bits, 23, 26)] << "</td>";
      
      //file << line.name << ": " << line.bits << endl;
      
      file << "</tr>" << endl;
    }
    
    file << "</table></body>" << endl << "</html>";
    
    file.close();
  } else {
    cout << "Cannot write file: " << path << endl;
  }
}

int getInt(const bitset<80> bits, int fromBit, int toBit) {
  int result = 0;
  
  for(int i = toBit; i >= fromBit; i--) {
    result = (result << 1) + bits[i];
  }
  
  return result;
}
