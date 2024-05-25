// Copyright (c) 2023 Haofan Zheng
// Use of this source code is governed by an MIT-style
// license that can be found in the LICENSE file or at
// https://opensource.org/licenses/MIT.


#include <gtest/gtest.h>

#include <list>
#include <vector>

#ifdef _MSC_VER
#include <windows.h>
#endif // _MSC_VER
#include <SimpleObjects/Codec/Hex.hpp>


#ifndef SIMPLEOBJECTS_CUSTOMIZED_NAMESPACE
using namespace SimpleObjects::Codec;
#else
using namespace SIMPLEOBJECTS_CUSTOMIZED_NAMESPACE::Codec;
#endif


namespace SimpleObjects_Test
{
	extern size_t g_numOfTestFile;
}


GTEST_TEST(TestCodecHex, CountTestFile)
{
	static auto tmp = ++SimpleObjects_Test::g_numOfTestFile;
	(void)tmp;
}


//==============================================================================
//
// BytesToHexImpl
//
//==============================================================================


namespace{

template<typename _ByteValType, typename _Encoder>
static void Test_BytesToHexImpl_Single(
	const std::vector<
		std::tuple<_ByteValType, std::string, std::string, std::string>
	>& cases
)
{
	for (const auto& testCase: cases)
	{
		{
			const _ByteValType& input = std::get<0>(testCase);
			const std::string& expected = std::get<2>(testCase);

			std::string actual;
			_Encoder::template EncodeSingle<true>(
				std::back_inserter(actual),
				input,
				std::get<1>(testCase)
			);
			ASSERT_EQ(actual, expected);
			auto endIt = _Encoder::template EncodeSingle<true>(
				actual.begin(),
				input,
				std::get<1>(testCase)
			);
			EXPECT_EQ(actual, expected);
			EXPECT_EQ(endIt, actual.end());
		}
		{
			const _ByteValType& input = std::get<0>(testCase);
			const std::string& expected = std::get<3>(testCase);

			std::string actual;
			_Encoder::template EncodeSingle<false>(
				std::back_inserter(actual),
				input,
				std::get<1>(testCase)
			);
			EXPECT_EQ(actual, expected);
			auto endIt = _Encoder::template EncodeSingle<false>(
				actual.begin(),
				input,
				std::get<1>(testCase)
			);
			EXPECT_EQ(actual, expected);
			EXPECT_EQ(endIt, actual.end());
		}
	}
}

} // namespace


GTEST_TEST(TestCodecHex, Internal_BytesToHexImpl_UpperCase_Single)
{
	using namespace Internal;

	using _Encoder = BytesToHexImpl<HexUpperCaseAlphabet<char>, 1>;

	// unsigned bytes
	Test_BytesToHexImpl_Single<uint8_t, _Encoder>(
		{
			std::make_tuple(0x12U, "0x", "0x12", "0x12"),
			std::make_tuple(0x34U, "0x", "0x34", "0x34"),
			std::make_tuple(0x56U, "0x", "0x56", "0x56"),
			std::make_tuple(0x78U, "0x", "0x78", "0x78"),
			std::make_tuple(0x9AU, "0x", "0x9A", "0x9A"),
			std::make_tuple(0xBCU, "0x", "0xBC", "0xBC"),
			std::make_tuple(0xDEU, "0x", "0xDE", "0xDE"),
			std::make_tuple(0xF0U, "0x", "0xF0", "0xF0"),

			std::make_tuple(0x0FU, "",   "0F", "F"),
			std::make_tuple(0x00U, "",   "00", ""),
		}
	);

	// signed bytes
	Test_BytesToHexImpl_Single<int8_t, _Encoder>(
		{
			std::make_tuple(0x12, "0x", "0x12", "0x12"),
			std::make_tuple(0x34, "0x", "0x34", "0x34"),
			std::make_tuple(0x56, "0x", "0x56", "0x56"),
			std::make_tuple(0x78, "0x", "0x78", "0x78"),
			std::make_tuple(0x10, "0x", "0x10", "0x10"),

			std::make_tuple(int8_t(~(int8_t(0x00))), "", "FF", "FF"),
			std::make_tuple(int8_t(~(int8_t(0x0F))), "", "F0", "F0"),
			std::make_tuple(int8_t(~(int8_t(0x7F))), "", "80", "80"),

			std::make_tuple(0x0F, "",   "0F", "F"),
			std::make_tuple(0x00, "",   "00", ""),
		}
	);
}


GTEST_TEST(TestCodecHex, Internal_BytesToHexImpl_LowerCase_Single)
{
	using namespace Internal;

	using _Encoder = BytesToHexImpl<HexLowerCaseAlphabet<char>, 1>;

	// unsigned bytes
	Test_BytesToHexImpl_Single<uint8_t, _Encoder>(
		{
			std::make_tuple(0x12U, "0x", "0x12", "0x12"),
			std::make_tuple(0x34U, "0x", "0x34", "0x34"),
			std::make_tuple(0x56U, "0x", "0x56", "0x56"),
			std::make_tuple(0x78U, "0x", "0x78", "0x78"),
			std::make_tuple(0x9AU, "0x", "0x9a", "0x9a"),
			std::make_tuple(0xBCU, "0x", "0xbc", "0xbc"),
			std::make_tuple(0xDEU, "0x", "0xde", "0xde"),
			std::make_tuple(0xF0U, "0x", "0xf0", "0xf0"),

			std::make_tuple(0x0FU, "",   "0f", "f"),
			std::make_tuple(0x00U, "",   "00", ""),
		}
	);

	// signed bytes
	Test_BytesToHexImpl_Single<int8_t, _Encoder>(
		{
			std::make_tuple(0x12, "0x", "0x12", "0x12"),
			std::make_tuple(0x34, "0x", "0x34", "0x34"),
			std::make_tuple(0x56, "0x", "0x56", "0x56"),
			std::make_tuple(0x78, "0x", "0x78", "0x78"),
			std::make_tuple(0x10, "0x", "0x10", "0x10"),

			std::make_tuple(int8_t(~(int8_t(0x00))), "", "ff", "ff"),
			std::make_tuple(int8_t(~(int8_t(0x0F))), "", "f0", "f0"),
			std::make_tuple(int8_t(~(int8_t(0x7F))), "", "80", "80"),

			std::make_tuple(0x0F, "",   "0f", "f"),
			std::make_tuple(0x00, "",   "00", ""),
		}
	);
}


namespace{

template<typename _ByteValType, typename _Encoder>
static void Test_BytesToHexImpl_String(
	const std::vector<
		std::tuple<
			std::vector<_ByteValType>,
			std::string,
			std::string,
			std::string
		>
	>& cases
)
{
	for (const auto& testCase: cases)
	{
		{
			const std::vector<_ByteValType>& input =
				std::get<0>(testCase);
			const std::string& expected =
				std::get<2>(testCase);
			const std::string& prefix =
				std::get<1>(testCase);

			std::string actual;
			_Encoder::template Encode<true>(
				std::back_inserter(actual),
				input.cbegin(),
				input.cend(),
				prefix
			);
			ASSERT_EQ(actual, expected);
			auto endIt = _Encoder::template Encode<true>(
				actual.begin(),
				input.cbegin(),
				input.cend(),
				prefix
			);
			EXPECT_EQ(actual, expected);
			EXPECT_EQ(endIt, actual.end());
		}
		{
			const std::vector<_ByteValType>& input =
				std::get<0>(testCase);
			const std::string& expected =
				std::get<3>(testCase);
			const std::string& prefix =
				std::get<1>(testCase);

			std::string actual;
			_Encoder::template Encode<false>(
				std::back_inserter(actual),
				input.cbegin(),
				input.cend(),
				prefix
			);
			ASSERT_EQ(actual, expected);
			auto endIt = _Encoder::template Encode<false>(
				actual.begin(),
				input.cbegin(),
				input.cend(),
				prefix
			);
			EXPECT_EQ(actual, expected);
			EXPECT_EQ(endIt, actual.end());
		}
	}
}

} // namespace


