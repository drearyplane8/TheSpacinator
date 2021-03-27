#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#include <winuser.h>

char * outstring;

int main(int argc, char * argv[]) {
    setbuf(stdout, NULL);
    if(argc != 3) {
        printf("Format: TheSpacinator \"string\" [number of spaces] ");
        return 1;
    }

    char * startString = argv[1];
    int numSpaces = strtol(argv[2], NULL, 10);
    unsigned short len = strlen(startString);
    unsigned newLen = len + len * numSpaces + 1;//each letter, numSpaces for each letter, 1 for null terminator

    int endptr = 0;
    outstring = malloc(newLen);
    outstring[0] = '\0';
    
    for (int i = 0; i < len; ++i) { //loop over each letter in the old string
        outstring[endptr] = startString[i];
        endptr++;
        for (int j = 0; j < numSpaces; ++j) {
            outstring[endptr] = ' ';
            endptr++;
        }
        outstring[endptr] = '\0';
    }
    printf("Copied to clipboard!");

    OpenClipboard(GetActiveWindow());

    char * glob = GlobalAlloc(0, newLen); //make it a global to appease windows.
    memcpy(glob, outstring, newLen); //copy outstring into global

    EmptyClipboard();
    SetClipboardData(CF_TEXT, glob);
    CloseClipboard();


}
