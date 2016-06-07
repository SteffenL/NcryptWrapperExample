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
    PersistedKey CreateKey(const std::wstring& algorithm, const std::wstring& keyName);
    PersistedKey CreateKey(const std::wstring& algorithm);
    PersistedKey OpenKey(const std::wstring& keyName);
    void DeleteKey(PersistedKey& key);
    std::vector<uint8_t> ExportKey(const PersistedKey& key, const std::wstring& blobType);
    static KeyStorageProvider OpenDefault();
    void SetNativeHandle(NativeHandle handle);

    template<typename T = NativeHandle>
    T GetNativeHandle() const
    {
        return reinterpret_cast<T>(m_nativeHandle);
    }

private:
    NativeHandle m_nativeHandle;
};