GTEST_TEST(TestCodecHex, Internal_BytesToHexImpl_UpperCase_String)
{
	using namespace Internal;

	using _Encoder = BytesToHexImpl<HexUpperCaseAlphabet<char>, 1>;

	// unsigned bytes
	Test_BytesToHexImpl_String<uint8_t, _Encoder>(
		{
			std::make_tuple(
				std::vector<uint8_t>({  }),
				"",
				"",
				""
			),
			std::make_tuple(
				std::vector<uint8_t>({
					0x12U, 0x34U, 0x56U, 0x78U, 0x9AU, 0xBCU, 0xDEU, 0xF0U
				 }),
				"0x",
				"0x123456789ABCDEF0",
				"0x123456789ABCDEF0"
			),
			std::make_tuple(
				std::vector<uint8_t>({
					0x00U, 0x00U, 0x00U, 0x00U, 0x12U, 0x34U, 0x56U, 0x78U
				 }),
				"0x",
				"0x0000000012345678",
				"0x12345678"
			),
			std::make_tuple(
				std::vector<uint8_t>({
					0x00U, 0x00U, 0x00U, 0x00U, 0x01U, 0x23U, 0x45U, 0x67U
				 }),
				"0x",
				"0x0000000001234567",
				"0x1234567"
			),
		}
	);
}

GTEST_TEST(TestCodecHex, Internal_BytesToHexImpl_LowerCase_String)
{
	using namespace Internal;

	using _Encoder = BytesToHexImpl<HexLowerCaseAlphabet<char>, 1>;

	// unsigned bytes
	Test_BytesToHexImpl_String<uint8_t, _Encoder>(
		{
			std::make_tuple(
				std::vector<uint8_t>({  }),
				"",
				"",
				""
			),
			std::make_tuple(
				std::vector<uint8_t>({
					0x12U, 0x34U, 0x56U, 0x78U, 0x9AU, 0xBCU, 0xDEU, 0xF0U
				 }),
				"0x",
				"0x123456789abcdef0",
				"0x123456789abcdef0"
			),
			std::make_tuple(
				std::vector<uint8_t>({
					0x00U, 0x00U, 0x00U, 0x00U, 0x12U, 0x34U, 0x56U, 0x78U
				 }),
				"0x",
				"0x0000000012345678",
				"0x12345678"
			),
			std::make_tuple(
				std::vector<uint8_t>({
					0x00U, 0x00U, 0x00U, 0x00U, 0x01U, 0x23U, 0x45U, 0x67U
				 }),
				"0x",
				"0x0000000001234567",
				"0x1234567"
			),
		}
	);
}


//==============================================================================
//
// IntegerToHexImpl
//
//==============================================================================


namespace{

template<
	typename _Encoder,
	HexZero  _HexZeroOpt,
	typename _IntegerType
>
static void Test_IntegerToHexImpl_OneTestCase(
	const _IntegerType& input,
	const std::string& expected,
	const std::string& prefix
)
{
	std::string actual;
	auto endIt = actual.end();

	actual.clear();
	_Encoder::template Encode<_HexZeroOpt, true>(
		std::back_inserter(actual),
		input,
		prefix
	);
	ASSERT_EQ(actual, prefix + expected);

	endIt = _Encoder::template Encode<_HexZeroOpt, true>(
		actual.begin(),
		input,
		prefix
	);
	EXPECT_EQ(actual, prefix + expected);
	EXPECT_EQ(endIt, actual.end());


	const auto signedPrefix = input >= 0 ? prefix : "-" + prefix;

	actual.clear();
	_Encoder::template Encode<_HexZeroOpt, false>(
		std::back_inserter(actual),
		input,
		prefix
	);
	ASSERT_EQ(actual, signedPrefix + expected);

	endIt = _Encoder::template Encode<_HexZeroOpt, false>(
		actual.begin(),
		input,
		prefix
	);
	EXPECT_EQ(actual, signedPrefix + expected);
	EXPECT_EQ(endIt, actual.end());
}

template<typename _Alphabet, typename _IntegerType>
static void Test_IntegerToHexImpl(
	const std::vector<
		std::tuple<
			_IntegerType,
			std::string
		>
	>& testCases
)
{
	using _Encoder = Internal::IntegerToHexImpl<_Alphabet>;

	for(const auto& testCase : testCases)
	{
		const _IntegerType& input = std::get<0>(testCase);
		const std::string& expectedZeros = std::get<1>(testCase);
		const auto nonZeroPos = expectedZeros.find_first_not_of('0');
		const std::string expectedNoLZero =
			nonZeroPos == std::string::npos ?
				std::string() :
				expectedZeros.substr(nonZeroPos);
		const std::string expectedOneLZero =
			nonZeroPos == std::string::npos ?
				std::string("0") :
				expectedZeros.substr(nonZeroPos);

		Test_IntegerToHexImpl_OneTestCase<_Encoder, HexZero::Keep>(
			input,
			expectedZeros,
			""
		);
		Test_IntegerToHexImpl_OneTestCase<_Encoder, HexZero::Keep>(
			input,
			expectedZeros,
			"0x"
		);

		Test_IntegerToHexImpl_OneTestCase<_Encoder, HexZero::AtLeastOne>(
			input,
			expectedOneLZero,
			""
		);
		Test_IntegerToHexImpl_OneTestCase<_Encoder, HexZero::AtLeastOne>(
			input,
			expectedOneLZero,
			"0x"
		);

		Test_IntegerToHexImpl_OneTestCase<_Encoder, HexZero::SkipAll>(
			input,
			expectedNoLZero,
			""
		);
		Test_IntegerToHexImpl_OneTestCase<_Encoder, HexZero::SkipAll>(
			input,
			expectedNoLZero,
			"0x"
		);
	}
}

} // namespace


