// #include "lab1.hh"

// using Lab1 = utcn::ip::Lab1;

#include "nfd.h"
#include <cstdio>
#include <cstdlib>

int main() {
  // Lab1 lab1;
  // lab1.runLab();

  // return 0;
  NFD_Init();

    nfdchar_t *outPath;
    nfdfilteritem_t filterItem[2] = { { "Source code", "c,cpp,cc" }, { "Headers", "h,hpp" } };
    nfdresult_t result = NFD_OpenDialog(&outPath, filterItem, 2, NULL);
    if (result == NFD_OKAY)
    {
        puts("Success!");
        puts(outPath);
        NFD_FreePath(outPath);
    }
    else if (result == NFD_CANCEL)
    {
        puts("User pressed cancel.");
    }
    else 
    {
        printf("Error: %s\n", NFD_GetError());
    }

    NFD_Quit();
    return 0;
}
