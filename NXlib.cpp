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




#include "NXlib.h"

#include "globals.h"
#include "lout.h"
#include "tools.h"


namespace NXlib
{
    u32 get_input_focus_window()
    {
        xcb_get_input_focus_cookie_t const cookie = xcb_get_input_focus(conn);
        xcb_get_input_focus_reply_t* reply = xcb_get_input_focus_reply(conn, cookie, nullptr);
        if (!reply)
        {
            loutE << "xcb_get_input_focus_reply_t returnd NOT VALID" << loutEND;
            return u32MAX;
        }

        u32 const focused_window = reply->focus;
        free(reply);

        return focused_window;
    }

    u32 open_font(const char* name)
    {
        u32 const font = xcb_generate_id(conn);
        xcb_open_font
        (
            conn,
            font,
            tools::slen(name),
            name
        );

        xcb_flush(conn);
        return font;
    }

    u32 create_font_gc(u32 const window, u8 const text_color, u8 const background_color, u32 const font)
    {
        u32 const font_gc = xcb_generate_id(conn);
        u32 const data[3] = {get_color(text_color), get_color(background_color), font};

        xcb_create_gc
        (
            conn,
            font_gc,
            window,
            GC_FONT_MASK,
            data
        );

        xcb_flush(conn);
        return font_gc;
    }

    std_size_t calculate_utf8_size(char const* input)
    {
        std_size_t count = 0;
        while (*input != '\0')
        {
            auto const* str = reinterpret_cast<const unsigned char*>(input);

            // 1-byte character
            if (str[0] <= 0x7F)
            {
                input += 1;
            }
            else if ((str[0] & 0xE0) == 0xC0) // 2-byte character
            {
                input += 2;
            }
            // 3-byte character
            else if ((str[0] & 0xF0) == 0xE0)
            {
                input += 3;
            }
            // 4-byte character
            else if ((str[0] & 0xF8) == 0xF0)
            {
                input += 4;
            }
            // Invalid UTF-8, assume 1-byte to move past the invalid byte
            else
            {
                input += 1;
            }

            count++;
        }

        return count;
    }

    xcb_char2b_t* to_char2b(const char* input, i32* len)
    {
        std_size_t const max_chars = calculate_utf8_size(input);

        auto* char2b = static_cast<xcb_char2b_t *>(malloc(max_chars * sizeof(xcb_char2b_t)));
        if (char2b == nullptr)
        {
            // Handle memory allocation failure
            *len = 0;
            return nullptr;
        }

        int count = 0;
        while (*input != '\0' && count < max_chars)
        {
            u32 const codepoint = decode_utf8_char(&input);

            // Convert Unicode codepoint to xcb_char2b_t
            char2b[count].byte1 = (codepoint >> 8) & 0xFF;
            char2b[count].byte2 = codepoint & 0xFF;
            count++;
        }

        // Actual number of characters converted
        *len = count;

        return char2b;
    }

    u32 decode_utf8_char(char const** input)
    {
        auto const* str = reinterpret_cast<const unsigned char*>(*input);
        uint32_t codepoint = 0;

        /* 1-byte character */
        if (str[0] <= 0x7F)
        {
            codepoint = str[0];
            *input += 1;
        }
        /* 2-byte character */
        else if ((str[0] & 0xE0) == 0xC0)
        {
            codepoint = ((str[0] & 0x1F) << 6) | (str[1] & 0x3F);
            *input += 2;
        }
        /* 3-byte character */
        else if ((str[0] & 0xF0) == 0xE0)
        {
            codepoint = ((str[0] & 0x0F) << 12) | ((str[1] & 0x3F) << 6) | (str[2] & 0x3F);
            *input += 3;
        }
        /* 4-byte character (will not be fully represented in UCS-2) */
        else if ((str[0] & 0xF8) == 0xF0)
        {
            // Replacement character, as UCS-2 cannot represent this
            codepoint = 0xFFFD;
            *input += 4;
        }
        /* Invalid UTF-8, return replacement character */
        else
        {
            codepoint = 0xFFFD;

            // Advance past the invalid byte
            *input += 1;
        }

        return codepoint;
    }

