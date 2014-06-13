#include <iostream>
#include <iomanip>
#include <string>

#pragma warning(disable: 4819)
#include "FreeImage.h"

#pragma comment( lib, "FreeImage" )

using namespace std;


struct _565{
    unsigned short operator()(unsigned char r, unsigned char g, unsigned char b, unsigned char a)
    {
        return ((r>>3)<<11)|((g>>2)<<5)|(b>>3);
    }
};

struct _4444{
    unsigned short operator()(unsigned char r, unsigned char g, unsigned char b, unsigned char a)
    {
        r = r*a/255;
        g = g*a/255;
        b = b*a/255;
        return ((r>>4)<<12)|((g>>4)<<8)|(b>>4)<<4|(a>>4);
    }
};




template <typename Convertor>
int output(FIBITMAP* src, const string& name, Convertor cvt)
{
    int w = FreeImage_GetWidth(src);
    int h = FreeImage_GetHeight(src);
    int step = FreeImage_GetBPP(src)/8;

    cout <<"#define " << name << "_W    " << w << endl;
    cout <<"#define " << name << "_H    " << h << endl;

    cout <<"unsigned short " << name << "_data[] = {" << endl;

    for(int y = 0; y < h; y++) {
        BYTE *bytes = (BYTE *)FreeImage_GetScanLine(src, y);
        for(int x = 0; x < w; x++) {
            cout << "0x" << hex << setw(4) << setfill('0') 
                << cvt(bytes[FI_RGBA_RED], bytes[FI_RGBA_GREEN], bytes[FI_RGBA_BLUE],bytes[FI_RGBA_ALPHA])
                << ",";
            bytes += step;
        }
        cout << endl;
    }
    cout << "};" << endl << endl;
    return 0;
}


std::string basename( const std::string& p, const std::string& suffix/*=std::string()*/ )
{
    static const std::string slashes("/\\");
    std::string::size_type beg = p.find_last_of(slashes);

    beg = (beg == std::string::npos) ? 0 : beg + 1;

    std::string::size_type end;
    if (suffix.empty())
    {
        end = p.size();
    }
    else
    {
        end = p.rfind(suffix);
        if (end == std::string::npos)
        {
            end = p.size();
        }
    }
    return p.substr(beg, end-beg);
}

int compile(const string& format, const string filename)
{
    FREE_IMAGE_FORMAT fif = FreeImage_GetFileType(filename.c_str(), 0);
    if(fif == FIF_UNKNOWN) {
        fif = FreeImage_GetFIFFromFilename(filename.c_str());
    }
    // check that the plugin has reading capabilities ...
    if((fif == FIF_UNKNOWN) || !FreeImage_FIFSupportsReading(fif))
        return -1;

    FIBITMAP * src = FreeImage_Load(fif, filename.c_str(), 0);

    std::string base = basename(filename, ".png");

    if (format == "RGB565")
        output(src, base, _565());
    else if (format == "RGBA4444")
        output(src, base, _4444());
    return 0;
}



int main(int argc, char **argv)
{
    if (argc != 3)
        return -1;

    return compile(argv[1], argv[2]);
}
