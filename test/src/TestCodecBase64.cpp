// Copyright (c) 2023 Haofan Zheng
// Use of this source code is governed by an MIT-style
// license that can be found in the LICENSE file or at
// https://opensource.org/licenses/MIT.


#include <gtest/gtest.h>

#ifdef _MSC_VER
#include <windows.h>
#endif // _MSC_VER
#include <SimpleObjects/Codec/Base64.hpp>


#ifndef SIMPLEOBJECTS_CUSTOMIZED_NAMESPACE
using namespace SimpleObjects::Codec;
#else
using namespace SIMPLEOBJECTS_CUSTOMIZED_NAMESPACE::Codec;
#endif


namespace SimpleObjects_Test
{
	extern size_t g_numOfTestFile;
}


GTEST_TEST(TestCodecBase64, CountTestFile)
{
	static auto tmp = ++SimpleObjects_Test::g_numOfTestFile;
	(void)tmp;
}



//==============================================================================
//
// Utils
//
//==============================================================================


GTEST_TEST(TestCodecBase64, Base64Sizes)
{
	using _Sizes = Internal::Base64Sizes;

	static_assert(
		_Sizes::sk_inGroupSize == 3,
		"sk_inGroupSize != 3"
	);
	static_assert(
		_Sizes::sk_outGroupSize == 4,
		"sk_outGroupSize != 4"
	);

	// encoding num of groups

	static_assert(
		_Sizes::EstNumGroupsByBytes(0) == 0,
		"EstNumGroupsByBytes(0) != 0"
	);

	EXPECT_EQ(
		_Sizes::EstNumGroupsByBytes(0),
		0
	);
	EXPECT_EQ(
		_Sizes::EstNumGroupsByBytes(std::string("light w").size()),
		3
	);
	EXPECT_EQ(
		_Sizes::EstNumGroupsByBytes(std::string("light wo").size()),
		3
	);
	EXPECT_EQ(
		_Sizes::EstNumGroupsByBytes(std::string("light wor").size()),
		3
	);
	EXPECT_EQ(
		_Sizes::EstNumGroupsByBytes(std::string("light work").size()),
		4
	);
	EXPECT_EQ(
		_Sizes::EstNumGroupsByBytes(std::string("light work.").size()),
		4
	);

	// encoding output size

	static_assert(
		_Sizes::EstEncodedSize(0) == 0,
		"EstEncodedSize(0) != 0"
	);

	EXPECT_EQ(
		_Sizes::EstEncodedSize(0),
		0
	);
	EXPECT_EQ(
		_Sizes::EstEncodedSize(std::string("light w").size()),
		12
	);
	EXPECT_EQ(
		_Sizes::EstEncodedSize(std::string("light wo").size()),
		12
	);
	EXPECT_EQ(
		_Sizes::EstEncodedSize(std::string("light wor").size()),
		12
	);
	EXPECT_EQ(
		_Sizes::EstEncodedSize(std::string("light work").size()),
		16
	);
	EXPECT_EQ(
		_Sizes::EstEncodedSize(std::string("light work.").size()),
		16
	);

	// decoding num of groups

	static_assert(
		_Sizes::EstNumGroupsByChar(0) == 0,
		"EstNumGroupsByChar(0) != 0"
	);

	EXPECT_EQ(
		_Sizes::EstNumGroupsByChar(0),
		0
	);
	EXPECT_EQ(
		_Sizes::EstNumGroupsByChar(std::string("bGlnaHQgd29yay4=").size()),
		4
	);
	EXPECT_EQ(
		_Sizes::EstNumGroupsByChar(std::string("bGlnaHQgd29yaw==").size()),
		4
	);
	EXPECT_EQ(
		_Sizes::EstNumGroupsByChar(std::string("bGlnaHQgd29y").size()),
		3
	);
	EXPECT_EQ(
		_Sizes::EstNumGroupsByChar(std::string("bGlnaHQgd28=").size()),
		3
	);
	EXPECT_EQ(
		_Sizes::EstNumGroupsByChar(std::string("bGlnaHQgdw==").size()),
		3
	);

	// decoding output size

	static_assert(
		_Sizes::EstDecodedSize(0) == 0,
		"EstDecodedSize(0) != 0"
	);

	EXPECT_EQ(
		_Sizes::EstDecodedSize(0),
		0
	);
	EXPECT_EQ(
		_Sizes::EstDecodedSize(std::string("bGlnaHQgd29yay4=").size()),
		12
	);
	EXPECT_EQ(
		_Sizes::EstDecodedSize(std::string("bGlnaHQgd29yaw==").size()),
		12
	);
	EXPECT_EQ(
		_Sizes::EstDecodedSize(std::string("bGlnaHQgd29y").size()),
		9
	);
	EXPECT_EQ(
		_Sizes::EstDecodedSize(std::string("bGlnaHQgd28=").size()),
		9
	);
	EXPECT_EQ(
		_Sizes::EstDecodedSize(std::string("bGlnaHQgdw==").size()),
		9
	);

}


// ==========
// Encoding
// ==========


GTEST_TEST(TestCodecBase64, Alphabet)
{
	using _Alphabet = Internal::Base64Alphabet<char>;
	constexpr auto alphabet = _Alphabet::Alphabet();
	static_assert(
		std::tuple_size<decltype(alphabet)>::value == 64,
		"Alphabet size is not 64"
	);

	static_assert(alphabet[0] == 'A', "Alphabet[0] != 'A'");
	static_assert(alphabet[1] == 'B', "Alphabet[1] != 'B'");
	static_assert(alphabet[2] == 'C', "Alphabet[2] != 'C'");
	static_assert(alphabet[3] == 'D', "Alphabet[3] != 'D'");
	static_assert(alphabet[4] == 'E', "Alphabet[4] != 'E'");
	static_assert(alphabet[5] == 'F', "Alphabet[5] != 'F'");
	static_assert(alphabet[6] == 'G', "Alphabet[6] != 'G'");
	static_assert(alphabet[7] == 'H', "Alphabet[7] != 'H'");
	static_assert(alphabet[8] == 'I', "Alphabet[8] != 'I'");
	static_assert(alphabet[9] == 'J', "Alphabet[9] != 'J'");
	static_assert(alphabet[10] == 'K', "Alphabet[10] != 'K'");
	static_assert(alphabet[11] == 'L', "Alphabet[11] != 'L'");
	static_assert(alphabet[12] == 'M', "Alphabet[12] != 'M'");
	static_assert(alphabet[13] == 'N', "Alphabet[13] != 'N'");
	static_assert(alphabet[14] == 'O', "Alphabet[14] != 'O'");
	static_assert(alphabet[15] == 'P', "Alphabet[15] != 'P'");
	static_assert(alphabet[16] == 'Q', "Alphabet[16] != 'Q'");
	static_assert(alphabet[17] == 'R', "Alphabet[17] != 'R'");
	static_assert(alphabet[18] == 'S', "Alphabet[18] != 'S'");
	static_assert(alphabet[19] == 'T', "Alphabet[19] != 'T'");
	static_assert(alphabet[20] == 'U', "Alphabet[20] != 'U'");
	static_assert(alphabet[21] == 'V', "Alphabet[21] != 'V'");
	static_assert(alphabet[22] == 'W', "Alphabet[22] != 'W'");
	static_assert(alphabet[23] == 'X', "Alphabet[23] != 'X'");
	static_assert(alphabet[24] == 'Y', "Alphabet[24] != 'Y'");
	static_assert(alphabet[25] == 'Z', "Alphabet[25] != 'Z'");

	static_assert(alphabet[26] == 'a', "Alphabet[26] != 'a'");
	static_assert(alphabet[27] == 'b', "Alphabet[27] != 'b'");
	static_assert(alphabet[28] == 'c', "Alphabet[28] != 'c'");
	static_assert(alphabet[29] == 'd', "Alphabet[29] != 'd'");
	static_assert(alphabet[30] == 'e', "Alphabet[30] != 'e'");
	static_assert(alphabet[31] == 'f', "Alphabet[31] != 'f'");
	static_assert(alphabet[32] == 'g', "Alphabet[32] != 'g'");
	static_assert(alphabet[33] == 'h', "Alphabet[33] != 'h'");
	static_assert(alphabet[34] == 'i', "Alphabet[34] != 'i'");
	static_assert(alphabet[35] == 'j', "Alphabet[35] != 'j'");
	static_assert(alphabet[36] == 'k', "Alphabet[36] != 'k'");
	static_assert(alphabet[37] == 'l', "Alphabet[37] != 'l'");
	static_assert(alphabet[38] == 'm', "Alphabet[38] != 'm'");
	static_assert(alphabet[39] == 'n', "Alphabet[39] != 'n'");
	static_assert(alphabet[40] == 'o', "Alphabet[40] != 'o'");
	static_assert(alphabet[41] == 'p', "Alphabet[41] != 'p'");
	static_assert(alphabet[42] == 'q', "Alphabet[42] != 'q'");
	static_assert(alphabet[43] == 'r', "Alphabet[43] != 'r'");
	static_assert(alphabet[44] == 's', "Alphabet[44] != 's'");
	static_assert(alphabet[45] == 't', "Alphabet[45] != 't'");
	static_assert(alphabet[46] == 'u', "Alphabet[46] != 'u'");
	static_assert(alphabet[47] == 'v', "Alphabet[47] != 'v'");
	static_assert(alphabet[48] == 'w', "Alphabet[48] != 'w'");
	static_assert(alphabet[49] == 'x', "Alphabet[49] != 'x'");
	static_assert(alphabet[50] == 'y', "Alphabet[50] != 'y'");
	static_assert(alphabet[51] == 'z', "Alphabet[51] != 'z'");

	static_assert(alphabet[52] == '0', "Alphabet[52] != '0'");
	static_assert(alphabet[53] == '1', "Alphabet[53] != '1'");
	static_assert(alphabet[54] == '2', "Alphabet[54] != '2'");
	static_assert(alphabet[55] == '3', "Alphabet[55] != '3'");
	static_assert(alphabet[56] == '4', "Alphabet[56] != '4'");
	static_assert(alphabet[57] == '5', "Alphabet[57] != '5'");
	static_assert(alphabet[58] == '6', "Alphabet[58] != '6'");
	static_assert(alphabet[59] == '7', "Alphabet[59] != '7'");
	static_assert(alphabet[60] == '8', "Alphabet[60] != '8'");
	static_assert(alphabet[61] == '9', "Alphabet[61] != '9'");

	static_assert(alphabet[62] == '+', "Alphabet[62] != '+'");
	static_assert(alphabet[63] == '/', "Alphabet[63] != '/'");

	static_assert(_Alphabet::Padding() == '=', "padding != '='");
}