    xcb_char2b_t* convert_to_char2b(char const* input, i32* len)
    {
        std_size_t const utf8_len = tools::slen(input);

        // Maximum possible number of characters (all 1-byte)
        std_size_t const max_chars = utf8_len;

        auto const char2b = static_cast<xcb_char2b_t*>(malloc(max_chars * sizeof(xcb_char2b_t)));
        i32 count = 0;
        while (*input != '\0' && count < max_chars)
        {
            u32 const codepoint = decode_utf8_char(&input);

            // Convert Unicode codepoint to xcb_char2b_t
            char2b[count].byte1 = (codepoint >> 8) & 0xFF;
            char2b[count].byte2 = codepoint & 0xFF;
            count++;
        }

        // Actual number of characters converted
        *len = count;

        return char2b;
    }

    void geo(u32 const window, i16* x = nullptr, i16* y = nullptr, u16* width = nullptr, u16* height = nullptr)
    {
        xcb_get_geometry_cookie_t const cookie = xcb_get_geometry_unchecked(conn, window);
        xcb_get_geometry_reply_t *reply = xcb_get_geometry_reply(conn, cookie, nullptr);
        if (!reply)
        {
            loutE << WINDOW_ID_BY_INPUT(window) << "('xcb_get_geometry_reply') returned a nullptr" << loutEND;
            return;
        }

        if (x     ) *x      = reply->x;
        if (y     ) *y      = reply->y;
        if (width ) *width  = reply->width;
        if (height) *height = reply->height;

        free(reply);
    }

    u32 get_color(u8 const input_color)
    {
        xcb_colormap_t const     cmap  = screen->default_colormap;
        rgb_color_code_t const     ccode = rgb_code(input_color);
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
            loutE << "xcb_alloc_color_reply_t returned nullptr" << loutEND;
            return 0;
        }

        u32 const pi = r->pixel;
        free(r);

        return pi;
    }

    void File_System::create(const string& path, create_type_t const type)
    {
        if (type == FOLDER)
        {
            bool create_bool = false;

            if (!fs::exists(path))
            {
                loutI << "dir:" << loutPath(path) << " does not exist creating dir" << loutEND;
                try
                {
                    create_bool = fs::create_directory(path);
                }
                catch (exception& e)
                {
                    loutE << "Failed to create dir:" << loutPath(path) << " error: " << e.what() << loutEND;
                    status = false;
                }

                if (create_bool == true)
                {
                    loutI << "Successfully created dir:" << loutPath(path) << '\n';
                    status = true;
                }
            }

            if (!fs::is_directory(path))
            {
                bool remove_bool = false;
                loutI << "dir:" << loutPath(path) << " exists but is not a dir deleting and remaking as dir" << loutEND;

                try
                {
                    remove_bool = fs::remove(path);
                }
                catch (exception& e)
                {
                    loutE << "Failed to remove non-dir:" << loutPath(path) << " error: " << e.what() << loutEND;
                    status = false;
                }

                if (remove_bool == true)
                {
                    try
                    {
                        create_bool = fs::create_directory(path);
                    }
                    catch (exception& e)
                    {
                        loutE << "Failed to create dir:" << loutPath(path) << " error: " << e.what() << loutEND;
                        status = false;
                    }

                    if (create_bool == true)
                    {
                        loutI << "Successfully created dir:" << loutPath(path) << loutEND;
                        status = false;
                    }
                }
            }
        }
    }

    void File_System::init_check()
    {
        create(config_folder);
        create(icon_folder);
    }

    bool File_System::check_status() const
    {
        return status;
    }

    string File_System::accessor(accessor_t const folder, const string& sub_path) const
    {
        if (folder == CONFIG_FOLDER)
        {
            return (config_folder + "/" + sub_path);
        }

        if (folder == ICON_FOLDER)
        {
            return (icon_folder + "/" + sub_path);
        }

        return string{};
    }

    constexpr rgb_color_code_t rgb_code(u8 const input_color)
    {
        rgb_color_code_t color;
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
}