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
template<typename _ToStringType>
class HashableBaseObject : public BaseObject<_ToStringType>
{
public: // Static Member

	using Self = HashableBaseObject<_ToStringType>;
	using Base = BaseObject<_ToStringType>;
	using ToStringType = _ToStringType;

	using NullBase    = typename Base::NullBase;
	using NumericBase = typename Base::NumericBase;
	using StringBase  = typename Base::StringBase;
	using ListBase    = typename Base::ListBase;
	using DictBase    = typename Base::DictBase;

	static constexpr Self* sk_null = nullptr;

public:
	HashableBaseObject() = default;

	virtual ~HashableBaseObject() = default;

	virtual std::size_t Hash() const = 0;

	virtual std::unique_ptr<Self> Copy(const Self* /*unused*/) const = 0;

	virtual std::unique_ptr<Self> Move(const Self* /*unused*/) = 0;

	virtual std::unique_ptr<Base> Copy(const Base* /*unused*/) const override
	{
		return Copy(sk_null);
	}

	virtual std::unique_ptr<Base> Move(const Base* /*unused*/) override
	{
		return Move(sk_null);
	}

}; // class HashableBaseObject

}//namespace SimpleObjects

// ========== Hash ==========
namespace std
{
	template<typename _ToStringType>
#ifndef SIMPLEOBJECTS_CUSTOMIZED_NAMESPACE
	struct hash<SimpleObjects::HashableBaseObject<_ToStringType> >
	{
		using _ObjType = SimpleObjects::HashableBaseObject<_ToStringType>;
#else
	struct hash<SIMPLEOBJECTS_CUSTOMIZED_NAMESPACE::HashableBaseObject<_ToStringType> >
	{
		using _ObjType = SIMPLEOBJECTS_CUSTOMIZED_NAMESPACE::HashableBaseObject<_ToStringType>;
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
