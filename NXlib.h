/*
    MIT Open Source License

    Copyright (c) 2024 Melwin Svensson

    Permission is hereby granted, free of charge, to any person obtaining a copy
    of this software and associated documentation files (the "Software"), to deal
    in (the "Software") without restriction, including without limitation the rights
    to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
    copies of (the "Software"), subject to the following conditions:

    The above copyright notice and this permission notice shall be included in all
    copies or substantial portions of (the "Software").

    Any modifications to (the "Software") must include a prominent notice stating that
    (the "Software") was created by Melwin Svensson, and that the modifications were made
    by a different author. The notice must explicitly state that Melwin Svensson created
    the precursor to the current work, and that (the "Software") has been modified since its
    original creation. Additionally, a link to the original source code (https://github.com/mellw0101/mm_wm)
    must be included in a format similar to the following:

    "Melwin Svensson CREATED THE PRECURSOR TO 'the current file' AND IS THE SOLE OWNER AND AUTHOR OF THE PRECURSOR WORK."

    All copies, substantial portions, and derivative works of (the "Software") must be distributed
    under the exact same license (MIT Open Source License) including all clauses stated in this
    notice, ensuring that (the "Software") remains free and open source forever.

    Any distribution of (the "Software") in its entirety or in portions, including
    any derivative works, must retain this license in its entirety and may not be
    re-licensed under any other license than the same MIT Open Source License.
    All clauses laid out in this notice must be upheld in all future licenses for (the "Software").

    Any software that includes (the "Software") or any portions of (the "Software") must also be
    open source and distributed under a license that complies with the Open Source Definition
    (https://opensource.org/osd).

    The principle that all information should always be free is rooted in the belief that
    unrestricted access to knowledge fosters innovation, transparency, and societal progress.
    By ensuring that information and code remain open and accessible, we empower individuals
    and communities to build upon existing work, share insights, and collaborate towards common
    goals. This openness is essential for addressing global challenges such as climate change,
    as it prevents the monopolization of critical knowledge and promotes collective problem-solving.
    Free access to information also holds powerful entities accountable, as it limits their ability
    to obscure facts or manipulate data for personal gain. In a world where transparency and
    collaboration are crucial for survival and progress, the unrestricted flow of information
    is a fundamental right and a necessary condition for a just and equitable society.

    THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
    IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
    FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
    AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
    LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
    OUT OF OR IN CONNECTION WITH (the "Software") OR THE USE OR OTHER DEALINGS IN (the "Software").
*/

//
// Created by mellw on 5/22/24.
//




#ifndef NXLIB_H
#define NXLIB_H


#include <iostream>
#include "globals.h"

using namespace std;


namespace NXlib
{
    typedef struct rgb_color_code_t
    {
        uint8_t r;
        uint8_t g;
        uint8_t b;
    } rgb_color_code_t;

    enum color_t : u8
    {
        BLACK   = 0,
        WHITE   = 1,
        RED     = 2,
        GREEN   = 3,
        BLUE    = 4,
        BLUE_2  = 5,
        BLUE_3  = 6,
        BLUE_4  = 7,
        BLUE_5  = 8,
        BLUE_6  = 9,
        BLUE_7  = 10,
        BLUE_8  = 11,
        BLUE_9  = 12,
        BLUE_10 = 13,
        YELLOW  = 14,
        MAGENTA = 15,
        CYAN = 16,
        GREY = 17,
        DARK_GREY = 18,
        DARK_GREY_2 = 19,
        DARK_GREY_3 = 20,
        DARK_GREY_4 = 21,
        LIGHT_GREY = 22,
        ORANGE = 23,
        BROWN = 24,
        PINK = 25,
        PURPLE = 26,
        NO_COLOR = 27,
        DEFAULT_COLOR = DARK_GREY
    };

    u32           get_input_focus_window();
    u32           open_font(char const* name);
    u32           create_font_gc(u32 window, u8 text_color, u8 background_color, u32 font);
    xcb_char2b_t* to_char2b(char const* input, i32* len);
    std_size_t    calculate_utf8_size(char const* input);         /**

        @brief Calculates the total number of Unicode characters in a UTF-8 string.
            This function helps in determining the exact number of xcb_char2b_t
            structures required to represent the string.

        @param input Pointer to the UTF-8 encoded string.
        @return The total number of Unicode characters in the input string.

    */
    u32           decode_utf8_char(char const** input);           /**

        @brief Decodes a single UTF-8 encoded character from the input string
            and returns the Unicode code point.
            Also advances the input string by the number of bytes used for
            the decoded character.

    */
    xcb_char2b_t* convert_to_char2b(char const* input, i32* len); /*

        Converts a UTF-8 string to an array
        of xcb_char2b_t for xcb_image_text_16

    */
    void          get_window_geo(int16_t* x = nullptr, int16_t* y = nullptr, uint16_t* width = nullptr, uint16_t* height = nullptr);
    u32           get_color(u8 input_color);
    constexpr rgb_color_code_t rgb_code(u8 input_color);
}

#endif //NXLIB_H
