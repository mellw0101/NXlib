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
// Created by mellw on 5/23/24.
//

#include "Bitmap.h"

namespace NXlib
{
    void Bitmap::modify(i16 const row, i16 const startCol, i16 const endCol, u8 const value)
    {
        if (row < 0 || row >= height || startCol < 0 || endCol > width)
        {
            loutE << "Invalid row or column indices" << loutEND;
        }

        for (int i = startCol; i < endCol; ++i)
        {
            bitmap[row][i] = value;
        }
    }

    void Bitmap::exportToPng(const char* file_name) const
    {
        FILE *fp = fopen(file_name, "wb");
        if (!fp)
        {
            loutE << "Failed to create PNG file" << loutEND;
            return;
        }

        png_structp png_ptr = png_create_write_struct(PNG_LIBPNG_VER_STRING, nullptr, nullptr, nullptr);
        if (!png_ptr)
        {
            fclose(fp);
            loutE << "Failed to create PNG write struct" << loutEND;
            return;
        }

        png_infop info_ptr = png_create_info_struct(png_ptr);
        if (!info_ptr)
        {
            fclose(fp);
            png_destroy_write_struct(&png_ptr, nullptr);
            loutE << "Failed to create PNG info struct" << loutEND;
            return;
        }

        if (_setjmp ((*png_set_longjmp_fn((png_ptr), longjmp, (sizeof (jmp_buf))))))
        {
            fclose(fp);
            png_destroy_write_struct(&png_ptr, &info_ptr);
            loutE << "Error during PNG creation" << loutEND;
            return;
        }

        png_init_io(png_ptr, fp);
        png_set_IHDR(png_ptr, info_ptr, width, height, 8, PNG_COLOR_TYPE_GRAY,
            PNG_INTERLACE_NONE, PNG_COMPRESSION_TYPE_BASE, PNG_FILTER_TYPE_BASE);

        png_write_info(png_ptr, info_ptr);

        auto const row = new png_byte[width];
        for (int y = 0; y < height; y++)
        {
            for (int x = 0; x < width; x++)
            {
                row[x] = bitmap[y][x] ? 0xFF : 0x00;
            }

            png_write_row(png_ptr, row);
        }

        delete[] row;
        png_write_end(png_ptr, nullptr);
        fclose(fp);
        png_destroy_write_struct(&png_ptr, &info_ptr);
    }

    Bitmap::Bitmap(u16 const width, u16 const height)
    : width(width), height(height), bitmap(height, vector(width, false))
    {}




    Color_Bitmap::Color_Bitmap(u16 const width, u16 const height, const vector<uint32_t>& pixels)
    : width(width), height(height), pixels(pixels)
    {}

    void Color_Bitmap::exportToPng(char const* fileName) const
    {
        FILE *fp = fopen(fileName, "wb");
        if (!fp)
        {
            loutE << "Could not open file: " << fileName << '\n';
            return;
        }

        png_structp png_ptr = png_create_write_struct(PNG_LIBPNG_VER_STRING, nullptr, nullptr, nullptr);
        if (!png_ptr)
        {
            fclose(fp);
            loutE << "Could not create write struct" << '\n';
            return;
        }

        png_infop info_ptr = png_create_info_struct(png_ptr);
        if (!info_ptr)
        {
            fclose(fp);
            png_destroy_write_struct(&png_ptr, nullptr);
            loutE << "Could not create info struct" << '\n';
            return;
        }

        if (_setjmp ((*png_set_longjmp_fn((png_ptr), longjmp, (sizeof (jmp_buf))))))
        {
            fclose(fp);
            png_destroy_write_struct(&png_ptr, &info_ptr);
            loutE << "setjmp failed" << loutEND;
            return;
        }

        png_init_io(png_ptr, fp);
        // Note: Using PNG_COLOR_TYPE_RGB_ALPHA to include alpha channel
        png_set_IHDR(png_ptr, info_ptr, width, height, 8, PNG_COLOR_TYPE_RGB_ALPHA, PNG_INTERLACE_NONE, PNG_COMPRESSION_TYPE_BASE, PNG_FILTER_TYPE_BASE);
        png_write_info(png_ptr, info_ptr);

        // Prepare row pointers
        png_bytep row_pointers[height];
        for (u16 y=0; y < height; y++)
        {
            row_pointers[y] = (png_bytep)&pixels[y * width];
        }

        png_write_image(png_ptr, row_pointers);
        png_write_end(png_ptr, nullptr);

        fclose(fp);
        png_destroy_write_struct(&png_ptr, &info_ptr);
    }
} // NXlib