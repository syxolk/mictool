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
    
    const char* MI_INTERRUPT = "LDM\0\0RDM\0\0CLM\0\0STM\0\0BCLM\0BSTM\0LDST\0RDST\0ENI\0\0DISI\0RDVC\0CLI\0\0CLMR\0CLMB\0CLVC\0MCL";
    
    // program lines
    for(auto& line : lines) {
      
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
      
      file << "<td>";
      file << MI_INTERRUPT + getInt(line.bits, 75, 78) * 5;
      file << "</td>";
      
      // Constant
      file << "<td>";
      if(line.bits[74]) {
        file << "D";
      } else {
        file << "K";
      }
      file << "</td>";
    
      file << line.name << ": " << line.bits << endl;
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
