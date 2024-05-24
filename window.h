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

#include "Bitmap.h"
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

        /// Overload the assignment operator with a 'u32'
        auto operator=(u32 new_window) -> window&;

        auto create_window(u32      parent, i16 x, i16 y, u16 width, u16 height, u8 color = DEFAULT_COLOR,
                           u32      event_mask = 0, i32 flags = 0, void const* border_data = nullptr,
                           Cursor_t cursor = Cursor_t::arrow) -> void;

        auto draw_text_8(char const* str, i16 x, i16 y, u8 text_color = u8MAX,
                         u8          background_color = u8MAX, char const* font_name = DEFAULT_FONT) -> void;

        auto unmap() const -> void;
        auto map()   const -> void;
        auto focus() const -> void;
        auto clear() const -> void;
        auto raise() const -> void;
        auto set_active_EWMH_window() const -> void;
        auto set_EWMH_fullscreen_state() const -> void;
        auto unset_EWMH_fullscreen_state() const -> void;
        auto change_back_pixel(u32 pixel) const -> void;
        auto apply_event_mask(u32 mask) const -> void;
        auto set_backround_color(u8 input_color) -> void;
        auto change_background_color(u8 input_color) -> void;
        auto reparent(u32 new_parent, i16 x, i16 y) const -> void;
        auto grab_keys(initializer_list<pair<u32 const, u16 const>> bindings) const -> void;

        auto grab_button(initializer_list<pair<u8, u16>> bindings, bool owner_events = false) const -> void;
        auto update_geo_from_req() -> void;
        auto update(i16 x, i16 y, u16 width, u16 height) -> void;
        auto destroy() const -> void;
        auto set_pointer(Cursor_t cursor_type) const -> void;
        auto change_attributes(u32 mask, void const* data) const -> void;
        auto conf_unchecked(u32 mask, void const* data) const -> void;
        auto configure(u32 mask, void const* data) const -> void;
        auto kill() const -> void;
        auto send_event(u32 event_mask, void const* value_list = nullptr) const -> void;
        auto get_best_quality_window_icon(u32* width = nullptr, u32* height = nullptr) const -> vector<u32>;
        auto make_png_from_icon() const -> void;
        auto set_backround_png(char const* imagePath) const -> void;


        [[nodiscard]] auto is_mapped() const -> bool;
        [[nodiscard]] auto check_frameless_window_hint() const -> bool;
        [[nodiscard]] auto is_EWMH_fullscreen() const -> bool;
        [[nodiscard]] auto is_active_EWMH_window() const -> bool;
        [[nodiscard]] auto get_transient() const -> u32;
        [[nodiscard]] auto get_pid() const -> u32;
        [[nodiscard]] auto get_net_wm_name_by_req() const -> string;
        [[nodiscard]] bool is_active_input_focus() const;
        [[nodiscard]] auto check_event_mask_sum() const -> u32;
        [[nodiscard]] auto check_event_mask_codes() const -> vector<xcb_event_mask_t>;
        [[nodiscard]] auto is_mask_active(u32 event_mask) const -> bool;
        [[nodiscard]] auto get_min_window_size_hints() const -> min_size_hints_t;
        [[nodiscard]] auto get_icccm_class() const -> string;
        [[nodiscard]] auto create_pixmap() const -> u32;
        [[nodiscard]] auto create_graphics_exposure_gc() const -> u32;
        [[nodiscard]] auto get_parent() const -> u32;
        [[nodiscard]] auto x() const -> i16;
        [[nodiscard]] auto y() const -> i16;
        [[nodiscard]] auto width() const -> u16;
        [[nodiscard]] auto height() const -> u16;

        auto x(u32 x) -> void;
        auto y(u32 y) -> void;
        auto width(u32 width) -> void;
        auto height(u32 height) -> void;
        auto x_y(u32 x, u32 y) -> void;
        auto width_height(u32 width, u32 height) -> void;
        auto x_y_width_height(u32 x, u32 y, u32 width, u32 height) -> void;
        auto x_width_height(u32 x, u32 width, u32 height) -> void;
        auto y_width_height(u32 y, u32 width, u32 height) -> void;
        auto x_width(u32 x, u32 width) -> void;
        auto x_height(u32 x, u32 height) -> void;
        auto y_width(u32 y, u32 width) -> void;
        auto y_height(u32 y, u32 height) -> void;
        auto x_y_width(u32 x, u32 y, u32 width) -> void;
        auto x_y_height(u32 x, u32 y, u32 height) -> void;

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

        auto make_window() -> void;
        auto create_font_gc(u8 text_color, u8 background_color, u32 font) -> void;

        [[nodiscard]] auto get_window_u32() const -> u32;
    };
}


#endif //WINDOW_H
