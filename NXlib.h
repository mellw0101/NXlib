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
#include <sstream>
#include <filesystem>

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

    typedef struct min_size_hints_t
    {
        i32 min_width, min_height;
    } size_hints_t;

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
    u32            decode_utf8_char(char const** input);           /**

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
    rgb_color_code_t rgb_code(u8 input_color);

    class Crypto
    {
        #define HASH(__input) \
            crypro->str_hash_32(__input)

    public:
        /* Methods */
        static vector<u32> hash_str_32_bit_fixed(const string& input)
        {
            hash<string> const hasher;
            auto const         hashedValue = hasher(input);
            vector<u32>        hashSequence(32);
            for (size_t i = 0; i < hashSequence.size(); ++i)
            {
                hashSequence[i] = hashedValue ^ (hashedValue >> (i % (sizeof(size_t) * 8)));
            }

            return hashSequence;
        }

        static string hash_vec_to_str(vector<u32> const &hash_vec)
        {
            stringstream ss;
            for (size_t i = 0; i < hash_vec.size(); ++i)
            {
                // Convert each number to a string and concatenate them
                // You might want to use a delimiter if you need to parse this string back into numbers
                ss << hash_vec[i];
                if (i < hash_vec.size() - 1)
                {
                    ss << ", "; // Add a delimiter (comma) between the numbers
                }
            }
            return ss.str();
        }

        static string str_hash_32(const string &input)
        {
            // Hash the input
            hash<string> constexpr hashFn;
            auto const   hash = hashFn(input);

            // Convert hash to a hexadecimal string
            stringstream hexStream;
            hexStream << hex << hash;

            // Get the hexadecimal string
            string const hexString = hexStream.str();

            /*
                Ensure the hexadecimal string is 32 characters long
                Note: This involves padding and possibly trimming,
                assuming size_t is less than or equal to 64 bits.
            */
            string paddedHexString = string(32 - std::min(32, static_cast<int>(hexString.length())), '0') + hexString;
            if (paddedHexString.length() > 32)
            {
                paddedHexString = paddedHexString.substr(0, 32);
            }

            // Optionally, convert hex to a purely numeric string if needed
            // For simplicity, we'll assume the hex string suffices for demonstration

            return paddedHexString;
        }
    };

    namespace fs = std::filesystem;

    class File_System
    {
        #define FS_ACC(_folder, _sub_path) file_system->accessor(_folder, _sub_path)
        #define ICONFOLDER File_System::ICON_FOLDER
        #define ICON_FOLDER_HASH(__class) FS_ACC(ICONFOLDER, HASH(__class))
        #define ICON_FOLDER(_class) FS_ACC(ICONFOLDER, _class)

        #define PNG_PATH(_class) FS_ACC(ICONFOLDER, _class + "/" + "icon.png")

        #define PNG_HASH(__class) FS_ACC(ICONFOLDER, HASH(__class) + "/" + HASH("png"))

        typedef enum : uint8_t {
            FOLDER
        } create_type_t;

    public:
        string config_folder = USER_PATH_PREFIX("/.config/mwm"), icon_folder = config_folder + "/icons";
        bool   status;

        typedef enum : uint8_t {
            CONFIG_FOLDER,
            ICON_FOLDER
        } accessor_t;

        void                 create(const string& path, create_type_t type = FOLDER);
        void                 init_check();
        [[nodiscard]] bool   check_status() const;
        [[nodiscard]] string accessor(accessor_t folder, const string &sub_path) const;
    };

    static File_System* file_system = nullptr;
}

#endif //NXLIB_H
