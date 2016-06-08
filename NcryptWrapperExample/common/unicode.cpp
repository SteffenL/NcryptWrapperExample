#include "unicode.h"

namespace unicode {
std::string narrow(const std::wstring& s)
{
    return std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>>().to_bytes(s);
}

std::string narrow(const wchar_t* s, unsigned int length)
{
    return std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>>().to_bytes(s, s + length);
}
}
