#include "crypto/KeyStorageProvider.h"
#include "crypto/PersistedKey.h"

#include <Windows.h>
#include <ncrypt.h>
#pragma comment(lib, "ncrypt.lib")


int main()
{
    auto keyStorageProvider = KeyStorageProvider::OpenDefault(); // Something wrong in here?
    auto key = keyStorageProvider.CreateKey(BCRYPT_RSA_ALGORITHM, NULL); // Crashes here
    /*
    Debug Assertion Failed!

    Program: C:\Windows\SYSTEM32\MSVCP140D.dll
    File: c:\program files (x86)\microsoft visual studio 14.0\vc\include\xstring
    Line: 1176

    Expression: invalid null pointer
    */

    key.Finalize();
    auto keyBlob = keyStorageProvider.ExportKey(key, BCRYPT_RSAPUBLIC_BLOB);
    memset(&keyBlob[0], 0, keyBlob.size());

    return 0;
}
