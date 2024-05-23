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
#include "NXlib.h"


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
    enum
    {
        MAP_WINDOW   = 1 << 0,
        RAISE_WINDOW = 1 << 1,
        FOCUS_WINDOW = 1 << 2,
        KILL_WINDOW  = 1 << 3,
    };

    enum class Cursor_t
    {
        arrow,
        hand1,
        hand2,
        watch,
        xterm,
        cross,
        left_ptr,
        right_ptr,
        center_ptr,
        sb_v_double_arrow,
        sb_h_double_arrow,
        fleur,
        question_arrow,
        pirate,
        coffee_mug,
        umbrella,
        circle,
        xsb_left_arrow,
        xsb_right_arrow,
        xsb_up_arrow,
        xsb_down_arrow,
        top_left_corner,
        top_right_corner,
        bottom_left_corner,
        bottom_right_corner,
        sb_left_arrow,
        sb_right_arrow,
        sb_up_arrow,
        sb_down_arrow,
        top_side,
        bottom_side,
        left_side,
        right_side,
        top_tee,
        bottom_tee,
        left_tee,
        right_tee,
        top_left_arrow,
        top_right_arrow,
        bottom_left_arrow,
        bottom_right_arrow
    };

    class window
    {
    public:
        window() = default;

        operator             u32() const;
        window& operator=(u32 new_window); /// Overload the assignment operator with a 'u32'

        void create_window(u32 parent, i16 x, i16 y, u16 width, u16 height,
            u8 color = DEFAULT_COLOR, uint32_t event_mask = 0, i32 flags = 0, const void* border_data = nullptr, Cursor_t cursor = Cursor_t::arrow);

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
        void                                   draw_text_8(char const* str, i16 x, i16 y, u8 text_color = u8MAX, u8 background_color = u8MAX, const char *font_name = DEFAULT_FONT);
        [[nodiscard]] u32                      check_event_mask_sum() const;
        [[nodiscard]] vector<xcb_event_mask_t> check_event_mask_codes() const;
        [[nodiscard]] bool                     is_mask_active(u32 event_mask) const;
        void                                   grab_keys(initializer_list<pair<u32 const, u16 const>> bindings) const;
        void                                   grab_button(initializer_list<pair<u8, u16>> bindings, bool owner_events = false) const;
        void                                   update_geo_from_req();
        void                                   update(i16 x, i16 y, u16 width, u16 height);
        void                                   destroy() const;
        void                                   set_pointer(Cursor_t cursor_type) const;
        void                                   change_attributes(u32 mask, void const* data) const;
        void                                   conf_unchecked(u32 mask, void const* data) const;
        void                                   configure(u32 mask, void const* data) const;
        [[nodiscard]] min_size_hints_t         get_min_window_size_hints() const;
        void                                   kill() const;
        void                                   send_event(u32 event_mask, void const* value_list = nullptr) const;
        vector<u32>                            get_best_quality_window_icon(u32* width = nullptr, u32* height = nullptr) const;

        [[nodiscard]] u32 get_parent() const;
        [[nodiscard]] i16 x() const;
        [[nodiscard]] i16 y() const;
        [[nodiscard]] u16 width() const;
        [[nodiscard]] u16 height() const;

        void x(u32 x);

        void y(u32 y);

        void width(u32 width);
        void height(u32 height);
        void x_y(u32 x, u32 y);
        void width_height(u32 width, u32 height);
        void x_y_width_height(u32 x, u32 y, u32 width, u32 height);
        void x_width_height(u32 x, u32 width, u32 height);
        void y_width_height(u32 y, u32 width, u32 height);
        void x_width(u32 x, u32 width);
        void x_height(u32 x, u32 height);
        void y_width(u32 y, u32 width);
        void y_height(u32 y, u32 height);
        void x_y_width(u32 x, u32 y, u32 width);
        void x_y_height(u32 x, u32 y, u32 height);

    private:
        u32 _window  = 0;
        u32 _parent  = 0;

        i16 _x       = 0;
        i16 _y       = 0;
        u16 _width   = 0;
        u16 _height  = 0;

        u8  _color   = u8MAX;
        u32 _font    = 0;
        u32 _font_gc = 0;


        [[nodiscard]] u32 get_window_u32() const;
        void              create_font_gc(u8 text_color, u8 background_color, u32 font);
        void              make_window();
    };
}


#endif //WINDOW_H
