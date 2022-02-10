#pragma once

#include "BaseObject.hpp"

#ifndef SIMPLEOBJECTS_CUSTOMIZED_NAMESPACE
namespace SimpleObjects
#else
namespace SIMPLEOBJECTS_CUSTOMIZED_NAMESPACE
#endif
{

/**
 * @brief Defining a interface class for objects that are hashable
 *
 */
class HashableBaseObject : public BaseObject
{
public: // Static Member

	using Base = BaseObject;

	static constexpr HashableBaseObject* sk_null = nullptr;

public:
	HashableBaseObject() = default;

	virtual ~HashableBaseObject() = default;

	virtual std::size_t Hash() const = 0;

	virtual std::unique_ptr<HashableBaseObject> Copy(const HashableBaseObject* /*unused*/) const = 0;

	virtual std::unique_ptr<HashableBaseObject> Move(const HashableBaseObject* /*unused*/) = 0;

	virtual std::unique_ptr<BaseObject> Copy(const BaseObject* /*unused*/) const override
	{
		return Copy(sk_null);
	}

	virtual std::unique_ptr<BaseObject> Move(const BaseObject* /*unused*/) override
	{
		return Move(sk_null);
	}

}; // class HashableBaseObject

}//namespace SimpleObjects

// ========== Hash ==========
namespace std
{
	template<>
#ifndef SIMPLEOBJECTS_CUSTOMIZED_NAMESPACE
	struct hash<SimpleObjects::HashableBaseObject>
	{
		using _ObjType = SimpleObjects::HashableBaseObject;
#else
	struct hash<SIMPLEOBJECTS_CUSTOMIZED_NAMESPACE::HashableBaseObject>
	{
		using _ObjType = SIMPLEOBJECTS_CUSTOMIZED_NAMESPACE::HashableBaseObject;
#endif
	public:

#if __cplusplus < 201703L
		typedef size_t       result_type;
		typedef _ObjType     argument_type;
#endif

		size_t operator()(const _ObjType& obj) const
		{
			return obj.Hash();
		}
	};
}
