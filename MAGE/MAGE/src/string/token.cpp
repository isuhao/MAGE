//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "string\token.hpp"
#include "string\string_utils.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Definitions
//-----------------------------------------------------------------------------
namespace mage {

	//-------------------------------------------------------------------------
	// Conversion Utilities
	//-------------------------------------------------------------------------

	TokenResult StringToBool(const char *str, bool &result) {
		if (!str) {
			return no_token;
		}

		if (str_equals(str, "true")) {
			result = true;
			return valid_token;
		}
		
		result = false;
		return (str_equals(str, "false")) ? valid_token : invalid_token;
	}
	TokenResult StringToInt8(const char *str, int8_t &result) {
		if (!str) {
			return no_token;
		}

		char *inner_context = nullptr;
		result = (int8_t)strtol(str, &inner_context, 10);
		return (*inner_context == '\0') ? valid_token : invalid_token;
	}
	TokenResult StringToUInt8(const char *str, uint8_t &result) {
		if (!str) {
			return no_token;
		}

		char *inner_context = nullptr;
		result = (uint8_t)strtoul(str, &inner_context, 10);
		return (*inner_context == '\0') ? valid_token : invalid_token;
	}
	TokenResult StringToInt16(const char *str, int16_t &result) {
		if (!str) {
			return no_token;
		}

		char *inner_context = nullptr;
		result = (int16_t)strtol(str, &inner_context, 10);
		return (*inner_context == '\0') ? valid_token : invalid_token;
	}
	TokenResult StringToUInt16(const char *str, uint16_t &result) {
		if (!str) {
			return no_token;
		}

		char *inner_context = nullptr;
		result = (uint16_t)strtoul(str, &inner_context, 10);
		return (*inner_context == '\0') ? valid_token : invalid_token;
	}
	TokenResult StringToInt32(const char *str, int32_t &result) {
		if (!str) {
			return no_token;
		}

		char *inner_context = nullptr;
		result = (int32_t)strtol(str, &inner_context, 10);
		return (*inner_context == '\0') ? valid_token : invalid_token;
	}
	TokenResult StringToUInt32(const char *str, uint32_t &result) {
		if (!str) {
			return no_token;
		}

		char *inner_context = nullptr;
		result = (uint32_t)strtoul(str, &inner_context, 10);
		return (*inner_context == '\0') ? valid_token : invalid_token;
	}
	TokenResult StringToInt64(const char *str, int64_t &result) {
		if (!str) {
			return no_token;
		}

		char *inner_context = nullptr;
		result = (int64_t)strtoll(str, &inner_context, 10);
		return (*inner_context == '\0') ? valid_token : invalid_token;
	}
	TokenResult StringToUInt64(const char *str, uint64_t &result) {
		if (!str) {
			return no_token;
		}

		char *inner_context = nullptr;
		result = (uint64_t)strtoull(str, &inner_context, 10);
		return (*inner_context == '\0') ? valid_token : invalid_token;
	}
	TokenResult StringToFloat(const char *str, float &result) {
		if (!str) {
			return no_token;
		}

		char *inner_context = nullptr;
		result = strtof(str, &inner_context);
		return (*inner_context == '\0') ? valid_token : invalid_token;
	}
	TokenResult StringToDouble(const char *str, double &result) {
		if (!str) {
			return no_token;
		}

		char *inner_context = nullptr;
		result = strtod(str, &inner_context);
		return (*inner_context == '\0') ? valid_token : invalid_token;
	}
	
