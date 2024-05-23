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
#include "color.h"

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
    class KEY_CODES { public: enum
    {
        NXlib_KEY_A          = 0x61,
        NXlib_KEY_B          = 0x62,
        NXlib_KEY_C          = 0x63,
        NXlib_KEY_D          = 0x64,
        NXlib_KEY_E          = 0x65,
        NXlib_KEY_F          = 0x66,
        NXlib_KEY_G          = 0x67,
        NXlib_KEY_H          = 0x68,
        NXlib_KEY_I          = 0x69,
        NXlib_KEY_J          = 0x6a,
        NXlib_KEY_K          = 0x6b,
        NXlib_KEY_L          = 0x6c,
        NXlib_KEY_M          = 0x6d,
        NXlib_KEY_N          = 0x6e,
        NXlib_KEY_O          = 0x6f,
        NXlib_KEY_P          = 0x70,
        NXlib_KEY_Q          = 0x71,
        NXlib_KEY_R          = 0x72,
        NXlib_KEY_S          = 0x73,
        NXlib_KEY_T          = 0x74,
        NXlib_KEY_U          = 0x75,
        NXlib_KEY_V          = 0x76,
        NXlib_KEY_W          = 0x77,
        NXlib_KEY_X          = 0x78,
        NXlib_KEY_Y          = 0x79,
        NXlib_KEY_Z          = 0x7a,
        NXlib_KEY_SPACE_BAR  = 0x20,
        NXlib_KEY_ENTER      = 0xff0d,
        NXlib_KEY_DELETE     = 0xff08,
        NXlib_KEY_F11        = 0xffc8,
        NXlib_KEY_F12        = 0xffc9,
        NXlib_KEY_N_1        = 0x31,
        NXlib_KEY_N_2        = 0x32,
        NXlib_KEY_N_3        = 0x33,
        NXlib_KEY_N_4        = 0x34,
        NXlib_KEY_N_5        = 0x35,
        NXlib_KEY_L_ARROW    = 0xff51,
        NXlib_KEY_U_ARROW    = 0xff52,
        NXlib_KEY_R_ARROW    = 0xff53,
        NXlib_KEY_D_ARROW    = 0xff54,
        NXlib_KEY_TAB        = 0xff09,
        NXlib_KEY_SEMI       = 0x3b,
        NXlib_KEY_QUOTE      = 0x22,
        NXlib_KEY_COMMA      = 0x2c,
        NXlib_KEY_DOT        = 0x2e,
        NXlib_KEY_SLASH      = 0x2f,
        NXlib_KEY_ESC        = 0xff1b,
        NXlib_KEY_SUPER_L    = 0xffeb,
        NXlib_KEY_MINUS      = 0x2d,
        NXlib_KEY_UNDERSCORE = 0x5f,
    };};

    class window
    {
    public:
        window() = default;

        operator             u32() const;
        window& operator=(u32 new_window); /// Overload the assignment operator with a 'u32'

        // void                 make_window(const window_size_t &window_size);
        void create_window(
            u32         parent,
            i16         x,
            i16         y,
            u16         width,
            u16         height,
            u8          color = DEFAULT_COLOR,
            uint32_t    event_mask = 0,
            i32         flags = 0,
            const void* border_data = nullptr
        );
        void                                   map() const;
        void                                   unmap() const;
        void                                   focus() const;
        void                                   clear() const;
        void                                   raise() const;
        [[nodiscard]] bool                     is_mapped() const;
        [[nodiscard]] bool                     check_frameless_window_hint() const;
        [[nodiscard]] bool                     is_EWMH_fullscreen() const;
        [[nodiscard]] bool                     is_active_EWMH_window() const;
        void                                   set_active_EWMH_window() const;
        void                                   set_EWMH_fullscreen_state() const;
        void                                   unset_EWMH_fullscreen_state() const;
        [[nodiscard]] u32                      get_transient() const;
        [[nodiscard]] u32                      get_pid() const;
        [[nodiscard]] string                   get_net_wm_name_by_req() const;
        void                                   change_back_pixel(u32 pixel) const;
        void                                   apply_event_mask(u32 mask) const;
        void                                   set_backround_color(u8 input_color);
        void                                   change_background_color(u8 input_color);
        void                                   reparent(u32 new_parent, i16 x, i16 y) const;
        [[nodiscard]] bool                     is_active_input_focus() const;
        void                                   draw_text_8(const char* str, u8 text_color, u8 background_color, const char *font_name, i16 x, i16 y);
        [[nodiscard]] u32                      check_event_mask_sum() const;
        [[nodiscard]] vector<xcb_event_mask_t> check_event_mask_codes() const;
        [[nodiscard]] bool                     is_mask_active(u32 event_mask) const;
        void                                   grab_keys(initializer_list<pair<u32 const, u16 const>> bindings) const;

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
        void              create_font_gc(u8 text_color, u8 background_color, u32 font);
        void              make_window();
    };
}


#endif //WINDOW_H
