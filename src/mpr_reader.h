#ifndef _MICTOOL_MPR_READER_H_
#define _MICTOOL_MPR_READER_H_

#include <iostream>
#include "mpr.h"

/**
 * Interface that defines eaxactly one method: readMPR(ostream, file).
 * That method shall read an MPR file from the input stream into the MPR
 * file instance.
 *
 * @author Hans Kirchner
 */
class MPRReader {
	public:
		/**
		 * Empty constructor.
		 */
		MPRReader() {};

		/**
		 * Empty deconstructor. Can be overwritten in subclasses.
		 */
		virtual ~MPRReader() {};

		/**
		 * Read a single MPR file from the input stream and puts
		 * the parsed content into the given MPRFile instance.
		 *
		 * Virtual method that must be overwritten in subclasses.
		 *
		 * @return false if the reading or parsing failed
		 */
		virtual bool readMPR(std::istream& stream, MPRFile& file) =0;
};

#endif /* _MICTOOL_MPR_READER_H_ */

