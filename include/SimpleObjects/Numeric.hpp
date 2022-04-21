// Copyright 2022 Haofan Zheng
// Use of this source code is governed by an MIT-style
// license that can be found in the LICENSE file or at
// https://opensource.org/licenses/MIT.

#pragma once

#include "NumericBaseObject.hpp"

#include <tuple>
#include <type_traits>
#include <limits>

#include "Exception.hpp"
#include "NumericTypeInfer.hpp"
#include "PrimitiveCmp.hpp"
#include "ToString.hpp"
#include "Utils.hpp"

#ifndef SIMPLEOBJECTS_CUSTOMIZED_NAMESPACE
namespace SimpleObjects
#else
namespace SIMPLEOBJECTS_CUSTOMIZED_NAMESPACE
#endif
{

template<typename _ValType>
struct NumericTraits
{
	static constexpr ObjCategory sk_cat();
	static constexpr const char* sk_catName();

	static constexpr NumericType sk_numType();
	static constexpr const char* sk_numTypeName();

}; // struct NumericTraits

namespace Internal
{

struct NumCompareEq
{
	template <typename _LhsType, typename _RhsType>
	bool operator()(const _LhsType& lhs, const _RhsType& rhs) const
	{
		return lhs == rhs;
	}
}; // struct NumCompareEq

struct NumCompareCmp
{
	template <typename _LhsType, typename _RhsType>
	int operator()(const _LhsType& lhs, const _RhsType& rhs) const
	{
		return lhs.RealNumCmp(rhs);
	}
}; // struct NumCompareCmp

template<typename _DstValType, typename _SrcValType>
struct NumericBinOp;

template<typename _ValType>
struct NumericBinOp<_ValType, _ValType>
{
	static void Set(_ValType& dst, const _ValType& src)
	{
		dst = src;
	}
}; // struct NumericBinOp

template<typename _DstValType, typename _SrcValType>
struct NumericBinOp
{
	static void Set(_DstValType& dst, const _SrcValType& src)
	{
		using namespace Internal;

		// // Check if a "check" is needed
		// if (DstType.Lowest <= SrcType.Lowest) and (SrcType.Max <= DstType.Max)
		//    Src's possible range is within Dst's range => no need to check
		// else
		//    Src's value might fall outside of Dst's range => need to check
		static constexpr bool isCheckNeed = (
			!(
				RealNumCompare<_DstValType, _SrcValType>::LessEqual(
					std::numeric_limits<_DstValType>::lowest(),
					std::numeric_limits<_SrcValType>::lowest()) &&
				RealNumCompare<_SrcValType, _DstValType>::LessEqual(
					std::numeric_limits<_SrcValType>::max(),
					std::numeric_limits<_DstValType>::max())
			));

		if (isCheckNeed)
		{
			// // ==> to check `src`:
			// if (src < DstType.Lowest) or (DstType.Max < src)
			//    throw
			const bool isOutRange = (
					(RealNumCompare<_SrcValType, _DstValType>::Less(
						src,
						std::numeric_limits<_DstValType>::lowest())) ||
					(RealNumCompare<_DstValType, _SrcValType>::Less(
						std::numeric_limits<_DstValType>::max(),
						src))
				);
			if (isOutRange)
			{
				throw TypeError(NumericTraits<_DstValType>::sk_numTypeName(),
					NumericTraits<_SrcValType>::sk_numTypeName());
			}
		}

		// value range should have passed the check at this point
		dst = static_cast<_DstValType>(src);
	}
}; // struct NumericBinOp

} // namespace Internal

template<typename _ValType, typename _ToStringType>
class Numeric : public NumericBaseObject<_ToStringType>
{
public: // Static member:

	using InternalType = _ValType;
	using ToStringType = _ToStringType;
	using Self = Numeric<InternalType, ToStringType>;
	using SelfBool = Numeric<bool, ToStringType>;
	using Base = NumericBaseObject<ToStringType>;
	using BaseBase = typename Base::Base;
	using BaseBaseBase = typename BaseBase::Base;

	static_assert(std::is_same<BaseBase, HashableBaseObject<_ToStringType> >::value,
		"Expecting Base::Base to be HashableBaseObject class");
	static_assert(std::is_same<BaseBaseBase, BaseObject<_ToStringType> >::value,
		"Expecting Base::Base::Base to be BaseObject class");

	template<typename _OtherInternalType, typename _OtherToStringType>
	friend class Numeric;

	friend struct std::hash<Self>;

	static constexpr ObjCategory sk_cat()
	{
		return NumericTraits<InternalType>::sk_cat();
	}

public:
	Numeric() :
		m_data()
	{}

	explicit Numeric(const InternalType& val) :
		m_data(val)
	{}

	explicit Numeric(InternalType&& val) noexcept :
		m_data(std::forward<InternalType>(val))
	{}

	Numeric(const Self& other) :
		m_data(other.m_data)
	{}

	Numeric(Self&& other) noexcept:
		m_data(std::forward<InternalType>(other.m_data))
	{}

	virtual ~Numeric() = default;

	// operator const InternalType&() const
	// {
	// 	return m_data;
	// }

	// operator InternalType&()
	// {
	// 	return m_data;
	// }

	const InternalType& GetVal() const
	{
		return m_data;
	}

	template<typename _RetType, typename _Op>
	std::tuple<bool, _RetType> GenericBinaryOp(const Base& rhs, _Op op) const;

	template<typename _RetType, typename _Op>
	_RetType GenericBinaryOpThrow(
		const std::string& opName, const Base& rhs, _Op op) const
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

	// ========== Comparisons ==========

	// ===== This class

	template<typename _RhsValType, typename _RhsStringType>
	int RealNumCmp(const Numeric<_RhsValType, _RhsStringType>& rhs) const
	{
		return Internal::RealNumCompare<InternalType, _RhsValType>::Compare(
			(m_data), (rhs.m_data));
	}

	template<typename _RhsValType, typename _RhsStringType>
	bool operator==(const Numeric<_RhsValType, _RhsStringType>& rhs) const
	{
		return Internal::RealNumCompare<InternalType, _RhsValType>::Equal(
			(m_data), (rhs.m_data));
	}

#ifdef __cpp_lib_three_way_comparison
	template<typename _RhsValType, typename _RhsStringType>
	std::strong_ordering operator<=>(
		const Numeric<_RhsValType, _RhsStringType>& rhs) const
	{
		auto cmpRes = RealNumCmp(rhs);
		return cmpRes == 0 ? std::strong_ordering::equal :
				(cmpRes < 0 ? std::strong_ordering::less :
				(std::strong_ordering::greater));
	}
#else
	template<typename _RhsValType, typename _RhsStringType>
	bool operator!=(const Numeric<_RhsValType, _RhsStringType>& rhs) const
	{
		return !(this->operator==(rhs));
	}

	template<typename _RhsValType, typename _RhsStringType>
	bool operator<(const Numeric<_RhsValType, _RhsStringType>& rhs) const
	{
		return RealNumCmp(rhs) < 0;
	}

	template<typename _RhsValType, typename _RhsStringType>
	bool operator>(const Numeric<_RhsValType, _RhsStringType>& rhs) const
	{
		return RealNumCmp(rhs) > 0;
	}

	template<typename _RhsValType, typename _RhsStringType>
	bool operator<=(const Numeric<_RhsValType, _RhsStringType>& rhs) const
	{
		return RealNumCmp(rhs) <= 0;
	}

	template<typename _RhsValType, typename _RhsStringType>
	bool operator>=(const Numeric<_RhsValType, _RhsStringType>& rhs) const
	{
		return RealNumCmp(rhs) >= 0;
	}
#endif

	// ===== RealNumBase class

	virtual bool RealNumBaseEqual(const Base& rhs) const override
	{
		return GenericBinaryOpThrow<bool>("=", rhs, Internal::NumCompareEq());
	}

	virtual int RealNumBaseCmp(const Base& rhs) const override
	{
		return GenericBinaryOpThrow<int>("<=>", rhs, Internal::NumCompareCmp());
	}

	using Base::operator==;
	using Base::operator!=;
	using Base::operator<;
	using Base::operator>;
	using Base::operator<=;
	using Base::operator>=;

	//     ========== Assignment and Move ==========

	Self& operator=(const InternalType& rhs)
	{
		m_data = rhs;

		return *this;
	}

	Self& operator=(InternalType&& rhs) noexcept
	{
		m_data = std::forward<InternalType>(rhs);

		return *this;
	}

	Self& operator=(const Self& rhs)
	{
		m_data = rhs.m_data;

		return *this;
	}

	Self& operator=(Self&& rhs) noexcept
	{
		m_data = std::forward<InternalType>(rhs.m_data);

		return *this;
	}

	//     ========== operators for Numeric ==========
	//     &, |, ^, <<, >>, ~,
	//     +=, -=, *=, /=, %=, &=, |=, ^=
	//     ++, --, -

	template<typename _RhsValType, typename _RhsStringType>
	Self operator&(const Numeric<_RhsValType, _RhsStringType>& rhs) const
	{
		return Self(m_data & rhs.m_data);
	}

	template<typename _RhsValType, typename _RhsStringType>
	Self operator|(const Numeric<_RhsValType, _RhsStringType>& rhs) const
	{
		return Self(m_data | rhs.m_data);
	}

	template<typename _RhsValType, typename _RhsStringType>
	Self operator^(const Numeric<_RhsValType, _RhsStringType>& rhs) const
	{
		return Self(m_data ^ rhs.m_data);
	}

	template<typename _RhsValType, typename _RhsStringType>
	Self operator<<(const Numeric<_RhsValType, _RhsStringType>& rhs) const
	{
		return Self(m_data << rhs.m_data);
	}

	template<typename _RhsValType, typename _RhsStringType>
	Self operator>>(const Numeric<_RhsValType, _RhsStringType>& rhs) const
	{
		return Self(m_data >> rhs.m_data);
	}

	Self operator~() const
	{
		return Self(~m_data);
	}

	template<typename _RhsValType, typename _RhsStringType>
	Self& operator+=(const Numeric<_RhsValType, _RhsStringType>& rhs)
	{
		m_data = static_cast<InternalType>(m_data + rhs.m_data);
		return *this;
	}

	template<typename _RhsValType, typename _RhsStringType>
	Self& operator-=(const Numeric<_RhsValType, _RhsStringType>& rhs)
	{
		m_data = static_cast<InternalType>(m_data - rhs.m_data);
		return *this;
	}

	template<typename _RhsValType, typename _RhsStringType>
	Self& operator*=(const Numeric<_RhsValType, _RhsStringType>& rhs)
	{
		m_data = static_cast<InternalType>(m_data * rhs.m_data);
		return *this;
	}

	template<typename _RhsValType, typename _RhsStringType>
	Self& operator/=(const Numeric<_RhsValType, _RhsStringType>& rhs)
	{
		m_data = static_cast<InternalType>(m_data / rhs.m_data);
		return *this;
	}

	Self& operator+=(const Self& rhs)
	{
		m_data += rhs.m_data;
		return *this;
	}

	Self& operator-=(const Self& rhs)
	{
		m_data -= rhs.m_data;
		return *this;
	}

	Self& operator*=(const Self& rhs)
	{
		m_data *= rhs.m_data;
		return *this;
	}

	Self& operator/=(const Self& rhs)
	{
		m_data /= rhs.m_data;
		return *this;
	}

	template<typename _RhsValType, typename _RhsStringType>
	Self& operator%=(const Numeric<_RhsValType, _RhsStringType>& rhs)
	{
		m_data %= rhs.m_data;
		return *this;
	}

	template<typename _RhsValType, typename _RhsStringType>
	Self& operator&=(const Numeric<_RhsValType, _RhsStringType>& rhs)
	{
		m_data &= rhs.m_data;
		return *this;
	}

	template<typename _RhsValType, typename _RhsStringType>
	Self& operator|=(const Numeric<_RhsValType, _RhsStringType>& rhs)
	{
		m_data |= rhs.m_data;
		return *this;
	}

	template<typename _RhsValType, typename _RhsStringType>
	Self& operator^=(const Numeric<_RhsValType, _RhsStringType>& rhs)
	{
		m_data ^= rhs.m_data;
		return *this;
	}

	Self& operator++()
	{
		++m_data;
		return *this;
	}

	Self& operator--()
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

	// ========== Overrides BaseObject ==========

	virtual void Set(const BaseBaseBase& other) override
	{
		try
		{
			const Self& casted = dynamic_cast<const Self&>(other);
			*this = casted;
		}
		catch(const std::bad_cast&)
		{
			throw TypeError(
				NumericTraits<InternalType>::sk_numTypeName(),
				this->GetCategoryName());
		}
	}

	virtual void Set(BaseBaseBase&& other) override
	{
		try
		{
			Self&& casted = dynamic_cast<Self&&>(other);
			*this = std::forward<Self>(casted);
		}
		catch(const std::bad_cast&)
		{
			throw TypeError(
				NumericTraits<InternalType>::sk_numTypeName(),
				this->GetCategoryName());
		}
	}

	virtual void Set(bool val) override
	{
		Internal::NumericBinOp<InternalType, bool>::Set(m_data, val);
	}

	virtual void Set(uint8_t val) override
	{
		Internal::NumericBinOp<InternalType, uint8_t>::Set(m_data, val);
	}

	virtual void Set(int8_t val) override
	{
		Internal::NumericBinOp<InternalType, int8_t>::Set(m_data, val);
	}

	virtual void Set(uint32_t val) override
	{
		Internal::NumericBinOp<InternalType, uint32_t>::Set(m_data, val);
	}

	virtual void Set(int32_t val) override
	{
		Internal::NumericBinOp<InternalType, int32_t>::Set(m_data, val);
	}

	virtual void Set(uint64_t val) override
	{
		Internal::NumericBinOp<InternalType, uint64_t>::Set(m_data, val);
	}

	virtual void Set(int64_t val) override
	{
		Internal::NumericBinOp<InternalType, int64_t>::Set(m_data, val);
	}

	virtual void Set(double val) override
	{
		Internal::NumericBinOp<InternalType, double>::Set(m_data, val);
	}

	virtual bool IsTrue() const override
	{
		return static_cast<bool>(m_data);
	}

	virtual uint8_t AsCppUInt8() const override
	{
		uint8_t tmp;
		Internal::NumericBinOp<uint8_t, InternalType>::Set(tmp, m_data);
		return tmp;
	}

	virtual int8_t AsCppInt8() const override
	{
		int8_t tmp;
		Internal::NumericBinOp<int8_t, InternalType>::Set(tmp, m_data);
		return tmp;
	}

	virtual uint32_t AsCppUInt32() const override
	{
		uint32_t tmp;
		Internal::NumericBinOp<uint32_t, InternalType>::Set(tmp, m_data);
		return tmp;
	}

	virtual int32_t AsCppInt32() const override
	{
		int32_t tmp;
		Internal::NumericBinOp<int32_t, InternalType>::Set(tmp, m_data);
		return tmp;
	}

	virtual uint64_t AsCppUInt64() const override
	{
		uint64_t tmp;
		Internal::NumericBinOp<uint64_t, InternalType>::Set(tmp, m_data);
		return tmp;
	}

	virtual int64_t AsCppInt64() const override
	{
		int64_t tmp;
		Internal::NumericBinOp<int64_t, InternalType>::Set(tmp, m_data);
		return tmp;
	}

	virtual double AsCppDouble() const override
	{
		double tmp;
		Internal::NumericBinOp<double, InternalType>::Set(tmp, m_data);
		return tmp;
	}

	virtual ObjCategory GetCategory() const override
	{
		return sk_cat();
	}

	virtual const char* GetCategoryName() const override
	{
		return NumericTraits<InternalType>::sk_catName();
	}

	// ========== Overrides HashableBaseObject ==========

	virtual std::size_t Hash() const override
	{
		return std::hash<InternalType>()(m_data);
	}

	// ========== Overrides NumericBaseObject ==========

	virtual NumericType GetNumType() const override
	{
		return NumericTraits<InternalType>::sk_numType();
	}

	virtual const char* GetNumTypeName() const override
	{
		return NumericTraits<InternalType>::sk_numTypeName();
	}

	// ========== Interface copy/Move ==========

	using Base::Copy;
	virtual std::unique_ptr<Base> Copy(const Base* /*unused*/) const override
	{
		return CopyImpl();
	}

	using Base::Move;
	virtual std::unique_ptr<Base> Move(const Base* /*unused*/) override
	{
		return MoveImpl();
	}

	// ========== To string ==========

	virtual std::string DebugString() const override
	{
		return Internal::ToString<std::string>(m_data);
	}

	virtual std::string ShortDebugString() const override
	{
		return DebugString();
	}

	virtual ToStringType ToString() const override
	{
		return Internal::ToString<ToStringType>(m_data);
	}

	virtual void DumpString(OutIterator<typename ToStringType::value_type> outIt) const override
	{
		const auto str = Internal::ToString<ToStringType>(m_data);
		std::copy(str.begin(), str.end(), outIt);
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

	InternalType m_data;
}; // class Numeric

// ========== Category specialization ==========

template<>
inline constexpr ObjCategory NumericTraits<bool    >::sk_cat() { return ObjCategory::Bool; }
template<>
inline constexpr ObjCategory NumericTraits<int8_t  >::sk_cat() { return ObjCategory::Integer; }
template<>
inline constexpr ObjCategory NumericTraits<int16_t >::sk_cat() { return ObjCategory::Integer; }
template<>
inline constexpr ObjCategory NumericTraits<int32_t >::sk_cat() { return ObjCategory::Integer; }
template<>
inline constexpr ObjCategory NumericTraits<int64_t >::sk_cat() { return ObjCategory::Integer; }
template<>
inline constexpr ObjCategory NumericTraits<uint8_t >::sk_cat() { return ObjCategory::Integer; }
template<>
inline constexpr ObjCategory NumericTraits<uint16_t>::sk_cat() { return ObjCategory::Integer; }
template<>
inline constexpr ObjCategory NumericTraits<uint32_t>::sk_cat() { return ObjCategory::Integer; }
template<>
inline constexpr ObjCategory NumericTraits<uint64_t>::sk_cat() { return ObjCategory::Integer; }
template<>
inline constexpr ObjCategory NumericTraits<float   >::sk_cat() { return ObjCategory::Real; }
template<>
inline constexpr ObjCategory NumericTraits<double  >::sk_cat() { return ObjCategory::Real; }

template<>
inline constexpr const char* NumericTraits<bool    >::sk_catName() { return "Bool";  }
template<>
inline constexpr const char* NumericTraits<int8_t  >::sk_catName() { return "Integer";  }
template<>
inline constexpr const char* NumericTraits<int16_t >::sk_catName() { return "Integer"; }
template<>
inline constexpr const char* NumericTraits<int32_t >::sk_catName() { return "Integer"; }
template<>
inline constexpr const char* NumericTraits<int64_t >::sk_catName() { return "Integer"; }
template<>
inline constexpr const char* NumericTraits<uint8_t >::sk_catName() { return "Integer";  }
template<>
inline constexpr const char* NumericTraits<uint16_t>::sk_catName() { return "Integer"; }
template<>
inline constexpr const char* NumericTraits<uint32_t>::sk_catName() { return "Integer"; }
template<>
inline constexpr const char* NumericTraits<uint64_t>::sk_catName() { return "Integer"; }
template<>
inline constexpr const char* NumericTraits<float   >::sk_catName() { return "Real";  }
template<>
inline constexpr const char* NumericTraits<double  >::sk_catName() { return "Real"; }

template<>
inline constexpr NumericType NumericTraits<bool    >::sk_numType() { return NumericType::Bool;  }
template<>
inline constexpr NumericType NumericTraits<int8_t  >::sk_numType() { return NumericType::Int8;  }
template<>
inline constexpr NumericType NumericTraits<int16_t >::sk_numType() { return NumericType::Int16; }
template<>
inline constexpr NumericType NumericTraits<int32_t >::sk_numType() { return NumericType::Int32; }
template<>
inline constexpr NumericType NumericTraits<int64_t >::sk_numType() { return NumericType::Int64; }
template<>
inline constexpr NumericType NumericTraits<uint8_t >::sk_numType() { return NumericType::UInt8;  }
template<>
inline constexpr NumericType NumericTraits<uint16_t>::sk_numType() { return NumericType::UInt16; }
template<>
inline constexpr NumericType NumericTraits<uint32_t>::sk_numType() { return NumericType::UInt32; }
template<>
inline constexpr NumericType NumericTraits<uint64_t>::sk_numType() { return NumericType::UInt64; }
template<>
inline constexpr NumericType NumericTraits<float   >::sk_numType() { return NumericType::Float;  }
template<>
inline constexpr NumericType NumericTraits<double  >::sk_numType() { return NumericType::Double; }

template<>
inline constexpr const char* NumericTraits<bool    >::sk_numTypeName() { return "Bool";  }
template<>
inline constexpr const char* NumericTraits<int8_t  >::sk_numTypeName() { return "Int8";  }
template<>
inline constexpr const char* NumericTraits<int16_t >::sk_numTypeName() { return "Int16"; }
template<>
inline constexpr const char* NumericTraits<int32_t >::sk_numTypeName() { return "Int32"; }
template<>
inline constexpr const char* NumericTraits<int64_t >::sk_numTypeName() { return "Int64"; }
template<>
inline constexpr const char* NumericTraits<uint8_t >::sk_numTypeName() { return "UInt8";  }
template<>
inline constexpr const char* NumericTraits<uint16_t>::sk_numTypeName() { return "UInt16"; }
template<>
inline constexpr const char* NumericTraits<uint32_t>::sk_numTypeName() { return "UInt32"; }
template<>
inline constexpr const char* NumericTraits<uint64_t>::sk_numTypeName() { return "UInt64"; }
template<>
inline constexpr const char* NumericTraits<float   >::sk_numTypeName() { return "Float";  }
template<>
inline constexpr const char* NumericTraits<double  >::sk_numTypeName() { return "Double"; }

// ========== binary operators for Numeric ==========

template<typename _LhsValType, typename _RhsValType, typename _ToStringType>
inline Numeric<
	typename Internal::InferBinOpRetType<_LhsValType, _RhsValType>::RetType,
	_ToStringType>
operator+(const Numeric<_LhsValType, _ToStringType>& lhs,
	const Numeric<_RhsValType, _ToStringType>& rhs)
{
	using RetInternalType = typename Internal::InferBinOpRetType<_LhsValType, _RhsValType>::RetType;
	using RetType = Numeric<RetInternalType, _ToStringType>;
	return RetType(static_cast<RetInternalType>(lhs.GetVal() + rhs.GetVal()));
}

template<typename _LhsValType, typename _RhsValType, typename _ToStringType>
inline Numeric<
	typename Internal::InferBinOpRetType<_LhsValType, _RhsValType>::RetType,
	_ToStringType>
operator-(const Numeric<_LhsValType, _ToStringType>& lhs,
	const Numeric<_RhsValType, _ToStringType>& rhs)
{
	using RetInternalType = typename Internal::InferBinOpRetType<_LhsValType, _RhsValType>::RetType;
	using RetType = Numeric<RetInternalType, _ToStringType>;
	return RetType(static_cast<RetInternalType>(lhs.GetVal() - rhs.GetVal()));
}

template<typename _LhsValType, typename _RhsValType, typename _ToStringType>
inline Numeric<
	typename Internal::InferBinOpRetType<_LhsValType, _RhsValType>::RetType,
	_ToStringType>
operator*(const Numeric<_LhsValType, _ToStringType>& lhs,
	const Numeric<_RhsValType, _ToStringType>& rhs)
{
	using RetInternalType = typename Internal::InferBinOpRetType<_LhsValType, _RhsValType>::RetType;
	using RetType = Numeric<RetInternalType, _ToStringType>;
	return RetType(static_cast<RetInternalType>(lhs.GetVal() * rhs.GetVal()));
}

template<typename _LhsValType, typename _RhsValType, typename _ToStringType>
inline Numeric<
	typename Internal::InferBinOpRetType<_LhsValType, _RhsValType>::RetType,
	_ToStringType>
operator/(const Numeric<_LhsValType, _ToStringType>& lhs,
	const Numeric<_RhsValType, _ToStringType>& rhs)
{
	using RetInternalType = typename Internal::InferBinOpRetType<_LhsValType, _RhsValType>::RetType;
	using RetType = Numeric<RetInternalType, _ToStringType>;
	return RetType(static_cast<RetInternalType>(lhs.GetVal() / rhs.GetVal()));
}

template<typename _LhsValType, typename _RhsValType, typename _ToStringType>
inline Numeric<
	typename Internal::InferBinOpRetType<_LhsValType, _RhsValType>::RetType,
	_ToStringType>
operator%(const Numeric<_LhsValType, _ToStringType>& lhs,
	const Numeric<_RhsValType, _ToStringType>& rhs)
{
	using RetInternalType = typename Internal::InferBinOpRetType<_LhsValType, _RhsValType>::RetType;
	using RetType = Numeric<RetInternalType, _ToStringType>;
	return RetType(static_cast<RetInternalType>(lhs.GetVal() % rhs.GetVal()));
}

// ========== Generic operations ==========

template<typename _ValType, typename _ToStringType>
template<typename _RetType, typename _Op>
inline std::tuple<bool, _RetType> Numeric<_ValType, _ToStringType>::GenericBinaryOp(
	const NumericBaseObject<_ToStringType>& rhs, _Op op) const
{
	using namespace Internal;
	using _Bool   = Numeric<bool    , _ToStringType>;
	using _Int8   = Numeric<int8_t  , _ToStringType>;
	using _Int16  = Numeric<int16_t , _ToStringType>;
	using _Int32  = Numeric<int32_t , _ToStringType>;
	using _Int64  = Numeric<int64_t , _ToStringType>;
	using _UInt8  = Numeric<uint8_t , _ToStringType>;
	using _UInt16 = Numeric<uint16_t, _ToStringType>;
	using _UInt32 = Numeric<uint32_t, _ToStringType>;
	using _UInt64 = Numeric<uint64_t, _ToStringType>;
	using _Float  = Numeric<float   , _ToStringType>;
	using _Double = Numeric<double  , _ToStringType>;

	auto rhsType = rhs.GetNumType();
	switch (rhsType)
	{
	case NumericType::Bool:
		return std::make_tuple(true,  _RetType(op((*this) /*RHS*/, DownCast<_Bool  >(rhs) /*LHS*/)));
	case NumericType::Int8:
		return std::make_tuple(true,  _RetType(op((*this) /*RHS*/, DownCast<_Int8  >(rhs) /*LHS*/)));
	case NumericType::Int16:
		return std::make_tuple(true,  _RetType(op((*this) /*RHS*/, DownCast<_Int16 >(rhs) /*LHS*/)));
	case NumericType::Int32:
		return std::make_tuple(true,  _RetType(op((*this) /*RHS*/, DownCast<_Int32 >(rhs) /*LHS*/)));
	case NumericType::Int64:
		return std::make_tuple(true,  _RetType(op((*this) /*RHS*/, DownCast<_Int64 >(rhs) /*LHS*/)));
	case NumericType::UInt8:
		return std::make_tuple(true,  _RetType(op((*this) /*RHS*/, DownCast<_UInt8 >(rhs) /*LHS*/)));
	case NumericType::UInt16:
		return std::make_tuple(true,  _RetType(op((*this) /*RHS*/, DownCast<_UInt16>(rhs) /*LHS*/)));
	case NumericType::UInt32:
		return std::make_tuple(true,  _RetType(op((*this) /*RHS*/, DownCast<_UInt32>(rhs) /*LHS*/)));
	case NumericType::UInt64:
		return std::make_tuple(true,  _RetType(op((*this) /*RHS*/, DownCast<_UInt64>(rhs) /*LHS*/)));
	case NumericType::Float:
		return std::make_tuple(true,  _RetType(op((*this) /*RHS*/, DownCast<_Float >(rhs) /*LHS*/)));
	case NumericType::Double:
		return std::make_tuple(true,  _RetType(op((*this) /*RHS*/, DownCast<_Double>(rhs) /*LHS*/)));
	default:
		return std::make_tuple(false, _RetType());
	}
}

}// namespace SimpleObjects

// ========== Hash ==========
namespace std
{
	template<typename _ValType, typename _ToStringType>
#ifndef SIMPLEOBJECTS_CUSTOMIZED_NAMESPACE
	struct hash<SimpleObjects::Numeric<_ValType, _ToStringType> > : hash<_ValType>
	{
		using _ObjType = SimpleObjects::Numeric<_ValType, _ToStringType>;
#else
	struct hash<SIMPLEOBJECTS_CUSTOMIZED_NAMESPACE::Numeric<_ValType, _ToStringType> > : hash<_ValType>
	{
		using _ObjType = SIMPLEOBJECTS_CUSTOMIZED_NAMESPACE::Numeric<_ValType, _ToStringType>;
#endif
	public:
		using _Base = std::hash<_ValType>;

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
