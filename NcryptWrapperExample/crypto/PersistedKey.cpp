#include "PersistedKey.h"

#include <stdexcept>

#include <Windows.h>
#include <ncrypt.h>


PersistedKey::PersistedKey(NativeHandle nativeHandle) : m_nativeHandle(nativeHandle)
{

}

PersistedKey::~PersistedKey()
{
    auto keyHandle = GetNativeHandle<NCRYPT_KEY_HANDLE>();
    if (keyHandle) {
        NCryptFreeObject(keyHandle);
        keyHandle = NULL;
    }
}

PersistedKey& PersistedKey::Finalize()
{
    auto keyHandle = GetNativeHandle<NCRYPT_KEY_HANDLE>();
    if (NCryptFinalizeKey(keyHandle, 0) != ERROR_SUCCESS) {
        throw std::runtime_error("Failed to finalize key");
    }

    return *this;
}

PersistedKey& PersistedKey::SetLength(uint32_t lengthInBits)
{
    auto keyHandle = GetNativeHandle<NCRYPT_KEY_HANDLE>();
    if (NCryptSetProperty(keyHandle, NCRYPT_LENGTH_PROPERTY, reinterpret_cast<PBYTE>(&lengthInBits), sizeof(lengthInBits), 0) != ERROR_SUCCESS) {
        throw std::runtime_error("Failed to set length property for key");
    }

    return *this;
}

void PersistedKey::SetNativeHandle(NativeHandle handle)
{
    m_nativeHandle = handle;
}
