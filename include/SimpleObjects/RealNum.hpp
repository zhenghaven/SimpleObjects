// Copyright 2022 Haofan Zheng
// Use of this source code is governed by an MIT-style
// license that can be found in the LICENSE file or at
// https://opensource.org/licenses/MIT.

#pragma once

#include "RealNumBaseObject.hpp"

#include <tuple>
#include <type_traits>
#include <limits>

#include "CompareRealNum.hpp"
#include "Exception.hpp"
#include "RealNumTypeInfer.hpp"
#include "ToString.hpp"
#include "Utils.hpp"

#ifndef SIMPLEOBJECTS_CUSTOMIZED_NAMESPACE
namespace SimpleObjects
#else
namespace SIMPLEOBJECTS_CUSTOMIZED_NAMESPACE
#endif
{

template<typename _ValType>
struct RealNumTraits
{
	static constexpr ObjCategory sk_cat();
	static constexpr const char* sk_catName();

	static constexpr RealNumType sk_numType();
	static constexpr const char* sk_numTypeName();

}; // struct RealNumTraits

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
struct RealNumBinOp;

template<typename _ValType>
struct RealNumBinOp<_ValType, _ValType>
{
	static void Set(_ValType& dst, const _ValType& src)
	{
		dst = src;
	}
}; // struct RealNumBinOp

template<typename _DstValType, typename _SrcValType>
struct RealNumBinOp
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
				throw TypeError(RealNumTraits<_DstValType>::sk_numTypeName(),
					RealNumTraits<_SrcValType>::sk_numTypeName());
			}
		}

		// value range should have passed the check at this point
		dst = static_cast<_DstValType>(src);
	}
}; // struct RealNumBinOp

} // namespace Internal

template<typename _ValType, typename _ToStringType>
class RealNumImpl : public RealNumBaseObject<_ToStringType>
{
public: // Static member:

	using InternalType = _ValType;
	using ToStringType = _ToStringType;
	using Self = RealNumImpl<InternalType, ToStringType>;
	using SelfBool = RealNumImpl<bool, ToStringType>;
	using Base = RealNumBaseObject<ToStringType>;
	using BaseBase = typename Base::Base;
	using BaseBaseBase = typename BaseBase::Base;

	static_assert(std::is_same<BaseBase, HashableBaseObject<_ToStringType> >::value,
		"Expecting Base::Base to be HashableBaseObject class");
	static_assert(std::is_same<BaseBaseBase, BaseObject<_ToStringType> >::value,
		"Expecting Base::Base::Base to be BaseObject class");

	template<typename _OtherInternalType, typename _OtherToStringType>
	friend class RealNumImpl;

	friend struct std::hash<Self>;

	static constexpr ObjCategory sk_cat()
	{
		return RealNumTraits<InternalType>::sk_cat();
	}

public:
	RealNumImpl() :
		m_data()
	{}

	explicit RealNumImpl(const InternalType& val) :
		m_data(val)
	{}

	explicit RealNumImpl(InternalType&& val) noexcept :
		m_data(std::forward<InternalType>(val))
	{}

	RealNumImpl(const Self& other) :
		m_data(other.m_data)
	{}

	RealNumImpl(Self&& other) noexcept:
		m_data(std::forward<InternalType>(other.m_data))
	{}

	virtual ~RealNumImpl() = default;

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
	int RealNumCmp(const RealNumImpl<_RhsValType, _RhsStringType>& rhs) const
	{
		return Internal::RealNumCompare<InternalType, _RhsValType>::Compare(
			(m_data), (rhs.m_data));
	}

	template<typename _RhsValType, typename _RhsStringType>
	bool operator==(const RealNumImpl<_RhsValType, _RhsStringType>& rhs) const
	{
		return Internal::RealNumCompare<InternalType, _RhsValType>::Equal(
			(m_data), (rhs.m_data));
	}

#ifdef __cpp_lib_three_way_comparison
	template<typename _RhsValType, typename _RhsStringType>
	std::strong_ordering operator<=>(
		const RealNumImpl<_RhsValType, _RhsStringType>& rhs) const
	{
		auto cmpRes = RealNumCmp(rhs);
		return cmpRes == 0 ? std::strong_ordering::equal :
				(cmpRes < 0 ? std::strong_ordering::less :
				(std::strong_ordering::greater));
	}
#else
	template<typename _RhsValType, typename _RhsStringType>
	bool operator!=(const RealNumImpl<_RhsValType, _RhsStringType>& rhs) const
	{
		return !(this->operator==(rhs));
	}