GTEST_TEST(TestCodecHex, Internal_IntegerToHexImpl_LowerCase)
{
	using _Alphabet = Internal::HexLowerCaseAlphabet<char>;

	Test_IntegerToHexImpl<_Alphabet, uint8_t>({
		std::make_tuple<uint8_t, std::string>(0x7FU, "7f"),
		std::make_tuple<uint8_t, std::string>(0x0FU, "0f"),
		std::make_tuple<uint8_t, std::string>(0x00U, "00"),
	});

	Test_IntegerToHexImpl<_Alphabet, uint16_t>({
		std::make_tuple<uint16_t, std::string>(0x3E4BU, "3e4b"),
		std::make_tuple<uint16_t, std::string>(0x004BU, "004b"),
		std::make_tuple<uint16_t, std::string>(0x000BU, "000b"),
		std::make_tuple<uint16_t, std::string>(0x0000U, "0000"),
	});

	Test_IntegerToHexImpl<_Alphabet, uint32_t>({
		std::make_tuple<uint32_t, std::string>(0x3E4B239AU, "3e4b239a"),
		std::make_tuple<uint32_t, std::string>(0x004B239AU, "004b239a"),
		std::make_tuple<uint32_t, std::string>(0x000B239AU, "000b239a"),
		std::make_tuple<uint32_t, std::string>(0x00000000U, "00000000"),
	});

	Test_IntegerToHexImpl<_Alphabet, uint64_t>({
		std::make_tuple<uint64_t, std::string>(0x3E4B239A3F5C2D79ULL, "3e4b239a3f5c2d79"),
		std::make_tuple<uint64_t, std::string>(0x000000003F5C2D79ULL, "000000003f5c2d79"),
		std::make_tuple<uint64_t, std::string>(0x000000000F5C2D79ULL, "000000000f5c2d79"),
		std::make_tuple<uint64_t, std::string>(0x0000000000000000ULL, "0000000000000000"),
	});

	// Signed integers

	Test_IntegerToHexImpl<_Alphabet, int32_t>({
		std::make_tuple<int32_t, std::string>(0x3E4B239A, "3e4b239a"),
		std::make_tuple<int32_t, std::string>(0x004B239A, "004b239a"),
		std::make_tuple<int32_t, std::string>(0x000B239A, "000b239a"),
		std::make_tuple<int32_t, std::string>(0x00000000, "00000000"),
		std::make_tuple<int32_t, std::string>(-0x3E4B239A, "3e4b239a"),
		std::make_tuple<int32_t, std::string>(-0x000B239A, "000b239a"),
	});

	Test_IntegerToHexImpl<_Alphabet, int64_t>({
		std::make_tuple<int64_t, std::string>(0x3E4B239A3F5C2D79LL, "3e4b239a3f5c2d79"),
		std::make_tuple<int64_t, std::string>(0x000000003F5C2D79LL, "000000003f5c2d79"),
		std::make_tuple<int64_t, std::string>(0x000000000F5C2D79LL, "000000000f5c2d79"),
		std::make_tuple<int64_t, std::string>(0x0000000000000000LL, "0000000000000000"),
		std::make_tuple<int64_t, std::string>(-0x3E4B239A3F5C2D79LL, "3e4b239a3f5c2d79"),
		std::make_tuple<int64_t, std::string>(-0x000000000F5C2D79LL, "000000000f5c2d79"),
	});
}


GTEST_TEST(TestCodecHex, Internal_IntegerToHexImpl_UpperCase)
{
	using _Alphabet = Internal::HexUpperCaseAlphabet<char>;

	Test_IntegerToHexImpl<_Alphabet, uint8_t>({
		std::make_tuple<uint8_t, std::string>(0x7FU, "7F"),
		std::make_tuple<uint8_t, std::string>(0x0FU, "0F"),
		std::make_tuple<uint8_t, std::string>(0x00U, "00"),
	});

	Test_IntegerToHexImpl<_Alphabet, uint16_t>({
		std::make_tuple<uint16_t, std::string>(0x3E4BU, "3E4B"),
		std::make_tuple<uint16_t, std::string>(0x004BU, "004B"),
		std::make_tuple<uint16_t, std::string>(0x000BU, "000B"),
		std::make_tuple<uint16_t, std::string>(0x0000U, "0000"),
	});

	Test_IntegerToHexImpl<_Alphabet, uint32_t>({
		std::make_tuple<uint32_t, std::string>(0x3E4B239AU, "3E4B239A"),
		std::make_tuple<uint32_t, std::string>(0x004B239AU, "004B239A"),
		std::make_tuple<uint32_t, std::string>(0x000B239AU, "000B239A"),
		std::make_tuple<uint32_t, std::string>(0x00000000U, "00000000"),
	});

	Test_IntegerToHexImpl<_Alphabet, uint64_t>({
		std::make_tuple<uint64_t, std::string>(0x3E4B239A3F5C2D79ULL, "3E4B239A3F5C2D79"),
		std::make_tuple<uint64_t, std::string>(0x000000003F5C2D79ULL, "000000003F5C2D79"),
		std::make_tuple<uint64_t, std::string>(0x000000000F5C2D79ULL, "000000000F5C2D79"),
		std::make_tuple<uint64_t, std::string>(0x0000000000000000ULL, "0000000000000000"),
	});

	// Signed integers

	Test_IntegerToHexImpl<_Alphabet, int32_t>({
		std::make_tuple<int32_t, std::string>(0x3E4B239A, "3E4B239A"),
		std::make_tuple<int32_t, std::string>(0x004B239A, "004B239A"),
		std::make_tuple<int32_t, std::string>(0x000B239A, "000B239A"),
		std::make_tuple<int32_t, std::string>(0x00000000, "00000000"),
		std::make_tuple<int32_t, std::string>(-0x3E4B239A, "3E4B239A"),
		std::make_tuple<int32_t, std::string>(-0x000B239A, "000B239A"),
	});

	Test_IntegerToHexImpl<_Alphabet, int64_t>({
		std::make_tuple<int64_t, std::string>(0x3E4B239A3F5C2D79LL, "3E4B239A3F5C2D79"),
		std::make_tuple<int64_t, std::string>(0x000000003F5C2D79LL, "000000003F5C2D79"),
		std::make_tuple<int64_t, std::string>(0x000000000F5C2D79LL, "000000000F5C2D79"),
		std::make_tuple<int64_t, std::string>(0x0000000000000000LL, "0000000000000000"),
		std::make_tuple<int64_t, std::string>(-0x3E4B239A3F5C2D79LL, "3E4B239A3F5C2D79"),
		std::make_tuple<int64_t, std::string>(-0x000000000F5C2D79LL, "000000000F5C2D79"),
	});
}

namespace {

template<typename _EncoderSet, typename _IntegerType>
static void Test_HexEncode_Integer_OneCase(
	_IntegerType val,
	const std::string& expectedDefault,
	const std::string& expectedKeepT
)
{
	std::string actual;

	// integer --> container
	actual = _EncoderSet::template Encode<std::string>(val);
	EXPECT_EQ(actual, expectedDefault);
	actual = _EncoderSet::template Encode<std::string, HexZero::Keep, true>(val);
	EXPECT_EQ(actual, expectedKeepT);

	auto endIt = actual.end();

	// integer --> iterator
	actual.clear();
	_EncoderSet::Encode(std::back_inserter(actual), val);
	ASSERT_EQ(actual, expectedDefault);
	endIt = _EncoderSet::Encode(actual.begin(), val);
	EXPECT_EQ(actual, expectedDefault);
	EXPECT_EQ(endIt, actual.end());

	actual.clear();
	_EncoderSet::template Encode<HexZero::Keep, true>(std::back_inserter(actual), val);
	ASSERT_EQ(actual, expectedKeepT);
	endIt = _EncoderSet::template Encode<HexZero::Keep, true>(actual.begin(), val);
	EXPECT_EQ(actual, expectedKeepT);
	EXPECT_EQ(endIt, actual.end());
}

} // namespace


