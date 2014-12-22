#ifndef _MICTOOL_MPR_READER_H_
#define _MICTOOL_MPR_READER_H_

#include <iostream>
#include "mpr.h"

/**
 * @brief Interface that defines exactly one method: readMPR(ostream, file).
 *
 * That method shall read an MPR file from the input stream into the MPR
 * file instance.
 *
 * @author Hans Kirchner
 */
class MPRReader {
	public:
		/**
		 * @brief Empty constructor.
		 */
		MPRReader() {};

		/**
		 * @brief Empty deconstructor.
		 *
		 * Can be overwritten in subclasses.
		 */
		virtual ~MPRReader() {};

		/**
		 * @brief Read a single MPR file from the input stream.
		 *
		 * Puts the parsed content into the given MPRFile instance.
		 *
		 * Virtual method that must be overwritten in subclasses.
		 *
		 * @param stream input stream to read from
		 * @param mprFile MPR file instance to put parsed data into
		 * @return false if the reading or parsing failed otherwise true
		 */
		virtual bool readMPR(std::istream& stream, MPRFile& mprFile) =0;
};

#endif /* _MICTOOL_MPR_READER_H_ */