GTEST_TEST(TestCodecBase64, Base64Encode3ImplPadding)
{
	using _Alphabet = Internal::Base64Alphabet<char>;
	using _Encoder = Internal::Base64Encode3Impl<_Alphabet, true>;

	uint8_t input[3];
	std::string output;

	// examples from: https://en.wikipedia.org/wiki/Base64#Examples
	input[0] = 'M'; input[1] = 'a'; input[2] = 'n';
	output.clear();
	_Encoder::Encode3(std::back_inserter(output), input[0], input[1], input[2]);
	EXPECT_EQ("TWFu", output);

	input[0] = 'M'; input[1] = 'a';
	output.clear();
	_Encoder::Encode3(std::back_inserter(output), input[0], input[1]);
	EXPECT_EQ("TWE=", output);

	input[0] = 'M';
	output.clear();
	_Encoder::Encode3(std::back_inserter(output), input[0]);
	EXPECT_EQ("TQ==", output);


	input[0] = 0xAAU; input[1] = 0xAAU; input[2] = 0xAAU;
	output.clear();
	_Encoder::Encode3(std::back_inserter(output), input[0], input[1], input[2]);
	EXPECT_EQ("qqqq", output);

	input[0] = 0xAAU; input[1] = 0xAAU;
	output.clear();
	_Encoder::Encode3(std::back_inserter(output), input[0], input[1]);
	EXPECT_EQ("qqo=", output);

	input[0] = 0xAAU;
	output.clear();
	_Encoder::Encode3(std::back_inserter(output), input[0]);
	EXPECT_EQ("qg==", output);


	input[0] = 0x55U; input[1] = 0x55U; input[2] = 0x55U;
	output.clear();
	_Encoder::Encode3(std::back_inserter(output), input[0], input[1], input[2]);
	EXPECT_EQ("VVVV", output);

	input[0] = 0x55U; input[1] = 0x55U;
	output.clear();
	_Encoder::Encode3(std::back_inserter(output), input[0], input[1]);
	EXPECT_EQ("VVU=", output);

	input[0] = 0x55U;
	output.clear();
	_Encoder::Encode3(std::back_inserter(output), input[0]);
	EXPECT_EQ("VQ==", output);
}


GTEST_TEST(TestCodecBase64, Base64Encode3ImplNoPadding)
{
	using _Alphabet = Internal::Base64Alphabet<char>;
	using _Encoder = Internal::Base64Encode3Impl<_Alphabet, false>;

	uint8_t input[3];
	std::string output;

	// examples from: https://en.wikipedia.org/wiki/Base64#Examples
	input[0] = 'M'; input[1] = 'a'; input[2] = 'n';
	output.clear();
	_Encoder::Encode3(std::back_inserter(output), input[0], input[1], input[2]);
	EXPECT_EQ("TWFu", output);

	input[0] = 'M'; input[1] = 'a';
	output.clear();
	_Encoder::Encode3(std::back_inserter(output), input[0], input[1]);
	EXPECT_EQ("TWE", output);

	input[0] = 'M';
	output.clear();
	_Encoder::Encode3(std::back_inserter(output), input[0]);
	EXPECT_EQ("TQ", output);


	input[0] = 0xAAU; input[1] = 0xAAU; input[2] = 0xAAU;
	output.clear();
	_Encoder::Encode3(std::back_inserter(output), input[0], input[1], input[2]);
	EXPECT_EQ("qqqq", output);

	input[0] = 0xAAU; input[1] = 0xAAU;
	output.clear();
	_Encoder::Encode3(std::back_inserter(output), input[0], input[1]);
	EXPECT_EQ("qqo", output);

	input[0] = 0xAAU;
	output.clear();
	_Encoder::Encode3(std::back_inserter(output), input[0]);
	EXPECT_EQ("qg", output);


	input[0] = 0x55U; input[1] = 0x55U; input[2] = 0x55U;
	output.clear();
	_Encoder::Encode3(std::back_inserter(output), input[0], input[1], input[2]);
	EXPECT_EQ("VVVV", output);

	input[0] = 0x55U; input[1] = 0x55U;
	output.clear();
	_Encoder::Encode3(std::back_inserter(output), input[0], input[1]);
	EXPECT_EQ("VVU", output);

	input[0] = 0x55U;
	output.clear();
	_Encoder::Encode3(std::back_inserter(output), input[0]);
	EXPECT_EQ("VQ", output);
}


// ==========
// Decoding
// ==========


GTEST_TEST(TestCodecBase64, Base64Base64ValueLutThrow)
{
	using _Lut = Internal::Base64ValueLut<uint8_t, char, true>;

	for (size_t i = 0; i < '+'; ++i)
	{
		char ch = static_cast<char>(i);
		EXPECT_THROW(_Lut::GetValue(ch), std::invalid_argument);
	}

	EXPECT_EQ(_Lut::GetValue('+'), 62);
	EXPECT_THROW(_Lut::GetValue(','), std::invalid_argument);
	EXPECT_THROW(_Lut::GetValue('-'), std::invalid_argument);
	EXPECT_THROW(_Lut::GetValue('.'), std::invalid_argument);
	EXPECT_EQ(_Lut::GetValue('/'), 63);
	EXPECT_EQ(_Lut::GetValue('0'), 52);
	EXPECT_EQ(_Lut::GetValue('1'), 53);
	EXPECT_EQ(_Lut::GetValue('2'), 54);
	EXPECT_EQ(_Lut::GetValue('3'), 55);
	EXPECT_EQ(_Lut::GetValue('4'), 56);
	EXPECT_EQ(_Lut::GetValue('5'), 57);
	EXPECT_EQ(_Lut::GetValue('6'), 58);
	EXPECT_EQ(_Lut::GetValue('7'), 59);
	EXPECT_EQ(_Lut::GetValue('8'), 60);
	EXPECT_EQ(_Lut::GetValue('9'), 61);
	EXPECT_THROW(_Lut::GetValue(':'), std::invalid_argument);
	EXPECT_THROW(_Lut::GetValue(';'), std::invalid_argument);
	EXPECT_THROW(_Lut::GetValue('<'), std::invalid_argument);
	EXPECT_THROW(_Lut::GetValue('='), std::invalid_argument);
	EXPECT_THROW(_Lut::GetValue('>'), std::invalid_argument);
	EXPECT_THROW(_Lut::GetValue('?'), std::invalid_argument);

	EXPECT_THROW(_Lut::GetValue('@'), std::invalid_argument);
	EXPECT_EQ(_Lut::GetValue('A'), 0);
	EXPECT_EQ(_Lut::GetValue('B'), 1);
	EXPECT_EQ(_Lut::GetValue('C'), 2);
	EXPECT_EQ(_Lut::GetValue('D'), 3);
	EXPECT_EQ(_Lut::GetValue('E'), 4);
	EXPECT_EQ(_Lut::GetValue('F'), 5);
	EXPECT_EQ(_Lut::GetValue('G'), 6);
	EXPECT_EQ(_Lut::GetValue('H'), 7);
	EXPECT_EQ(_Lut::GetValue('I'), 8);
	EXPECT_EQ(_Lut::GetValue('J'), 9);
	EXPECT_EQ(_Lut::GetValue('K'), 10);
	EXPECT_EQ(_Lut::GetValue('L'), 11);
	EXPECT_EQ(_Lut::GetValue('M'), 12);
	EXPECT_EQ(_Lut::GetValue('N'), 13);
	EXPECT_EQ(_Lut::GetValue('O'), 14);
	EXPECT_EQ(_Lut::GetValue('P'), 15);
	EXPECT_EQ(_Lut::GetValue('Q'), 16);
	EXPECT_EQ(_Lut::GetValue('R'), 17);
	EXPECT_EQ(_Lut::GetValue('S'), 18);
	EXPECT_EQ(_Lut::GetValue('T'), 19);
	EXPECT_EQ(_Lut::GetValue('U'), 20);
	EXPECT_EQ(_Lut::GetValue('V'), 21);
	EXPECT_EQ(_Lut::GetValue('W'), 22);
	EXPECT_EQ(_Lut::GetValue('X'), 23);
	EXPECT_EQ(_Lut::GetValue('Y'), 24);
	EXPECT_EQ(_Lut::GetValue('Z'), 25);

	EXPECT_THROW(_Lut::GetValue('['), std::invalid_argument);
	EXPECT_THROW(_Lut::GetValue('\\'), std::invalid_argument);
	EXPECT_THROW(_Lut::GetValue(']'), std::invalid_argument);
	EXPECT_THROW(_Lut::GetValue('^'), std::invalid_argument);
	EXPECT_THROW(_Lut::GetValue('_'), std::invalid_argument);

	EXPECT_THROW(_Lut::GetValue('`'), std::invalid_argument);
	EXPECT_EQ(_Lut::GetValue('a'), 26);
	EXPECT_EQ(_Lut::GetValue('b'), 27);
	EXPECT_EQ(_Lut::GetValue('c'), 28);
	EXPECT_EQ(_Lut::GetValue('d'), 29);
	EXPECT_EQ(_Lut::GetValue('e'), 30);
	EXPECT_EQ(_Lut::GetValue('f'), 31);
	EXPECT_EQ(_Lut::GetValue('g'), 32);
	EXPECT_EQ(_Lut::GetValue('h'), 33);
	EXPECT_EQ(_Lut::GetValue('i'), 34);
	EXPECT_EQ(_Lut::GetValue('j'), 35);
	EXPECT_EQ(_Lut::GetValue('k'), 36);
	EXPECT_EQ(_Lut::GetValue('l'), 37);
	EXPECT_EQ(_Lut::GetValue('m'), 38);
	EXPECT_EQ(_Lut::GetValue('n'), 39);
	EXPECT_EQ(_Lut::GetValue('o'), 40);
	EXPECT_EQ(_Lut::GetValue('p'), 41);
	EXPECT_EQ(_Lut::GetValue('q'), 42);
	EXPECT_EQ(_Lut::GetValue('r'), 43);
	EXPECT_EQ(_Lut::GetValue('s'), 44);
	EXPECT_EQ(_Lut::GetValue('t'), 45);
	EXPECT_EQ(_Lut::GetValue('u'), 46);
	EXPECT_EQ(_Lut::GetValue('v'), 47);
	EXPECT_EQ(_Lut::GetValue('w'), 48);
	EXPECT_EQ(_Lut::GetValue('x'), 49);
	EXPECT_EQ(_Lut::GetValue('y'), 50);
	EXPECT_EQ(_Lut::GetValue('z'), 51);

	for (
		size_t i = static_cast<size_t>('z' + 1);
		i < static_cast<size_t>(std::numeric_limits<char>::max() + 1);
		++i
	)
	{
		char ch = static_cast<char>(i);
		EXPECT_THROW(_Lut::GetValue(ch), std::invalid_argument);
	}
}