GTEST_TEST(TestCodecHex, Hex_Encode_Integer)
{
	Test_HexEncode_Integer_OneCase<Hex, uint8_t>(0x0AU, "0xa", "0x0a");
	Test_HexEncode_Integer_OneCase<Hex, uint16_t>(0x0E4BU, "0xe4b", "0x0e4b");
	Test_HexEncode_Integer_OneCase<Hex, uint32_t>(0x0E4B239AU, "0xe4b239a", "0x0e4b239a");
	Test_HexEncode_Integer_OneCase<Hex, uint64_t>(0x0E4B239A3F5C2D79ULL, "0xe4b239a3f5c2d79", "0x0e4b239a3f5c2d79");


	Test_HexEncode_Integer_OneCase<Hex, int32_t>(-0x0E4B239A, "-0xe4b239a", "0x0e4b239a");
	Test_HexEncode_Integer_OneCase<Hex, int64_t>(-0x0E4B239A3F5C2D79LL, "-0xe4b239a3f5c2d79", "0x0e4b239a3f5c2d79");


	Test_HexEncode_Integer_OneCase<HEX, uint8_t>(0x0AU, "0xA", "0x0A");
	Test_HexEncode_Integer_OneCase<HEX, uint16_t>(0x0E4BU, "0xE4B", "0x0E4B");
	Test_HexEncode_Integer_OneCase<HEX, uint32_t>(0x0E4B239AU, "0xE4B239A", "0x0E4B239A");
	Test_HexEncode_Integer_OneCase<HEX, uint64_t>(0x0E4B239A3F5C2D79ULL, "0xE4B239A3F5C2D79", "0x0E4B239A3F5C2D79");


	Test_HexEncode_Integer_OneCase<HEX, int32_t>(-0x0E4B239A, "-0xE4B239A", "0x0E4B239A");
	Test_HexEncode_Integer_OneCase<HEX, int64_t>(-0x0E4B239A3F5C2D79LL, "-0xE4B239A3F5C2D79", "0x0E4B239A3F5C2D79");
}


//==============================================================================
//
// Hex::Encode(bytes)
//
//==============================================================================


namespace {

static void Test_Hex_Encode(
	const std::vector<
		std::tuple<
			std::vector<uint8_t>,
			std::string,
			std::string
		>
	>& testCases
)
{
	for (const auto& testCase: testCases)
	{
		const std::vector<uint8_t>& input =
			std::get<0>(testCase);
		const std::string& expectedLower =
			std::get<1>(testCase);
		const std::string& expectedLowerNoLZero =
			expectedLower.substr(expectedLower.find_first_not_of('0'));
		const std::string& expectedUpper =
			std::get<2>(testCase);
		const std::string& expectedUpperNoLZero =
			expectedUpper.substr(expectedUpper.find_first_not_of('0'));

		std::string actual;
		auto endIt = actual.begin();
		// container -> container
		{
			// lower case
			actual = Hex::Encode<std::string>(input);
			EXPECT_EQ(actual, expectedLower);
			actual = Hex::Encode<std::string>(input, "0x");
			EXPECT_EQ(actual, "0x" + expectedLower);

			actual = Hex::Encode<std::string, false>(input);
			EXPECT_EQ(actual, expectedLowerNoLZero);
			actual = Hex::Encode<std::string, false>(input, "0x");
			EXPECT_EQ(actual, "0x" + expectedLowerNoLZero);

			// upper case
			actual = HEX::Encode<std::string>(input);
			EXPECT_EQ(actual, expectedUpper);
			actual = HEX::Encode<std::string>(input, "0x");
			EXPECT_EQ(actual, "0x" + expectedUpper);

			actual = HEX::Encode<std::string, false>(input);
			EXPECT_EQ(actual, expectedUpperNoLZero);
			actual = HEX::Encode<std::string, false>(input, "0x");
			EXPECT_EQ(actual, "0x" + expectedUpperNoLZero);
		}

		// iterator -> container
		{
			// lower case
			actual = Hex::Encode<std::string>(input.cbegin(), input.cend());
			EXPECT_EQ(actual, expectedLower);
			actual = Hex::Encode<std::string>(input.cbegin(), input.cend(), "0x");
			EXPECT_EQ(actual, "0x" + expectedLower);

			actual = Hex::Encode<std::string, false>(input.cbegin(), input.cend());
			EXPECT_EQ(actual, expectedLowerNoLZero);
			actual = Hex::Encode<std::string, false>(input.cbegin(), input.cend(), "0x");
			EXPECT_EQ(actual, "0x" + expectedLowerNoLZero);

			// upper case
			actual = HEX::Encode<std::string>(input.cbegin(), input.cend());
			EXPECT_EQ(actual, expectedUpper);
			actual = HEX::Encode<std::string>(input.cbegin(), input.cend(), "0x");
			EXPECT_EQ(actual, "0x" + expectedUpper);

			actual = HEX::Encode<std::string, false>(input.cbegin(), input.cend());
			EXPECT_EQ(actual, expectedUpperNoLZero);
			actual = HEX::Encode<std::string, false>(input.cbegin(), input.cend(), "0x");
			EXPECT_EQ(actual, "0x" + expectedUpperNoLZero);
		}

		// iterator -> iterator
		{
			// lower case
			actual.clear();
			Hex::Encode(std::back_inserter(actual), input.cbegin(), input.cend());
			ASSERT_EQ(actual, expectedLower);
			endIt = Hex::Encode(actual.begin(), input.cbegin(), input.cend());
			EXPECT_EQ(actual, expectedLower);
			ASSERT_EQ(endIt, actual.end());

			actual.clear();
			Hex::Encode(std::back_inserter(actual), input.cbegin(), input.cend(), "0x");
			ASSERT_EQ(actual, "0x" + expectedLower);
			endIt = Hex::Encode(actual.begin(), input.cbegin(), input.cend(), "0x");
			EXPECT_EQ(actual, "0x" + expectedLower);
			ASSERT_EQ(endIt, actual.end());

			actual.clear();
			Hex::Encode<false>(std::back_inserter(actual), input.cbegin(), input.cend());
			ASSERT_EQ(actual, expectedLowerNoLZero);
			endIt = Hex::Encode<false>(actual.begin(), input.cbegin(), input.cend());
			EXPECT_EQ(actual, expectedLowerNoLZero);
			ASSERT_EQ(endIt, actual.end());

			actual.clear();
			Hex::Encode<false>(std::back_inserter(actual), input.cbegin(), input.cend(), "0x");
			ASSERT_EQ(actual, "0x" + expectedLowerNoLZero);
			endIt = Hex::Encode<false>(actual.begin(), input.cbegin(), input.cend(), "0x");
			EXPECT_EQ(actual, "0x" + expectedLowerNoLZero);
			ASSERT_EQ(endIt, actual.end());

			// upper case
			actual.clear();
			HEX::Encode(std::back_inserter(actual), input.cbegin(), input.cend());
			ASSERT_EQ(actual, expectedUpper);
			endIt = HEX::Encode(actual.begin(), input.cbegin(), input.cend());
			EXPECT_EQ(actual, expectedUpper);
			ASSERT_EQ(endIt, actual.end());

			actual.clear();
			HEX::Encode(std::back_inserter(actual), input.cbegin(), input.cend(), "0x");
			ASSERT_EQ(actual, "0x" + expectedUpper);
			endIt = HEX::Encode(actual.begin(), input.cbegin(), input.cend(), "0x");
			EXPECT_EQ(actual, "0x" + expectedUpper);
			ASSERT_EQ(endIt, actual.end());

			actual.clear();
			HEX::Encode<false>(std::back_inserter(actual), input.cbegin(), input.cend());
			ASSERT_EQ(actual, expectedUpperNoLZero);
			endIt = HEX::Encode<false>(actual.begin(), input.cbegin(), input.cend());
			EXPECT_EQ(actual, expectedUpperNoLZero);
			ASSERT_EQ(endIt, actual.end());

			actual.clear();
			HEX::Encode<false>(std::back_inserter(actual), input.cbegin(), input.cend(), "0x");
			ASSERT_EQ(actual, "0x" + expectedUpperNoLZero);
			endIt = HEX::Encode<false>(actual.begin(), input.cbegin(), input.cend(), "0x");
			EXPECT_EQ(actual, "0x" + expectedUpperNoLZero);
			ASSERT_EQ(endIt, actual.end());
		}
	}
}

} // namespace


