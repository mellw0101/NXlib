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
#include "color.h"


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
        u32 const data[3] = {color->get(text_color), color->get(background_color), font};

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
}