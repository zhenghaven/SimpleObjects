#pragma once

#include "NumericBaseObject.hpp"

#include <functional>
#include <tuple>
#include <type_traits>

#include "Exception.hpp"
#include "NumericTypeInfer.hpp"
#include "Utils.hpp"

#ifndef SIMPLEOBJECTS_CUSTOMIZED_NAMESPACE
namespace SimpleObjects
#else
namespace SIMPLEOBJECTS_CUSTOMIZED_NAMESPACE
#endif
{

template<typename _ValType>
class Numeric : public NumericBaseObject
{
public: // Static member:

	using _InternalType = _ValType;
	using Self = Numeric<_InternalType>;
	using Base = NumericBaseObject;

	static constexpr ObjCategory sk_cat();

	template<typename _OtherInternalType>
	friend class Numeric;

	friend struct std::hash<Self>;

public:
	Numeric() :
		m_data()
	{}

	explicit Numeric(const _InternalType& val) :
		m_data(val)
	{}

	explicit Numeric(_InternalType&& val) noexcept :
		m_data(std::forward<_InternalType>(val))
	{}

	Numeric(const Numeric& other) :
		m_data(other.m_data)
	{}

	Numeric(Numeric&& other) noexcept:
		m_data(std::forward<_InternalType>(other.m_data))
	{}

	virtual ~Numeric() = default;

	operator bool() const
	{
		return static_cast<bool>(m_data);
	}

	// ========== Assignment and Move ==========

	Numeric& operator=(const _InternalType& rhs)
	{
		m_data = rhs;

		return *this;
	}

	Numeric& operator=(_InternalType&& rhs) noexcept
	{
		m_data = std::forward<_InternalType>(rhs);

		return *this;
	}

	Numeric& operator=(const Numeric& rhs)
	{
		m_data = rhs.m_data;

		return *this;
	}

	Numeric& operator=(Numeric&& rhs) noexcept
	{
		m_data = std::forward<_InternalType>(rhs.m_data);

		return *this;
	}

	// ========== operators for Numeric ==========
	// ==, !=, <=, >=, <, >,
	// &, |, ^, <<, >>, ~,
	// +=, -=, *=, /=, %=, &=, |=, ^=
	// ++, --, -

	template<typename _RhsInternalType>
	Numeric<bool> operator==(const Numeric<_RhsInternalType>& rhs) const
	{
		return Numeric<bool>(
			Internal::
				BoolToInt<_InternalType, _RhsInternalType>::Convert(m_data) ==
			Internal::
				BoolToInt<_RhsInternalType, _InternalType>::Convert(rhs.m_data));
	}

	template<typename _RhsInternalType>
	Numeric<bool> operator!=(const Numeric<_RhsInternalType>& rhs) const
	{
		return Numeric<bool>(
			Internal::
				BoolToInt<_InternalType, _RhsInternalType>::Convert(m_data) !=
			Internal::
				BoolToInt<_RhsInternalType, _InternalType>::Convert(rhs.m_data));
	}

	template<typename _RhsInternalType>
	Numeric<bool> operator<=(const Numeric<_RhsInternalType>& rhs) const
	{
		return Numeric<bool>(
			Internal::
				BoolToInt<_InternalType, _RhsInternalType>::Convert(m_data) <=
			Internal::
				BoolToInt<_RhsInternalType, _InternalType>::Convert(rhs.m_data));
	}

	template<typename _RhsInternalType>
	Numeric<bool> operator>=(const Numeric<_RhsInternalType>& rhs) const
	{
		return Numeric<bool>(
			Internal::
				BoolToInt<_InternalType, _RhsInternalType>::Convert(m_data) >=
			Internal::
				BoolToInt<_RhsInternalType, _InternalType>::Convert(rhs.m_data));
	}

	template<typename _RhsInternalType>
	Numeric<bool> operator<(const Numeric<_RhsInternalType>& rhs) const
	{
		return Numeric<bool>(
			Internal::
				BoolToInt<_InternalType, _RhsInternalType>::Convert(m_data) <
			Internal::
				BoolToInt<_RhsInternalType, _InternalType>::Convert(rhs.m_data));
	}

	template<typename _RhsInternalType>
	Numeric<bool> operator>(const Numeric<_RhsInternalType>& rhs) const
	{
		return Numeric<bool>(
			Internal::
				BoolToInt<_InternalType, _RhsInternalType>::Convert(m_data) >
			Internal::
				BoolToInt<_RhsInternalType, _InternalType>::Convert(rhs.m_data));
	}

	template<typename _RhsInternalType>
	Self operator&(const Numeric<_RhsInternalType>& rhs) const
	{
		return Self(m_data & rhs.m_data);
	}

	template<typename _RhsInternalType>
	Self operator|(const Numeric<_RhsInternalType>& rhs) const
	{
		return Self(m_data | rhs.m_data);
	}

	template<typename _RhsInternalType>
	Self operator^(const Numeric<_RhsInternalType>& rhs) const
	{
		return Self(m_data ^ rhs.m_data);
	}

	template<typename _RhsInternalType>
	Self operator<<(const Numeric<_RhsInternalType>& rhs) const
	{
		return Self(m_data << rhs.m_data);
	}

	template<typename _RhsInternalType>
	Self operator>>(const Numeric<_RhsInternalType>& rhs) const
	{
		return Self(m_data >> rhs.m_data);
	}

	Self operator~() const
	{
		return Self(~m_data);
	}

	template<typename _RhsInternalType>
	Numeric& operator+=(const Numeric<_RhsInternalType>& rhs)
	{
		m_data = static_cast<_InternalType>(m_data + rhs.m_data);
		return *this;
	}

	template<typename _RhsInternalType>
	Numeric& operator-=(const Numeric<_RhsInternalType>& rhs)
	{
		m_data = static_cast<_InternalType>(m_data - rhs.m_data);
		return *this;
	}

	template<typename _RhsInternalType>
	Numeric& operator*=(const Numeric<_RhsInternalType>& rhs)
	{
		m_data = static_cast<_InternalType>(m_data * rhs.m_data);
		return *this;
	}

	template<typename _RhsInternalType>
	Numeric& operator/=(const Numeric<_RhsInternalType>& rhs)
	{
		m_data = static_cast<_InternalType>(m_data / rhs.m_data);
		return *this;
	}

	Numeric& operator+=(const Numeric& rhs)
	{
		m_data += rhs.m_data;
		return *this;
	}

	Numeric& operator-=(const Numeric& rhs)
	{
		m_data -= rhs.m_data;
		return *this;
	}

	Numeric& operator*=(const Numeric& rhs)
	{
		m_data *= rhs.m_data;
		return *this;
	}

	Numeric& operator/=(const Numeric& rhs)
	{
		m_data /= rhs.m_data;
		return *this;
	}

	template<typename _RhsInternalType>
	Numeric& operator%=(const Numeric<_RhsInternalType>& rhs)
	{
		m_data %= rhs.m_data;
		return *this;
	}

	template<typename _RhsInternalType>
	Numeric& operator&=(const Numeric<_RhsInternalType>& rhs)
	{
		m_data &= rhs.m_data;
		return *this;
	}

	template<typename _RhsInternalType>
	Numeric& operator|=(const Numeric<_RhsInternalType>& rhs)
	{
		m_data |= rhs.m_data;
		return *this;
	}

	template<typename _RhsInternalType>
	Numeric& operator^=(const Numeric<_RhsInternalType>& rhs)
	{
		m_data ^= rhs.m_data;
		return *this;
	}

	Numeric& operator++()
	{
		++m_data;
		return *this;
	}

	Numeric& operator--()
	{
		--m_data;
		return *this;
	}

	Self operator++(int)
	{
		return Self(m_data++);
	}

	Self operator--(int)
	{
		return Self(m_data--);
	}

	Self operator-() const
	{
		return Self(-m_data);
	}

	virtual ObjCategory GetCategory() const override
	{
		return sk_cat();
	}

	virtual const char* GetCategoryName() const override;

	virtual bool operator==(const NumericBaseObject& rhs) const override;

	virtual bool operator<(const NumericBaseObject& rhs) const override;

	virtual bool operator>(const NumericBaseObject& rhs) const override;

	virtual std::size_t Hash() const override
	{
		return std::hash<_InternalType>()(m_data);
	}

	virtual NumericType GetNumType() const override;

	virtual const char* GetNumTypeName() const override;

	const _InternalType& GetVal() const
	{
		return m_data;
	}

	template<typename _RetType, typename _Op>
	std::tuple<bool, _RetType> GenericBinaryOp(const NumericBaseObject& rhs, _Op op) const;

	template<typename _RetType, typename _Op>
	_RetType GenericBinaryOpThrow(
		const std::string& opName, const NumericBaseObject& rhs, _Op op) const
	{
		bool isSupported = false;
		_RetType res;

		std::tie(isSupported, res) = GenericBinaryOp<_RetType>(rhs, op);
		if (!isSupported)
		{
			throw UnsupportedOperation(opName, GetNumTypeName(), rhs.GetNumTypeName());
		}

		return res;
	}

	using Base::Copy;
	virtual std::unique_ptr<NumericBaseObject> Copy(const NumericBaseObject* /*unused*/) const override
	{
		return CopyImpl();
	}

	using Base::Move;
	virtual std::unique_ptr<NumericBaseObject> Move(const NumericBaseObject* /*unused*/) override
	{
		return MoveImpl();
	}

protected:

	//std::unique_ptr<NumericBase> UnsupportedGenericBinaryOp(const NumericBase& rhs, OperationType opType);

private:

	std::unique_ptr<Self> CopyImpl() const
	{
		// TODO: make_unique
		return std::unique_ptr<Self>(new Self(*this));
	}

	std::unique_ptr<Self> MoveImpl()
	{
		// TODO: make_unique
		return std::unique_ptr<Self>(new Self(std::move(*this)));
	}

	_InternalType m_data;
};

// ========== Category specialization ==========

template<>
inline constexpr ObjCategory Numeric<bool >::sk_cat()
{ return ObjCategory::Bool; }
template<>
inline constexpr ObjCategory Numeric<int8_t >::sk_cat()
{ return ObjCategory::Integer; }
template<>
inline constexpr ObjCategory Numeric<int16_t>::sk_cat()
{ return ObjCategory::Integer; }
template<>
inline constexpr ObjCategory Numeric<int32_t>::sk_cat()
{ return ObjCategory::Integer; }
template<>
inline constexpr ObjCategory Numeric<int64_t>::sk_cat()
{ return ObjCategory::Integer; }

template<>
inline constexpr ObjCategory Numeric<uint8_t >::sk_cat()
{ return ObjCategory::Integer; }
template<>
inline constexpr ObjCategory Numeric<uint16_t>::sk_cat()
{ return ObjCategory::Integer; }
template<>
inline constexpr ObjCategory Numeric<uint32_t>::sk_cat()
{ return ObjCategory::Integer; }
template<>
inline constexpr ObjCategory Numeric<uint64_t>::sk_cat()
{ return ObjCategory::Integer; }

template<>
inline constexpr ObjCategory Numeric<float>::sk_cat()
{ return ObjCategory::Real; }
template<>
inline constexpr ObjCategory Numeric<double>::sk_cat()
{ return ObjCategory::Real; }

template<>
inline NumericType Numeric<bool   >::GetNumType() const { return NumericType::Bool;  }
template<>
inline NumericType Numeric<int8_t >::GetNumType() const { return NumericType::Int8;  }
template<>
inline NumericType Numeric<int16_t>::GetNumType() const { return NumericType::Int16; }
template<>
inline NumericType Numeric<int32_t>::GetNumType() const { return NumericType::Int32; }
template<>
inline NumericType Numeric<int64_t>::GetNumType() const { return NumericType::Int64; }
template<>
inline NumericType Numeric<uint8_t >::GetNumType() const { return NumericType::UInt8;  }
template<>
inline NumericType Numeric<uint16_t>::GetNumType() const { return NumericType::UInt16; }
template<>
inline NumericType Numeric<uint32_t>::GetNumType() const { return NumericType::UInt32; }
template<>
inline NumericType Numeric<uint64_t>::GetNumType() const { return NumericType::UInt64; }
template<>
inline NumericType Numeric<float >::GetNumType() const { return NumericType::Float;  }
template<>
inline NumericType Numeric<double>::GetNumType() const { return NumericType::Double; }

template<>
inline const char* Numeric<bool   >::GetNumTypeName() const { return "Bool";  }
template<>
inline const char* Numeric<int8_t >::GetNumTypeName() const { return "Int8";  }
template<>
inline const char* Numeric<int16_t>::GetNumTypeName() const { return "Int16"; }
template<>
inline const char* Numeric<int32_t>::GetNumTypeName() const { return "Int32"; }
template<>
inline const char* Numeric<int64_t>::GetNumTypeName() const { return "Int64"; }
template<>
inline const char* Numeric<uint8_t >::GetNumTypeName() const { return "UInt8";  }
template<>
inline const char* Numeric<uint16_t>::GetNumTypeName() const { return "UInt16"; }
template<>
inline const char* Numeric<uint32_t>::GetNumTypeName() const { return "UInt32"; }
template<>
inline const char* Numeric<uint64_t>::GetNumTypeName() const { return "UInt64"; }
template<>
inline const char* Numeric<float >::GetNumTypeName() const { return "Float";  }
template<>
inline const char* Numeric<double>::GetNumTypeName() const { return "Double"; }

template<>
inline const char* Numeric<bool   >::GetCategoryName() const { return "Bool";  }
template<>
inline const char* Numeric<int8_t >::GetCategoryName() const { return "Integer";  }
template<>
inline const char* Numeric<int16_t>::GetCategoryName() const { return "Integer"; }
template<>
inline const char* Numeric<int32_t>::GetCategoryName() const { return "Integer"; }
template<>
inline const char* Numeric<int64_t>::GetCategoryName() const { return "Integer"; }
template<>
inline const char* Numeric<uint8_t >::GetCategoryName() const { return "Integer";  }
template<>
inline const char* Numeric<uint16_t>::GetCategoryName() const { return "Integer"; }
template<>
inline const char* Numeric<uint32_t>::GetCategoryName() const { return "Integer"; }
template<>
inline const char* Numeric<uint64_t>::GetCategoryName() const { return "Integer"; }
template<>
inline const char* Numeric<float >::GetCategoryName() const { return "Real";  }
template<>
inline const char* Numeric<double>::GetCategoryName() const { return "Real"; }

// ========== binary operators for Numeric ==========

template<typename _LhsInternalType, typename _RhsInternalType>
inline Numeric<typename Internal::InferBinOpRetType<_LhsInternalType, _RhsInternalType>::RetType>
operator+(const Numeric<_LhsInternalType>& lhs, const Numeric<_RhsInternalType>& rhs)
{
	using RetInternalType = typename Internal::InferBinOpRetType<_LhsInternalType, _RhsInternalType>::RetType;
	using RetType = Numeric<RetInternalType>;
	return RetType(static_cast<RetInternalType>(lhs.GetVal() + rhs.GetVal()));
}

template<typename _LhsInternalType, typename _RhsInternalType>
inline Numeric<typename Internal::InferBinOpRetType<_LhsInternalType, _RhsInternalType>::RetType>
operator-(const Numeric<_LhsInternalType>& lhs, const Numeric<_RhsInternalType>& rhs)
{
	using RetInternalType = typename Internal::InferBinOpRetType<_LhsInternalType, _RhsInternalType>::RetType;
	using RetType = Numeric<RetInternalType>;
	return RetType(static_cast<RetInternalType>(lhs.GetVal() - rhs.GetVal()));
}

template<typename _LhsInternalType, typename _RhsInternalType>
inline Numeric<typename Internal::InferBinOpRetType<_LhsInternalType, _RhsInternalType>::RetType>
operator*(const Numeric<_LhsInternalType>& lhs, const Numeric<_RhsInternalType>& rhs)
{
	using RetInternalType = typename Internal::InferBinOpRetType<_LhsInternalType, _RhsInternalType>::RetType;
	using RetType = Numeric<RetInternalType>;
	return RetType(static_cast<RetInternalType>(lhs.GetVal() * rhs.GetVal()));
}

template<typename _LhsInternalType, typename _RhsInternalType>
inline Numeric<typename Internal::InferBinOpRetType<_LhsInternalType, _RhsInternalType>::RetType>
operator/(const Numeric<_LhsInternalType>& lhs, const Numeric<_RhsInternalType>& rhs)
{
	using RetInternalType = typename Internal::InferBinOpRetType<_LhsInternalType, _RhsInternalType>::RetType;
	using RetType = Numeric<RetInternalType>;
	return RetType(static_cast<RetInternalType>(lhs.GetVal() / rhs.GetVal()));
}

template<typename _LhsInternalType, typename _RhsInternalType>
inline Numeric<typename Internal::InferBinOpRetType<_LhsInternalType, _RhsInternalType>::RetType>
operator%(const Numeric<_LhsInternalType>& lhs, const Numeric<_RhsInternalType>& rhs)
{
	using RetInternalType = typename Internal::InferBinOpRetType<_LhsInternalType, _RhsInternalType>::RetType;
	using RetType = Numeric<RetInternalType>;
	return RetType(static_cast<RetInternalType>(lhs.GetVal() % rhs.GetVal()));
}

// ========== Convenient types of Numeric ==========

using Bool  = Numeric<bool >;

using Int8  = Numeric<int8_t >;
using Int16 = Numeric<int16_t>;
using Int32 = Numeric<int32_t>;
using Int64 = Numeric<int64_t>;

using UInt8  = Numeric<uint8_t >;
using UInt16 = Numeric<uint16_t>;
using UInt32 = Numeric<uint32_t>;
using UInt64 = Numeric<uint64_t>;

using Float = Numeric<float>;
using Double = Numeric<double>;

// ========== Generic operations ==========

template<typename _InternalType>
template<typename _RetType, typename _Op>
inline std::tuple<bool, _RetType> Numeric<_InternalType>::GenericBinaryOp(const NumericBaseObject& rhs, _Op op) const
{
	using namespace Internal;
	auto rhsType = rhs.GetNumType();
	switch (rhsType)
	{
	case NumericType::Bool:
		return std::make_tuple(true, op((*this) /*RHS*/, DownCast<Bool  >(rhs) /*LHS*/));
	case NumericType::Int8:
		return std::make_tuple(true, op((*this) /*RHS*/, DownCast<Int8  >(rhs) /*LHS*/));
	case NumericType::Int16:
		return std::make_tuple(true, op((*this) /*RHS*/, DownCast<Int16 >(rhs) /*LHS*/));
	case NumericType::Int32:
		return std::make_tuple(true, op((*this) /*RHS*/, DownCast<Int32 >(rhs) /*LHS*/));
	case NumericType::Int64:
		return std::make_tuple(true, op((*this) /*RHS*/, DownCast<Int64 >(rhs) /*LHS*/));
	case NumericType::UInt8:
		return std::make_tuple(true, op((*this) /*RHS*/, DownCast<UInt8 >(rhs) /*LHS*/));
	case NumericType::UInt16:
		return std::make_tuple(true, op((*this) /*RHS*/, DownCast<UInt16>(rhs) /*LHS*/));
	case NumericType::UInt32:
		return std::make_tuple(true, op((*this) /*RHS*/, DownCast<UInt32>(rhs) /*LHS*/));
	case NumericType::UInt64:
		return std::make_tuple(true, op((*this) /*RHS*/, DownCast<UInt64>(rhs) /*LHS*/));
	case NumericType::Float:
		return std::make_tuple(true, op((*this) /*RHS*/, DownCast<Float >(rhs) /*LHS*/));
	case NumericType::Double:
		return std::make_tuple(true, op((*this) /*RHS*/, DownCast<Double>(rhs) /*LHS*/));
	default:
		return std::make_tuple(false, _RetType());
	}
}

namespace Internal
{

struct NumCompareEq {
	template <typename _LhsType, typename _RhsType>
	Bool operator()(const _LhsType& lhs, const _RhsType& rhs) const
	{
		return lhs == rhs;
	}
};

struct NumCompareLt {
	template <typename _LhsType, typename _RhsType>
	Bool operator()(const _LhsType& lhs, const _RhsType& rhs) const
	{
		return lhs < rhs;
	}
};

struct NumCompareGt {
	template <typename _LhsType, typename _RhsType>
	Bool operator()(const _LhsType& lhs, const _RhsType& rhs) const
	{
		return lhs > rhs;
	}
};

}// namespace Internal

template<typename _InternalType>
inline bool Numeric<_InternalType>::operator==(const NumericBaseObject& rhs) const
{
	return GenericBinaryOpThrow<Bool>("=", rhs, Internal::NumCompareEq()).GetVal();
}

template<typename _InternalType>
inline bool Numeric<_InternalType>::operator<(const NumericBaseObject& rhs) const
{
	return GenericBinaryOpThrow<Bool>("<", rhs, Internal::NumCompareLt()).GetVal();
}

template<typename _InternalType>
inline bool Numeric<_InternalType>::operator>(const NumericBaseObject& rhs) const
{
	return GenericBinaryOpThrow<Bool>(">", rhs, Internal::NumCompareGt()).GetVal();
}

}// namespace SimpleObjects

// ========== Hash ==========
namespace std
{
	template<typename _InternalType>
#ifndef SIMPLEOBJECTS_CUSTOMIZED_NAMESPACE
	struct hash<SimpleObjects::Numeric<_InternalType> > : hash<_InternalType>
	{
		using _ObjType = SimpleObjects::Numeric<_InternalType>;
#else
	struct hash<SIMPLEOBJECTS_CUSTOMIZED_NAMESPACE::Numeric<_InternalType> > : hash<_InternalType>
	{
		using _ObjType = SIMPLEOBJECTS_CUSTOMIZED_NAMESPACE::Numeric<_InternalType>;
#endif
	public:
		using _Base = std::hash<_InternalType>;

#if __cplusplus < 201703L
		typedef typename _Base::result_type       result_type;
		typedef typename _Base::argument_type     argument_type;
#endif

		size_t operator()(const _ObjType& cnt) const
		{
			return _Base::operator()(cnt.m_data);
		}
	};
}
