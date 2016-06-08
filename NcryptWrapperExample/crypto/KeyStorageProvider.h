#pragma once

#include "../common/noncopyable.h"

#include <string>
#include <cstdint>
#include <vector>

class PersistedKey;

class KeyStorageProvider : public noncopyable
{
public:
    using NativeHandle = void*;

    KeyStorageProvider(KeyStorageProvider&&) = default;
    KeyStorageProvider& operator=(KeyStorageProvider&&) = default;

    KeyStorageProvider(NativeHandle nativeHandle);
    virtual ~KeyStorageProvider();
    PersistedKey CreateKey(const wchar_t* algorithm, const wchar_t* keyName);
    PersistedKey CreateKey(const wchar_t* algorithm, const std::string& keyName);
    PersistedKey OpenKey(const wchar_t* keyName);
    PersistedKey OpenKey(const std::string& keyName);
    void DeleteKey(PersistedKey& key);
    std::vector<uint8_t> ExportKey(const PersistedKey& key, const wchar_t* blobType);
    static KeyStorageProvider OpenDefaultProvider();
    void SetNativeHandle(NativeHandle handle);

    template<typename T = NativeHandle>
    T GetNativeHandle() const
    {
        return reinterpret_cast<T>(m_nativeHandle);
    }

private:
    NativeHandle m_nativeHandle;
};
