#ifndef _MICTOOL_MPR_WRITER_H_
#define _MICTOOL_MPR_WRITER_H_

#include <iostream>
#include <mpr/mpr.h>

/**
 * @brief Interface which defines exactly one method: writeMPR(istream, file).
 *
 * That method shall write the given MPR file to the output stream.
 *
 * @author Hans Kirchner
 */
class MPRWriter {
	public:
		/**
		 * @brief Empty constructor.
		 */
		MPRWriter() {};

		/**
		 * @brief Empty deconstructor.
		 *
		 * Can be overwritten in subclasses because it's virtual.
		 */
		virtual ~MPRWriter() {};

		/**
		 * @brief Write the given MPR file to the output stream.
		 *
		 * Virtual method that must be implemented in subclasses.
		 *
		 * @param stream output stream to write the MPR file into
		 * @param mprFile MPRFile instance that will be written
		 * @return false if the writing failed otherwise true
		 */
		virtual bool writeMPR(std::ostream& stream, const MPRFile& mprFile) =0;
};

#endif /* _MICTOOL_MPR_WRITER_H_ */