	template<typename _RhsValType, typename _RhsStringType>
	bool operator<(const RealNumImpl<_RhsValType, _RhsStringType>& rhs) const
	{
		return RealNumCmp(rhs) < 0;
	}

	template<typename _RhsValType, typename _RhsStringType>
	bool operator>(const RealNumImpl<_RhsValType, _RhsStringType>& rhs) const
	{
		return RealNumCmp(rhs) > 0;
	}

	template<typename _RhsValType, typename _RhsStringType>
	bool operator<=(const RealNumImpl<_RhsValType, _RhsStringType>& rhs) const
	{
		return RealNumCmp(rhs) <= 0;
	}

	template<typename _RhsValType, typename _RhsStringType>
	bool operator>=(const RealNumImpl<_RhsValType, _RhsStringType>& rhs) const
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
#ifdef __cpp_lib_three_way_comparison
	using Base::operator<=>;
#else
	using Base::operator!=;
	using Base::operator<;
	using Base::operator>;
	using Base::operator<=;
	using Base::operator>=;
#endif

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

	//     ========== operators for RealNumImpl ==========
	//     &, |, ^, <<, >>, ~,
	//     +=, -=, *=, /=, %=, &=, |=, ^=
	//     ++, --, -

	template<typename _RhsValType, typename _RhsStringType>
	Self operator&(const RealNumImpl<_RhsValType, _RhsStringType>& rhs) const
	{
		return Self(m_data & rhs.m_data);
	}

	template<typename _RhsValType, typename _RhsStringType>
	Self operator|(const RealNumImpl<_RhsValType, _RhsStringType>& rhs) const
	{
		return Self(m_data | rhs.m_data);
	}

	template<typename _RhsValType, typename _RhsStringType>
	Self operator^(const RealNumImpl<_RhsValType, _RhsStringType>& rhs) const
	{
		return Self(m_data ^ rhs.m_data);
	}

	template<typename _RhsValType, typename _RhsStringType>
	Self operator<<(const RealNumImpl<_RhsValType, _RhsStringType>& rhs) const
	{
		return Self(m_data << rhs.m_data);
	}

	template<typename _RhsValType, typename _RhsStringType>
	Self operator>>(const RealNumImpl<_RhsValType, _RhsStringType>& rhs) const
	{
		return Self(m_data >> rhs.m_data);
	}

	Self operator~() const
	{
		return Self(~m_data);
	}

	template<typename _RhsValType, typename _RhsStringType>
	Self& operator+=(const RealNumImpl<_RhsValType, _RhsStringType>& rhs)
	{
		m_data = static_cast<InternalType>(m_data + rhs.m_data);
		return *this;
	}

	template<typename _RhsValType, typename _RhsStringType>
	Self& operator-=(const RealNumImpl<_RhsValType, _RhsStringType>& rhs)
	{
		m_data = static_cast<InternalType>(m_data - rhs.m_data);
		return *this;
	}

	template<typename _RhsValType, typename _RhsStringType>
	Self& operator*=(const RealNumImpl<_RhsValType, _RhsStringType>& rhs)
	{
		m_data = static_cast<InternalType>(m_data * rhs.m_data);
		return *this;
	}

	template<typename _RhsValType, typename _RhsStringType>
	Self& operator/=(const RealNumImpl<_RhsValType, _RhsStringType>& rhs)
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
	Self& operator%=(const RealNumImpl<_RhsValType, _RhsStringType>& rhs)
	{
		m_data %= rhs.m_data;
		return *this;
	}

	template<typename _RhsValType, typename _RhsStringType>
	Self& operator&=(const RealNumImpl<_RhsValType, _RhsStringType>& rhs)
	{
		m_data &= rhs.m_data;
		return *this;
	}

	template<typename _RhsValType, typename _RhsStringType>
	Self& operator|=(const RealNumImpl<_RhsValType, _RhsStringType>& rhs)
	{
		m_data |= rhs.m_data;
		return *this;
	}

