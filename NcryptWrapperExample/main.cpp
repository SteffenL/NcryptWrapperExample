#include "crypto/KeyStorageProvider.h"
#include "crypto/PersistedKey.h"

#include <Windows.h>
#include <ncrypt.h>
#pragma comment(lib, "ncrypt.lib")


int main()
{
    auto provider = KeyStorageProvider::OpenDefault();

    // No key name (don't persist key)
    {
        auto key = provider.CreateKey(BCRYPT_RSA_ALGORITHM, nullptr);
        key.Finalize();
        auto keyBlob = provider.ExportKey(key, BCRYPT_RSAPUBLIC_BLOB);
        memset(&keyBlob[0], 0, keyBlob.size());
    }

    // UTF-16-encoded key name
    {
        auto key = provider.CreateKey(BCRYPT_RSA_ALGORITHM, L"TestKey");
        key.Finalize();
        auto keyBlob = provider.ExportKey(key, BCRYPT_RSAPUBLIC_BLOB);
        memset(&keyBlob[0], 0, keyBlob.size());
        provider.DeleteKey(key);
    }

    // UTF-8-encoded key name
    {
        auto key = provider.CreateKey(BCRYPT_RSA_ALGORITHM, "TestKey");
        key.Finalize();
        auto keyBlob = provider.ExportKey(key, BCRYPT_RSAPUBLIC_BLOB);
        memset(&keyBlob[0], 0, keyBlob.size());
        provider.DeleteKey(key);
    }

    return 0;
}
