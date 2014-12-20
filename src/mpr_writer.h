#ifndef _MICTOOL_MPR_WRITER_H_
#define _MICTOOL_MPR_WRITER_H_

#include <iostream>
#include "mpr.h"

/**
 * Interface which defines exactly one method: writeMPR(istream, file).
 * That method shall write the given MPR file to the output stream.
 *
 * @author Hans Kirchner
 */
class MPRWriter {
	public:
		/**
		 * Empty constructor.
		 */
		MPRWriter() {};

		/**
		 * Empty deconstructor. Can be overwritten in subclasses
		 * because it's virtual.
		 */
		virtual ~MPRWriter() {};

		/**
		 * Write the given MPR file to the output stream.
		 *
		 * Virtual method that must be implemented in subclasses.
		 *
		 * @return false if the writing failed
		 */
		virtual bool writeMPR(std::ostream& stream, const MPRFile& file) =0;
};

#endif /* _MICTOOL_MPR_WRITER_H_ */