	template<typename _RhsValType, typename _RhsStringType>
	Self& operator^=(const RealNumImpl<_RhsValType, _RhsStringType>& rhs)
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
				RealNumTraits<InternalType>::sk_numTypeName(),
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
				RealNumTraits<InternalType>::sk_numTypeName(),
				this->GetCategoryName());
		}
	}

	virtual void Set(bool val) override
	{
		Internal::RealNumBinOp<InternalType, bool>::Set(m_data, val);
	}

	virtual void Set(uint8_t val) override
	{
		Internal::RealNumBinOp<InternalType, uint8_t>::Set(m_data, val);
	}

	virtual void Set(int8_t val) override
	{
		Internal::RealNumBinOp<InternalType, int8_t>::Set(m_data, val);
	}

	virtual void Set(uint32_t val) override
	{
		Internal::RealNumBinOp<InternalType, uint32_t>::Set(m_data, val);
	}

	virtual void Set(int32_t val) override
	{
		Internal::RealNumBinOp<InternalType, int32_t>::Set(m_data, val);
	}

	virtual void Set(uint64_t val) override
	{
		Internal::RealNumBinOp<InternalType, uint64_t>::Set(m_data, val);
	}

	virtual void Set(int64_t val) override
	{
		Internal::RealNumBinOp<InternalType, int64_t>::Set(m_data, val);
	}

	virtual void Set(double val) override
	{
		Internal::RealNumBinOp<InternalType, double>::Set(m_data, val);
	}

	virtual bool IsTrue() const override
	{
		return static_cast<bool>(m_data);
	}

	virtual uint8_t AsCppUInt8() const override
	{
		uint8_t tmp;
		Internal::RealNumBinOp<uint8_t, InternalType>::Set(tmp, m_data);
		return tmp;
	}

	virtual int8_t AsCppInt8() const override
	{
		int8_t tmp;
		Internal::RealNumBinOp<int8_t, InternalType>::Set(tmp, m_data);
		return tmp;
	}

	virtual uint32_t AsCppUInt32() const override
	{
		uint32_t tmp;
		Internal::RealNumBinOp<uint32_t, InternalType>::Set(tmp, m_data);
		return tmp;
	}

	virtual int32_t AsCppInt32() const override
	{
		int32_t tmp;
		Internal::RealNumBinOp<int32_t, InternalType>::Set(tmp, m_data);
		return tmp;
	}

	virtual uint64_t AsCppUInt64() const override
	{
		uint64_t tmp;
		Internal::RealNumBinOp<uint64_t, InternalType>::Set(tmp, m_data);
		return tmp;
	}

	virtual int64_t AsCppInt64() const override
	{
		int64_t tmp;
		Internal::RealNumBinOp<int64_t, InternalType>::Set(tmp, m_data);
		return tmp;
	}

	virtual double AsCppDouble() const override
	{
		double tmp;
		Internal::RealNumBinOp<double, InternalType>::Set(tmp, m_data);
		return tmp;
	}

	virtual ObjCategory GetCategory() const override
	{
		return sk_cat();
	}

	virtual const char* GetCategoryName() const override
	{
		return RealNumTraits<InternalType>::sk_catName();
	}

	// ========== Overrides HashableBaseObject ==========

	virtual std::size_t Hash() const override
	{
		return std::hash<InternalType>()(m_data);
	}

	// ========== Overrides RealNumBaseObject ==========

	virtual RealNumType GetNumType() const override
	{
		return RealNumTraits<InternalType>::sk_numType();
	}

	virtual const char* GetNumTypeName() const override
	{
		return RealNumTraits<InternalType>::sk_numTypeName();
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

	//std::unique_ptr<RealNumBase> UnsupportedGenericBinaryOp(const RealNumBase& rhs, OperationType opType);

private:

	std::unique_ptr<Self> CopyImpl() const
	{
		return Internal::make_unique<Self>(*this);
	}

	std::unique_ptr<Self> MoveImpl()
	{
		return Internal::make_unique<Self>(std::move(*this));
	}

	InternalType m_data;
}; // class RealNumImpl

// ========== Category specialization ==========

