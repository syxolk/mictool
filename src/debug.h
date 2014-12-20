#ifndef _MICTOOL_DEBUG_H_
#define _MICTOOL_DEBUG_H_

#include <iostream>
#include "mpr.h"
#include "mpr_writer.h"

/**
 * Special implementation of MPRWriter that is only
 * intended to be used for debugging purposes.
 *
 * It outputs the raw content of an MPRFile instance.
 *
 * @author Hans Kirchner
 */
class MPRWriterDebug : public MPRWriter {
	public:
		/**
		 * Constructs a new debug writer.
		 */
		MPRWriterDebug() {};

		/**
		 * Write the raw content of the MPR file to the output stream.
		 *
		 * @return always true since there can't be an error here
		 */
		bool writeMPR(std::ostream& stream, const MPRFile& mpr);
};

#endif /* _MICTOOL_DEBUG_H_ */