GTEST_TEST(TestCodecBase64, Base64Base64ValueLutNonThrow)
{
	using _Lut = Internal::Base64ValueLut<uint8_t, char, false>;

	static constexpr auto sk_iVal = _Lut::sk_iVal;

	for (size_t i = 0; i < '+'; ++i)
	{
		char ch = static_cast<char>(i);
		ASSERT_EQ(_Lut::GetValue(ch), sk_iVal);
	}

	EXPECT_EQ(_Lut::GetValue('+'), 62);
	EXPECT_EQ(_Lut::GetValue(','), sk_iVal);
	EXPECT_EQ(_Lut::GetValue('-'), sk_iVal);
	EXPECT_EQ(_Lut::GetValue('.'), sk_iVal);
	EXPECT_EQ(_Lut::GetValue('/'), 63);
	EXPECT_EQ(_Lut::GetValue('0'), 52);
	EXPECT_EQ(_Lut::GetValue('1'), 53);
	EXPECT_EQ(_Lut::GetValue('2'), 54);
	EXPECT_EQ(_Lut::GetValue('3'), 55);
	EXPECT_EQ(_Lut::GetValue('4'), 56);
	EXPECT_EQ(_Lut::GetValue('5'), 57);
	EXPECT_EQ(_Lut::GetValue('6'), 58);
	EXPECT_EQ(_Lut::GetValue('7'), 59);
	EXPECT_EQ(_Lut::GetValue('8'), 60);
	EXPECT_EQ(_Lut::GetValue('9'), 61);
	EXPECT_EQ(_Lut::GetValue(':'), sk_iVal);
	EXPECT_EQ(_Lut::GetValue(';'), sk_iVal);
	EXPECT_EQ(_Lut::GetValue('<'), sk_iVal);
	EXPECT_EQ(_Lut::GetValue('='), sk_iVal);
	EXPECT_EQ(_Lut::GetValue('>'), sk_iVal);
	EXPECT_EQ(_Lut::GetValue('?'), sk_iVal);

	EXPECT_EQ(_Lut::GetValue('@'), sk_iVal);
	EXPECT_EQ(_Lut::GetValue('A'), 0);
	EXPECT_EQ(_Lut::GetValue('B'), 1);
	EXPECT_EQ(_Lut::GetValue('C'), 2);
	EXPECT_EQ(_Lut::GetValue('D'), 3);
	EXPECT_EQ(_Lut::GetValue('E'), 4);
	EXPECT_EQ(_Lut::GetValue('F'), 5);
	EXPECT_EQ(_Lut::GetValue('G'), 6);
	EXPECT_EQ(_Lut::GetValue('H'), 7);
	EXPECT_EQ(_Lut::GetValue('I'), 8);
	EXPECT_EQ(_Lut::GetValue('J'), 9);
	EXPECT_EQ(_Lut::GetValue('K'), 10);
	EXPECT_EQ(_Lut::GetValue('L'), 11);
	EXPECT_EQ(_Lut::GetValue('M'), 12);
	EXPECT_EQ(_Lut::GetValue('N'), 13);
	EXPECT_EQ(_Lut::GetValue('O'), 14);
	EXPECT_EQ(_Lut::GetValue('P'), 15);
	EXPECT_EQ(_Lut::GetValue('Q'), 16);
	EXPECT_EQ(_Lut::GetValue('R'), 17);
	EXPECT_EQ(_Lut::GetValue('S'), 18);
	EXPECT_EQ(_Lut::GetValue('T'), 19);
	EXPECT_EQ(_Lut::GetValue('U'), 20);
	EXPECT_EQ(_Lut::GetValue('V'), 21);
	EXPECT_EQ(_Lut::GetValue('W'), 22);
	EXPECT_EQ(_Lut::GetValue('X'), 23);
	EXPECT_EQ(_Lut::GetValue('Y'), 24);
	EXPECT_EQ(_Lut::GetValue('Z'), 25);

	EXPECT_EQ(_Lut::GetValue('['), sk_iVal);
	EXPECT_EQ(_Lut::GetValue('\\'), sk_iVal);
	EXPECT_EQ(_Lut::GetValue(']'), sk_iVal);
	EXPECT_EQ(_Lut::GetValue('^'), sk_iVal);
	EXPECT_EQ(_Lut::GetValue('_'), sk_iVal);

	EXPECT_EQ(_Lut::GetValue('`'), sk_iVal);
	EXPECT_EQ(_Lut::GetValue('a'), 26);
	EXPECT_EQ(_Lut::GetValue('b'), 27);
	EXPECT_EQ(_Lut::GetValue('c'), 28);
	EXPECT_EQ(_Lut::GetValue('d'), 29);
	EXPECT_EQ(_Lut::GetValue('e'), 30);
	EXPECT_EQ(_Lut::GetValue('f'), 31);
	EXPECT_EQ(_Lut::GetValue('g'), 32);
	EXPECT_EQ(_Lut::GetValue('h'), 33);
	EXPECT_EQ(_Lut::GetValue('i'), 34);
	EXPECT_EQ(_Lut::GetValue('j'), 35);
	EXPECT_EQ(_Lut::GetValue('k'), 36);
	EXPECT_EQ(_Lut::GetValue('l'), 37);
	EXPECT_EQ(_Lut::GetValue('m'), 38);
	EXPECT_EQ(_Lut::GetValue('n'), 39);
	EXPECT_EQ(_Lut::GetValue('o'), 40);
	EXPECT_EQ(_Lut::GetValue('p'), 41);
	EXPECT_EQ(_Lut::GetValue('q'), 42);
	EXPECT_EQ(_Lut::GetValue('r'), 43);
	EXPECT_EQ(_Lut::GetValue('s'), 44);
	EXPECT_EQ(_Lut::GetValue('t'), 45);
	EXPECT_EQ(_Lut::GetValue('u'), 46);
	EXPECT_EQ(_Lut::GetValue('v'), 47);
	EXPECT_EQ(_Lut::GetValue('w'), 48);
	EXPECT_EQ(_Lut::GetValue('x'), 49);
	EXPECT_EQ(_Lut::GetValue('y'), 50);
	EXPECT_EQ(_Lut::GetValue('z'), 51);

	for (
		size_t i = static_cast<size_t>('z' + 1);
		i < static_cast<size_t>(std::numeric_limits<char>::max() + 1);
		++i
	)
	{
		char ch = static_cast<char>(i);
		ASSERT_EQ(_Lut::GetValue(ch), sk_iVal);
	}
}