	TokenResult StringToBool(const char *begin, const char *end, bool &result) {
		if (!begin) {
			return no_token;
		}

		if (end - begin == 4) {
			if ((*begin != 't') || 
				(*(begin + 1) != 'r') || 
				(*(begin + 2) != 'u') || 
				(*(begin + 3) != 'e')) {
				result = false;
				return invalid_token;
			}

			result = true;
			return valid_token;
		} 
		
		if (end - begin == 5) {
			if ((*begin != 'f') ||
				(*(begin + 1) != 'a') ||
				(*(begin + 2) != 'l') ||
				(*(begin + 3) != 's') ||
				(*(begin + 4) != 'e')) {
				result = false;
				return invalid_token;
			}

			result = false;
			return valid_token;
		}
		
		result = false;
		return invalid_token;
	}
	TokenResult StringToInt8(const char *begin, const char *end, int8_t &result) {
		if (!begin) {
			return no_token;
		}

		char *inner_context = nullptr;
		result = (int8_t)strtol(begin, &inner_context, 10);
		return (inner_context == end) ? valid_token : invalid_token;
	}
	TokenResult StringToUInt8(const char *begin, const char *end, uint8_t &result) {
		if (!begin) {
			return no_token;
		}

		char *inner_context = nullptr;
		result = (uint8_t)strtoul(begin, &inner_context, 10);
		return (inner_context == end) ? valid_token : invalid_token;
	}
	TokenResult StringToInt16(const char *begin, const char *end, int16_t &result) {
		if (!begin) {
			return no_token;
		}

		char *inner_context = nullptr;
		result = (int16_t)strtol(begin, &inner_context, 10);
		return (inner_context == end) ? valid_token : invalid_token;
	}
	TokenResult StringToUInt16(const char *begin, const char *end, uint16_t &result) {
		if (!begin) {
			return no_token;
		}

		char *inner_context = nullptr;
		result = (uint16_t)strtoul(begin, &inner_context, 10);
		return (inner_context == end) ? valid_token : invalid_token;
	}
	TokenResult StringToInt32(const char *begin, const char *end, int32_t &result) {
		if (!begin) {
			return no_token;
		}

		char *inner_context = nullptr;
		result = (int32_t)strtol(begin, &inner_context, 10);
		return (inner_context == end) ? valid_token : invalid_token;
	}
	TokenResult StringToUInt32(const char *begin, const char *end, uint32_t &result) {
		if (!begin) {
			return no_token;
		}

		char *inner_context = nullptr;
		result = (uint32_t)strtoul(begin, &inner_context, 10);
		return (inner_context == end) ? valid_token : invalid_token;
	}
	TokenResult StringToInt64(const char *begin, const char *end, int64_t &result) {
		if (!begin) {
			return no_token;
		}

		char *inner_context = nullptr;
		result = (int64_t)strtoll(begin, &inner_context, 10);
		return (inner_context == end) ? valid_token : invalid_token;
	}
	TokenResult StringToUInt64(const char *begin, const char *end, uint64_t &result) {
		if (!begin) {
			return no_token;
		}

		char *inner_context = nullptr;
		result = (uint64_t)strtoull(begin, &inner_context, 10);
		return (inner_context == end) ? valid_token : invalid_token;
	}
	TokenResult StringToFloat(const char *begin, const char *end, float &result) {
		if (!begin) {
			return no_token;
		}

		char *inner_context = nullptr;
		result = strtof(begin, &inner_context);
		return (inner_context == end) ? valid_token : invalid_token;
	}
	TokenResult StringToDouble(const char *begin, const char *end, double &result) {
		if (!begin) {
			return no_token;
		}

		char *inner_context = nullptr;
		result = strtod(begin, &inner_context);
		return (inner_context == end) ? valid_token : invalid_token;
	}