GTEST_TEST(TestCodecHex, Hex_Encode)
{
	Test_Hex_Encode(
		{
			std::make_tuple(
				std::vector<uint8_t>({
					0x12U, 0x34U, 0x56U, 0x78U, 0x9AU, 0xBCU, 0xDEU, 0xF0U,
				}),
				"123456789abcdef0",
				"123456789ABCDEF0"
			),
			std::make_tuple(
				std::vector<uint8_t>({
					0x00U, 0x00U, 0x00U, 0x08U, 0x9AU, 0xBCU, 0xDEU, 0xF0U,
				}),
				"000000089abcdef0",
				"000000089ABCDEF0"
			),
		}
	);
}


GTEST_TEST(TestCodecHex, Hex_Encode_C_Array)
{
	std::string output;
	std::string expOutput;

	uint8_t arrInput[] =
		{ 0x12U, 0x34U, 0x56U, 0x78U, 0x9AU, 0xBCU, 0xDEU, 0xF0U, };
	output = Hex::Encode<std::string>(arrInput);
	expOutput = "123456789abcdef0";
	EXPECT_EQ(output, expOutput);
}


//==============================================================================
//
// HexToBytesImpl
//
//==============================================================================


GTEST_TEST(TestCodecHex, Internal_HexValueLut)
{
	using namespace Internal;

	using _LutType = HexValueLut<uint8_t, char>;

	EXPECT_EQ(_LutType::GetValue('0'), 0);
	EXPECT_EQ(_LutType::GetValue('1'), 1);
	EXPECT_EQ(_LutType::GetValue('2'), 2);
	EXPECT_EQ(_LutType::GetValue('3'), 3);
	EXPECT_EQ(_LutType::GetValue('4'), 4);
	EXPECT_EQ(_LutType::GetValue('5'), 5);
	EXPECT_EQ(_LutType::GetValue('6'), 6);
	EXPECT_EQ(_LutType::GetValue('7'), 7);
	EXPECT_EQ(_LutType::GetValue('8'), 8);
	EXPECT_EQ(_LutType::GetValue('9'), 9);

	EXPECT_EQ(_LutType::GetValue('a'), 10);
	EXPECT_EQ(_LutType::GetValue('b'), 11);
	EXPECT_EQ(_LutType::GetValue('c'), 12);
	EXPECT_EQ(_LutType::GetValue('d'), 13);
	EXPECT_EQ(_LutType::GetValue('e'), 14);
	EXPECT_EQ(_LutType::GetValue('f'), 15);

	EXPECT_EQ(_LutType::GetValue('A'), 10);
	EXPECT_EQ(_LutType::GetValue('B'), 11);
	EXPECT_EQ(_LutType::GetValue('C'), 12);
	EXPECT_EQ(_LutType::GetValue('D'), 13);
	EXPECT_EQ(_LutType::GetValue('E'), 14);
	EXPECT_EQ(_LutType::GetValue('F'), 15);

	EXPECT_THROW(_LutType::GetValue('g'), std::invalid_argument);
	EXPECT_THROW(_LutType::GetValue('G'), std::invalid_argument);
}


GTEST_TEST(TestCodecHex, Internal_HexToBytesImpl_DecodeSingle)
{
	using namespace Internal;

	using _Decoder = HexToBytesImpl<HexValueLut<uint8_t, char>, 1>;

	{
		uint8_t val = 0;

		val = _Decoder::DecodeSingle<uint8_t>('0', '0');
		EXPECT_EQ(val, 0x00U);
		val = _Decoder::DecodeSingle<uint8_t>('1', '1');
		EXPECT_EQ(val, 0x11U);
		val = _Decoder::DecodeSingle<uint8_t>('a', 'A');
		EXPECT_EQ(val, 0xAAU);
		val = _Decoder::DecodeSingle<uint8_t>('b', 'B');
		EXPECT_EQ(val, 0xBBU);
		val = _Decoder::DecodeSingle<uint8_t>('c', 'C');
		EXPECT_EQ(val, 0xCCU);
		val = _Decoder::DecodeSingle<uint8_t>('D', 'd');
		EXPECT_EQ(val, 0xDDU);
		val = _Decoder::DecodeSingle<uint8_t>('E', 'e');
		EXPECT_EQ(val, 0xEEU);
		val = _Decoder::DecodeSingle<uint8_t>('F', 'f');
		EXPECT_EQ(val, 0xFFU);
	}

	{
		char val = 0;

		val = _Decoder::DecodeSingle<char>('0', '0');
		EXPECT_EQ(val, 0x00);
		val = _Decoder::DecodeSingle<char>('1', '1');
		EXPECT_EQ(val, 0x11);
		val = _Decoder::DecodeSingle<char>('a', 'A');
		EXPECT_EQ(val, ~char(0x55));
		val = _Decoder::DecodeSingle<char>('b', 'B');
		EXPECT_EQ(val, ~char(0x44));
		val = _Decoder::DecodeSingle<char>('c', 'C');
		EXPECT_EQ(val, ~char(0x33));
		val = _Decoder::DecodeSingle<char>('D', 'd');
		EXPECT_EQ(val, ~char(0x22));
		val = _Decoder::DecodeSingle<char>('E', 'e');
		EXPECT_EQ(val, ~char(0x11));
		val = _Decoder::DecodeSingle<char>('F', 'f');
		EXPECT_EQ(val, ~char(0x00));
	}
}