template<>
inline constexpr ObjCategory RealNumTraits<bool    >::sk_cat() { return ObjCategory::Bool; }
template<>
inline constexpr ObjCategory RealNumTraits<int8_t  >::sk_cat() { return ObjCategory::Integer; }
template<>
inline constexpr ObjCategory RealNumTraits<int16_t >::sk_cat() { return ObjCategory::Integer; }
template<>
inline constexpr ObjCategory RealNumTraits<int32_t >::sk_cat() { return ObjCategory::Integer; }
template<>
inline constexpr ObjCategory RealNumTraits<int64_t >::sk_cat() { return ObjCategory::Integer; }
template<>
inline constexpr ObjCategory RealNumTraits<uint8_t >::sk_cat() { return ObjCategory::Integer; }
template<>
inline constexpr ObjCategory RealNumTraits<uint16_t>::sk_cat() { return ObjCategory::Integer; }
template<>
inline constexpr ObjCategory RealNumTraits<uint32_t>::sk_cat() { return ObjCategory::Integer; }
template<>
inline constexpr ObjCategory RealNumTraits<uint64_t>::sk_cat() { return ObjCategory::Integer; }
template<>
inline constexpr ObjCategory RealNumTraits<float   >::sk_cat() { return ObjCategory::Real; }
template<>
inline constexpr ObjCategory RealNumTraits<double  >::sk_cat() { return ObjCategory::Real; }

template<>
inline constexpr const char* RealNumTraits<bool    >::sk_catName() { return "Bool";  }
template<>
inline constexpr const char* RealNumTraits<int8_t  >::sk_catName() { return "Integer";  }
template<>
inline constexpr const char* RealNumTraits<int16_t >::sk_catName() { return "Integer"; }
template<>
inline constexpr const char* RealNumTraits<int32_t >::sk_catName() { return "Integer"; }
template<>
inline constexpr const char* RealNumTraits<int64_t >::sk_catName() { return "Integer"; }
template<>
inline constexpr const char* RealNumTraits<uint8_t >::sk_catName() { return "Integer";  }
template<>
inline constexpr const char* RealNumTraits<uint16_t>::sk_catName() { return "Integer"; }
template<>
inline constexpr const char* RealNumTraits<uint32_t>::sk_catName() { return "Integer"; }
template<>
inline constexpr const char* RealNumTraits<uint64_t>::sk_catName() { return "Integer"; }
template<>
inline constexpr const char* RealNumTraits<float   >::sk_catName() { return "Real";  }
template<>
inline constexpr const char* RealNumTraits<double  >::sk_catName() { return "Real"; }

template<>
inline constexpr RealNumType RealNumTraits<bool    >::sk_numType() { return RealNumType::Bool;  }
template<>
inline constexpr RealNumType RealNumTraits<int8_t  >::sk_numType() { return RealNumType::Int8;  }
template<>
inline constexpr RealNumType RealNumTraits<int16_t >::sk_numType() { return RealNumType::Int16; }
template<>
inline constexpr RealNumType RealNumTraits<int32_t >::sk_numType() { return RealNumType::Int32; }
template<>
inline constexpr RealNumType RealNumTraits<int64_t >::sk_numType() { return RealNumType::Int64; }
template<>
inline constexpr RealNumType RealNumTraits<uint8_t >::sk_numType() { return RealNumType::UInt8;  }
template<>
inline constexpr RealNumType RealNumTraits<uint16_t>::sk_numType() { return RealNumType::UInt16; }
template<>
inline constexpr RealNumType RealNumTraits<uint32_t>::sk_numType() { return RealNumType::UInt32; }
template<>
inline constexpr RealNumType RealNumTraits<uint64_t>::sk_numType() { return RealNumType::UInt64; }
template<>
inline constexpr RealNumType RealNumTraits<float   >::sk_numType() { return RealNumType::Float;  }
template<>
inline constexpr RealNumType RealNumTraits<double  >::sk_numType() { return RealNumType::Double; }

