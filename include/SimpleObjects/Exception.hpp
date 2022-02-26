#pragma once

#include <string>
#include <stdexcept>

#ifndef SIMPLEOBJECTS_CUSTOMIZED_NAMESPACE
namespace SimpleObjects
#else
namespace SIMPLEOBJECTS_CUSTOMIZED_NAMESPACE
#endif
{

/**
 * @brief The exception base class for all SimpleObjects classes' exceptions.
 *        This class is inherited from std::runtime_error class.
 *
 */
class Exception : public std::runtime_error
{
public:

	/**
	 * @brief Construct a new Exception object.
	 *        Same usage as the one in std::runtime_error.
	 *
	 * @param what_arg explanatory string
	 */
	Exception(const std::string& what_arg) :
		std::runtime_error(what_arg)
	{}

	/**
	 * @brief Construct a new Exception object.
	 *        Same usage as the one in std::runtime_error.
	 *
	 * @param what_arg explanatory string
	 */
	Exception(const char* what_arg) :
		std::runtime_error(what_arg)
	{}

	/**
	 * @brief Construct a new Exception object.
	 *        Same usage as the one in std::runtime_error.
	 *
	 * @param other another exception object to copy
	 */
	Exception(const Exception& other) noexcept :
		std::runtime_error(other)
	{}

	// LCOV_EXCL_START
	/**
	 * @brief Destroy the Exception object
	 *
	 */
	virtual ~Exception() = default;
	// LCOV_EXCL_STOP

}; // class Exception

class UnsupportedOperation : public Exception
{
public:

	UnsupportedOperation(
		const std::string& opName,
		const std::string& typeAName,
		const std::string& typeBName) :
		Exception("Operation \'" + opName + "\' is not supported between type \'" +
			typeAName + "\' and type \'" + typeBName + "\'")
	{}

	// LCOV_EXCL_START
	/**
	 * @brief Destroy the Unsupported Operation object
	 *
	 */
	virtual ~UnsupportedOperation() = default;
	// LCOV_EXCL_STOP

}; // class UnsupportedOperation

class TypeError : public Exception
{
public:

	TypeError(const std::string& expType, const std::string& actType) :
		Exception("Expecting type \'" + expType + "\', while the type \'" + actType + "\' is given")
	{}

	// LCOV_EXCL_START
	/**
	 * @brief Destroy the Type Error object
	 *
	 */
	virtual ~TypeError() = default;
	// LCOV_EXCL_STOP

}; // class TypeError

}//namespace SimpleObjects
