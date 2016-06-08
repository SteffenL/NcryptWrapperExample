#include "KeyStorageProvider.h"
#include "PersistedKey.h"
#include "../common/unicode.h"

#include <stdexcept>

#include <Windows.h>
#include <ncrypt.h>


KeyStorageProvider::KeyStorageProvider(NativeHandle nativeHandle)
    : m_nativeHandle(nativeHandle)
{
}

KeyStorageProvider::~KeyStorageProvider()
{
    auto providerHandle = GetNativeHandle<NCRYPT_PROV_HANDLE>();
    if (providerHandle) {
        NCryptFreeObject(providerHandle);
        providerHandle = NULL;
    }
}

PersistedKey KeyStorageProvider::CreateKey(const wchar_t* algorithm, const wchar_t* keyName)
{
    if (!algorithm) {
        throw std::logic_error("Algorithm cannot be null");
    }

    auto providerHandle = GetNativeHandle<NCRYPT_PROV_HANDLE>();
    NCRYPT_KEY_HANDLE keyHandle;
    if (NCryptCreatePersistedKey(providerHandle, &keyHandle, algorithm, keyName, 0, 0) != ERROR_SUCCESS) {
        throw std::runtime_error("Failed to create persisted key");
    }

    return PersistedKey{ reinterpret_cast<PersistedKey::NativeHandle>(keyHandle) };
}

PersistedKey KeyStorageProvider::CreateKey(const wchar_t* algorithm, const std::string& keyName)
{
    return CreateKey(algorithm, unicode::widen(keyName).c_str());
}

PersistedKey KeyStorageProvider::OpenKey(const wchar_t* keyName)
{
    if (!keyName) {
        throw std::logic_error("Key name cannot be null");
    }

    auto providerHandle = GetNativeHandle<NCRYPT_PROV_HANDLE>();
    NCRYPT_KEY_HANDLE keyHandle;
    if (NCryptOpenKey(providerHandle, &keyHandle, keyName, 0, 0) != ERROR_SUCCESS) {
        throw std::runtime_error("Failed to open key");
    }

    return PersistedKey{ reinterpret_cast<PersistedKey::NativeHandle>(keyHandle) };
}

PersistedKey KeyStorageProvider::OpenKey(const std::string& keyName)
{
    return OpenKey(unicode::widen(keyName).c_str());
}

void KeyStorageProvider::DeleteKey(PersistedKey& key)
{
    auto keyHandle = key.GetNativeHandle<NCRYPT_KEY_HANDLE>();
    if (NCryptDeleteKey(keyHandle, 0) != ERROR_SUCCESS) {
        throw std::runtime_error("Failed to delete key");
    }

    key.SetNativeHandle(NULL);
}

std::vector<uint8_t> KeyStorageProvider::ExportKey(const PersistedKey& key, const wchar_t* blobType)
{
    if (!blobType) {
        throw std::logic_error("Blob type cannot be null");
    }

    std::vector<uint8_t> keyBlob;
    DWORD keySize = 0;
    auto keyHandle = key.GetNativeHandle<NCRYPT_KEY_HANDLE>();

    if (NCryptExportKey(keyHandle, NULL, blobType, NULL, NULL, 0, &keySize, 0) != ERROR_SUCCESS) {
        throw std::runtime_error("Failed to determine size of key to export");
    }

    keyBlob.resize(keySize);
    if (NCryptExportKey(keyHandle, NULL, blobType, NULL, &keyBlob[0], keySize, &keySize, 0) != ERROR_SUCCESS) {
        throw std::runtime_error("Failed to export key");
    }

    return keyBlob;
}

KeyStorageProvider KeyStorageProvider::OpenDefault()
{
    NCRYPT_PROV_HANDLE nativeHandle;
    if (NCryptOpenStorageProvider(&nativeHandle, NULL, 0) != ERROR_SUCCESS) {
        throw std::runtime_error("Failed to open default key storage provider");
    }

    return KeyStorageProvider{ reinterpret_cast<NativeHandle>(nativeHandle) };
}

void KeyStorageProvider::SetNativeHandle(NativeHandle handle)
{
    m_nativeHandle = handle;
}
