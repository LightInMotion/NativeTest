/* =========================================================================================

   This is an auto-generated file: Any edits you make may be overwritten!

*/

#ifndef BINARYDATA_H_21001989_INCLUDED
#define BINARYDATA_H_21001989_INCLUDED

namespace BinaryData
{
    extern const char*   icon_png;
    const int            icon_pngSize = 13780;

    extern const char*   minifirm_hex;
    const int            minifirm_hexSize = 5194;

    extern const char*   X1FIRM_HEX;
    const int            X1FIRM_HEXSize = 5982;

    extern const char*   X1IDLE_HEX;
    const int            X1IDLE_HEXSize = 192;

    // Points to the start of a list of resource names.
    extern const char* namedResourceList[];

    // Number of elements in the namedResourceList array.
    const int namedResourceListSize = 4;

    // If you provide the name of one of the binary resource variables above, this function will
    // return the corresponding data and its size (or a null pointer if the name isn't found).
    const char* getNamedResource (const char* resourceNameUTF8, int& dataSizeInBytes) throw();
}

#endif
