#include <iostream>
#include <string>
#include <curl/curl.h>
#include <iconv.h>
#include <cstring>
#include <memory>
#include <iomanip>

static size_t WriteCallback(void* contents, size_t size, size_t nmemb, void* userp) {
    size_t totalSize = size * nmemb;
    std::string* str = reinterpret_cast<std::string*>(userp);
    str->append(reinterpret_cast<char*>(contents), totalSize);
    return totalSize;
}

void parsing_code(const std::string& str) {
    size_t pos = 0;
    
    while (true) {
        
        size_t nameStart = str.find("<Name>", pos);
        if (nameStart == std::string::npos) break;
        
        
        size_t nameEnd = str.find("</Name>", nameStart);
        if (nameEnd == std::string::npos) break;
        
        
        std::string name = str.substr(nameStart + 6, nameEnd - nameStart - 6);
        
        
        size_t valueStart = str.find("<Value>", nameEnd);
        if (valueStart == std::string::npos) break;
        
        size_t valueEnd = str.find("</Value>", valueStart);
        if (valueEnd == std::string::npos) break;
        
        
        std::string value = str.substr(valueStart + 7, valueEnd - valueStart - 7);
        

        
        std::cout << "|\x1B[32m"<< std::setw(10) << std::left <<value << "\033[0m";
        std::cout << "  |"<< std::setw(50) << std::left << name << std::endl;
        
        pos = valueEnd + 8;
    }
}

std::string Windows1251ToUtf8(const std::string& windows1251Str) {
    if (windows1251Str.empty()) return "";
    
    iconv_t cd = iconv_open("UTF-8", "WINDOWS-1251");
    if (cd == (iconv_t)-1) {
        return windows1251Str;
    }
    
    
    char* inBuf = const_cast<char*>(windows1251Str.c_str());
    size_t inBytesLeft = windows1251Str.size();
    
    
    size_t outBufferSize = inBytesLeft * 4;
    std::string utf8Str(outBufferSize, '\0');
    char* outBuf = &utf8Str[0];
    size_t outBytesLeft = outBufferSize;
    
    
    size_t result = iconv(cd, &inBuf, &inBytesLeft, &outBuf, &outBytesLeft);
    
    iconv_close(cd);
    
    if (result == (size_t)-1) {
        return windows1251Str;
    }
    
    
    utf8Str.resize(outBufferSize - outBytesLeft);
    return utf8Str;
}

int main(int argc, const char * argv[]) {
//    printf("\x1B[31mTexting\033[0m\t\t");
//    printf("\x1B[32mTexting\033[0m\t\t");
//    printf("\x1B[33mTexting\033[0m\t\t");
//    printf("\x1B[34mTexting\033[0m\t\t");
//    printf("\x1B[35mTexting\033[0m\n");
//    
//    printf("\x1B[36mTexting\033[0m\t\t");
//    printf("\x1B[36mTexting\033[0m\t\t");
//    printf("\x1B[36mTexting\033[0m\t\t");
//    printf("\x1B[37mTexting\033[0m\t\t");
//    printf("\x1B[93mTexting\033[0m\n");
//    
//    printf("\033[3;42;30mTexting\033[0m\t\t");
//    printf("\033[3;43;30mTexting\033[0m\t\t");
//    printf("\033[3;44;30mTexting\033[0m\t\t");
//    printf("\033[3;104;30mTexting\033[0m\t\t");
//    printf("\033[3;100;30mTexting\033[0m\n");
//
//    printf("\033[3;47;35mTexting\033[0m\t\t");
//    printf("\033[2;47;35mTexting\033[0m\t\t");
//    printf("\033[1;47;35mTexting\033[0m\t\t\n\n");
    CURL* curl = curl_easy_init();
    std::string response;
    
    if (curl) {
        curl_easy_setopt(curl, CURLOPT_URL, "http://www.cbr.ru/scripts/XML_daily.asp");
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response);
        curl_easy_setopt(curl, CURLOPT_USERAGENT, "MyApp/1.0");
        
        CURLcode res = curl_easy_perform(curl);
        
        if (res == CURLE_OK) {

            
            std::string utf8String = Windows1251ToUtf8(response);
            parsing_code(utf8String);
            
        } else {
            std::cerr << "Ошибка: " << curl_easy_strerror(res) << std::endl;
        }
        
        curl_easy_cleanup(curl);
    }
        
    return EXIT_SUCCESS;
}