GTEST_TEST(TestCodecBase64, Base64AssembleImplCheck)
{
	using _Lut = Internal::Base64ValueLut<uint8_t, char, true>;
	using _Decoder = Internal::Base64AssembleImpl<uint8_t, true>;

	std::vector<uint8_t> output;
	auto it = output.begin();

	output.resize(100);

	// ===== 2 chars =====

	it = _Decoder::Assemble(
		output.begin(),
		_Lut::GetValue('T'), // 0x13
		_Lut::GetValue('Q')  // 0x10
	);
	EXPECT_EQ(it, output.begin() + 1);
	EXPECT_EQ(output[0], 0x4dU);

	it = _Decoder::Assemble(
		output.begin(),
		_Lut::GetValue('a'), // 0x1a
		_Lut::GetValue('w')  // 0x30
	);
	EXPECT_EQ(it, output.begin() + 1);
	EXPECT_EQ(output[0], 0x6bU);

	it = _Decoder::Assemble(
		output.begin(),
		_Lut::GetValue('d'), // 0x1d
		_Lut::GetValue('w')  // 0x30
	);
	EXPECT_EQ(it, output.begin() + 1);
	EXPECT_EQ(output[0], 0x77U);

	EXPECT_THROW(
		_Decoder::Assemble(
			output.begin(),
			0x13U,
			0x11U
		),
		std::invalid_argument
	);

	EXPECT_THROW(
		_Decoder::Assemble(
			output.begin(),
			0x1aU,
			0x38U
		),
		std::invalid_argument
	);

	// ===== 3 chars =====

	it = _Decoder::Assemble(
		output.begin(),
		_Lut::GetValue('T'), // 0x13
		_Lut::GetValue('W'), // 0x16
		_Lut::GetValue('E')  // 0x04
	);
	EXPECT_EQ(it, output.begin() + 2);
	EXPECT_EQ(output[0], 0x4dU);
	EXPECT_EQ(output[1], 0x61U);

	it = _Decoder::Assemble(
		output.begin(),
		_Lut::GetValue('a'), // 0x1a
		_Lut::GetValue('y'), // 0x32
		_Lut::GetValue('4')  // 0x38
	);
	EXPECT_EQ(it, output.begin() + 2);
	EXPECT_EQ(output[0], 0x6bU);
	EXPECT_EQ(output[1], 0x2eU);

	it = _Decoder::Assemble(
		output.begin(),
		_Lut::GetValue('d'), // 0x1d
		_Lut::GetValue('2'), // 0x36
		_Lut::GetValue('8')  // 0x3c
	);
	EXPECT_EQ(it, output.begin() + 2);
	EXPECT_EQ(output[0], 0x77U);
	EXPECT_EQ(output[1], 0x6fU);

	EXPECT_THROW(
		_Decoder::Assemble(
			output.begin(),
			0x13U,
			0x16U,
			0x06U
		),
		std::invalid_argument
	);

	EXPECT_THROW(
		_Decoder::Assemble(
			output.begin(),
			0x1aU,
			0x32U,
			0x39U
		),
		std::invalid_argument
	);

	EXPECT_THROW(
		_Decoder::Assemble(
			output.begin(),
			0x1dU,
			0x36U,
			0x3dU
		),
		std::invalid_argument
	);

	// ===== 4 chars =====

	it = _Decoder::Assemble(
		output.begin(),
		_Lut::GetValue('T'), // 0x13
		_Lut::GetValue('W'), // 0x16
		_Lut::GetValue('F'), // 0x05
		_Lut::GetValue('u')  // 0x2e
	);
	EXPECT_EQ(it, output.begin() + 3);
	EXPECT_EQ(output[0], 0x4dU);
	EXPECT_EQ(output[1], 0x61U);
	EXPECT_EQ(output[2], 0x6eU);

	it = _Decoder::Assemble(
		output.begin(),
		_Lut::GetValue('d'), // 0x1d
		_Lut::GetValue('2'), // 0x36
		_Lut::GetValue('9'), // 0x3d
		_Lut::GetValue('y')  // 0x32
	);
	EXPECT_EQ(it, output.begin() + 3);
	EXPECT_EQ(output[0], 0x77U);
	EXPECT_EQ(output[1], 0x6fU);
	EXPECT_EQ(output[2], 0x72U);

	it = _Decoder::Assemble(
		output.begin(),
		_Lut::GetValue('q'), // 0x2a
		_Lut::GetValue('q'), // 0x2a
		_Lut::GetValue('q'), // 0x2a
		_Lut::GetValue('q')  // 0x2a
	);
	EXPECT_EQ(it, output.begin() + 3);
	EXPECT_EQ(output[0], 0xAAU);
	EXPECT_EQ(output[1], 0xAAU);
	EXPECT_EQ(output[2], 0xAAU);

	it = _Decoder::Assemble(
		output.begin(),
		_Lut::GetValue('V'), // 0x15
		_Lut::GetValue('V'), // 0x15
		_Lut::GetValue('V'), // 0x15
		_Lut::GetValue('V')  // 0x15
	);
	EXPECT_EQ(it, output.begin() + 3);
	EXPECT_EQ(output[0], 0x55U);
	EXPECT_EQ(output[1], 0x55U);
	EXPECT_EQ(output[2], 0x55U);
}


GTEST_TEST(TestCodecBase64, Base64AssembleImplNoCheck)
{
	using _Lut = Internal::Base64ValueLut<uint8_t, char, true>;
	using _Decoder = Internal::Base64AssembleImpl<uint8_t, false>;

	std::vector<uint8_t> output;
	auto it = output.begin();

	output.resize(100);

	// ===== 2 chars =====

	it = _Decoder::Assemble(
		output.begin(),
		_Lut::GetValue('T'), // 0x13
		_Lut::GetValue('Q')  // 0x10
	);
	EXPECT_EQ(it, output.begin() + 1);
	EXPECT_EQ(output[0], 0x4dU);

	it = _Decoder::Assemble(
		output.begin(),
		_Lut::GetValue('a'), // 0x1a
		_Lut::GetValue('w')  // 0x30
	);
	EXPECT_EQ(it, output.begin() + 1);
	EXPECT_EQ(output[0], 0x6bU);

	it = _Decoder::Assemble(
		output.begin(),
		_Lut::GetValue('d'), // 0x1d
		_Lut::GetValue('w')  // 0x30
	);
	EXPECT_EQ(it, output.begin() + 1);
	EXPECT_EQ(output[0], 0x77U);

	it = _Decoder::Assemble(
		output.begin(),
		0x13U,
		0x11U
	);
	EXPECT_EQ(it, output.begin() + 1);
	EXPECT_EQ(output[0], 0x4dU);

	it = _Decoder::Assemble(
		output.begin(),
		0x1aU,
		0x38U
	);
	EXPECT_EQ(it, output.begin() + 1);
	EXPECT_EQ(output[0], 0x6bU);

	// ===== 3 chars =====

	it = _Decoder::Assemble(
		output.begin(),
		_Lut::GetValue('T'), // 0x13
		_Lut::GetValue('W'), // 0x16
		_Lut::GetValue('E')  // 0x04
	);
	EXPECT_EQ(it, output.begin() + 2);
	EXPECT_EQ(output[0], 0x4dU);
	EXPECT_EQ(output[1], 0x61U);

	it = _Decoder::Assemble(
		output.begin(),
		_Lut::GetValue('a'), // 0x1a
		_Lut::GetValue('y'), // 0x32
		_Lut::GetValue('4')  // 0x38
	);
	EXPECT_EQ(it, output.begin() + 2);
	EXPECT_EQ(output[0], 0x6bU);
	EXPECT_EQ(output[1], 0x2eU);

	it = _Decoder::Assemble(
		output.begin(),
		_Lut::GetValue('d'), // 0x1d
		_Lut::GetValue('2'), // 0x36
		_Lut::GetValue('8')  // 0x3c
	);
	EXPECT_EQ(it, output.begin() + 2);
	EXPECT_EQ(output[0], 0x77U);
	EXPECT_EQ(output[1], 0x6fU);

	it = _Decoder::Assemble(
		output.begin(),
		0x13U,
		0x16U,
		0x06U
	);
	EXPECT_EQ(it, output.begin() + 2);
	EXPECT_EQ(output[0], 0x4dU);
	EXPECT_EQ(output[1], 0x61U);

	it = _Decoder::Assemble(
		output.begin(),
		0x1aU,
		0x32U,
		0x39U
	);
	EXPECT_EQ(it, output.begin() + 2);
	EXPECT_EQ(output[0], 0x6bU);
	EXPECT_EQ(output[1], 0x2eU);

	it = _Decoder::Assemble(
		output.begin(),
		0x1dU,
		0x36U,
		0x3dU
	);
	EXPECT_EQ(it, output.begin() + 2);
	EXPECT_EQ(output[0], 0x77U);
	EXPECT_EQ(output[1], 0x6fU);

	// ===== 4 chars =====

	it = _Decoder::Assemble(
		output.begin(),
		_Lut::GetValue('T'), // 0x13
		_Lut::GetValue('W'), // 0x16
		_Lut::GetValue('F'), // 0x05
		_Lut::GetValue('u')  // 0x2e
	);
	EXPECT_EQ(it, output.begin() + 3);
	EXPECT_EQ(output[0], 0x4dU);
	EXPECT_EQ(output[1], 0x61U);
	EXPECT_EQ(output[2], 0x6eU);

	it = _Decoder::Assemble(
		output.begin(),
		_Lut::GetValue('d'), // 0x1d
		_Lut::GetValue('2'), // 0x36
		_Lut::GetValue('9'), // 0x3d
		_Lut::GetValue('y')  // 0x32
	);
	EXPECT_EQ(it, output.begin() + 3);
	EXPECT_EQ(output[0], 0x77U);
	EXPECT_EQ(output[1], 0x6fU);
	EXPECT_EQ(output[2], 0x72U);

	it = _Decoder::Assemble(
		output.begin(),
		_Lut::GetValue('q'), // 0x2a
		_Lut::GetValue('q'), // 0x2a
		_Lut::GetValue('q'), // 0x2a
		_Lut::GetValue('q')  // 0x2a
	);
	EXPECT_EQ(it, output.begin() + 3);
	EXPECT_EQ(output[0], 0xAAU);
	EXPECT_EQ(output[1], 0xAAU);
	EXPECT_EQ(output[2], 0xAAU);

	it = _Decoder::Assemble(
		output.begin(),
		_Lut::GetValue('V'), // 0x15
		_Lut::GetValue('V'), // 0x15
		_Lut::GetValue('V'), // 0x15
		_Lut::GetValue('V')  // 0x15
	);
	EXPECT_EQ(it, output.begin() + 3);
	EXPECT_EQ(output[0], 0x55U);
	EXPECT_EQ(output[1], 0x55U);
	EXPECT_EQ(output[2], 0x55U);
}