	TokenResult StringPrefixToInt8(const char *str, int8_t &result) {
		if (!str) {
			return no_token;
		}

		char *inner_context = nullptr;
		result = (int8_t)strtol(str, &inner_context, 10);
		return (inner_context != str) ? valid_token : invalid_token;
	}
	TokenResult StringPrefixToUInt8(const char *str, uint8_t &result) {
		if (!str) {
			return no_token;
		}

		char *inner_context = nullptr;
		result = (uint8_t)strtoul(str, &inner_context, 10);
		return (inner_context != str) ? valid_token : invalid_token;
	}
	TokenResult StringPrefixToInt16(const char *str, int16_t &result) {
		if (!str) {
			return no_token;
		}

		char *inner_context = nullptr;
		result = (int16_t)strtol(str, &inner_context, 10);
		return (inner_context != str) ? valid_token : invalid_token;
	}
	TokenResult StringPrefixToUInt16(const char *str, uint16_t &result) {
		if (!str) {
			return no_token;
		}

		char *inner_context = nullptr;
		result = (uint16_t)strtoul(str, &inner_context, 10);
		return (inner_context != str) ? valid_token : invalid_token;
	}
	TokenResult StringPrefixToInt32(const char *str, int32_t &result) {
		if (!str) {
			return no_token;
		}

		char *inner_context = nullptr;
		result = (int32_t)strtol(str, &inner_context, 10);
		return (inner_context != str) ? valid_token : invalid_token;
	}
	TokenResult StringPrefixToUInt32(const char *str, uint32_t &result) {
		if (!str) {
			return no_token;
		}

		char *inner_context = nullptr;
		result = (uint32_t)strtoul(str, &inner_context, 10);
		return (inner_context != str) ? valid_token : invalid_token;
	}
	TokenResult StringPrefixToInt64(const char *str, int64_t &result) {
		if (!str) {
			return no_token;
		}

		char *inner_context = nullptr;
		result = (int64_t)strtoll(str, &inner_context, 10);
		return (inner_context != str) ? valid_token : invalid_token;
	}
	TokenResult StringPrefixToUInt64(const char *str, uint64_t &result) {
		if (!str) {
			return no_token;
		}

		char *inner_context = nullptr;
		result = (uint64_t)strtoull(str, &inner_context, 10);
		return (inner_context != str) ? valid_token : invalid_token;
	}
	TokenResult StringPrefixToFloat(const char *str, float &result) {
		if (!str) {
			return no_token;
		}

		char *inner_context = nullptr;
		result = strtof(str, &inner_context);
		return (inner_context != str) ? valid_token : invalid_token;
	}
	TokenResult StringPrefixToDouble(const char *str, double &result) {
		if (!str) {
			return no_token;
		}

		char *inner_context = nullptr;
		result = strtod(str, &inner_context);
		return (inner_context != str) ? valid_token : invalid_token;
	}

	//-------------------------------------------------------------------------
	// Parsing Utilities
	//-------------------------------------------------------------------------

