#include "crypto/KeyStorageProvider.h"
#include "crypto/PersistedKey.h"

#include <string>

#include <Windows.h>
#include <ncrypt.h>
#pragma comment(lib, "ncrypt.lib")


int main()
{
    auto provider = KeyStorageProvider::OpenDefaultProvider();

    // No key name (don't persist key)
    {
        auto key = provider.CreateKey(BCRYPT_RSA_ALGORITHM, nullptr);
        key.Finalize();
        auto keyBlob = provider.ExportKey(key, BCRYPT_RSAPUBLIC_BLOB);
        memset(&keyBlob[0], 0, keyBlob.size());
    }

    // Key name as wide string (for Windows)
    {
        auto key = provider.CreateKey(BCRYPT_RSA_ALGORITHM, L"TestKey");
        key.Finalize();
        auto keyBlob = provider.ExportKey(key, BCRYPT_RSAPUBLIC_BLOB);
        memset(&keyBlob[0], 0, keyBlob.size());
        provider.DeleteKey(key);
    }

    // Key name encoded with UTF-8
    {
        auto key = provider.CreateKey(BCRYPT_RSA_ALGORITHM, u8"TestKey");
        key.Finalize();
        auto keyBlob = provider.ExportKey(key, BCRYPT_RSAPUBLIC_BLOB);
        memset(&keyBlob[0], 0, keyBlob.size());
        provider.DeleteKey(key);
    }

    return 0;
}