GTEST_TEST(TestCodecBase64, Base64ValueGetterThrow)
{
	using _Decoder = Internal::Base64ValueGetter<uint8_t, char, true>;

	Internal::Base64DecodeChType chType;
	uint8_t val;
	std::string str;
	auto it = str.begin();

	str = "VV";
	it = str.begin();

	std::tie(chType, val, it) = _Decoder::GetNextValue(it, str.end());
	EXPECT_EQ(chType, Internal::Base64DecodeChType::Valid);
	EXPECT_EQ(val, 21);
	EXPECT_EQ(it, str.begin() + 1);

	std::tie(chType, val, it) = _Decoder::GetNextValue(it, str.end());
	EXPECT_EQ(chType, Internal::Base64DecodeChType::Valid);
	EXPECT_EQ(val, 21);
	EXPECT_EQ(it, str.end());

	std::tie(chType, val, it) = _Decoder::GetNextValue(it, str.end());
	EXPECT_EQ(chType, Internal::Base64DecodeChType::End);
	EXPECT_EQ(it, str.end());

	str = "V=#";
	it = str.begin();

	std::tie(chType, val, it) = _Decoder::GetNextValue(it, str.end());
	EXPECT_EQ(chType, Internal::Base64DecodeChType::Valid);
	EXPECT_EQ(val, 21);
	EXPECT_EQ(it, str.begin() + 1);

	std::tie(chType, val, it) = _Decoder::GetNextValue(it, str.end());
	EXPECT_EQ(chType, Internal::Base64DecodeChType::Pad);
	EXPECT_EQ(it, str.begin() + 2);

	EXPECT_THROW(
		_Decoder::GetNextValue(it, str.end()),
		std::invalid_argument
	);
}


GTEST_TEST(TestCodecBase64, Base64ValueGetterNoThrow)
{
	using _Decoder = Internal::Base64ValueGetter<uint8_t, char, false>;

	Internal::Base64DecodeChType chType;
	uint8_t val;
	std::string str;
	auto it = str.begin();

	str = "VV";
	it = str.begin();

	std::tie(chType, val, it) = _Decoder::GetNextValue(it, str.end());
	EXPECT_EQ(chType, Internal::Base64DecodeChType::Valid);
	EXPECT_EQ(val, 21);
	EXPECT_EQ(it, str.begin() + 1);

	std::tie(chType, val, it) = _Decoder::GetNextValue(it, str.end());
	EXPECT_EQ(chType, Internal::Base64DecodeChType::Valid);
	EXPECT_EQ(val, 21);
	EXPECT_EQ(it, str.end());

	std::tie(chType, val, it) = _Decoder::GetNextValue(it, str.end());
	EXPECT_EQ(chType, Internal::Base64DecodeChType::End);
	EXPECT_EQ(it, str.end());

	str = "V=#";
	it = str.begin();

	std::tie(chType, val, it) = _Decoder::GetNextValue(it, str.end());
	EXPECT_EQ(chType, Internal::Base64DecodeChType::Valid);
	EXPECT_EQ(val, 21);
	EXPECT_EQ(it, str.begin() + 1);

	std::tie(chType, val, it) = _Decoder::GetNextValue(it, str.end());
	EXPECT_EQ(chType, Internal::Base64DecodeChType::Pad);
	EXPECT_EQ(it, str.begin() + 2);

	std::tie(chType, val, it) = _Decoder::GetNextValue(it, str.end());
	EXPECT_EQ(chType, Internal::Base64DecodeChType::End);
	EXPECT_EQ(it, str.end());

	str = "V#V";
	it = str.begin();

	std::tie(chType, val, it) = _Decoder::GetNextValue(it, str.end());
	EXPECT_EQ(chType, Internal::Base64DecodeChType::Valid);
	EXPECT_EQ(val, 21);
	EXPECT_EQ(it, str.begin() + 1);

	std::tie(chType, val, it) = _Decoder::GetNextValue(it, str.end());
	EXPECT_EQ(chType, Internal::Base64DecodeChType::Valid);
	EXPECT_EQ(val, 21);
	EXPECT_EQ(it, str.end());

	std::tie(chType, val, it) = _Decoder::GetNextValue(it, str.end());
	EXPECT_EQ(chType, Internal::Base64DecodeChType::End);
	EXPECT_EQ(it, str.end());
}



//==============================================================================
//
// Impl
//
//==============================================================================


// ==========
// Encoding
// ==========


GTEST_TEST(TestCodecBase64, Base64EncodeImplPadding)
{
	using _Alphabet = Internal::Base64Alphabet<char>;
	using _Encoder = Internal::Base64EncodeImpl<_Alphabet, true>;

	std::vector<uint8_t> input;
	std::string output;
	output.resize(100);
	auto it = output.begin();

	it = output.begin();
	input = {
		0xAAU, 0xAAU, 0xAAU, 0xAAU, 0xAAU, 0xAAU, 0xAAU, 0xAAU, 0xAAU,
	};
	it = _Encoder::Encode(it, input.begin(), input.end());
	EXPECT_EQ(it, output.begin() + 12);
	EXPECT_EQ(output.substr(0, 12), "qqqqqqqqqqqq");

	it = output.begin();
	input = {
		0xAAU, 0xAAU, 0xAAU, 0xAAU, 0xAAU, 0xAAU, 0xAAU, 0xAAU, 0xAAU,
		0xAAU,
	};
	it = _Encoder::Encode(it, input.begin(), input.end());
	EXPECT_EQ(it, output.begin() + 16);
	EXPECT_EQ(output.substr(0, 16), "qqqqqqqqqqqqqg==");

	it = output.begin();
	input = {
		0xAAU, 0xAAU, 0xAAU, 0xAAU, 0xAAU, 0xAAU, 0xAAU, 0xAAU, 0xAAU,
		0xAAU, 0xAAU,
	};
	it = _Encoder::Encode(it, input.begin(), input.end());
	EXPECT_EQ(it, output.begin() + 16);
	EXPECT_EQ(output.substr(0, 16), "qqqqqqqqqqqqqqo=");

	it = output.begin();
	input = {
		0xAAU, 0xAAU, 0xAAU, 0xAAU, 0xAAU, 0xAAU, 0xAAU, 0xAAU, 0xAAU,
		0xAAU, 0xAAU, 0xAAU,
	};
	it = _Encoder::Encode(it, input.begin(), input.end());
	EXPECT_EQ(it, output.begin() + 16);
	EXPECT_EQ(output.substr(0, 16), "qqqqqqqqqqqqqqqq");

	it = output.begin();
	input = {
		0x55U, 0x55U, 0x55U, 0x55U, 0x55U, 0x55U, 0x55U, 0x55U, 0x55U,
	};
	it = _Encoder::Encode(it, input.begin(), input.end());
	EXPECT_EQ(it, output.begin() + 12);
	EXPECT_EQ(output.substr(0, 12), "VVVVVVVVVVVV");

	it = output.begin();
	input = {
		0x55U, 0x55U, 0x55U, 0x55U, 0x55U, 0x55U, 0x55U, 0x55U, 0x55U,
		0x55U,
	};
	it = _Encoder::Encode(it, input.begin(), input.end());
	EXPECT_EQ(it, output.begin() + 16);
	EXPECT_EQ(output.substr(0, 16), "VVVVVVVVVVVVVQ==");

	it = output.begin();
	input = {
		0x55U, 0x55U, 0x55U, 0x55U, 0x55U, 0x55U, 0x55U, 0x55U, 0x55U,
		0x55U, 0x55U,
	};
	it = _Encoder::Encode(it, input.begin(), input.end());
	EXPECT_EQ(it, output.begin() + 16);
	EXPECT_EQ(output.substr(0, 16), "VVVVVVVVVVVVVVU=");

	it = output.begin();
	input = {
		0x55U, 0x55U, 0x55U, 0x55U, 0x55U, 0x55U, 0x55U, 0x55U, 0x55U,
		0x55U, 0x55U, 0x55U,
	};
	it = _Encoder::Encode(it, input.begin(), input.end());
	EXPECT_EQ(it, output.begin() + 16);
	EXPECT_EQ(output.substr(0, 16), "VVVVVVVVVVVVVVVV");

	it = output.begin();
	input = {
		'l', 'i', 'g', 'h', 't', ' ', 'w', 'o', 'r', 'k', '.',
	};
	it = _Encoder::Encode(it, input.begin(), input.end());
	EXPECT_EQ(it, output.begin() + 16);
	EXPECT_EQ(output.substr(0, 16), "bGlnaHQgd29yay4=");

	it = output.begin();
	input = {
		'l', 'i', 'g', 'h', 't', ' ', 'w', 'o', 'r', 'k',
	};
	it = _Encoder::Encode(it, input.begin(), input.end());
	EXPECT_EQ(it, output.begin() + 16);
	EXPECT_EQ(output.substr(0, 16), "bGlnaHQgd29yaw==");

	it = output.begin();
	input = {
		'l', 'i', 'g', 'h', 't', ' ', 'w', 'o', 'r',
	};
	it = _Encoder::Encode(it, input.begin(), input.end());
	EXPECT_EQ(it, output.begin() + 12);
	EXPECT_EQ(output.substr(0, 12), "bGlnaHQgd29y");
}


