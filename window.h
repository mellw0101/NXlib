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
    original creation. Additionally, a link to the original source code (https://github.com/mellw0101)
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

#ifndef WINDOW_H
#define WINDOW_H


#include "globals.h"

#include <string>
#include "lout.h"

using namespace std;

typedef struct window_size_t
{
    u32 parent = 0;
    i16 x      = 0;
    i16 y      = 0;
    u16 width  = 0;
    u16 height = 0;
} window_size_t;

/**

    @brief Struct representing the _MOTIF_WM_HINTS property format

*/
typedef struct motif_wm_hints_t
{
    u32 functions;
    u32 flags;
    u32 decorations;
    i32 input_mode;
    u32 status;
} motif_wm_hints_t;

namespace NXlib
{
    class window
    {
    public:
        explicit             operator u32() const;
        window&              operator=(u32 new_window); /// Overload the assignment operator with a 'u32'
        bool                 operator==(uint32_t id) const;

        void                 make_window(const window_size_t &window_size);
        void                 map() const;
        void                 unmap() const;
        void                 focus() const;
        void                 clear() const;
        void                 raise() const;
        [[nodiscard]] bool   is_mapped() const;
        [[nodiscard]] bool   check_frameless_window_hint() const;
        [[nodiscard]] bool   is_EWMH_fullscreen() const;
        [[nodiscard]] bool   is_active_EWMH_window() const;
        void                 set_active_EWMH_window() const;
        void                 set_EWMH_fullscreen_state() const;
        void                 unset_EWMH_fullscreen_state() const;
        [[nodiscard]] u32    get_transient() const;
        [[nodiscard]] u32    get_pid() const;
        [[nodiscard]] string get_net_wm_name_by_req() const;
        void                 change_back_pixel(u32 pixel) const;
        void                 apply_event_mask(u32 mask) const;
        void                 set_backround_color(u8 input_color);
        void                 change_background_color(u8 input_color);
        void                 reparent(u32 new_parent, i16 x, i16 y) const;
        [[nodiscard]] bool   is_active_input_focus() const;
        void                 draw_text_8(const char* str, u8 text_color, u8 background_color, const char *font_name, i16 x, i16 y);

    private:
        u32 _window  = 0;
        u32 _parent  = 0;

        u8  _color   = 0;
        u32 _font    = 0;
        u32 _font_gc = 0;

        i16 _x       = 0;
        i16 _y       = 0;
        u16 _width   = 0;
        u16 _height  = 0;

        [[nodiscard]] u32 get_window_u32() const;
    };
}


#endif //WINDOW_H