namespace
{

template<bool _expected, typename _InIt>
static bool CanPadInPlace(_InIt)
{
	using namespace Internal;

	static constexpr bool canPadInPlace = HexDecodeCanPadInPlace<_InIt>();
	static_assert(
		canPadInPlace == _expected,
		"CanPadInPlace() returned unexpected value"
	);

	return canPadInPlace;
}

template<bool _canPadInPlace>
struct Test_HexToBytesImpl_ThrowIfPadDisabled;

template<>
struct Test_HexToBytesImpl_ThrowIfPadDisabled<true>
{
	template<typename _Decoder, bool _KeepLeadingZeroBytes, typename _Container>
	static void Test(const _Container& input)
	{
		if (input.size() % 2 != 0)
		{
			// decoder can pad in place, and input is odd
			// we want to test throwing behavior when padding is disabled

			size_t decodedSize = 0;
			std::vector<uint8_t> actual;

			auto prog1 = [&](){
				_Decoder::template
					Decode<_KeepLeadingZeroBytes, HexPad::Disabled, uint8_t>(
						std::back_inserter(actual),
						input.cbegin(),
						input.cend(),
						decodedSize
					);
			};
			EXPECT_THROW(prog1(), std::invalid_argument);

			auto prog2 = [&](){
				_Decoder::template
					Decode<_KeepLeadingZeroBytes, HexPad::Disabled, uint8_t>(
						actual.begin(),
						input.cbegin(),
						input.cend(),
						decodedSize
					);
			};
			EXPECT_THROW(prog2(), std::invalid_argument);
		}
	}
}; // struct Test_HexToBytesImpl_ThrowIfPadDisabled<true>

template<>
struct Test_HexToBytesImpl_ThrowIfPadDisabled<false>
{
	template<typename _Decoder, bool _KeepLeadingZeroBytes, typename _Container>
	static void Test(const _Container& /* input */)
	{}
}; // struct Test_HexToBytesImpl_ThrowIfPadDisabled<false>


template<typename _InputType>
static void Test_HexToBytesImpl_Decode_InputIt(
	const std::vector<
		std::tuple<
			_InputType,
			std::vector<uint8_t>,
			size_t,
			std::vector<uint8_t>,
			size_t
		>
	>& testCases
)
{
	using namespace Internal;

	using _Decoder = HexToBytesImpl<HexValueLut<uint8_t, char>, 1>;

	static constexpr bool sk_canPad =
		HexDecodeCanPadInPlace<typename _InputType::const_iterator>();

	size_t decodedSize = 0;
	std::vector<uint8_t> actual;
	auto endIt = actual.end();

	for (const auto& testCase: testCases)
	{
		const auto& input = std::get<0>(testCase);
		// keep leading zero bytes
		{
			const auto& expected = std::get<1>(testCase);
			const auto& expectedSize = std::get<2>(testCase);

			Test_HexToBytesImpl_ThrowIfPadDisabled<sk_canPad>::
				template Test<_Decoder, true>(input);

			decodedSize = 0;
			actual.clear();
			_Decoder::Decode<true, HexPad::Front, uint8_t>(
				std::back_inserter(actual),
				input.cbegin(),
				input.cend(),
				decodedSize
			);
			ASSERT_EQ(actual, expected);
			ASSERT_EQ(decodedSize, expectedSize);

			decodedSize = 0;
			endIt = _Decoder::Decode<true, HexPad::Front, uint8_t>(
				actual.begin(),
				input.cbegin(),
				input.cend(),
				decodedSize
			);
			EXPECT_EQ(endIt, actual.end());
			EXPECT_EQ(actual, expected);
			EXPECT_EQ(decodedSize, expectedSize);
		}
		// skip leading zero bytes
		{
			const auto& expected = std::get<3>(testCase);
			const auto& expectedSize = std::get<4>(testCase);

			Test_HexToBytesImpl_ThrowIfPadDisabled<sk_canPad>::
				template Test<_Decoder, false>(input);

			decodedSize = 0;
			actual.clear();
			_Decoder::Decode<false, HexPad::Front, uint8_t>(
				std::back_inserter(actual),
				input.cbegin(),
				input.cend(),
				decodedSize
			);
			ASSERT_EQ(actual, expected);
			ASSERT_EQ(decodedSize, expectedSize);

			decodedSize = 0;
			endIt = _Decoder::Decode<false, HexPad::Front, uint8_t>(
				actual.begin(),
				input.cbegin(),
				input.cend(),
				decodedSize
			);
			EXPECT_EQ(endIt, actual.end());
			EXPECT_EQ(actual, expected);
			EXPECT_EQ(decodedSize, expectedSize);
		}
	}
}

} // namespace


GTEST_TEST(TestCodecHex, Internal_HexToBytesImpl_CanPadInPlace)
{
	{
		std::vector<uint8_t> input;
		bool res = CanPadInPlace<true>(input.begin());
		EXPECT_TRUE(res);
	}
	{
		std::list<uint8_t> input;
		bool res = CanPadInPlace<false>(input.begin());
		EXPECT_FALSE(res);
	}
}


GTEST_TEST(TestCodecHex, Internal_HexToBytesImpl_Decode_InputIt)
{
	using namespace Internal;

	Test_HexToBytesImpl_Decode_InputIt<std::list<char> >(
		{
			std::make_tuple(
				std::list<char>({
					'1', '2', '3', '4', '5', '6', '7', '8',
					'9', 'a', 'b', 'c', 'd', 'e', 'f', '0',
				}),
				std::vector<uint8_t>({
					0x12U, 0x34U, 0x56U, 0x78U, 0x9AU, 0xBCU, 0xDEU, 0xF0U,
				}),
				16,
				std::vector<uint8_t>({
					0x12U, 0x34U, 0x56U, 0x78U, 0x9AU, 0xBCU, 0xDEU, 0xF0U,
				}),
				16
			),

			std::make_tuple(
				std::list<char>({
					'0', '1', '2', '3', '4', '5', '6', '7',
					'8', '9', 'a', 'b', 'c', 'd', 'e', 'f',
				}),
				std::vector<uint8_t>({
					0x01U, 0x23U, 0x45U, 0x67U, 0x89U, 0xABU, 0xCDU, 0xEFU,
				}),
				16,
				std::vector<uint8_t>({
					0x01U, 0x23U, 0x45U, 0x67U, 0x89U, 0xABU, 0xCDU, 0xEFU,
				}),
				16
			),

			std::make_tuple(
				std::list<char>({
					'0', '0', '2', '3', '4', '5', '6', '7',
					'8', '9', 'a', 'b', 'c', 'd', 'e', 'f',
				}),
				std::vector<uint8_t>({
					0x00U, 0x23U, 0x45U, 0x67U, 0x89U, 0xABU, 0xCDU, 0xEFU,
				}),
				16,
				std::vector<uint8_t>({
					0x23U, 0x45U, 0x67U, 0x89U, 0xABU, 0xCDU, 0xEFU,
				}),
				16
			),

			std::make_tuple(
				std::list<char>({
				}),
				std::vector<uint8_t>({
				}),
				0,
				std::vector<uint8_t>({
				}),
				0
			),

			std::make_tuple(
				std::list<char>({
					'0', '0',
				}),
				std::vector<uint8_t>({
					0x00U,
				}),
				2,
				std::vector<uint8_t>({
				}),
				2
			),

			std::make_tuple(
				std::list<char>({
					'0',
				}),
				std::vector<uint8_t>({
					0x00U,
				}),
				1,
				std::vector<uint8_t>({
				}),
				1
			),

			std::make_tuple(
				std::list<char>({
					'1', '2', '3',
				}),
				std::vector<uint8_t>({
					0x12U, 0x30U,
				}),
				3,
				std::vector<uint8_t>({
					0x12U, 0x30U,
				}),
				3
			),
		}
	);
}


GTEST_TEST(TestCodecHex, Internal_HexToBytesImpl_Decode_RandIt)
{
	using namespace Internal;

	Test_HexToBytesImpl_Decode_InputIt<std::string>(
		{
			std::make_tuple(
				std::string("123456789abcdef0"),
				std::vector<uint8_t>({
					0x12U, 0x34U, 0x56U, 0x78U, 0x9AU, 0xBCU, 0xDEU, 0xF0U,
				}),
				16,
				std::vector<uint8_t>({
					0x12U, 0x34U, 0x56U, 0x78U, 0x9AU, 0xBCU, 0xDEU, 0xF0U,
				}),
				16
			),
			std::make_tuple(
				std::string("0123456789abcdef"),
				std::vector<uint8_t>({
					0x01U, 0x23U, 0x45U, 0x67U, 0x89U, 0xABU, 0xCDU, 0xEFU,
				}),
				16,
				std::vector<uint8_t>({
					0x01U, 0x23U, 0x45U, 0x67U, 0x89U, 0xABU, 0xCDU, 0xEFU,
				}),
				16
			),
			std::make_tuple(
				std::string("0023456789abcdef"),
				std::vector<uint8_t>({
					0x00U, 0x23U, 0x45U, 0x67U, 0x89U, 0xABU, 0xCDU, 0xEFU,
				}),
				16,
				std::vector<uint8_t>({
					0x23U, 0x45U, 0x67U, 0x89U, 0xABU, 0xCDU, 0xEFU,
				}),
				16
			),
			std::make_tuple(
				std::string(),
				std::vector<uint8_t>(),
				0,
				std::vector<uint8_t>(),
				0
			),
			std::make_tuple(
				std::string("00"),
				std::vector<uint8_t>({ 0x00U, }),
				2,
				std::vector<uint8_t>(),
				2
			),
			std::make_tuple(
				std::string("0"),
				std::vector<uint8_t>({ 0x00U, }),
				2,
				std::vector<uint8_t>(),
				2
			),
			std::make_tuple(
				std::string("0000"),
				std::vector<uint8_t>({ 0x00U, 0x00U, }),
				4,
				std::vector<uint8_t>(),
				4
			),
			std::make_tuple(
				std::string("000"),
				std::vector<uint8_t>({ 0x00U, 0x00U, }),
				4,
				std::vector<uint8_t>(),
				4
			),
			std::make_tuple(
				std::string("123"),
				std::vector<uint8_t>({ 0x01U, 0x23U, }),
				4,
				std::vector<uint8_t>({ 0x01U, 0x23U, }),
				4
			),
		}
	);
}