	TokenResult ReadChars(char *str, char **context, char **result, const char *delimiters) {
		*result = strtok_s(str, delimiters, context);
		if (!result) {
			return no_token;
		}

		return valid_token;
	}
	TokenResult ReadString(char *str, char **context, string &result, const char *delimiters) {
		const char *token = strtok_s(str, delimiters, context);
		if (!token) {
			return no_token;
		}
		
		result = token;

		return valid_token;
	}
	TokenResult ReadQuotedString(char *str, char **context, string &result, const char *delimiters) {
		char *start = (str) ? SkipDelimiters(str, delimiters) : SkipDelimiters(*context, delimiters);
		if (!start) {
			return no_token;
		}

		char *first_quote = str_escape_first(start, '"');
		if (!first_quote) {
			return invalid_token;
		}
		char *last_quote = str_escape_first(first_quote + 1, '"');
		if (!last_quote) {
			return invalid_token;
		}

		if (!str_contains(delimiters, *(last_quote + 1))) {
			return invalid_token;
		}

		*last_quote = '\0';
		result = first_quote + 1;
		*context = last_quote + 1;
		return valid_token;
	}
	TokenResult ReadBool(char *str, char **context, bool &result, const char *delimiters) {
		const char *token = strtok_s(str, delimiters, context);
		return StringToBool(token, result);
	}
	TokenResult ReadInt8(char *str, char **context, int8_t &result, const char *delimiters) {
		const char *token = strtok_s(str, delimiters, context);
		return StringToInt8(token, result);
	}
	TokenResult ReadUInt8(char *str, char **context, uint8_t &result, const char *delimiters) {
		const char *token = strtok_s(str, delimiters, context);
		return StringToUInt8(token, result);
	}
	TokenResult ReadInt16(char *str, char **context, int16_t &result, const char *delimiters) {
		const char *token = strtok_s(str, delimiters, context);
		return StringToInt16(token, result);
	}
	TokenResult ReadUInt16(char *str, char **context, uint16_t &result, const char *delimiters) {
		const char *token = strtok_s(str, delimiters, context);
		return StringToUInt16(token, result);
	}
	TokenResult ReadInt32(char *str, char **context, int32_t &result, const char *delimiters) {
		const char *token = strtok_s(str, delimiters, context);
		return StringToInt32(token, result);
	}
	TokenResult ReadUInt32(char *str, char **context, uint32_t &result, const char *delimiters) {
		const char *token = strtok_s(str, delimiters, context);
		return StringToUInt32(token, result);
	}
	TokenResult ReadInt64(char *str, char **context, int64_t &result, const char *delimiters) {
		const char *token = strtok_s(str, delimiters, context);
		return StringToInt64(token, result);
	}
	TokenResult ReadUInt64(char *str, char **context, uint64_t &result, const char *delimiters) {
		const char *token = strtok_s(str, delimiters, context);
		return StringToUInt64(token, result);
	}
	TokenResult ReadFloat(char *str, char **context, float &result, const char *delimiters) {
		const char *token = strtok_s(str, delimiters, context);
		return StringToFloat(token, result);
	}
	TokenResult ReadDouble(char *str, char **context, double &result, const char *delimiters) {
		const char *token = strtok_s(str, delimiters, context);
		return StringToDouble(token, result);
	}
	TokenResult ReadFloat2(char *str, char **context, XMFLOAT2 &result, const char *delimiters) {
		const TokenResult token_result_x = ReadFloat(str, context, result.x, delimiters);
		if (token_result_x != valid_token) {
			return token_result_x;
		}

		const TokenResult token_result_y = ReadFloat(str, context, result.y, delimiters);
		if (token_result_y != valid_token) {
			return token_result_y;
		}
		
		return valid_token;
	}
	TokenResult ReadFloat3(char *str, char **context, XMFLOAT3 &result, const char *delimiters) {
		const TokenResult token_result_x = ReadFloat(str, context, result.x, delimiters);
		if (token_result_x != valid_token) {
			return token_result_x;
		}

		const TokenResult token_result_y = ReadFloat(str, context, result.y, delimiters);
		if (token_result_y != valid_token) {
			return token_result_y;
		}

		const TokenResult token_result_z = ReadFloat(str, context, result.z, delimiters);
		if (token_result_z != valid_token) {
			return token_result_z;
		}

		return valid_token;
	}
	TokenResult ReadFloat4(char *str, char **context, XMFLOAT4 &result, const char *delimiters) {
		const TokenResult token_result_x = ReadFloat(str, context, result.x, delimiters);
		if (token_result_x != valid_token) {
			return token_result_x;
		}

		const TokenResult token_result_y = ReadFloat(str, context, result.y, delimiters);
		if (token_result_y != valid_token) {
			return token_result_y;
		}

		const TokenResult token_result_z = ReadFloat(str, context, result.z, delimiters);
		if (token_result_z != valid_token) {
			return token_result_z;
		}

		const TokenResult token_result_w = ReadFloat(str, context, result.w, delimiters);
		if (token_result_w != valid_token) {
			return token_result_w;
		}

		return valid_token;
	}