template<>
inline constexpr const char* RealNumTraits<bool    >::sk_numTypeName() { return "Bool";  }
template<>
inline constexpr const char* RealNumTraits<int8_t  >::sk_numTypeName() { return "Int8";  }
template<>
inline constexpr const char* RealNumTraits<int16_t >::sk_numTypeName() { return "Int16"; }
template<>
inline constexpr const char* RealNumTraits<int32_t >::sk_numTypeName() { return "Int32"; }
template<>
inline constexpr const char* RealNumTraits<int64_t >::sk_numTypeName() { return "Int64"; }
template<>
inline constexpr const char* RealNumTraits<uint8_t >::sk_numTypeName() { return "UInt8";  }
template<>
inline constexpr const char* RealNumTraits<uint16_t>::sk_numTypeName() { return "UInt16"; }
template<>
inline constexpr const char* RealNumTraits<uint32_t>::sk_numTypeName() { return "UInt32"; }
template<>
inline constexpr const char* RealNumTraits<uint64_t>::sk_numTypeName() { return "UInt64"; }
template<>
inline constexpr const char* RealNumTraits<float   >::sk_numTypeName() { return "Float";  }
template<>
inline constexpr const char* RealNumTraits<double  >::sk_numTypeName() { return "Double"; }

// ========== binary operators for RealNumImpl ==========

template<typename _LhsValType, typename _RhsValType, typename _ToStringType>
inline RealNumImpl<
	typename Internal::InferBinOpRetType<_LhsValType, _RhsValType>::RetType,
	_ToStringType>
operator+(const RealNumImpl<_LhsValType, _ToStringType>& lhs,
	const RealNumImpl<_RhsValType, _ToStringType>& rhs)
{
	using RetInternalType = typename Internal::InferBinOpRetType<_LhsValType, _RhsValType>::RetType;
	using RetType = RealNumImpl<RetInternalType, _ToStringType>;
	return RetType(static_cast<RetInternalType>(lhs.GetVal() + rhs.GetVal()));
}

template<typename _LhsValType, typename _RhsValType, typename _ToStringType>
inline RealNumImpl<
	typename Internal::InferBinOpRetType<_LhsValType, _RhsValType>::RetType,
	_ToStringType>
operator-(const RealNumImpl<_LhsValType, _ToStringType>& lhs,
	const RealNumImpl<_RhsValType, _ToStringType>& rhs)
{
	using RetInternalType = typename Internal::InferBinOpRetType<_LhsValType, _RhsValType>::RetType;
	using RetType = RealNumImpl<RetInternalType, _ToStringType>;
	return RetType(static_cast<RetInternalType>(lhs.GetVal() - rhs.GetVal()));
}

template<typename _LhsValType, typename _RhsValType, typename _ToStringType>
inline RealNumImpl<
	typename Internal::InferBinOpRetType<_LhsValType, _RhsValType>::RetType,
	_ToStringType>
operator*(const RealNumImpl<_LhsValType, _ToStringType>& lhs,
	const RealNumImpl<_RhsValType, _ToStringType>& rhs)
{
	using RetInternalType = typename Internal::InferBinOpRetType<_LhsValType, _RhsValType>::RetType;
	using RetType = RealNumImpl<RetInternalType, _ToStringType>;
	return RetType(static_cast<RetInternalType>(lhs.GetVal() * rhs.GetVal()));
}

template<typename _LhsValType, typename _RhsValType, typename _ToStringType>
inline RealNumImpl<
	typename Internal::InferBinOpRetType<_LhsValType, _RhsValType>::RetType,
	_ToStringType>
operator/(const RealNumImpl<_LhsValType, _ToStringType>& lhs,
	const RealNumImpl<_RhsValType, _ToStringType>& rhs)
{
	using RetInternalType = typename Internal::InferBinOpRetType<_LhsValType, _RhsValType>::RetType;
	using RetType = RealNumImpl<RetInternalType, _ToStringType>;
	return RetType(static_cast<RetInternalType>(lhs.GetVal() / rhs.GetVal()));
}

template<typename _LhsValType, typename _RhsValType, typename _ToStringType>
inline RealNumImpl<
	typename Internal::InferBinOpRetType<_LhsValType, _RhsValType>::RetType,
	_ToStringType>
operator%(const RealNumImpl<_LhsValType, _ToStringType>& lhs,
	const RealNumImpl<_RhsValType, _ToStringType>& rhs)
{
	using RetInternalType = typename Internal::InferBinOpRetType<_LhsValType, _RhsValType>::RetType;
	using RetType = RealNumImpl<RetInternalType, _ToStringType>;
	return RetType(static_cast<RetInternalType>(lhs.GetVal() % rhs.GetVal()));
}

