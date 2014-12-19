#include <fstream>
#include <iostream>
#include "util.h"
#include "latex.h"

void MPRWriterLaTeX::writeMulticolumn(std::ostream& file, std::string value, int colspan) {
	if (colspan > 1) {
		file << "\\multicolumn{" << colspan << "}{|l|}{" << value << "}";
	} else {
		file << value;
	}
}

void MPRWriterLaTeX::writeRotatedMulticolumn(std::ostream& file, std::string value, int colspan) {
	writeMulticolumn(file, "\\rotatebox[origin=c]{90}{" + value + "}", colspan);
}

void MPRWriterLaTeX::writeMulticolumnWithAmp(std::ostream& file, std::string value,
		int colspan) {
	writeMulticolumn(file, value, colspan);
	file << " & ";
}

void MPRWriterLaTeX::writeMulticolumnWithAmp(std::ostream& file, std::string value) {
	writeMulticolumn(file, value, 1);
	file << " & ";
}

bool MPRWriterLaTeX::writeMPR(std::ostream& file, const MPRFile& mprFile) {
	//std::ofstream file(path);

		const int TABLE_COL_COUNT = 49;

		// write LaTeX header
		file << "\\documentclass[landscape,10pt,oneside,a4paper]{article}\n"
				<< "\\usepackage[landscape, top=1cm, left=1cm, right=1cm, bottom=1cm]{geometry}\n"
				<< "\\usepackage{longtable}\n" << "\\usepackage{graphicx}\n" << "\\begin{document}\n"
				<< "\\thispagestyle{empty}\n" << "\\begin{center}\n"
				<< "\\begingroup\n"
				<< "\\setlength\\tabcolsep{3pt}\n" << "\\begin{longtable}{|";
		for (int i = 0; i < TABLE_COL_COUNT; i++) {
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
			} else if (i == 48) {
				file << " & {\\tiny 48 - 45}";
			} else if (i < 48 && i >= 45) {
				// no column
			} else if (i == 43) {
				file << " & {\\tiny 43 - 40}";
			} else if (i < 43 && i >= 40) {
				// no column
			} else {
				file << " & {\\tiny " << i << "}";
			}
		}
		file << " \\\\ \\hline\n";

		// table description header
		static ColumnDescriptor columnDescriptors[] = { { "IE", 1 }, {
				"Interrupt", 4 }, { "KMUX", 1 }, { "Konst.", 1 },
				{ "Src", 3 }, { "Func", 3 }, { "Dest", 3 }, { "RA", 1 }, {
						"ASEL", 1 }, { "RB", 1 }, { "BSEL", 1 }, { "YMUX", 2 },
				{ "CIN MUX", 2 }, { "Shift", 4 }, { "CE$\\mu$", 1 },
				{ "CEM", 1 }, { "Test", 6 }, { "CCEN", 1 }, { "AM2910", 4 }, {
						"BAR", 1 }, { "BZ\\_LD", 1 }, { "BZ\\_ED", 1 }, { "BZ\\_INC",
						1 }, { "BZ\\_EA", 1 }, { "IR\\_LD", 1 }, { "MWE", 1 }, {
				NULL, 0 } };

		// write header row
		for (ColumnDescriptor *column = columnDescriptors; column->name != NULL;
				column++) {

			file << " & ";
			writeRotatedMulticolumn(file, column->name, column->colspan);
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
				writeMulticolumn(file, "\\textbf{" + escapeLatex(line.getName()) + "}", TABLE_COL_COUNT);
				file << " \\\\\n";
				file << "\\hline\n";
				outputExtraNameLine = true;
			}

			// Name and line number
			file << line.getLineNumber();
			// don't insert the name of the line if there is already the special named row
			if (!outputExtraNameLine && !line.getName().empty()) {
				file << " {\\tiny " << escapeLatex(line.getName()) << "}";
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
			writeMulticolumnWithAmp(file, intToString(line.getRAAddr()), 1);
			writeMulticolumnWithAmp(file, line.getRAAddrContext());

			// RB Addr
			writeMulticolumnWithAmp(file, intToString(line.getRBAddr()), 1);
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
					replaceLatexCommands(line.getStatusRegisterTestContext()), 2);
			writeMulticolumnWithAmp(file,
					replaceLatexCommands(line.getStatusRegisterTest()), 4);

			// Condition Code Enable
			writeMulticolumnWithAmp(file, line.getConditionCodeEnable());

			// Jump
			writeMulticolumnWithAmp(file, line.getJump(), 4);

			// BAR
			int barColumn = line.getBAR();
			file << barColumn;
			// Disabled due to lack of space on A4 paper
			/*if (barColumn != 0) {
				std::string barName = mprFile.getMicroLineByLineNumber(
						barColumn);
				if (!barName.empty()) {
					file << " {\\tiny (" << escapeLatex(barName) << ")}";
				}
			}*/
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
		file << "\\hline\n" << "\\end{longtable}\n" << "\\endgroup\n" << "\\end{center}\n" << "\\end{document}";

		return true;
}