GTEST_TEST(TestCodecBase64, Base64EncodeImplNoPadding)
{
	using _Alphabet = Internal::Base64Alphabet<char>;
	using _Encoder = Internal::Base64EncodeImpl<_Alphabet, false>;

	std::vector<uint8_t> input;
	std::string output;
	output.resize(100);
	auto it = output.begin();

	it = output.begin();
	input = {
		0xAAU, 0xAAU, 0xAAU, 0xAAU, 0xAAU, 0xAAU, 0xAAU, 0xAAU, 0xAAU,
	};
	it = _Encoder::Encode(it, input.begin(), input.end());
	EXPECT_EQ(it, output.begin() + 12);
	EXPECT_EQ(output.substr(0, 12), "qqqqqqqqqqqq");

	it = output.begin();
	input = {
		0xAAU, 0xAAU, 0xAAU, 0xAAU, 0xAAU, 0xAAU, 0xAAU, 0xAAU, 0xAAU,
		0xAAU,
	};
	it = _Encoder::Encode(it, input.begin(), input.end());
	EXPECT_EQ(it, output.begin() + 14);
	EXPECT_EQ(output.substr(0, 14), "qqqqqqqqqqqqqg");

	it = output.begin();
	input = {
		0xAAU, 0xAAU, 0xAAU, 0xAAU, 0xAAU, 0xAAU, 0xAAU, 0xAAU, 0xAAU,
		0xAAU, 0xAAU,
	};
	it = _Encoder::Encode(it, input.begin(), input.end());
	EXPECT_EQ(it, output.begin() + 15);
	EXPECT_EQ(output.substr(0, 15), "qqqqqqqqqqqqqqo");

	it = output.begin();
	input = {
		0xAAU, 0xAAU, 0xAAU, 0xAAU, 0xAAU, 0xAAU, 0xAAU, 0xAAU, 0xAAU,
		0xAAU, 0xAAU, 0xAAU,
	};
	it = _Encoder::Encode(it, input.begin(), input.end());
	EXPECT_EQ(it, output.begin() + 16);
	EXPECT_EQ(output.substr(0, 16), "qqqqqqqqqqqqqqqq");

	it = output.begin();
	input = {
		0x55U, 0x55U, 0x55U, 0x55U, 0x55U, 0x55U, 0x55U, 0x55U, 0x55U,
	};
	it = _Encoder::Encode(it, input.begin(), input.end());
	EXPECT_EQ(it, output.begin() + 12);
	EXPECT_EQ(output.substr(0, 12), "VVVVVVVVVVVV");

	it = output.begin();
	input = {
		0x55U, 0x55U, 0x55U, 0x55U, 0x55U, 0x55U, 0x55U, 0x55U, 0x55U,
		0x55U,
	};
	it = _Encoder::Encode(it, input.begin(), input.end());
	EXPECT_EQ(it, output.begin() + 14);
	EXPECT_EQ(output.substr(0, 14), "VVVVVVVVVVVVVQ");

	it = output.begin();
	input = {
		0x55U, 0x55U, 0x55U, 0x55U, 0x55U, 0x55U, 0x55U, 0x55U, 0x55U,
		0x55U, 0x55U,
	};
	it = _Encoder::Encode(it, input.begin(), input.end());
	EXPECT_EQ(it, output.begin() + 15);
	EXPECT_EQ(output.substr(0, 15), "VVVVVVVVVVVVVVU");

	it = output.begin();
	input = {
		0x55U, 0x55U, 0x55U, 0x55U, 0x55U, 0x55U, 0x55U, 0x55U, 0x55U,
		0x55U, 0x55U, 0x55U,
	};
	it = _Encoder::Encode(it, input.begin(), input.end());
	EXPECT_EQ(it, output.begin() + 16);
	EXPECT_EQ(output.substr(0, 16), "VVVVVVVVVVVVVVVV");

	it = output.begin();
	input = {
		'l', 'i', 'g', 'h', 't', ' ', 'w', 'o', 'r', 'k', '.',
	};
	it = _Encoder::Encode(it, input.begin(), input.end());
	EXPECT_EQ(it, output.begin() + 15);
	EXPECT_EQ(output.substr(0, 15), "bGlnaHQgd29yay4");

	it = output.begin();
	input = {
		'l', 'i', 'g', 'h', 't', ' ', 'w', 'o', 'r', 'k',
	};
	it = _Encoder::Encode(it, input.begin(), input.end());
	EXPECT_EQ(it, output.begin() + 14);
	EXPECT_EQ(output.substr(0, 14), "bGlnaHQgd29yaw");

	it = output.begin();
	input = {
		'l', 'i', 'g', 'h', 't', ' ', 'w', 'o', 'r',
	};
	it = _Encoder::Encode(it, input.begin(), input.end());
	EXPECT_EQ(it, output.begin() + 12);
	EXPECT_EQ(output.substr(0, 12), "bGlnaHQgd29y");
}


// ==========
// Decoding
// ==========


GTEST_TEST(TestCodecBase64, Base64DecodeImplRestricted)
{
	using _LutType = Internal::Base64ValueGetter<uint8_t, char, true>;
	using _Decoder = Internal::Base64DecodeImpl<
		_LutType,
		true,
		true
	>;

	std::string input;
	std::vector<uint8_t> output;
	output.resize(100);
	auto it = output.begin();

	it = output.begin();
	input = "VVVV";
	it = _Decoder::Decode(it, input.begin(), input.end());
	EXPECT_EQ(it, output.begin() + 3);
	EXPECT_EQ(
		std::vector<uint8_t>(output.begin(), it),
		std::vector<uint8_t>({ 0x55U, 0x55U, 0x55U })
	);

	it = output.begin();
	input = "bGlnaHQgd29y";
	it = _Decoder::Decode(it, input.begin(), input.end());
	EXPECT_EQ(it, output.begin() + 9);
	EXPECT_EQ(
		std::vector<uint8_t>(output.begin(), it),
		std::vector<uint8_t>(
			{ 'l', 'i', 'g', 'h', 't', ' ', 'w', 'o', 'r', }
		)
	);

	it = output.begin();
	input = "bGlnaHQgd29yaw==";
	it = _Decoder::Decode(it, input.begin(), input.end());
	EXPECT_EQ(it, output.begin() + 10);
	EXPECT_EQ(
		std::vector<uint8_t>(output.begin(), it),
		std::vector<uint8_t>(
			{ 'l', 'i', 'g', 'h', 't', ' ', 'w', 'o', 'r', 'k', }
		)
	);

	it = output.begin();
	input = "bGlnaHQgd29yay4=";
	it = _Decoder::Decode(it, input.begin(), input.end());
	EXPECT_EQ(it, output.begin() + 11);
	EXPECT_EQ(
		std::vector<uint8_t>(output.begin(), it),
		std::vector<uint8_t>(
			{ 'l', 'i', 'g', 'h', 't', ' ', 'w', 'o', 'r', 'k', '.', }
		)
	);


	// ===== malformed input =====


	// first char of quad is padding
	it = output.begin();
	input = "bGlnaHQgd29y====";
	EXPECT_THROW(
		_Decoder::Decode(it, input.begin(), input.end());,
		std::invalid_argument
	);

	// second char of quad is padding
	it = output.begin();
	input = "bGlnaHQgd29ya===";
	EXPECT_THROW(
		_Decoder::Decode(it, input.begin(), input.end());,
		std::invalid_argument
	);

	// end on second char of quad
	it = output.begin();
	input = "bGlnaHQgd29ya";
	EXPECT_THROW(
		_Decoder::Decode(it, input.begin(), input.end());,
		std::invalid_argument
	);

	// missing a padding char
	it = output.begin();
	input = "bGlnaHQgd29yaw=";
	EXPECT_THROW(
		_Decoder::Decode(it, input.begin(), input.end());,
		std::invalid_argument
	);

	// missing 2 padding chars
	it = output.begin();
	input = "bGlnaHQgd29yaw";
	EXPECT_THROW(
		_Decoder::Decode(it, input.begin(), input.end());,
		std::invalid_argument
	);

	// missing 1 padding chars
	it = output.begin();
	input = "bGlnaHQgd29yay4";
	EXPECT_THROW(
		_Decoder::Decode(it, input.begin(), input.end());,
		std::invalid_argument
	);
}


