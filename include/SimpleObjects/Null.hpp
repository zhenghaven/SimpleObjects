#pragma once

#include "HashableBaseObject.hpp"

#ifndef SIMPLEOBJECTS_CUSTOMIZED_NAMESPACE
namespace SimpleObjects
#else
namespace SIMPLEOBJECTS_CUSTOMIZED_NAMESPACE
#endif
{

class Null : public HashableBaseObject
{
public: // Static member:

	using Base = HashableBaseObject;

	static constexpr ObjCategory sk_cat()
	{
		return ObjCategory::Null;
	}

public:

	Null() = default;

	virtual ~Null() = default;

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

	virtual Null& AsNull() override
	{
		return *this;
	}

	virtual const Null& AsNull() const override
	{
		return *this;
	}

	using Base::Copy;
	virtual std::unique_ptr<HashableBaseObject> Copy(const HashableBaseObject* /*unused*/) const override
	{
		return CopyImpl();
	}

	using Base::Move;
	virtual std::unique_ptr<HashableBaseObject> Move(const HashableBaseObject* /*unused*/) override
	{
		return CopyImpl();
	}

private:

	std::unique_ptr<Null> CopyImpl() const
	{
		// TODO: make_unique
		return std::unique_ptr<Null>(new Null());
	}

}; //class Null

}//namespace SimpleObjects
