#ifndef _MICTOOL_DEBUG_H_
#define _MICTOOL_DEBUG_H_

#include <iostream>
#include <mpr/mpr.h>
#include <writer/mpr_writer.h>

/**
 * @brief Implementation of MPRWriter for debugging outputs.
 *
 * This is only relevant for developers of this program.
 * It outputs the raw content of an MPRFile instance.
 *
 * @author Hans Kirchner
 */
class MPRWriterDebug : public MPRWriter {
	public:
		/**
		 * @brief Constructs a new debug writer.
		 */
		MPRWriterDebug() {};

		/**
		 * @brief Write the raw content of the MPR file to the output stream.
		 *
		 * @param stream the method will write into this stream
		 * @param mprFile this MPR file will be written
		 * @return always true since there can't be an error here
		 */
		bool writeMPR(std::ostream& stream, const MPRFile& mprFile);
};

#endif /* _MICTOOL_DEBUG_H_ */