	TokenResult HasChars(const char *str, const char *delimiters) {
		const char *start = SkipDelimiters(str, delimiters);
		return (start) ? valid_token : no_token;
	}
	TokenResult HasString(const char *str, const char *delimiters) {
		return HasChars(str, delimiters);
	}
	TokenResult HasQuotedString(const char *str, const char *delimiters) {
		const char *start = SkipDelimiters(str, delimiters);
		if (!start) {
			return no_token;
		}
		
		const char *first_quote = str_escape_first(start, '"');
		if (!first_quote) {
			return invalid_token;
		}
		const char *last_quote = str_escape_first(first_quote + 1, '"');
		if (!last_quote) {
			return invalid_token;
		}
		
		return str_contains(delimiters, *(last_quote + 1)) ? valid_token : invalid_token;
	}
	TokenResult HasBool(const char *str, const char *delimiters) {
		const char *start = SkipDelimiters(str, delimiters);
		if (!start) {
			return no_token;
		}
		const char *end = GotoDelimiters(start, delimiters);

		bool result;
		return StringToBool(start, end, result);
	}
	TokenResult HasInt8(const char *str, const char *delimiters) {
		const char *start = SkipDelimiters(str, delimiters);
		if (!start) {
			return no_token;
		}
		const char *end = GotoDelimiters(start, delimiters);

		int8_t result;
		return StringToInt8(start, end, result);
	}
	TokenResult HasUInt8(const char *str, const char *delimiters) {
		const char *start = SkipDelimiters(str, delimiters);
		if (!start) {
			return no_token;
		}
		const char *end = GotoDelimiters(start, delimiters);

		uint8_t result;
		return StringToUInt8(start, end, result);
	}
	TokenResult HasInt16(const char *str, const char *delimiters) {
		const char *start = SkipDelimiters(str, delimiters);
		if (!start) {
			return no_token;
		}
		const char *end = GotoDelimiters(start, delimiters);

		int16_t result;
		return StringToInt16(start, end, result);
	}
	TokenResult HasUInt16(const char *str, const char *delimiters) {
		const char *start = SkipDelimiters(str, delimiters);
		if (!start) {
			return no_token;
		}
		const char *end = GotoDelimiters(start, delimiters);

		uint16_t result;
		return StringToUInt16(start, end, result);
	}
	TokenResult HasInt32(const char *str, const char *delimiters) {
		const char *start = SkipDelimiters(str, delimiters);
		if (!start) {
			return no_token;
		}
		const char *end = GotoDelimiters(start, delimiters);

		int32_t result;
		return StringToInt32(start, end, result);
	}
	TokenResult HasUInt32(const char *str, const char *delimiters) {
		const char *start = SkipDelimiters(str, delimiters);
		if (!start) {
			return no_token;
		}
		const char *end = GotoDelimiters(start, delimiters);

		uint32_t result;
		return StringToUInt32(start, end, result);
	}
	TokenResult HasInt64(const char *str, const char *delimiters) {
		const char *start = SkipDelimiters(str, delimiters);
		if (!start) {
			return no_token;
		}
		const char *end = GotoDelimiters(start, delimiters);

		int64_t result;
		return StringToInt64(start, end, result);
	}
	TokenResult HasUInt64(const char *str, const char *delimiters) {
		const char *start = SkipDelimiters(str, delimiters);
		if (!start) {
			return no_token;
		}
		const char *end = GotoDelimiters(start, delimiters);

		uint64_t result;
		return StringToUInt64(start, end, result);
	}
	TokenResult HasFloat(const char *str, const char *delimiters) {
		const char *start = SkipDelimiters(str, delimiters);
		if (!start) {
			return no_token;
		}
		const char *end = GotoDelimiters(start, delimiters);

		float result;
		return StringToFloat(start, end, result);
	}
	TokenResult HasDouble(const char *str, const char *delimiters) {
		const char *start = SkipDelimiters(str, delimiters);
		if (!start) {
			return no_token;
		}
		const char *end = GotoDelimiters(start, delimiters);

		double result;
		return StringToDouble(start, end, result);
	}

	char *SkipDelimiters(char *str, const char *delimiters) {
		while (*str != '\0' && str_contains(delimiters, *str)) {
			++str;
		}
		return (*str != '\0') ? str : nullptr;
	}
	const char *SkipDelimiters(const char *str, const char *delimiters) {
		while (*str != '\0' && str_contains(delimiters, *str)) {
			++str;
		}
		return (*str != '\0') ? str : nullptr;
	}
	char *GotoDelimiters(char *str, const char *delimiters) {
		while (*str != '\0' && !str_contains(delimiters, *str)) {
			++str;
		}
		return (*str != '\0') ? str : nullptr;
	}
	const char *GotoDelimiters(const char *str, const char *delimiters) {
		while (*str != '\0' && !str_contains(delimiters, *str)) {
			++str;
		}
		return (*str != '\0') ? str : nullptr;
	}
}