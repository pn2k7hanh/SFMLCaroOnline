#include <Windows.h>
#include <iostream>
#include "resource.h"

using namespace std;

int main()
{
    // Lấy handle của tệp bitmap từ tài nguyên
    HMODULE hModule = GetModuleHandle(nullptr);
    HRSRC hResource = FindResource(hModule, MAKEINTRESOURCE(IDB_BITMAP1), RT_BITMAP);
    if (hResource == nullptr)
    {
        std::cout << "Khong tim thay tai nguyen bitmap." << std::endl;
        return 1;
    }

    // Tải tệp bitmap lên bộ nhớ
    HGLOBAL hLoadedResource = LoadResource(nullptr, hResource);
    if (hLoadedResource == nullptr)
    {
        std::cout << "Khong the tai tai nguyen bitmap." << std::endl;
        return 1;
    }

    // Khóa tài nguyên để truy cập dữ liệu
    LPVOID pResourceData = LockResource(hLoadedResource);
    if (pResourceData == nullptr)
    {
        std::cout << "Khong the khoa tai nguyen bitmap." << std::endl;
        return 1;
    }

    // Đọc thông tin header của tệp bitmap
    BITMAPINFOHEADER* pBitmapInfoHeader = reinterpret_cast<BITMAPINFOHEADER*>(pResourceData);
    int width = pBitmapInfoHeader->biWidth;
    int height = pBitmapInfoHeader->biHeight;
    int bpp = pBitmapInfoHeader->biBitCount;

    // Tính kích thước dữ liệu pixel
    int dataSize = width * height * (bpp / 8);

    // Địa chỉ bắt đầu của dữ liệu pixel
    BYTE* pPixelData = reinterpret_cast<BYTE*>(pResourceData) + sizeof(BITMAPINFOHEADER);

    // In thông tin chiều dài, chiều rộng và số bit màu của tệp bitmap
    std::cout << "Chieu dai: " << width << std::endl;
    std::cout << "Chieu rong: " << height << std::endl;
    std::cout << "So bit mau: " << bpp << std::endl;

    // In mã màu RGB của từng pixel
    cout << "STARTED" << endl;
    for (int i = 0; i < dataSize; i += (bpp / 8))
    {
        cout << "Hi" << endl;
        BYTE blue = pPixelData[i];
        BYTE green = pPixelData[i + 1];
        BYTE red = pPixelData[i + 2];
        std::cout << "Pixel " << (i / (bpp / 8)) + 1 << ": RGB(" << (int)red << ", " << (int)green << ", " << (int)blue << ")" << std::endl;
    }
    cout << "FINISHED" << endl;

    // Giải phóng tài nguyên đã tải
    FreeResource(hLoadedResource);

    return 0;
}