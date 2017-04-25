// QueryKey - enumerates the subkeys of key and its associated values.
//     hKey - key whose subkeys and values are to be enumerated.

#include <windows.h>
#include <stdio.h>
#include <tchar.h>
#include <string.h>

#define MAX_KEY_LENGTH 255
#define MAX_VALUE_NAME 16383
 
void SerialPortEnum(HKEY hKey) 
{ 
    TCHAR    achKey[MAX_KEY_LENGTH];   // buffer for subkey name
    DWORD    cbName;                   // size of name string 
    TCHAR    achClass[MAX_PATH] = TEXT("");  // buffer for class name 
    DWORD    cchClassName = MAX_PATH;  // size of class string 
    DWORD    cSubKeys=0;               // number of subkeys 
    DWORD    cbMaxSubKey;              // longest subkey size 
    DWORD    cchMaxClass;              // longest class string 
    DWORD    cValues;              // number of values for key 
    DWORD    cchMaxValue;          // longest value name 
    DWORD    cbMaxValueData;       // longest value data 
    DWORD    cbSecurityDescriptor; // size of security descriptor 
    FILETIME ftLastWriteTime;      // last write time 
 
    DWORD   i;
    DWORD   retCode;
    DWORD   varData;

    UCHAR   achData[MAX_VALUE_NAME];
    TCHAR   achValue[MAX_VALUE_NAME]; 
    DWORD   cchValue = MAX_VALUE_NAME; 
 
    // get the class name and the value count. 
    retCode = RegQueryInfoKey(
        hKey,                    // key handle 
        achClass,                // buffer for class name 
        &cchClassName,           // size of class string 
        NULL,                    // reserved 
        &cSubKeys,               // number of subkeys 
        &cbMaxSubKey,            // longest subkey size 
        &cchMaxClass,            // longest class string 
        &cValues,                // number of values for this key 
        &cchMaxValue,            // longest value name 
        &cbMaxValueData,         // longest value data 
        &cbSecurityDescriptor,   // security descriptor 
        &ftLastWriteTime);       // last write time 
 
    // enumerate the subkeys, until RegEnumKeyEx fails.
    if (cSubKeys) {
        printf( "\nNumber of subkeys: %lu\n", cSubKeys);

        for (i=0; i<cSubKeys; i++) { 
            cbName = MAX_KEY_LENGTH;
            retCode = RegEnumKeyEx(
                hKey, 
                i,
                achKey, 
                &cbName, 
                NULL, 
                NULL, 
                NULL, 
                &ftLastWriteTime);

            if (retCode == ERROR_SUCCESS)
                _tprintf(TEXT("(%lu) %s\n"), i+1, achKey);
        }
    } 
 
    // enumerate the key values. 
    if (cValues) {
        printf( "\nNumber of values: %lu\n", cValues);

        for (i=0, retCode=ERROR_SUCCESS; i<cValues; i++) { 
            cchValue = MAX_VALUE_NAME; 
            achValue[0] = '\0';
            achData[0] = '\0';
            retCode = RegEnumValue(
                hKey, 
                i, 
                achValue, 
                &cchValue, 
                NULL, 
                NULL,
                achData,
                &varData);
 
            if (retCode == ERROR_SUCCESS )
                _tprintf(TEXT("(%lu) %s\t%s\n"), i+1, achValue, achData);
        }

        if (retCode != ERROR_SUCCESS )
            printf("Error code %lu\n", GetLastError());
    }
}

void __cdecl _tmain(void)
{
   HKEY hTestKey;

   DWORD   retCode;
   retCode = RegOpenKeyEx(
        HKEY_LOCAL_MACHINE,
        TEXT("HARDWARE\\DEVICEMAP\\SERIALCOMM"),
        0,
        KEY_READ,
        &hTestKey);

   if (retCode == ERROR_SUCCESS)
      SerialPortEnum(hTestKey);
   
   RegCloseKey(hTestKey);
}