// ========== Generic operations ==========

template<typename _ValType, typename _ToStringType>
template<typename _RetType, typename _Op>
inline std::tuple<bool, _RetType> RealNumImpl<_ValType, _ToStringType>::GenericBinaryOp(
	const RealNumBaseObject<_ToStringType>& rhs, _Op op) const
{
	using namespace Internal;
	using _Bool   = RealNumImpl<bool    , _ToStringType>;
	using _Int8   = RealNumImpl<int8_t  , _ToStringType>;
	using _Int16  = RealNumImpl<int16_t , _ToStringType>;
	using _Int32  = RealNumImpl<int32_t , _ToStringType>;
	using _Int64  = RealNumImpl<int64_t , _ToStringType>;
	using _UInt8  = RealNumImpl<uint8_t , _ToStringType>;
	using _UInt16 = RealNumImpl<uint16_t, _ToStringType>;
	using _UInt32 = RealNumImpl<uint32_t, _ToStringType>;
	using _UInt64 = RealNumImpl<uint64_t, _ToStringType>;
	using _Float  = RealNumImpl<float   , _ToStringType>;
	using _Double = RealNumImpl<double  , _ToStringType>;

	auto rhsType = rhs.GetNumType();
	switch (rhsType)
	{
	case RealNumType::Bool:
		return std::make_tuple(true,  _RetType(op((*this) /*RHS*/, DownCast<_Bool  >(rhs) /*LHS*/)));
	case RealNumType::Int8:
		return std::make_tuple(true,  _RetType(op((*this) /*RHS*/, DownCast<_Int8  >(rhs) /*LHS*/)));
	case RealNumType::Int16:
		return std::make_tuple(true,  _RetType(op((*this) /*RHS*/, DownCast<_Int16 >(rhs) /*LHS*/)));
	case RealNumType::Int32:
		return std::make_tuple(true,  _RetType(op((*this) /*RHS*/, DownCast<_Int32 >(rhs) /*LHS*/)));
	case RealNumType::Int64:
		return std::make_tuple(true,  _RetType(op((*this) /*RHS*/, DownCast<_Int64 >(rhs) /*LHS*/)));
	case RealNumType::UInt8:
		return std::make_tuple(true,  _RetType(op((*this) /*RHS*/, DownCast<_UInt8 >(rhs) /*LHS*/)));
	case RealNumType::UInt16:
		return std::make_tuple(true,  _RetType(op((*this) /*RHS*/, DownCast<_UInt16>(rhs) /*LHS*/)));
	case RealNumType::UInt32:
		return std::make_tuple(true,  _RetType(op((*this) /*RHS*/, DownCast<_UInt32>(rhs) /*LHS*/)));
	case RealNumType::UInt64:
		return std::make_tuple(true,  _RetType(op((*this) /*RHS*/, DownCast<_UInt64>(rhs) /*LHS*/)));
	case RealNumType::Float:
		return std::make_tuple(true,  _RetType(op((*this) /*RHS*/, DownCast<_Float >(rhs) /*LHS*/)));
	case RealNumType::Double:
		return std::make_tuple(true,  _RetType(op((*this) /*RHS*/, DownCast<_Double>(rhs) /*LHS*/)));
	default:
		return std::make_tuple(false, _RetType());
	}
}

} // namespace SimpleObjects

// ========== Hash ==========
namespace std
{
	template<typename _ValType, typename _ToStringType>
#ifndef SIMPLEOBJECTS_CUSTOMIZED_NAMESPACE
	struct hash<SimpleObjects::RealNumImpl<_ValType, _ToStringType> > : hash<_ValType>
	{
		using _ObjType = SimpleObjects::RealNumImpl<_ValType, _ToStringType>;
#else
	struct hash<SIMPLEOBJECTS_CUSTOMIZED_NAMESPACE::RealNumImpl<_ValType, _ToStringType> > : hash<_ValType>
	{
		using _ObjType = SIMPLEOBJECTS_CUSTOMIZED_NAMESPACE::RealNumImpl<_ValType, _ToStringType>;
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
	}; // struct hash
} // namespace std
