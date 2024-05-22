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
// Created by mellw on 5/21/24.
//


#include "color.h"

#include "lout.h"

enum COLOR : u8
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

namespace NXlib
{
    rgb_color_code Color::rgb_code(u8 const input_color)
    {
        rgb_color_code color;
        u8 r, g, b;

        switch (input_color)
        {
            case WHITE:
            {
                r = 255; g = 255; b = 255;
                break;
            }

            case BLACK:
            {
                r = 0; g = 0; b = 0;
                break;
            }

            case RED:
            {
                r = 255; g = 0; b = 0;
                break;
            }

            case GREEN:
            {
                r = 0; g = 255; b = 0;
                break;
            }

            case BLUE:
            {
                r = 0; g = 0; b = 255;
                break;
            }

            case BLUE_2:
            {
                r = 0; g = 0; b = 230;
                break;
            }

            case BLUE_3:
            {
                r = 0; g = 0; b = 204;
                break;
            }

            case BLUE_4:
            {
                r = 0; g = 0; b = 178;
                break;
            }

            case BLUE_5:
            {
                r = 0; g = 0; b = 153;
                break;
            }

            case BLUE_6:
            {
                r = 0; g = 0; b = 128;
                break;
            }

            case BLUE_7:
            {
                r = 0; g = 0; b = 102;
                break;
            }

            case BLUE_8:
            {
                r = 0; g = 0; b = 76;
                break;
            }

            case BLUE_9:
            {
                r = 0; g = 0; b = 51;
                break;
            }

            case BLUE_10:
            {
                r = 0; g = 0; b = 26;
                break;
            }

            case YELLOW:
            {
                r = 255; g = 255; b = 0;
                break;
            }

            case CYAN:
            {
                r = 0; g = 255; b = 255;
                break;
            }

            case MAGENTA:
            {
                r = 255; g = 0; b = 255;
                break;
            }

            case GREY:
            {
                r = 128; g = 128; b = 128;
                break;
            }

            case LIGHT_GREY:
            {
                r = 192; g = 192; b = 192;
                break;
            }

            case DARK_GREY:
            {
                r = 64; g = 64; b = 64;
                break;
            }

            case DARK_GREY_2: {
                r = 70; g = 70; b = 70;
                break;
            }

            case DARK_GREY_3:
            {
                r = 76; g = 76; b = 76;
                break;
            }

            case DARK_GREY_4:
            {
                r = 82; g = 82; b = 82;
                break;
            }

            case ORANGE:
            {
                r = 255; g = 165; b = 0;
                break;
            }

            case PURPLE:
            {
                r = 128; g = 0; b = 128;
                break;
            }

            case BROWN:
            {
                r = 165; g = 42; b = 42;
                break;
            }

            case PINK:
            {
                r = 255; g = 192; b = 203;
                break;
            }

            default:
            {
                r = 0; g = 0; b = 0;
                break;
            }
        }

        color.r = r;
        color.g = g;
        color.b = b;

        return color;
    }

    u32 Color::get_color(u8 const input_color)
    {
        xcb_colormap_t const     cmap  = screen->default_colormap;
        rgb_color_code const     ccode = {rgb_code(input_color)};
        xcb_alloc_color_reply_t* r     = xcb_alloc_color_reply
        (
            conn,
            xcb_alloc_color
            (
                conn,
                cmap,
                (ccode.r << 8) | ccode.r,
                (ccode.g << 8) | ccode.g,
                (ccode.b << 8) | ccode.b
            ),
            nullptr
        );

        if (!r)
        {
            // loutE << "xcb_alloc_color_reply_t returned nullptr" << loutEND;
            return 0;
        }

        u32 const pi = r->pixel;
        free(r);

        return pi;
    }

    void Color::init_colors(vector<u8> const &vec)
    {
        for (u8 const &i : vec)
        {
            colorVec.emplace_back(i, get_color(i));
        }
    }

    Color::Color(vector<u8> const &vec)
    {
        init_colors(vec);
    }

    u32 Color::get(u8 const input_color)
    {
        for (auto const & [first, second] : colorVec)
        {
            if (first == input_color) return second;
        }

        return 0;
    }
}