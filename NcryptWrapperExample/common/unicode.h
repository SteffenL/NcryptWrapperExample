#pragma once

#include <codecvt>

namespace unicode {

template<class T> std::string narrow(T&& s)
{
    return std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>>().to_bytes(s);
}

template<class T> std::string narrow(T&& s, unsigned int length)
{
    return std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>>().to_bytes(s, s + length);
}

template<class T> std::wstring widen(T&& s)
{
    return std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>>().from_bytes(s);
}

template<class T> std::wstring widen(T&& s, unsigned int length)
{
    return std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>>().from_bytes(s, s + length);
}

}
