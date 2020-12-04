/* =========================================================================================

   This is an auto-generated file: Any edits you make may be overwritten!

*/

#pragma once

namespace BinaryData
{
    extern const char*   background_png;
    const int            background_pngSize = 11949;

    extern const char*   dial_png;
    const int            dial_pngSize = 5257;

    extern const char*   finger_wav;
    const int            finger_wavSize = 65536;

    extern const char*   pick_wav;
    const int            pick_wavSize = 70604;

    extern const char*   stick_wav;
    const int            stick_wavSize = 65536;

    extern const char*   finger_png;
    const int            finger_pngSize = 3411;

    extern const char*   finger_press_png;
    const int            finger_press_pngSize = 4165;

    extern const char*   pick_png;
    const int            pick_pngSize = 3260;

    extern const char*   pick_press_png;
    const int            pick_press_pngSize = 3783;

    extern const char*   press_png;
    const int            press_pngSize = 8443;

    extern const char*   stick_png;
    const int            stick_pngSize = 2588;

    extern const char*   stick_press_png;
    const int            stick_press_pngSize = 2635;

    // Number of elements in the namedResourceList and originalFileNames arrays.
    const int namedResourceListSize = 12;

    // Points to the start of a list of resource names.
    extern const char* namedResourceList[];

    // Points to the start of a list of resource filenames.
    extern const char* originalFilenames[];

    // If you provide the name of one of the binary resource variables above, this function will
    // return the corresponding data and its size (or a null pointer if the name isn't found).
    const char* getNamedResource (const char* resourceNameUTF8, int& dataSizeInBytes);

    // If you provide the name of one of the binary resource variables above, this function will
    // return the corresponding original, non-mangled filename (or a null pointer if the name isn't found).
    const char* getNamedResourceOriginalFilename (const char* resourceNameUTF8);
}
