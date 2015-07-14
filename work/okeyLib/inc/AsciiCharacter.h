/********************************************************************
	created:	2015/07/14
	created:	17:39
	author:		okey
	
	purpose:	
*********************************************************************/
#ifndef __ASCII_CHARACTER_H__
#define __ASCII_CHARACTER_H__

namespace okey
{
	class AsciiCharacter
	{
	public:
		enum CharacterProperties
		{
			ACP_CONTROL  = 0x0001,
			ACP_SPACE    = 0x0002,//空白符，水平制表，换行，垂直制表，换页，回车 ，空格
			ACP_PUNCT    = 0x0004,//标点符号
			ACP_DIGIT    = 0x0008,//数字
			ACP_HEXDIGIT = 0x0010,//16进制 
			ACP_ALPHA    = 0x0020,//字母
			ACP_LOWER    = 0x0040,//小写字母
			ACP_UPPER    = 0x0080,//大写字母
			ACP_GRAPH    = 0x0100,
			ACP_PRINT    = 0x0200
		};

		static int GetProperties(int ch);
		static bool HasSomeProperties(int ch, int properties);
		static bool HasProperties(int ch, int properties);
		static bool IsAscii(int ch);
		static bool IsSpace(int ch);
		static bool IsDigit(int ch);
		static bool IsHexDigit(int ch);
		static bool IsPunct(int ch);
		static bool IsAlpha(int ch);	
		static bool IsAlphaNumeric(int ch);	
		static bool IsLower(int ch);
		static bool IsUpper(int ch);
		static int ToLower(int ch);
		static int ToUpper(int ch);
	private:
		static const int CHARACTER_PROPERTIES[128];
	};

	inline int AsciiCharacter::GetProperties(int ch)
	{
		if (IsAscii(ch)) 
			return CHARACTER_PROPERTIES[ch];
		else
			return 0;
	}

	inline bool AsciiCharacter::HasSomeProperties(int ch, int properties)
	{
		return (GetProperties(ch) & properties) == properties;
	}

	inline bool AsciiCharacter::HasProperties(int ch, int properties)
	{
		return (GetProperties(ch) & properties) != 0;
	}

	inline bool AsciiCharacter::IsAscii(int ch)
	{
		return (static_cast<unsigned int>(ch) & 0xFFFFFF80) == 0;
	}

	inline bool AsciiCharacter::IsSpace(int ch)
	{
		return HasProperties(ch, ACP_SPACE);
	}

	inline bool AsciiCharacter::IsDigit(int ch)
	{
		return HasProperties(ch, ACP_DIGIT);
	}

	inline bool AsciiCharacter::IsHexDigit(int ch)
	{
		return HasProperties(ch, ACP_HEXDIGIT);
	}

	inline bool AsciiCharacter::IsPunct(int ch)
	{
		return HasProperties(ch, ACP_PUNCT);
	}

	inline bool AsciiCharacter::IsAlpha(int ch)
	{
		return HasProperties(ch, ACP_ALPHA);
	}

	inline bool AsciiCharacter::IsAlphaNumeric(int ch)
	{
		return HasSomeProperties(ch, ACP_ALPHA | ACP_DIGIT);
	}

	inline bool AsciiCharacter::IsLower(int ch)
	{
		return HasProperties(ch, ACP_LOWER);
	}

	inline bool AsciiCharacter::IsUpper(int ch)
	{
		return HasProperties(ch, ACP_UPPER);
	}

	inline int AsciiCharacter::ToLower(int ch)
	{
		if (IsUpper(ch))
			return ch + 32;
		else
			return ch;
	}
	inline int AsciiCharacter::ToUpper(int ch)
	{
		if (IsLower(ch))
			return ch - 32;
		else
			return ch;
	}
}

#endif