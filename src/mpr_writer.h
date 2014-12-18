#ifndef _MICTOOL_MPR_WRITER_H
#define _MICTOOL_MPR_WRITER_H

public class MPRWriter {
	public:
		virtual void writeMPR(std::ostream& stream, const std::string& title) =0;
};

#endif
