#pragma once

#include "HashableBaseObject.hpp"
#include "ToString.hpp"

#ifndef SIMPLEOBJECTS_CUSTOMIZED_NAMESPACE
namespace SimpleObjects
#else
namespace SIMPLEOBJECTS_CUSTOMIZED_NAMESPACE
#endif
{

template<typename _ToStringType>
class NullImpl : public HashableBaseObject<_ToStringType>
{
public: // Static member:

	using ToStringType = _ToStringType;
	using Self = NullImpl<_ToStringType>;
	using Base = HashableBaseObject<_ToStringType>;

	static constexpr ObjCategory sk_cat()
	{
		return ObjCategory::Null;
	}

	static constexpr Self* sk_null = nullptr;

public:

	NullImpl() = default;

	virtual ~NullImpl() = default;

	virtual ObjCategory GetCategory() const override
	{
		return sk_cat();
	}

	virtual const char* GetCategoryName() const override
	{
		return "Null";
	}

	virtual std::size_t Hash() const override
	{
		// In a fix of GCC that adds support for std::hash<nullptr_t>, it will
		// always return zero for hash(nullptr)
		// see: https://gcc.gnu.org/git/?p=gcc.git&a=commit;h=17a73b3c47f58155350af2e1ca359e915ffedcae
		return 0;
	}

	virtual bool IsNull() const override
	{
		return true;
	}

	virtual Self& AsNull() override
	{
		return *this;
	}

	virtual const Self& AsNull() const override
	{
		return *this;
	}

	using Base::Copy;
	virtual std::unique_ptr<Base> Copy(const Base* /*unused*/) const override
	{
		return CopyImpl();
	}

	using Base::Move;
	virtual std::unique_ptr<Base> Move(const Base* /*unused*/) override
	{
		return CopyImpl();
	}

	virtual std::string DebugString() const override
	{
		return "null";
	}

	virtual std::string ShortDebugString() const override
	{
		return DebugString();
	}

	virtual ToStringType ToString() const override
	{
		return Internal::ToString<ToStringType>("null");
	}

	virtual void DumpString(OutIterator<typename ToStringType::value_type> outIt) const override
	{
		using StrValType = typename ToStringType::value_type;
		static constexpr StrValType str[] = "null";
		std::copy(std::begin(str), std::end(str) - 1, outIt);
	}

private:

	std::unique_ptr<Self> CopyImpl() const
	{
		// TODO: make_unique
		return std::unique_ptr<Self>(new Self());
	}

}; //class NullImpl

}//namespace SimpleObjects