GTEST_TEST(TestCodecBase64, Base64DecodeImplUnrestricted)
{
	using _LutType = Internal::Base64ValueGetter<uint8_t, char, false>;
	using _Decoder = Internal::Base64DecodeImpl<
		_LutType,
		false,
		false
	>;


	// ===== regular input =====


	std::string input;
	std::vector<uint8_t> output;
	output.resize(100);
	auto it = output.begin();

	it = output.begin();
	input = "VVVV";
	it = _Decoder::Decode(it, input.begin(), input.end());
	EXPECT_EQ(it, output.begin() + 3);
	EXPECT_EQ(
		std::vector<uint8_t>(output.begin(), it),
		std::vector<uint8_t>({ 0x55U, 0x55U, 0x55U })
	);

	it = output.begin();
	input = "bGlnaHQgd29y";
	it = _Decoder::Decode(it, input.begin(), input.end());
	EXPECT_EQ(it, output.begin() + 9);
	EXPECT_EQ(
		std::vector<uint8_t>(output.begin(), it),
		std::vector<uint8_t>(
			{ 'l', 'i', 'g', 'h', 't', ' ', 'w', 'o', 'r', }
		)
	);

	it = output.begin();
	input = "bGlnaHQgd29yaw==";
	it = _Decoder::Decode(it, input.begin(), input.end());
	EXPECT_EQ(it, output.begin() + 10);
	EXPECT_EQ(
		std::vector<uint8_t>(output.begin(), it),
		std::vector<uint8_t>(
			{ 'l', 'i', 'g', 'h', 't', ' ', 'w', 'o', 'r', 'k', }
		)
	);

	it = output.begin();
	input = "bGlnaHQgd29yay4=";
	it = _Decoder::Decode(it, input.begin(), input.end());
	EXPECT_EQ(it, output.begin() + 11);
	EXPECT_EQ(
		std::vector<uint8_t>(output.begin(), it),
		std::vector<uint8_t>(
			{ 'l', 'i', 'g', 'h', 't', ' ', 'w', 'o', 'r', 'k', '.', }
		)
	);


	// ===== input without padding =====


	it = output.begin();
	input = "bGlnaHQgd29yaw";
	it = _Decoder::Decode(it, input.begin(), input.end());
	EXPECT_EQ(it, output.begin() + 10);
	EXPECT_EQ(
		std::vector<uint8_t>(output.begin(), it),
		std::vector<uint8_t>(
			{ 'l', 'i', 'g', 'h', 't', ' ', 'w', 'o', 'r', 'k', }
		)
	);

	it = output.begin();
	input = "bGlnaHQgd29yay4";
	it = _Decoder::Decode(it, input.begin(), input.end());
	EXPECT_EQ(it, output.begin() + 11);
	EXPECT_EQ(
		std::vector<uint8_t>(output.begin(), it),
		std::vector<uint8_t>(
			{ 'l', 'i', 'g', 'h', 't', ' ', 'w', 'o', 'r', 'k', '.', }
		)
	);


	// ===== input with non-encoding char =====


	it = output.begin();
	input = "#b#G#l#n#a#H#Q#g#d#2#9#y#";
	it = _Decoder::Decode(it, input.begin(), input.end());
	EXPECT_EQ(it, output.begin() + 9);
	EXPECT_EQ(
		std::vector<uint8_t>(output.begin(), it),
		std::vector<uint8_t>(
			{ 'l', 'i', 'g', 'h', 't', ' ', 'w', 'o', 'r', }
		)
	);

	it = output.begin();
	input = "#@b#@G#@l#@n#@a#@H#@Q#@g#@d#@2#@9#@y#@";
	it = _Decoder::Decode(it, input.begin(), input.end());
	EXPECT_EQ(it, output.begin() + 9);
	EXPECT_EQ(
		std::vector<uint8_t>(output.begin(), it),
		std::vector<uint8_t>(
			{ 'l', 'i', 'g', 'h', 't', ' ', 'w', 'o', 'r', }
		)
	);

	it = output.begin();
	input = "#b#G#l#n#a#H#Q#g#d#2#9#y#a#w#=#=#";
	it = _Decoder::Decode(it, input.begin(), input.end());
	EXPECT_EQ(it, output.begin() + 10);
	EXPECT_EQ(
		std::vector<uint8_t>(output.begin(), it),
		std::vector<uint8_t>(
			{ 'l', 'i', 'g', 'h', 't', ' ', 'w', 'o', 'r', 'k', }
		)
	);

	it = output.begin();
	input = "#b#G#l#n#a#H#Q#g#d#2#9#y#a#y#4#=#";
	it = _Decoder::Decode(it, input.begin(), input.end());
	EXPECT_EQ(it, output.begin() + 11);
	EXPECT_EQ(
		std::vector<uint8_t>(output.begin(), it),
		std::vector<uint8_t>(
			{ 'l', 'i', 'g', 'h', 't', ' ', 'w', 'o', 'r', 'k', '.', }
		)
	);

	it = output.begin();
	input = "#b#G#l#n#a#H#Q#g#d#2#9#y#a#w#";
	it = _Decoder::Decode(it, input.begin(), input.end());
	EXPECT_EQ(it, output.begin() + 10);
	EXPECT_EQ(
		std::vector<uint8_t>(output.begin(), it),
		std::vector<uint8_t>(
			{ 'l', 'i', 'g', 'h', 't', ' ', 'w', 'o', 'r', 'k', }
		)
	);

	it = output.begin();
	input = "#b#G#l#n#a#H#Q#g#d#2#9#y#a#y#4#";
	it = _Decoder::Decode(it, input.begin(), input.end());
	EXPECT_EQ(it, output.begin() + 11);
	EXPECT_EQ(
		std::vector<uint8_t>(output.begin(), it),
		std::vector<uint8_t>(
			{ 'l', 'i', 'g', 'h', 't', ' ', 'w', 'o', 'r', 'k', '.', }
		)
	);


	// ===== malformed input =====


	// first char of quad is padding
	it = output.begin();
	input = "bGlnaHQgd29y====";
	EXPECT_THROW(
		_Decoder::Decode(it, input.begin(), input.end());,
		std::invalid_argument
	);

	// second char of quad is padding
	it = output.begin();
	input = "bGlnaHQgd29ya===";
	EXPECT_THROW(
		_Decoder::Decode(it, input.begin(), input.end());,
		std::invalid_argument
	);

	// end on second char of quad
	it = output.begin();
	input = "bGlnaHQgd29ya";
	EXPECT_THROW(
		_Decoder::Decode(it, input.begin(), input.end());,
		std::invalid_argument
	);

	// missing a padding char
	it = output.begin();
	input = "bGlnaHQgd29yaw=";
	EXPECT_THROW(
		_Decoder::Decode(it, input.begin(), input.end());,
		std::invalid_argument
	);
}



//==============================================================================
//
// APIs
//
//==============================================================================


// ==========
// Encoding
// ==========

GTEST_TEST(TestCodecBase64, Base64EncodeContainer2Container)
{
	std::vector<uint8_t> input;
	std::string output;

	input = { 'l', 'i', 'g', 'h', 't', ' ', 'w', 'o', 'r', 'k', '.', };
	output = Base64::Encode<std::string>(input);
	EXPECT_EQ(output, "bGlnaHQgd29yay4=");

	input = { 'l', 'i', 'g', 'h', 't', ' ', 'w', 'o', 'r', 'k', };
	output = Base64::Encode<std::string>(input);
	EXPECT_EQ(output, "bGlnaHQgd29yaw==");

	input = { 'l', 'i', 'g', 'h', 't', ' ', 'w', 'o', 'r', };
	output = Base64::Encode<std::string>(input);
	EXPECT_EQ(output, "bGlnaHQgd29y");

	input = { 'l', 'i', 'g', 'h', 't', ' ', 'w', 'o', 'r', 'k', '.', };
	output = Base64C<false>::Encode<std::string>(input);
	EXPECT_EQ(output, "bGlnaHQgd29yay4");

	input = { 'l', 'i', 'g', 'h', 't', ' ', 'w', 'o', 'r', 'k', };
	output = Base64C<false>::Encode<std::string>(input);
	EXPECT_EQ(output, "bGlnaHQgd29yaw");

	input = { 'l', 'i', 'g', 'h', 't', ' ', 'w', 'o', 'r', };
	output = Base64C<false>::Encode<std::string>(input);
	EXPECT_EQ(output, "bGlnaHQgd29y");

	input = {
		0x00U, 0x10U, 0x83U, 0x10U, 0x51U, 0x87U, 0x20U, 0x92U,
		0x8BU, 0x30U, 0xD3U, 0x8FU, 0x41U, 0x14U, 0x93U, 0x51U,
		0x55U, 0x97U, 0x61U, 0x96U, 0x9BU, 0x71U, 0xD7U, 0x9FU,
		0x82U, 0x18U, 0xA3U, 0x92U, 0x59U, 0xA7U, 0xA2U, 0x9AU,
		0xABU, 0xB2U, 0xDBU, 0xAFU, 0xC3U, 0x1CU, 0xB3U, 0xD3U,
		0x5DU, 0xB7U, 0xE3U, 0x9EU, 0xBBU, 0xF3U, 0xDFU, 0xBFU,
	};
	output = Base64::Encode<std::string>(input);
	EXPECT_EQ(output, "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/");
	output = Base64C<false>::Encode<std::string>(input);
	EXPECT_EQ(output, "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/");
}

GTEST_TEST(TestCodecBase64, Base64EncodeIt2Container)
{
	std::vector<uint8_t> input;
	std::string output;

	input = { 'l', 'i', 'g', 'h', 't', ' ', 'w', 'o', 'r', 'k', '.', };
	output = Base64::Encode<std::string>(input.begin(), input.end());
	EXPECT_EQ(output, "bGlnaHQgd29yay4=");

	input = { 'l', 'i', 'g', 'h', 't', ' ', 'w', 'o', 'r', 'k', };
	output = Base64::Encode<std::string>(input.begin(), input.end());
	EXPECT_EQ(output, "bGlnaHQgd29yaw==");

	input = { 'l', 'i', 'g', 'h', 't', ' ', 'w', 'o', 'r', };
	output = Base64::Encode<std::string>(input.begin(), input.end());
	EXPECT_EQ(output, "bGlnaHQgd29y");

	input = { 'l', 'i', 'g', 'h', 't', ' ', 'w', 'o', 'r', 'k', '.', };
	output = Base64C<false>::Encode<std::string>(input.begin(), input.end());
	EXPECT_EQ(output, "bGlnaHQgd29yay4");

	input = { 'l', 'i', 'g', 'h', 't', ' ', 'w', 'o', 'r', 'k', };
	output = Base64C<false>::Encode<std::string>(input.begin(), input.end());
	EXPECT_EQ(output, "bGlnaHQgd29yaw");

	input = { 'l', 'i', 'g', 'h', 't', ' ', 'w', 'o', 'r', };
	output = Base64C<false>::Encode<std::string>(input.begin(), input.end());
	EXPECT_EQ(output, "bGlnaHQgd29y");
}

GTEST_TEST(TestCodecBase64, Base64EncodeIt2It)
{
	std::vector<uint8_t> input;
	std::string output;
	auto it = output.begin();

	input = { 'l', 'i', 'g', 'h', 't', ' ', 'w', 'o', 'r', 'k', '.', };
	output.resize(Base64::Sizes::EstEncodedSize(input.size()));
	it = output.begin();
	it = Base64::Encode(it, input.begin(), input.end());
	EXPECT_EQ(it, output.begin() + 16);
	EXPECT_EQ(output, "bGlnaHQgd29yay4=");

	input = { 'l', 'i', 'g', 'h', 't', ' ', 'w', 'o', 'r', 'k', };
	output.resize(Base64::Sizes::EstEncodedSize(input.size()));
	it = output.begin();
	it = Base64::Encode(it, input.begin(), input.end());
	EXPECT_EQ(it, output.begin() + 16);
	EXPECT_EQ(output, "bGlnaHQgd29yaw==");

	input = { 'l', 'i', 'g', 'h', 't', ' ', 'w', 'o', 'r', };
	output.resize(Base64::Sizes::EstEncodedSize(input.size()));
	it = output.begin();
	it = Base64::Encode(it, input.begin(), input.end());
	EXPECT_EQ(it, output.begin() + 12);
	EXPECT_EQ(output, "bGlnaHQgd29y");

	input = { 'l', 'i', 'g', 'h', 't', ' ', 'w', 'o', 'r', 'k', '.', };
	output.resize(Base64::Sizes::EstEncodedSize(input.size()));
	it = output.begin();
	it = Base64C<false>::Encode(it, input.begin(), input.end());
	EXPECT_EQ(it, output.begin() + 15);
	EXPECT_EQ(output.substr(0, 15), "bGlnaHQgd29yay4");

	input = { 'l', 'i', 'g', 'h', 't', ' ', 'w', 'o', 'r', 'k', };
	output.resize(Base64::Sizes::EstEncodedSize(input.size()));
	it = output.begin();
	it = Base64C<false>::Encode(it, input.begin(), input.end());
	EXPECT_EQ(it, output.begin() + 14);
	EXPECT_EQ(output.substr(0, 14), "bGlnaHQgd29yaw");

	input = { 'l', 'i', 'g', 'h', 't', ' ', 'w', 'o', 'r', };
	output.resize(Base64::Sizes::EstEncodedSize(input.size()));
	it = output.begin();
	it = Base64C<false>::Encode(it, input.begin(), input.end());
	EXPECT_EQ(it, output.begin() + 12);
	EXPECT_EQ(output.substr(0, 12), "bGlnaHQgd29y");
}

