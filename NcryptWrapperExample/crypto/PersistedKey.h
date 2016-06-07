#pragma once

#include "../common/noncopyable.h"

#include <cstdint>

class PersistedKey : public noncopyable
{
public:
    using NativeHandle = void*;

    PersistedKey(PersistedKey&&) = default;
    PersistedKey& operator=(PersistedKey&&) = default;

    PersistedKey(NativeHandle nativeHandle);
    virtual ~PersistedKey();
    PersistedKey& Finalize();
    PersistedKey& SetLength(uint32_t lengthInBits);
    void SetNativeHandle(NativeHandle handle);

    template<typename T = NativeHandle>
    T GetNativeHandle() const
    {
        return reinterpret_cast<T>(m_nativeHandle);
    }


private:
    NativeHandle m_nativeHandle;
};