GTEST_TEST(TestCodecHex, BitWiseShiftBytesRight)
{
	using namespace Internal;

	{
		std::vector<uint8_t> input;
		EXPECT_THROW(
			BitWiseShiftBytesRight(input.begin(), input.end(), 0),
			std::invalid_argument
		);
		EXPECT_THROW(
			BitWiseShiftBytesRight(input.begin(), input.end(), 9),
			std::invalid_argument
		);
	}

	// shift 1 bits right
	{
		std::vector<uint8_t> input = {
			0x12U, 0x34U, 0x56U, 0x78U, 0x9AU, 0xBCU, 0xDEU, 0xF0U,
		};
		const std::vector<uint8_t> expected = {
			0x09U, 0x1AU, 0x2BU, 0x3CU, 0x4DU, 0x5EU, 0x6FU, 0x78U,
		};
		EXPECT_NO_THROW(BitWiseShiftBytesRight(input.begin(), input.end(), 1));
		EXPECT_EQ(input, expected);
	}
	// shift 2 bits right
	{
		std::vector<uint8_t> input = {
			0x12U, 0x34U, 0x56U, 0x78U, 0x9AU, 0xBCU, 0xDEU, 0xF0U,
		};
		const std::vector<uint8_t> expected = {
			0x04U, 0x8DU, 0x15U, 0x9EU, 0x26U, 0xAFU, 0x37U, 0xBCU,
		};
		EXPECT_NO_THROW(BitWiseShiftBytesRight(input.begin(), input.end(), 2));
		EXPECT_EQ(input, expected);
	}
	// shift 3 bits right
	{
		std::vector<uint8_t> input = {
			0x12U, 0x34U, 0x56U, 0x78U, 0x9AU, 0xBCU, 0xDEU, 0xF0U,
		};
		const std::vector<uint8_t> expected = {
			0x02U, 0x46U, 0x8AU, 0xCFU, 0x13U, 0x57U, 0x9BU, 0xDEU,
		};
		EXPECT_NO_THROW(BitWiseShiftBytesRight(input.begin(), input.end(), 3));
		EXPECT_EQ(input, expected);
	}
	// shift 4 bits right
	{
		std::vector<uint8_t> input = {
			0x12U, 0x34U, 0x56U, 0x78U, 0x9AU, 0xBCU, 0xDEU, 0xF0U,
		};
		const std::vector<uint8_t> expected = {
			0x01U, 0x23U, 0x45U, 0x67U, 0x89U, 0xABU, 0xCDU, 0xEFU,
		};
		EXPECT_NO_THROW(BitWiseShiftBytesRight(input.begin(), input.end(), 4));
		EXPECT_EQ(input, expected);
	}

	// shift 8 bits right
	{
		std::vector<uint8_t> input = {
			0x12U, 0x34U, 0x56U, 0x78U, 0x9AU, 0xBCU, 0xDEU, 0xF0U,
		};
		const std::vector<uint8_t> expected = {
			0x00U, 0x12U, 0x34U, 0x56U, 0x78U, 0x9AU, 0xBCU, 0xDEU,
		};
		EXPECT_NO_THROW(BitWiseShiftBytesRight(input.begin(), input.end(), 8));
		EXPECT_EQ(input, expected);
	}
}


//==============================================================================
//
// Hex::Decode
//
//==============================================================================


