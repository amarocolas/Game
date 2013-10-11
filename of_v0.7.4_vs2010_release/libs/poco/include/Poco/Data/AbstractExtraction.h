//
// AbstractExtraction.h
//
// $Id: //poco/1.4/Data/include/Poco/Data/AbstractExtraction.h#1 $
//
// Library: Data
// Package: DataCore
// Module:  AbstractExtraction
//
// Definition of the AbstractExtraction class.
//
// Copyright (c) 2006, Applied Informatics Software Engineering GmbH.
// and Contributors.
//
// Permission is hereby granted, free of charge, to any person or organization
// obtaining a copy of the software and accompanying documentation covered by
// this license (the "Software") to use, reproduce, display, distribute,
// execute, and transmit the Software, and to prepare derivative works of the
// Software, and to permit third-parties to whom the Software is furnished to
// do so, all subject to the following:
// 
// The copyright notices in the Software and this entire statement, including
// the above license grant, this restriction and the following disclaimer,
// must be included in all copies of the Software, in whole or in part, and
// all derivative works of the Software, unless such copies or derivative
// works are solely in the form of machine-executable object code generated by
// a source language processor.
// 
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE, TITLE AND NON-INFRINGEMENT. IN NO EVENT
// SHALL THE COPYRIGHT HOLDERS OR ANYONE DISTRIBUTING THE SOFTWARE BE LIABLE
// FOR ANY DAMAGES OR OTHER LIABILITY, WHETHER IN CONTRACT, TORT OR OTHERWISE,
// ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
// DEALINGS IN THE SOFTWARE.
//


#ifndef Data_AbstractExtraction_INCLUDED
#define Data_AbstractExtraction_INCLUDED


#include "Poco/Data/Data.h"
#include "Poco/Data/AbstractExtractor.h"
#include "Poco/Data/Limit.h"
#include "Poco/RefCountedObject.h"
#include "Poco/AutoPtr.h"
#include <vector>
#include <cstddef>


namespace Poco {
namespace Data {


class AbstractPrepare;
class AbstractPreparation;


class Data_API AbstractExtraction: public Poco::RefCountedObject
	/// AbstractExtraction is the interface class that connects output positions to concrete values
	/// retrieved via an AbstractExtractor.
{
public:
	AbstractExtraction(Poco::UInt32 limit = Limit::LIMIT_UNLIMITED);
		/// Creates the AbstractExtraction. A limit value equal to EXTRACT_UNLIMITED (0xffffffffu) 
		/// means that we extract as much data as possible during one execute.
		/// Otherwise the limit value is used to partition data extracting to a limited amount of rows.

	virtual ~AbstractExtraction();
		/// Destroys the AbstractExtraction.

	void setExtractor(AbstractExtractor* pExtractor);
		/// Sets the class used for extracting the data. Does not take ownership of the pointer.

	AbstractExtractor* getExtractor() const;
		/// Retrieves the extractor object

	virtual std::size_t numOfColumnsHandled() const = 0;
		/// Returns the number of columns that the extraction handles.
		///
		/// The trivial case will be one single column but when
		/// complex types are used this value can be larger than one.

	virtual std::size_t numOfRowsHandled() const = 0;
		/// Returns the number of rows that the extraction handles.
		///
		/// The trivial case will be one single row but 
		/// for collection data types (ie vector) it can be larger.

	virtual std::size_t numOfRowsAllowed() const = 0;
		/// Returns the upper limit on number of rows that the extraction will handle.

	virtual void extract(std::size_t pos) = 0;
		/// Extracts a value from the param, starting at the given column position.

	virtual void reset() = 0;
		/// Resets the etxractor so that it can be re-used.

	virtual AbstractPrepare* createPrepareObject(AbstractPreparation* pPrep, std::size_t pos) const = 0;
		/// Creates a Prepare object for the etxracting object

	void setLimit(Poco::UInt32 limit);
		/// Sets the limit.

	Poco::UInt32 getLimit() const;
		/// Gets the limit.

private:
	AbstractExtractor* _pExtractor;
	Poco::UInt32       _limit;
};


typedef Poco::AutoPtr<AbstractExtraction> AbstractExtractionPtr;
typedef std::vector<AbstractExtractionPtr> AbstractExtractionVec;


//
// inlines
//
inline void AbstractExtraction::setExtractor(AbstractExtractor* pExtractor)
{
	_pExtractor = pExtractor;
}


inline AbstractExtractor* AbstractExtraction::getExtractor() const
{
	return _pExtractor;
}


inline void AbstractExtraction::setLimit(Poco::UInt32 limit)
{
	_limit = limit;
}


inline Poco::UInt32 AbstractExtraction::getLimit() const
{
	return _limit;
}


} } // namespace Poco::Data


#endif // Data_AbstractExtraction_INCLUDED
