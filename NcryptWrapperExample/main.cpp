#include "crypto/KeyStorageProvider.h"
#include "crypto/PersistedKey.h"

#include <Windows.h>
#include <ncrypt.h>
#pragma comment(lib, "ncrypt.lib")


int main()
{
    auto keyStorageProvider = KeyStorageProvider::OpenDefault();
    auto key = keyStorageProvider.CreateKey(BCRYPT_RSA_ALGORITHM);
    key.Finalize();
    auto keyBlob = keyStorageProvider.ExportKey(key, BCRYPT_RSAPUBLIC_BLOB);
    memset(&keyBlob[0], 0, keyBlob.size());

    return 0;
}