namespace
{

template<typename _InputContainer>
static void Test_Hex_Decode(
	const std::vector<
		std::tuple<
			_InputContainer,
			std::vector<uint8_t>,
			std::vector<uint8_t>
		>
	>& testCases
)
{
	using _InputIt = typename _InputContainer::const_iterator;
	static constexpr bool sk_canPad =
		Internal::HexDecodeCanPadInPlace<_InputIt>();

	std::vector<uint8_t> actual;
	auto endIt = actual.end();

	for (const auto& testCase : testCases)
	{
		const auto& input = std::get<0>(testCase);

		// container -> container
		// with leading zeros
		{
			const auto& expected = std::get<1>(testCase);

			// padding disabled
			if (input.size() % 2 != 0)
			{
				// odd number of characters - test throwing behavior
				auto prog = [&](){
					Hex::Decode<std::vector<uint8_t> >(input);
				};
				EXPECT_THROW(prog(), std::invalid_argument);
			}
			else
			{
				// even number of characters - test decoding
				actual.clear();
				actual = Hex::Decode<std::vector<uint8_t> >(input);
				EXPECT_EQ(actual, expected);
			}

			// padding front
			actual.clear();
			actual = Hex::template
				Decode<std::vector<uint8_t>, true, HexPad::Front>(input);
			EXPECT_EQ(actual, expected);
		}

		// without leading zeros
		{
			const auto& expected = std::get<2>(testCase);

			// padding disabled
			if (input.size() % 2 != 0)
			{
				// odd number of characters - test throwing behavior
				auto prog = [&](){
					Hex::template
						Decode<std::vector<uint8_t>, false, HexPad::Disabled>(input);
				};
				EXPECT_THROW(prog(), std::invalid_argument);
			}
			else
			{
				// even number of characters - test decoding
				actual.clear();
				actual = Hex::template
					Decode<std::vector<uint8_t>, false, HexPad::Disabled>(input);
				EXPECT_EQ(actual, expected);
			}

			// padding front
			actual.clear();
			actual = Hex::template
				Decode<std::vector<uint8_t>, false, HexPad::Front>(input);
			EXPECT_EQ(actual, expected);
		}



		// iterator -> container
		// with leading zeros
		{
			const auto& expected = std::get<1>(testCase);

			// padding disabled
			if (input.size() % 2 != 0)
			{
				// odd number of characters - test throwing behavior
				auto prog = [&](){
					Hex::Decode<std::vector<uint8_t> >(std::begin(input), std::end(input));
				};
				EXPECT_THROW(prog(), std::invalid_argument);
			}
			else
			{
				// even number of characters - test decoding
				actual.clear();
				actual = Hex::Decode<std::vector<uint8_t> >(std::begin(input), std::end(input));
				EXPECT_EQ(actual, expected);
			}

			// padding front
			actual.clear();
			actual = Hex::template
				Decode<std::vector<uint8_t>, true, HexPad::Front>(std::begin(input), std::end(input));
			EXPECT_EQ(actual, expected);
		}

		// without leading zeros
		{
			const auto& expected = std::get<2>(testCase);

			// padding disabled
			if (input.size() % 2 != 0)
			{
				// odd number of characters - test throwing behavior
				auto prog = [&](){
					Hex::template
						Decode<std::vector<uint8_t>, false, HexPad::Disabled>(std::begin(input), std::end(input));
				};
				EXPECT_THROW(prog(), std::invalid_argument);
			}
			else
			{
				// even number of characters - test decoding
				actual.clear();
				actual = Hex::template
					Decode<std::vector<uint8_t>, false, HexPad::Disabled>(std::begin(input), std::end(input));
				EXPECT_EQ(actual, expected);
			}

			// padding front
			actual.clear();
			actual = Hex::template
				Decode<std::vector<uint8_t>, false, HexPad::Front>(std::begin(input), std::end(input));
			EXPECT_EQ(actual, expected);
		}



		// iterator -> iterator
		// with leading zeros
		{
			const auto& expected = std::get<1>(testCase);

			if ((input.size() % 2 != 0) && !sk_canPad)
			{
				// odd & can't pad --> must throw due to padding issue
				actual.clear();

				auto prog1 = [&](){
					Hex::Decode(std::back_inserter(actual), std::begin(input), std::end(input));
				};
				EXPECT_THROW(prog1(), std::invalid_argument);

				auto prog2 = [&](){
					Hex::template
						Decode<true, HexPad::Front>(std::back_inserter(actual), std::begin(input), std::end(input));
				};
				EXPECT_THROW(prog2(), std::invalid_argument);
			}
			else if (input.size() % 2 == 0)
			{
				// even --> must not throw
				actual.clear();
				Hex::Decode(std::back_inserter(actual), std::begin(input), std::end(input));
				ASSERT_EQ(actual, expected);
				endIt = Hex::Decode(actual.begin(), std::begin(input), std::end(input));
				EXPECT_EQ(actual, expected);
				EXPECT_EQ(endIt, actual.end());

				// padding front
				actual.clear();
				Hex::template
					Decode<true, HexPad::Front>(std::back_inserter(actual), std::begin(input), std::end(input));
				ASSERT_EQ(actual, expected);
				endIt = Hex::template
					Decode<true, HexPad::Front>(actual.begin(), std::begin(input), std::end(input));
				EXPECT_EQ(actual, expected);
				EXPECT_EQ(endIt, actual.end());
			}
			else
			{
				// odd & can pad --> throw when padding is disabled
				// no throw when padding is enabled
				actual.clear();

				auto prog1 = [&](){
					Hex::Decode(std::back_inserter(actual), std::begin(input), std::end(input));
				};
				EXPECT_THROW(prog1(), std::invalid_argument);

				// padding front
				actual.clear();
				Hex::template
					Decode<true, HexPad::Front>(std::back_inserter(actual), std::begin(input), std::end(input));
				ASSERT_EQ(actual, expected);
				endIt = Hex::template
					Decode<true, HexPad::Front>(actual.begin(), std::begin(input), std::end(input));
				EXPECT_EQ(actual, expected);
				EXPECT_EQ(endIt, actual.end());
			}
		}

		// without leading zeros
		{
			const auto& expected = std::get<2>(testCase);

			// no throw due to padding
			if ((input.size() % 2 != 0) && !sk_canPad)
			{
				// odd & can't pad --> must throw due to padding issue
				actual.clear();

				auto prog1 = [&](){
					Hex::template
						Decode<false, HexPad::Disabled>(std::back_inserter(actual), std::begin(input), std::end(input));
				};
				EXPECT_THROW(prog1(), std::invalid_argument);

				auto prog2 = [&](){
					Hex::template
						Decode<false, HexPad::Front>(std::back_inserter(actual), std::begin(input), std::end(input));
				};
				EXPECT_THROW(prog2(), std::invalid_argument);
			}
			else if (input.size() % 2 == 0)
			{
				// even --> must not throw
				actual.clear();
				Hex::template
					Decode<false, HexPad::Disabled>(std::back_inserter(actual), std::begin(input), std::end(input));
				ASSERT_EQ(actual, expected);
				endIt = Hex::template
					Decode<false, HexPad::Disabled>(actual.begin(), std::begin(input), std::end(input));
				EXPECT_EQ(actual, expected);
				EXPECT_EQ(endIt, actual.end());

				// padding front
				actual.clear();
				Hex::template
					Decode<false, HexPad::Front>(std::back_inserter(actual), std::begin(input), std::end(input));
				ASSERT_EQ(actual, expected);
				endIt = Hex::template
					Decode<false, HexPad::Front>(actual.begin(), std::begin(input), std::end(input));
				EXPECT_EQ(actual, expected);
				EXPECT_EQ(endIt, actual.end());
			}
			else
			{
				// odd & can pad --> throw when padding is disabled
				// no throw when padding is enabled
				actual.clear();

				auto prog1 = [&](){
					Hex::template
						Decode<false, HexPad::Disabled>(std::back_inserter(actual), std::begin(input), std::end(input));
				};
				EXPECT_THROW(prog1(), std::invalid_argument);

				// padding front
				actual.clear();
				Hex::template
					Decode<false, HexPad::Front>(std::back_inserter(actual), std::begin(input), std::end(input));
				ASSERT_EQ(actual, expected);
				endIt = Hex::template
					Decode<false, HexPad::Front>(actual.begin(), std::begin(input), std::end(input));
				EXPECT_EQ(actual, expected);
				EXPECT_EQ(endIt, actual.end());
			}
		}
	}
}

} // namespace


GTEST_TEST(TestCodecHex, Hex_Decode)
{
	using _Bytes = std::vector<uint8_t>;

	Test_Hex_Decode<std::list<char> >({
		std::make_tuple<std::list<char>, _Bytes, _Bytes>(
			{
				'0', '0', '2', '3', '4', '5', '6', '7',
				'8', '9', 'a', 'b', 'c', 'd', 'e', 'f',
			},
			{ 0x00U, 0x23U, 0x45U, 0x67U, 0x89U, 0xABU, 0xCDU, 0xEFU, },
			{ 0x23U, 0x45U, 0x67U, 0x89U, 0xABU, 0xCDU, 0xEFU, }
		),


		std::make_tuple<std::list<char>, _Bytes, _Bytes>(
			{ '1', '2', '3' },
			{ 0x01U, 0x23U },
			{ 0x01U, 0x23U }
		),

	});

	Test_Hex_Decode<std::string>({
		std::make_tuple<std::string, _Bytes, _Bytes>(
			"0023456789abcdef",
			{ 0x00U, 0x23U, 0x45U, 0x67U, 0x89U, 0xABU, 0xCDU, 0xEFU, },
			{ 0x23U, 0x45U, 0x67U, 0x89U, 0xABU, 0xCDU, 0xEFU, }
		),
		std::make_tuple<std::string, _Bytes, _Bytes>(
			"123",
			{ 0x01U, 0x23U },
			{ 0x01U, 0x23U }
		),

	});
}


GTEST_TEST(TestCodecHex, Hex_Decode_C_Array)
{
	std::vector<uint8_t> output;
	std::vector<uint8_t> expOutput;

	char arrInput[16] = {
		'0', '0', '2', '3', '4', '5', '6', '7',
		'8', '9', 'a', 'b', 'c', 'd', 'e', 'f',
	};
	output = Hex::Decode<std::vector<uint8_t> >(arrInput);
	expOutput = {
		0x00U, 0x23U, 0x45U, 0x67U, 0x89U, 0xABU, 0xCDU, 0xEFU,
	};
	EXPECT_EQ(output, expOutput);
}
