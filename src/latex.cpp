#include <fstream>
#include <iostream>
#include "util.h"
#include "latex.h"

struct ColumnDescriptor {
	const char* name;
	const int colspan;
};

void writeMulticolumn(std::ofstream& file, std::string value, int colspan) {
	if (colspan > 1) {
		file << "\\multicolumn{" << colspan << "}{|l|}{" << value << "}";
	} else {
		file << value;
	}
}

void writeRotatedMulticolumn(std::ofstream& file, std::string value, int colspan) {
	writeMulticolumn(file, "\\rotatebox[origin=c]{90}{" + value + "}", colspan);
}

void writeMulticolumnWithAmp(std::ofstream& file, std::string value,
		int colspan) {
	writeMulticolumn(file, value, colspan);
	file << " & ";
}

void writeMulticolumnWithAmp(std::ofstream& file, std::string value) {
	writeMulticolumn(file, value, 1);
	file << " & ";
}
bool writeLaTeX(const char* path, MPRFile& mprFile) {
	std::ofstream file(path);
	if (file.is_open()) {

		// write LaTeX header
		file << "\\documentclass[landscape,10pt,oneside,a4paper]{article}\n"
				<< "\\usepackage[landscape, top=1cm, left=1cm, right=1cm, bottom=1cm]{geometry}\n"
				<< "\\usepackage{longtable}\n" << "\\usepackage{graphicx}" << "\\begin{document}\n"
				<< "\\thispagestyle{empty}"
				<< "\\begin{center}\n" << "\\begin{longtable}{|";
		for (int i = 0; i < 55; i++) {
			file << "l|";
		}
		file << "}\n";

		file << "\\hline\n";
		// row with bit numbers
		for (int i = 79; i >= 0; i--) {
			if (i == 73) {
				file << " & {\\tiny 73 - 58}";
			} else if (i < 73 && i >= 58) {
				// no column
			} else if (i == 17) {
				file << " & {\\tiny 17 - 6}";
			} else if (i < 17 && i >= 6) {
				// no column
			} else {
				file << " & {\\tiny " << i << "}";
			}
		}
		file << " \\\\ \\hline\n";

		// table description header
		static ColumnDescriptor columnDescriptors[] = { { "IE", 1 }, {
				"Interrupt", 4 }, { "KMUX", 1 }, { "Konst.", 1 },
				{ "Src", 3 }, { "Func", 3 }, { "Dest", 3 }, { "RA", 4 }, {
						"ASEL", 1 }, { "RB", 4 }, { "BSEL", 1 }, { "YMUX", 2 },
				{ "CIN MUX", 2 }, { "Shift", 4 }, { "CE\\micro", 1 },
				{ "CEM", 1 }, { "Test", 6 }, { "CCEN", 1 }, { "AM2910", 4 }, {
						"BAR", 1 }, { "BZ_LD", 1 }, { "BZ_ED", 1 }, { "BZ_INC",
						1 }, { "BZ_EA", 1 }, { "IR_LD", 1 }, { "MWE", 1 }, {
				NULL, 0 } };

		// write header row
		for (ColumnDescriptor *column = columnDescriptors; column->name != NULL;
				column++) {

			file << " & ";
			writeRotatedMulticolumn(file, escapeLatex(column->name), column->colspan);
		}
		file << " \\\\ \\hline\n";

		int lastLineNumber = -1;
		bool outputExtraNameLine = true;
		bool isFirstLine = true;

		// program lines
		for (auto& line : mprFile.getMicroLines()) {

			// insert a special named row if there is a jump between the line numbers
			if (outputExtraNameLine
					|| (line.getLineNumber() > lastLineNumber + 1)) {

				if(!isFirstLine) {
					file << "\\hline\n";
				}
				writeMulticolumn(file, escapeLatex(line.getName()), 55);
				file << " \\\\\n";
				file << "\\hline\n";
				outputExtraNameLine = true;
			}

			// Name and line number
			file << line.getLineNumber();
			// don't insert the name of the line if there is already the special named row
			if (!outputExtraNameLine && !line.getName().empty()) {
				file << " " << escapeLatex(line.getName());
			}
			file << " & ";

			// Interrupt
			writeMulticolumnWithAmp(file, line.getInterruptFlag());
			writeMulticolumnWithAmp(file, line.getInterrupt(), 4);

			// KMUX
			writeMulticolumnWithAmp(file, line.getKMux());

			// Constant
			writeMulticolumnWithAmp(file, intToString(line.getConstant()));

			// Source
			writeMulticolumnWithAmp(file, line.getSource(), 3);

			// Function
			writeMulticolumnWithAmp(file, line.getFunction(), 3);

			// Destination
			writeMulticolumnWithAmp(file, line.getDestination(), 3);

			// RA Addr
			writeMulticolumnWithAmp(file, intToString(line.getRAAddr()), 4);
			writeMulticolumnWithAmp(file, line.getRAAddrContext());

			// RB Addr
			writeMulticolumnWithAmp(file, intToString(line.getRBAddr()), 4);
			writeMulticolumnWithAmp(file, line.getRBAddrContext());

			// Y-Mux
			writeMulticolumnWithAmp(file, line.getYMuxAB());
			writeMulticolumnWithAmp(file, line.getYMuxDB());

			// CIN-MUX
			writeMulticolumnWithAmp(file, line.getCINMux(), 2);

			// Shifts
			writeMulticolumnWithAmp(file, line.getShifts(), 4);

			// Load status register
			writeMulticolumnWithAmp(file, line.getCEMicro());
			writeMulticolumnWithAmp(file, line.getCEMachine());

			// Test status register
			writeMulticolumnWithAmp(file,
					escapeLatex(line.getStatusRegisterTestContext()), 2);
			writeMulticolumnWithAmp(file,
					escapeLatex(line.getStatusRegisterTest()), 4);

			// Condition Code Enable
			writeMulticolumnWithAmp(file, line.getConditionCodeEnable());

			// Jump
			writeMulticolumnWithAmp(file, line.getJump(), 4);

			// BAR
			int barColumn = line.getBAR();
			file << barColumn;
			if (barColumn != 0) {
				std::string barName = mprFile.getMicroLineByLineNumber(
						barColumn);
				if (!barName.empty()) {
					file << " (" << escapeLatex(barName) << ")";
				}
			}
			file << " & ";

			// BZ_LD
			writeMulticolumnWithAmp(file, line.getBZ_LD());

			// BZ_ED
			writeMulticolumnWithAmp(file, line.getBZ_ED());

			// BZ_INC
			writeMulticolumnWithAmp(file, line.getBZ_INC());

			// BZ_EA
			writeMulticolumnWithAmp(file, line.getBZ_EA());

			// IR_LD
			writeMulticolumnWithAmp(file, line.getIR_LD());

			// MWE
			writeMulticolumn(file, line.getMWE(), 1);

			file << " \\\\\n";

			// save the last line number and reset the extra name row variable
			lastLineNumber = line.getLineNumber();
			outputExtraNameLine = false;
			isFirstLine = false;
		}

		// output machine program / RAM
		file << "\\end{longtable}\n" << "\\end{center}\n" << "\\end{document}";

		file.close();
		return true;
	} else {
		std::cout << "Cannot write file: " << path << std::endl;
		return false;
	}
}