// ==========
// Decoding
// ==========

GTEST_TEST(TestCodecBase64, Base64DecodeContainer2Container)
{
	std::string input;
	std::vector<uint8_t> output;

	input = "bGlnaHQgd29yay4=";
	output = Base64::Decode<std::vector<uint8_t> >(input);
	EXPECT_EQ(
		output,
		std::vector<uint8_t>({ 'l', 'i', 'g', 'h', 't', ' ', 'w', 'o', 'r', 'k', '.', })
	);

	input = "bGlnaHQgd29yaw==";
	output = Base64::Decode<std::vector<uint8_t> >(input);
	EXPECT_EQ(
		output,
		std::vector<uint8_t>({ 'l', 'i', 'g', 'h', 't', ' ', 'w', 'o', 'r', 'k', })
	);

	input = "bGlnaHQgd29y";
	output = Base64::Decode<std::vector<uint8_t> >(input);
	EXPECT_EQ(
		output,
		std::vector<uint8_t>({ 'l', 'i', 'g', 'h', 't', ' ', 'w', 'o', 'r', })
	);

	input = "bGlnaHQgd29yay4";
	output = Base64C<false>::Decode<std::vector<uint8_t> >(input);
	EXPECT_EQ(
		output,
		std::vector<uint8_t>({ 'l', 'i', 'g', 'h', 't', ' ', 'w', 'o', 'r', 'k', '.', })
	);

	input = "bGlnaHQgd29yaw";
	output = Base64C<false>::Decode<std::vector<uint8_t> >(input);
	EXPECT_EQ(
		output,
		std::vector<uint8_t>({ 'l', 'i', 'g', 'h', 't', ' ', 'w', 'o', 'r', 'k', })
	);

	input = "bGlnaHQgd29y";
	output = Base64C<false>::Decode<std::vector<uint8_t> >(input);
	EXPECT_EQ(
		output,
		std::vector<uint8_t>({ 'l', 'i', 'g', 'h', 't', ' ', 'w', 'o', 'r', })
	);


	input = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";
	output = Base64::Decode<std::vector<uint8_t> >(input);
	EXPECT_EQ(
		output,
		std::vector<uint8_t>({
			0x00U, 0x10U, 0x83U, 0x10U, 0x51U, 0x87U, 0x20U, 0x92U,
			0x8BU, 0x30U, 0xD3U, 0x8FU, 0x41U, 0x14U, 0x93U, 0x51U,
			0x55U, 0x97U, 0x61U, 0x96U, 0x9BU, 0x71U, 0xD7U, 0x9FU,
			0x82U, 0x18U, 0xA3U, 0x92U, 0x59U, 0xA7U, 0xA2U, 0x9AU,
			0xABU, 0xB2U, 0xDBU, 0xAFU, 0xC3U, 0x1CU, 0xB3U, 0xD3U,
			0x5DU, 0xB7U, 0xE3U, 0x9EU, 0xBBU, 0xF3U, 0xDFU, 0xBFU,
		})
	);

	input = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";
	output = Base64C<false>::Decode<std::vector<uint8_t> >(input);
	EXPECT_EQ(
		output,
		std::vector<uint8_t>({
			0x00U, 0x10U, 0x83U, 0x10U, 0x51U, 0x87U, 0x20U, 0x92U,
			0x8BU, 0x30U, 0xD3U, 0x8FU, 0x41U, 0x14U, 0x93U, 0x51U,
			0x55U, 0x97U, 0x61U, 0x96U, 0x9BU, 0x71U, 0xD7U, 0x9FU,
			0x82U, 0x18U, 0xA3U, 0x92U, 0x59U, 0xA7U, 0xA2U, 0x9AU,
			0xABU, 0xB2U, 0xDBU, 0xAFU, 0xC3U, 0x1CU, 0xB3U, 0xD3U,
			0x5DU, 0xB7U, 0xE3U, 0x9EU, 0xBBU, 0xF3U, 0xDFU, 0xBFU,
		})
	);
}

GTEST_TEST(TestCodecBase64, Base64DecodeIt2Container)
{
	std::string input;
	std::vector<uint8_t> output;

	input = "bGlnaHQgd29yay4=";
	output = Base64::Decode<std::vector<uint8_t> >(input.cbegin(), input.cend());
	EXPECT_EQ(
		output,
		std::vector<uint8_t>({ 'l', 'i', 'g', 'h', 't', ' ', 'w', 'o', 'r', 'k', '.', })
	);

	input = "bGlnaHQgd29yaw==";
	output = Base64::Decode<std::vector<uint8_t> >(input.cbegin(), input.cend());
	EXPECT_EQ(
		output,
		std::vector<uint8_t>({ 'l', 'i', 'g', 'h', 't', ' ', 'w', 'o', 'r', 'k', })
	);

	input = "bGlnaHQgd29y";
	output = Base64::Decode<std::vector<uint8_t> >(input.cbegin(), input.cend());
	EXPECT_EQ(
		output,
		std::vector<uint8_t>({ 'l', 'i', 'g', 'h', 't', ' ', 'w', 'o', 'r', })
	);

	input = "bGlnaHQgd29yay4";
	output = Base64C<false>::Decode<std::vector<uint8_t> >(input.cbegin(), input.cend());
	EXPECT_EQ(
		output,
		std::vector<uint8_t>({ 'l', 'i', 'g', 'h', 't', ' ', 'w', 'o', 'r', 'k', '.', })
	);

	input = "bGlnaHQgd29yaw";
	output = Base64C<false>::Decode<std::vector<uint8_t> >(input.cbegin(), input.cend());
	EXPECT_EQ(
		output,
		std::vector<uint8_t>({ 'l', 'i', 'g', 'h', 't', ' ', 'w', 'o', 'r', 'k', })
	);

	input = "bGlnaHQgd29y";
	output = Base64C<false>::Decode<std::vector<uint8_t> >(input.cbegin(), input.cend());
	EXPECT_EQ(
		output,
		std::vector<uint8_t>({ 'l', 'i', 'g', 'h', 't', ' ', 'w', 'o', 'r', })
	);
}

GTEST_TEST(TestCodecBase64, Base64DecodeIt2It)
{
	std::string input;
	std::vector<uint8_t> output;
	std::vector<uint8_t> expOutput;
	auto it = output.begin();

	input = "bGlnaHQgd29yay4=";
	expOutput = { 'l', 'i', 'g', 'h', 't', ' ', 'w', 'o', 'r', 'k', '.', };
	output.resize(expOutput.size());
	it = output.begin();
	it = Base64::Decode(it, input.begin(), input.end());
	EXPECT_EQ(it, output.begin() + expOutput.size());
	EXPECT_EQ(output, expOutput);

	input = "bGlnaHQgd29yaw==";
	expOutput = { 'l', 'i', 'g', 'h', 't', ' ', 'w', 'o', 'r', 'k', };
	output.resize(expOutput.size());
	it = output.begin();
	it = Base64::Decode(it, input.begin(), input.end());
	EXPECT_EQ(it, output.begin() + expOutput.size());
	EXPECT_EQ(output, expOutput);

	input = "bGlnaHQgd29y";
	expOutput = { 'l', 'i', 'g', 'h', 't', ' ', 'w', 'o', 'r', };
	output.resize(expOutput.size());
	it = output.begin();
	it = Base64::Decode(it, input.begin(), input.end());
	EXPECT_EQ(it, output.begin() + expOutput.size());
	EXPECT_EQ(output, expOutput);

	input = "bGlnaHQgd29yay4";
	expOutput = { 'l', 'i', 'g', 'h', 't', ' ', 'w', 'o', 'r', 'k', '.', };
	output.resize(expOutput.size());
	it = output.begin();
	it = Base64C<false>::Decode(it, input.begin(), input.end());
	EXPECT_EQ(it, output.begin() + expOutput.size());
	EXPECT_EQ(output, expOutput);

	input = "bGlnaHQgd29yaw";
	expOutput = { 'l', 'i', 'g', 'h', 't', ' ', 'w', 'o', 'r', 'k', };
	output.resize(expOutput.size());
	it = output.begin();
	it = Base64C<false>::Decode(it, input.begin(), input.end());
	EXPECT_EQ(it, output.begin() + expOutput.size());
	EXPECT_EQ(output, expOutput);

	input = "bGlnaHQgd29y";
	expOutput = { 'l', 'i', 'g', 'h', 't', ' ', 'w', 'o', 'r', };
	output.resize(expOutput.size());
	it = output.begin();
	it = Base64C<false>::Decode(it, input.begin(), input.end());
	EXPECT_EQ(it, output.begin() + expOutput.size());
	EXPECT_EQ(output, expOutput);
}

