#include <fstream>
#include <iostream>
#include "html.h"
#include "util.h"

struct ColumnDescriptor {
  const char* name;
  const int colspan;
};

void writeTD(std::ostream& file, std::string value, int colspan, bool checkDefault) {
	file << "<td";

	if(colspan > 1) {
		file << " colspan=\"" << colspan << "\"";
	}

	if(checkDefault && MicroLine::isDefaultValue(value)) {
		file << " class=\"default\"";
	}

	file << ">" << value << "</td>";
}

void writeTDWithCheckDefault(std::ostream& file, std::string value) {
	writeTD(file, value, 1, true);
}

void writeTD(std::ostream& file, std::string value, int colspan) {
	writeTD(file, value, colspan, false);
}

void writeTD(std::ostream& file, std::string value) {
	writeTD(file, value, 1, false);
}

bool MPRWriterHTML::writeMPR(std::ostream& file, const MPRFile& mprFile) {
  //std::ofstream file(path);

    // write HTML header
    file << "<!doctype html>\n"
      << "<html>\n"
      << "<head>\n"
      << "<meta charset=\"utf-8\"><title>" << htmlspecialchars(mprFile.getName()) << "</title>\n"
      << "<style type=\"text/css\">\n"
      << ".bits, .description {font-size: xx-small;}\n"
      << ".ram {font-size: small;}\n"
      << ".program, .program th, .program td, .ram, .ram th, .ram td {border: 1px solid black;}\n"
      << ".program, .ram {border-collapse: collapse;}\n"
      << ".program .line-name {font-family: monospace;}\n"
      << ".program .default {color: lightgray;}\n"
      << ".program th {padding:5px;text-align:left;}\n"
      << "h1 {font-size: large;}\n"
      << "</style>\n"
      << "</head>\n"
      << "<body>\n";

    file << "<table class=\"program\">\n";

    // bit numbers from 79 to 0
    // skips some columns because we want less chars in the big columns
    file << "<tr class=\"bits\"><td></td>";
    for(int i = 79; i >= 0; i--) {
      if(i == 73) {
        file << "<td>73 - 58</td>";
      } else if(i < 73 && i >= 58) {
        // no column
      } else if(i == 17) {
        file << "<td>17 - 6</td>";
      } else if(i < 17 && i >= 6) {
        // no column
      } else {
        file << "<td>" << i << "</td>";
      }
    }
    file << "</tr>\n";

    // table description header
    static ColumnDescriptor columnDescriptors[] = {
      {"IE", 1},
      {"Interrupt", 4},
      {"KMUX", 1},
      {"Konstante", 1},
      {"Src", 3},
      {"Func", 3},
      {"Dest", 3},
      {"RA", 4}, {"ASEL", 1},
      {"RB", 4}, {"BSEL", 1},
      {"YMUX", 2}, {"CIN MUX", 2},
      {"Shift", 4},
      {"CE&micro;", 1}, {"CEM", 1},
      {"Test", 6},
      {"CCEN", 1},
      {"AM2910", 4},
      {"BAR", 1},
      {"BZ_LD", 1}, {"BZ_ED", 1}, {"BZ_INC", 1}, {"BZ_EA", 1},
      {"IR_LD", 1}, {"MWE", 1},
      {NULL, 0}
    };

    // write header row
    file << "<tr class=\"description\"><td></td>";
    for(ColumnDescriptor *column = columnDescriptors; column->name != NULL; column++) {
      writeTD(file, column->name, column->colspan);
    }
    file << "</tr>\n";

    int lastLineNumber = -1;
    bool outputExtraNameLine = true;

    // program lines
    for(auto& line : mprFile.getMicroLines()) {

      // insert a special named row if there is a jump between the line numbers
      if(outputExtraNameLine || (line.getLineNumber() > lastLineNumber + 1)) {
        file << "<tr><th colspan=\"55\">" << htmlspecialchars(line.getName()) << "</th></tr>\n";
        outputExtraNameLine = true;
      }

      file << "<tr>";

      // Name and line number
      file << "<td>" << line.getLineNumber();
      // don't insert the name of the line if there is already the special named row
      if(!outputExtraNameLine && !line.getName().empty()) {
        file << " <span class=\"line-name\">" << htmlspecialchars(line.getName()) << "</span>";
      }
      file << "</td>";

      // Interrupt
      writeTD(file, line.getInterruptFlag());
      writeTD(file, line.getInterrupt(), 4);

      // KMUX
      writeTD(file, line.getKMux());

      // Constant
      writeTD(file, intToString(line.getConstant()));

      // Source
      writeTD(file, line.getSource(), 3);

      // Function
      writeTD(file, line.getFunction(), 3);

      // Destination
      writeTD(file, line.getDestination(), 3);

      // RA Addr
      writeTD(file, intToString(line.getRAAddr()), 4);
      writeTD(file, line.getRAAddrContext());

      // RB Addr
      writeTD(file, intToString(line.getRBAddr()), 4);
      writeTD(file, line.getRBAddrContext());

      // Y-Mux
      writeTDWithCheckDefault(file, line.getYMuxAB());
      writeTDWithCheckDefault(file, line.getYMuxDB());

      // CIN-MUX
      writeTD(file, line.getCINMux(), 2);

      // Shifts
      writeTD(file, line.getShifts(), 4);

      // Load status register
      writeTDWithCheckDefault(file, line.getCEMicro());
      writeTDWithCheckDefault(file, line.getCEMachine());

      // Test status register
      writeTD(file, replaceHtmlCommands(line.getStatusRegisterTestContext()), 2);
      writeTD(file, replaceHtmlCommands(line.getStatusRegisterTest()), 4);

      // Condition Code Enable
      writeTD(file, line.getConditionCodeEnable());

      // Jump
      writeTD(file, line.getJump(), 4);

      // BAR
      int barColumn = line.getBAR();
      file << "<td>" << barColumn;
      if(barColumn != 0) {
        std::string barName = mprFile.getMicroLineByLineNumber(barColumn);
        if(!barName.empty()) {
          file << " (" << htmlspecialchars(barName) << ")";
        }
      }
      file << "</td>";

      // BZ_LD
      writeTDWithCheckDefault(file, line.getBZ_LD());

      // BZ_ED
      writeTDWithCheckDefault(file, line.getBZ_ED());

      // BZ_INC
      writeTDWithCheckDefault(file, line.getBZ_INC());

      // BZ_EA
      writeTDWithCheckDefault(file, line.getBZ_EA());

      // IR_LD
      writeTDWithCheckDefault(file, line.getIR_LD());

      // MWE
      writeTDWithCheckDefault(file, line.getMWE());

      file << "</tr>\n";

      // save the last line number and reset the extra name row variable
      lastLineNumber = line.getLineNumber();
      outputExtraNameLine = false;
    }

    // output machine program / RAM
    file << "</table>\n";
    file << "<h1>Machine program</h1>\n";
    file << "<table class=\"ram\">\n";
    file << "<tr><th>#</th><th>data</th><th>interpretation</th></tr>\n";

    int i = 0;
    for(auto& cell : mprFile.getRamCells()) {
      file << "<tr><td>" << (i++) <<"</td><td>" << cell.getData() << "</td><td>";

      // if this is may be no data but an opcode
      if(cell.couldHaveAnOpcode()) {
        int opCode = cell.getOpCode();
        std::string name = mprFile.getMicroLineByLineNumber(opCode * 16);

        if(!name.empty()) {
          file << htmlspecialchars(name);
        }
      }

      file << "</td></tr>\n";
    }

    file << "</table>\n</body>\n</html>";

    return true;
}
