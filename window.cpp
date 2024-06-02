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




#include "globals.h"
#include "NXlib.h"

#include "window.h"

// #include <csignal>

#include "lout.h"
#include "tools.h"

#include <xcb/xcb_cursor.h>
#include <xcb/xcb_icccm.h>


constexpr const char *pointer_from_enum(NXlib::Cursor_t const CURSOR)
{
    switch (CURSOR)
    {
        case NXlib::Cursor_t::arrow:
        {
            return "arrow";
        }

        case NXlib::Cursor_t::hand1:
        {
            return "hand1";
        }

        case NXlib::Cursor_t::hand2:
        {
            return "hand2";
        }

        case NXlib::Cursor_t::watch:
        {
            return "watch";
        }

        case NXlib::Cursor_t::xterm:
        {
            return "xterm";
        }

        case NXlib::Cursor_t::cross:
        {
            return "cross";
        }

        case NXlib::Cursor_t::left_ptr:
        {
            return "left_ptr";
        }

        case NXlib::Cursor_t::right_ptr:
        {
            return "right_ptr";
        }

        case NXlib::Cursor_t::center_ptr:
        {
            return "center_ptr";
        }

        case NXlib::Cursor_t::sb_v_double_arrow:
        {
            return "sb_v_double_arrow";
        }

        case NXlib::Cursor_t::sb_h_double_arrow:
        {
            return "sb_h_double_arrow";
        }

        case NXlib::Cursor_t::fleur:
        {
            return "fleur";
        }

        case NXlib::Cursor_t::question_arrow:
        {
            return "question_arrow";
        }

        case NXlib::Cursor_t::pirate:
        {
            return "pirate";
        }

        case NXlib::Cursor_t::coffee_mug:
        {
            return "coffee_mug";
        }

        case NXlib::Cursor_t::umbrella:
        {
            return "umbrella";
        }

        case NXlib::Cursor_t::circle:
        {
            return "circle";
        }

        case NXlib::Cursor_t::xsb_left_arrow:
        {
            return "xsb_left_arrow";
        }

        case NXlib::Cursor_t::xsb_right_arrow:
        {
            return "xsb_right_arrow";
        }

        case NXlib::Cursor_t::xsb_up_arrow:
        {
            return "xsb_up_arrow";
        }

        case NXlib::Cursor_t::xsb_down_arrow:
        {
            return "xsb_down_arrow";
        }

        case NXlib::Cursor_t::top_left_corner:
        {
            return "top_left_corner";
        }

        case NXlib::Cursor_t::top_right_corner:
        {
            return "top_right_corner";
        }

        case NXlib::Cursor_t::bottom_left_corner:
        {
            return "bottom_left_corner";
        }

        case NXlib::Cursor_t::bottom_right_corner:
        {
            return "bottom_right_corner";
        }

        case NXlib::Cursor_t::sb_left_arrow:
        {
            return "sb_left_arrow";
        }

        case NXlib::Cursor_t::sb_right_arrow:
        {
            return "sb_right_arrow";
        }

        case NXlib::Cursor_t::sb_up_arrow:
        {
            return "sb_up_arrow";
        }

        case NXlib::Cursor_t::sb_down_arrow:
        {
            return "sb_down_arrow";
        }

        case NXlib::Cursor_t::top_side:
        {
            return "top_side";
        }

        case NXlib::Cursor_t::bottom_side:
        {
            return "bottom_side";
        }

        case NXlib::Cursor_t::left_side:
        {
            return "left_side";
        }

        case NXlib::Cursor_t::right_side:
        {
            return "right_side";
        }

        case NXlib::Cursor_t::top_tee:
        {
            return "top_tee";
        }

        case NXlib::Cursor_t::bottom_tee:
        {
            return "bottom_tee";
        }

        case NXlib::Cursor_t::left_tee:
        {
            return "left_tee";
        }

        case NXlib::Cursor_t::right_tee:
        {
            return "right_tee";
        }

        case NXlib::Cursor_t::top_left_arrow:
        {
            return "top_left_arrow";
        }

        case NXlib::Cursor_t::top_right_arrow:
        {
            return "top_right_arrow";
        }

        case NXlib::Cursor_t::bottom_left_arrow:
        {
            return "bottom_left_arrow";
        }

        case NXlib::Cursor_t::bottom_right_arrow:
        {
            return "bottom_right_arrow";
        }

        default:
        {
            return "left_ptr";
        }
    }
}


using namespace std;

namespace NXlib
{
    /// @class window

    auto window::get_window_u32() const -> u32
    {
        return _window;
    }

    window::operator u32() const
    {
        return _window;
    }

    auto window::operator=(u32 const new_window) -> window&
    {
        _window = new_window;
        return *this;
    }

    auto window::create_window(u32 const      parent, i16 const x, i16 const y, u16 const width, u16 const height,
                               u8 const       color, u32 const  event_mask, i32 const flags, void const* border_data,
                               Cursor_t const cursor) -> void
    {
        _parent = parent;
        _x      = x;
        _y      = y;
        _width  = width;
        _height = height;

        make_window();
        set_backround_color(color);

        if (flags & MAP_WINDOW)
        {
            map();
            raise();
        }

        if (flags & RAISE_WINDOW)
        {
            raise();
        }

        if (flags & FOCUS_WINDOW)
        {
            focus();
        }

        if (event_mask > 0)
        {
            apply_event_mask(event_mask);
        }
        if (cursor != Cursor_t::arrow)
        {
            set_pointer(cursor);
        }

        /*if (flags & KEYS_FOR_TYPING) grab_keys_for_typing();*/
        /*if (__flags & FOCUS_INPUT    ) focus_input();
        if (__flags & MAP)
        {
            map();
            raise();
        }

        if (__event_mask > 0) apply_event_mask(&__event_mask);

        if (__border_data != nullptr)
        {
            const int *border_data = static_cast<const int *>(__border_data);
            make_borders(border_data[0], border_data[1], border_data[2]);
        }


        if (__flags & RAISE)
        {
            raise();
        }*/
    }

    auto window::map() const -> void
    {
        xcb_map_window(conn, _window);
        xcb_flush(conn);
    }

    auto window::unmap() const -> void
    {
        xcb_unmap_window(conn, _window);
        xcb_flush(conn);
    }

    auto window::is_mapped() const -> bool
    {
        xcb_get_window_attributes_cookie_t const cookie = xcb_get_window_attributes(conn, _window);
        xcb_get_window_attributes_reply_t* reply = xcb_get_window_attributes_reply(conn, cookie, nullptr);
        if (!reply)
        {
            loutEWin << "Unable to get window attributes" << loutEND;
            return false;
        }

        bool const isMapped = (reply->map_state == XCB_MAP_STATE_VIEWABLE);
        free(reply);

        return isMapped;
    }

    // Function to fetch and check the _MOTIF_WM_HINTS property
    auto window::check_frameless_window_hint() const -> bool
    {
        bool is_frameless = false;
        xcb_atom_t const property = tools::get_atom("_MOTIF_WM_HINTS");

        xcb_get_property_cookie_t const cookie = xcb_get_property
        (
            conn,
            0,
            _window,
            property,
            XCB_ATOM_ANY,
            0,
            sizeof(motif_wm_hints_t) / 4
        );

        if (xcb_get_property_reply_t* reply = xcb_get_property_reply(conn, cookie, nullptr))
        {
            if (reply->type != XCB_NONE && reply->format == 32 && reply->length >= 5)
            {
                if (auto const hints = static_cast<motif_wm_hints_t*>(xcb_get_property_value(reply));
                    hints->decorations == 0)
                {
                    is_frameless = true;
                }
            }
            else
            {
                // loutEWin << "No _MOTIF_WM_HINTS property found." << loutEND;
            }

            free(reply);
        }

        return is_frameless;
    }

    auto window::is_EWMH_fullscreen() const -> bool
    {
        xcb_get_property_cookie_t const cookie = xcb_ewmh_get_wm_state(ewmh, _window);
        xcb_ewmh_get_atoms_reply_t wm_state;

        if (xcb_ewmh_get_wm_state_reply(ewmh, cookie, &wm_state, nullptr) == 1)
        {
            for (unsigned int i = 0; i < wm_state.atoms_len; i++)
            {
                if (wm_state.atoms[i] == ewmh->_NET_WM_STATE_FULLSCREEN)
                {
                    xcb_ewmh_get_atoms_reply_wipe(&wm_state);
                    return true;
                }
            }

            xcb_ewmh_get_atoms_reply_wipe(&wm_state);
        }

        return false;
    }

    auto window::is_active_EWMH_window() const -> bool
    {
        uint32_t active_window = 0;

        /** TODO: check for unchecked foo */
        if (uint8_t const error = xcb_ewmh_get_active_window_reply(ewmh,
            xcb_ewmh_get_active_window(ewmh, 0), &active_window, nullptr); !error)
        {
            // loutE << "xcb_ewmh_get_active_window_reply failed" << loutEND;
        }

        return _window == active_window;
    }

    auto window::set_active_EWMH_window() const -> void
    {
        if (xcb_generic_error_t* error =
            xcb_request_check(conn, xcb_ewmh_set_active_window_checked(ewmh, 0, _window)))
        {
            loutE << "Failed to set " << WINDOW_ID_BY_INPUT(_window) <<
                " as active ewmh window error_code" << error->error_code << loutEND;

            free(error);
        }

        xcb_flush(conn);
    }

    auto window::set_EWMH_fullscreen_state() const -> void
    {
        xcb_change_property
        (
            conn,
            XCB_PROP_MODE_REPLACE,
            _window,
            ewmh->_NET_WM_STATE,
            XCB_ATOM_ATOM,
            32,
            1,
            &ewmh->_NET_WM_STATE_FULLSCREEN
        );

        xcb_flush(conn);
    }

    auto window::unset_EWMH_fullscreen_state() const -> void
    {
        xcb_change_property
        (
            conn,
            XCB_PROP_MODE_REPLACE,
            _window,
            ewmh->_NET_WM_STATE,
            XCB_ATOM_ATOM,
            32,
            0,
            nullptr /* TODO: Check that this works with 'nullptr' instead of '0' */
        );

        xcb_flush(conn);
    }

    auto window::get_transient() const -> u32
    {
        // Default to 0 (no parent)
        u32 t_for = 0;

        xcb_get_property_cookie_t const cookie = xcb_get_property
        (
            conn,
            0,
            _window,
            XCB_ATOM_WM_TRANSIENT_FOR,
            XCB_ATOM_WINDOW,
            0,
            sizeof(u32)
        );

        if (xcb_get_property_reply_t* reply = xcb_get_property_reply(conn, cookie, nullptr); reply && xcb_get_property_value_length(reply) == sizeof(u32))
        {
            t_for = * static_cast<u32*>(xcb_get_property_value(reply));

            // Remember to free the reply
            free(reply);
        }

        return t_for;
    }

    auto window::get_pid() const -> u32
    {
        xcb_atom_t property = XCB_ATOM_NONE;
        xcb_atom_t constexpr type = XCB_ATOM_CARDINAL;

        tools::iAtomC const cookie{false, "_NET_WM_PID"};
        if (tools::iAtomR const reply{cookie}; !reply.is_not_valid())
        {
            property = reply.Atom();
        }

        if (property == XCB_ATOM_NONE)
        {
            loutEWin << "Unable to find _NET_WM_PID atom." << '\n';
            return 0;
        }

        xcb_get_property_cookie_t const prop_cookie = xcb_get_property(conn, 0, _window, property, type, 0, sizeof(u32));
        xcb_get_property_reply_t* prop_reply = xcb_get_property_reply(conn, prop_cookie, nullptr);
        if (!prop_reply)
        {
            loutEWin << "Unable to get window property." << '\n';
            return 0;
        }

        if (xcb_get_property_value_length(prop_reply) == 0)
        {
            free(prop_reply);
            loutEWin << "The window does not have the _NET_WM_PID property." << '\n';
            return 0;
        }

        u32 const pid = * static_cast<u32*>(xcb_get_property_value(prop_reply));
        free(prop_reply);

        return pid;
    }

    auto window::get_net_wm_name_by_req() const -> string
    {
        xcb_ewmh_get_utf8_strings_reply_t wm_name;
        string windowName;

        if (xcb_ewmh_get_wm_name_reply(ewmh, xcb_ewmh_get_wm_name(ewmh, _window), &wm_name, nullptr))
        {
            windowName.assign(wm_name.strings, wm_name.strings_len);
            xcb_ewmh_get_utf8_strings_reply_wipe(&wm_name);
        }

        return windowName;
    }

    auto window::change_back_pixel(u32 const pixel) const -> void
    {
        u32 const values[1] = {pixel};
        xcb_change_window_attributes(conn, _window, XCB_CW_BACK_PIXEL, values);
        xcb_flush(conn);
    }

    auto window::apply_event_mask(u32 const mask) const -> void
    {
        u32 const data[1] = {mask};
        xcb_change_window_attributes
        (
            conn,
            _window,
            XCB_CW_EVENT_MASK,
            data
        );

        xcb_flush(conn);
    }

    auto window::clear() const -> void
    {
        xcb_clear_area(conn, 0, _window, 0, 0, _width, _height);
        xcb_flush(conn);
    }

    auto window::set_backround_color(u8 const input_color) -> void
    {
        _color = input_color;
        change_back_pixel(get_color(input_color));
    }

    auto window::change_background_color(u8 const input_color) -> void
    {
        set_backround_color(input_color);
        clear();
        xcb_flush(conn);
    }

    /**

        @brief avalible 'revert_to' options

        @p XCB_INPUT_FOCUS_NONE
        @p XCB_INPUT_FOCUS_PARENT
        @p XCB_INPUT_FOCUS_POINTER_ROOT

        @p XCB_INPUT_FOCUS_FOLLOW_KEYBOARD NOTE: This is experemental

    */
    auto window::focus() const -> void
    {
        xcb_set_input_focus(conn, XCB_INPUT_FOCUS_POINTER_ROOT, _window, XCB_CURRENT_TIME);
        xcb_flush(conn);

        set_active_EWMH_window();

        if (!is_active_EWMH_window())
        {
            loutEWin << "Failed to make window active EWMH window" << loutEND;
        }
    }

    auto window::raise() const -> void
    {
        u32 constexpr data[1] = {XCB_STACK_MODE_ABOVE};
        xcb_configure_window(conn, _window, XCB_CONFIG_WINDOW_STACK_MODE, data);
        xcb_flush(conn);
    }

    auto window::reparent(u32 const new_parent, i16 const x, i16 const y) const -> void
    {
        xcb_reparent_window(conn, _window, new_parent, x, y);
        xcb_flush(conn);
    }

    auto window::is_active_input_focus() const -> bool
    {
        if (u32 const focused_window = NXlib::get_input_focus_window();
            focused_window == _window)
        {
            return true;
        }

        return false;
    }

    auto window::draw_text_8(char const* str, i16 x, i16 y, u8 text_color, u8 background_color,
                             const char* font_name) -> void
    {
        if (_color == u8MAX)
        {
            loutE << "window has no color, use window.set_background_color(NXlib::'the color you want')" << loutEND;
            return;
        }

        if (background_color == u8MAX)
        {
            background_color = _color;
        }

        if (text_color == u8MAX)
        {
            if (background_color == WHITE)
            {
                text_color = BLACK;
            }
            else
            {
                text_color = WHITE;
            }
        }


        if (!_font)
        {
            _font = open_font(font_name);
        }

        if (!_font_gc)
        {
            create_font_gc(text_color, background_color, _font);
        }

        xcb_image_text_8
        (
            conn,
            tools::slen(str),
            _window,
            _font_gc,
            x,
            y,
            str
        );

        xcb_flush(conn);
    }

    auto window::create_font_gc(u8 const text_color, u8 const background_color, u32 const font) -> void
    {
        _font_gc = xcb_generate_id(conn);
        u32 const data[3] = {get_color(text_color), get_color(background_color), font};

        xcb_create_gc
        (
            conn,
            _font_gc,
            _window,
            GC_FONT_MASK,
            data
        );

        xcb_flush(conn);
    }

    auto window::make_window() -> void
    {
        if ((_window = xcb_generate_id(conn)) == u32MAX)
        {
            loutEWin << "Could not generate id for window" << '\n';
            return;
        }

        xcb_create_window
        (
            conn,
            screen->root_depth,
            _window,
            _parent,
            _x,
            _y,
            _width,
            _height,
            0,
            XCB_WINDOW_CLASS_INPUT_OUTPUT,
            screen->root_visual,
            0,
            nullptr
        );

        xcb_flush(conn);
    }

    auto window::check_event_mask_sum() const -> u32
    {
        xcb_get_window_attributes_cookie_t const cookie = xcb_get_window_attributes(conn, _window);
        xcb_get_window_attributes_reply_t *reply = xcb_get_window_attributes_reply(conn, cookie, nullptr);

        u32 const mask = (reply == nullptr) ? 0 : reply->all_event_masks;
        if (!mask)
        {
            loutE << "Error retriving window attributes" << loutEND;
        }

        free(reply);
        return mask;
    }

    auto window::check_event_mask_codes() const -> vector<xcb_event_mask_t>
    {
        uint32_t const maskSum = check_event_mask_sum();
        vector<xcb_event_mask_t> setMasks;
        for (int mask = XCB_EVENT_MASK_KEY_PRESS; mask <= XCB_EVENT_MASK_OWNER_GRAB_BUTTON; mask <<= 1)
        {
            if (maskSum & mask)
            {
                setMasks.push_back(static_cast<xcb_event_mask_t>(mask));
            }
        }

        return setMasks;
    }

    auto window::is_mask_active(u32 const event_mask) const -> bool
    {
        vector<xcb_event_mask_t> const masks = check_event_mask_codes();
        for (const auto &ev_mask : masks)
        {
            if (ev_mask == event_mask)
            {
                return true;
            }
        }

        return false;
    }

    auto window::grab_keys(initializer_list<pair<u32 const, u16 const>> bindings) const -> void
    {
        xcb_key_symbols_t* keysyms = xcb_key_symbols_alloc(conn);
        if (!keysyms)
        {
            loutE << "keysyms could not get initialized" << loutEND;
            return;
        }

        for (auto const & [key, modier] : bindings)
        {
            if (xcb_keycode_t* keycodes = xcb_key_symbols_get_keycode(keysyms, key))
            {
                for (auto const* kc = keycodes; * kc; kc++)
                {
                    xcb_grab_key
                    (
                        conn,
                        0,
                        _window,
                        modier,
                        *kc,
                        XCB_GRAB_MODE_ASYNC,
                        XCB_GRAB_MODE_ASYNC
                    );

                    xcb_flush(conn);
                }

                free(keycodes);
            }
        }

        xcb_key_symbols_free(keysyms);
        xcb_flush(conn);
    }

    auto window::grab_button(initializer_list<pair<u8, u16>> bindings, bool const owner_events) const -> void
    {
        for (auto const & [button, modifiers] : bindings)
        {
            xcb_grab_button
            (
                conn,
                owner_events,
                _window,
                XCB_EVENT_MASK_BUTTON_PRESS,
                XCB_GRAB_MODE_ASYNC,
                XCB_GRAB_MODE_ASYNC,
                XCB_NONE,
                XCB_NONE,
                button,
                modifiers
            );

            xcb_flush(conn);
        }
    }

    auto window::update_geo_from_req() -> void
    {
        xcb_get_geometry_cookie_t const cookie = xcb_get_geometry_unchecked(conn, _window);
        xcb_get_geometry_reply_t* reply = xcb_get_geometry_reply(conn, cookie, nullptr);
        if (!reply)
        {
            loutEWin << "('xcb_get_geometry_reply') returned a nullptr" << loutEND;
            return;
        }

        _x      = reply->x;
        _y      = reply->y;
        _width  = reply->width;
        _height = reply->height;

        free(reply);
    }

    auto window::update(i16 const x, i16 const y, u16 const width, u16 const height) -> void
    {
        _x      = x;
        _y      = y;
        _width  = width;
        _height = height;
    }

    auto window::create_graphics_exposure_gc() const -> u32
    {
        u32 const data[3] = {screen->black_pixel, screen->white_pixel, 0};
        u32 const gc      = xcb_generate_id(conn);
        xcb_create_gc
        (
            conn,
            gc,
            _window,
            GC_MASK,
            data
        );

        xcb_flush(conn);
        return gc;
    }

    auto window::get_parent() const -> u32
    {
        return _parent;
    }

    auto window::x() const -> i16
    {
        return _x;
    };

    auto window::y() const -> i16
    {
        return _y;
    }

    auto window::width() const -> u16
    {
        return _width;
    }

    auto window::height() const -> u16
    {
        return _height;
    }

    auto window::destroy() const -> void
    {
        xcb_destroy_window(conn, _window);
        xcb_flush(conn);
    }

    auto window::set_pointer(Cursor_t const cursor_type) const -> void
    {
        xcb_cursor_context_t* ctx;
        if (xcb_cursor_context_new(conn, screen, &ctx) < 0)
        {
            loutEWin << "Unable to create cursor context" << '\n';
            return;
        }

        xcb_cursor_t const cursor = xcb_cursor_load_cursor(ctx, pointer_from_enum(cursor_type));
        if (!cursor)
        {
            loutEWin << "Unable to load cursor" << '\n';
            xcb_cursor_context_free(ctx);
            xcb_free_cursor(conn, cursor);
            return;
        }

        u32 const data[1] = {cursor};
        change_attributes(XCB_CW_CURSOR, data);

        xcb_cursor_context_free(ctx);
        xcb_free_cursor(conn, cursor);

        xcb_flush(conn);
    }

    auto window::change_attributes(u32 const mask, void const* data) const -> void
    {
        xcb_change_window_attributes
        (
            conn,
            _window,
            mask,
            data
        );

        xcb_flush(conn);
    }

    auto window::conf_unchecked(u32 const mask, void const* data) const -> void
    {
        xcb_configure_window
        (
            conn,
            _window,
            mask,
            data
        );

        xcb_flush(conn);
    }

    auto window::configure(u32 const mask, void const* data) const -> void
    {
        xcb_configure_window
        (
            conn,
            _window,
            mask,
            data
        );

        xcb_flush(conn);
    }

    auto window::get_min_window_size_hints() const -> min_size_hints_t
    {
        xcb_size_hints_t hints;
        xcb_icccm_get_wm_normal_hints_reply(conn, xcb_icccm_get_wm_normal_hints(conn, _window), &hints, nullptr);

        if (hints.flags & XCB_ICCCM_SIZE_HINT_P_MIN_SIZE)
        {
            min_size_hints_t min_size_hints{hints.min_width, hints.min_width};
            return min_size_hints;
        }

        return {0, 0};
    }

    auto window::kill() const -> void
    {
        tools::iAtomR const p_reply(true, "WM_PROTOCOLS");
        tools::iAtomR const d_reply(false, "WM_DELETE_WINDOW");

        if (p_reply.is_not_valid())
        {
            loutE << "protocols reply is not valid" << loutEND;
            return;
        }

        if (d_reply.is_not_valid())
        {
            loutE << "delete reply is not valid" << loutEND;
            return;
        }

        const uint32_t values[3] = {32, p_reply.Atom(), d_reply.Atom()};
        send_event(KILL_WINDOW, values);

        xcb_flush(conn);
    }

    auto window::send_event(u32 const event_mask, void const* value_list) const -> void
    {
        if (event_mask & XCB_EVENT_MASK_EXPOSURE)
        {
            xcb_expose_event_t expose_event =
            {
                .response_type = XCB_EXPOSE,
                .window = _window,
                .x      = 0,       /* <- Top-left x coordinate of the area to be redrawn                 */
                .y      = 0,       /* <- Top-left y coordinate of the area to be redrawn                 */
                .width  = _width,  /* <- Width of the area to be redrawn                                 */
                .height = _height, /* <- Height of the area to be redrawn                                */
                .count  = 0        /* <- Number of expose events to follow if this is part of a sequence */
            };

            xcb_send_event
            (
                conn,
                false,
                _window,
                XCB_EVENT_MASK_EXPOSURE,
                reinterpret_cast<char*>(&expose_event)
            );
            xcb_flush(conn);
        }

        if (event_mask & XCB_EVENT_MASK_STRUCTURE_NOTIFY)
        {
            auto const* intern_value_list =  static_cast<const u32*>(value_list);

            xcb_configure_notify_event_t event;
            event.response_type     = XCB_CONFIGURE_NOTIFY;
            event.event             = _window;
            event.window            = _window;
            event.above_sibling     = XCB_NONE;
            event.x                 = static_cast<i16>(intern_value_list[0]);
            event.y                 = static_cast<i16>(intern_value_list[1]);
            event.width             = static_cast<u16>(intern_value_list[2]);
            event.height            = static_cast<u16>(intern_value_list[3]);
            event.border_width      = 0;
            event.override_redirect = false;
            event.pad0              = 0;
            event.sequence          = 0;

            xcb_send_event
            (
                conn,
                false,
                _window,
                XCB_EVENT_MASK_STRUCTURE_NOTIFY,
                reinterpret_cast<char*>(&event)
            );

            xcb_flush(conn);
        }

        if (event_mask & KILL_WINDOW)
        {
            auto const* intern_value_list = static_cast<const uint32_t*>(value_list);

            xcb_client_message_event_t ev;
            ev.response_type  = XCB_CLIENT_MESSAGE;
            ev.format         = intern_value_list[0];
            ev.sequence       = 0;
            ev.window         = _window;
            ev.type           = intern_value_list[1];
            ev.data.data32[0] = intern_value_list[2];
            ev.data.data32[1] = XCB_CURRENT_TIME;

            xcb_send_event
            (
                conn,
                true,
                _window,
                XCB_EVENT_MASK_NO_EVENT,
                reinterpret_cast<char*>(&ev)
            );
            xcb_flush(conn);
        }
    }

    auto window::x(u32 const x) -> void
    {
        u32 const data[1] = {x};
        configure(XCB_CONFIG_WINDOW_X, data);

        _x = static_cast<i16>(x);

        xcb_flush(conn);
    }

    auto window::y(u32 const y) -> void
    {
        u32 const data[1] = {y};
        configure(XCB_CONFIG_WINDOW_Y, data);

        _y = static_cast<i16>(y);

        xcb_flush(conn);
    }

    auto window::width(u32 const width) -> void
    {
        u32 const data[1] = {width};
        configure(XCB_CONFIG_WINDOW_WIDTH, data);

        _width = static_cast<u16>(width);

        xcb_flush(conn);
    }

    auto window::height(u32 const height) -> void
    {
        u32 const data[1] = {height};
        configure(XCB_CONFIG_WINDOW_HEIGHT, data);

        _height = static_cast<u16>(height);
        xcb_flush(conn);
    }

    auto window::x_y(u32 const x, u32 const y) -> void
    {
        u32 const data[2] = {x, y};
        configure(XCB_CONFIG_WINDOW_X | XCB_CONFIG_WINDOW_Y, data);

        _x = static_cast<i16>(x);
        _y = static_cast<i16>(y);

        xcb_flush(conn);
    }

    auto window::width_height(u32 const width, u32 const height) -> void
    {
        u32 const data[2] = {width, height};
        configure(XCB_CONFIG_WINDOW_WIDTH | XCB_CONFIG_WINDOW_HEIGHT, data);

        _width  = static_cast<u16>(width);
        _height = static_cast<u16>(height);

        xcb_flush(conn);
    }

    auto window::x_y_width_height(u32 const x, u32 const y, u32 const width, u32 const height) -> void
    {
        u32 const data[4] = {x, y, width, height};
        configure(XCB_CONFIG_WINDOW_X | XCB_CONFIG_WINDOW_Y | XCB_CONFIG_WINDOW_WIDTH | XCB_CONFIG_WINDOW_HEIGHT, data);

        _x      = static_cast<i16>(x);
        _y      = static_cast<i16>(y);
        _width  = static_cast<u16>(width);
        _height = static_cast<u16>(height);

        xcb_flush(conn);
    }

    auto window::x_width_height(u32 const x, u32 const width, u32 const height) -> void
    {
        u32 const data[3] = {x, width, height};
        configure(XCB_CONFIG_WINDOW_X | XCB_CONFIG_WINDOW_WIDTH | XCB_CONFIG_WINDOW_HEIGHT, data);

        _x      = static_cast<i16>(x);
        _width  = static_cast<u16>(width);
        _height = static_cast<u16>(height);
        xcb_flush(conn);
    }

    auto window::y_width_height(u32 const y, u32 const width, u32 const height) -> void
    {
        u32 const data[3] = {y, width, height};
        configure(XCB_CONFIG_WINDOW_Y | XCB_CONFIG_WINDOW_WIDTH | XCB_CONFIG_WINDOW_HEIGHT, data);

        _y      = static_cast<i16>(y);
        _width  = static_cast<u16>(width);
        _height = static_cast<u16>(height);

        xcb_flush(conn);
    }

    auto window::x_width(u32 const x, u32 const width) -> void
    {
        u32 const data[2] = {x, width};
        configure(XCB_CONFIG_WINDOW_X | XCB_CONFIG_WINDOW_WIDTH, data);

        _x      = static_cast<i16>(x);
        _width  = static_cast<u16>(width);

        xcb_flush(conn);
    }

    auto window::x_height(u32 const x, u32 const height) -> void
    {
        u32 const data[2] = {x, height};
        configure(XCB_CONFIG_WINDOW_X | XCB_CONFIG_WINDOW_HEIGHT, data);

        _x      = static_cast<i16>(x);
        _height = static_cast<u16>(height);

        xcb_flush(conn);
    }

    auto window::y_width(u32 const y, u32 const width) -> void
    {
        u32 const data[2] = {y, _width};
        configure(XCB_CONFIG_WINDOW_Y | XCB_CONFIG_WINDOW_WIDTH, data);

        _y      = static_cast<i16>(y);
        _width  = static_cast<u16>(width);

        xcb_flush(conn);
    }

    auto window::y_height(u32 const y, u32 const height) -> void
    {
        u32 const data[2] = {y, height};
        configure(XCB_CONFIG_WINDOW_Y | XCB_CONFIG_WINDOW_HEIGHT, data);

        _y      = static_cast<i16>(y);
        _height = static_cast<u16>(height);
        xcb_flush(conn);
    }

    auto window::x_y_width(u32 const x, uint32_t y, u32 const width) -> void
    {
        u32 const data[3] = {x, y, width};
        configure(XCB_CONFIG_WINDOW_X | XCB_CONFIG_WINDOW_Y | XCB_CONFIG_WINDOW_WIDTH, data);

        _x      = static_cast<i16>(x);
        _y      = static_cast<i16>(y);
        _width  = static_cast<u16>(width);

        xcb_flush(conn);
    }

    auto window::x_y_height(u32 const x, u32 const y, u32 const height) -> void
    {
        u32 const data[3] = {x, y, height};
        configure(XCB_CONFIG_WINDOW_X | XCB_CONFIG_WINDOW_Y | XCB_CONFIG_WINDOW_HEIGHT, data);

        _x      = static_cast<i16>(x);
        _y      = static_cast<i16>(y);
        _height = static_cast<u16>(height);

        xcb_flush(conn);
    }

    auto window::get_best_quality_window_icon(u32* width, u32* height) const -> vector<u32>
    {
        if (auto const ewmh_cookie = xcb_ewmh_init_atoms(conn, ewmh);
            !xcb_ewmh_init_atoms_replies(ewmh, ewmh_cookie, nullptr))
        {
            loutE << "Failed to initialize EWMH atoms" << loutEND;
            free(ewmh_cookie);
            return {};
        }

        xcb_get_property_cookie_t const cookie = xcb_get_property(conn, 0, _window,
            ewmh->_NET_WM_ICON,XCB_ATOM_CARDINAL, 0, UINT32_MAX);

        xcb_get_property_reply_t* reply = xcb_get_property_reply(conn, cookie, nullptr);

        vector<u32>               best_icon_data;
        u32                       best_width  = 0;
        u32                       best_height = 0;

        if (reply && reply->value_len > 0)
        {
            u32         best_size = 0;
            auto const* data      = static_cast<u32*>(xcb_get_property_value(reply));
            u32 const   len       = xcb_get_property_value_length(reply) / sizeof(u32);

            for (uint32_t i = 0; i < len; )
            {
                u32 const intern_width  = data[i++];
                u32 const intern_height = data[i++];
                u32 const size          = intern_width * intern_height;

                if (size > best_size)
                {
                    best_size = size;
                    best_width = intern_width;
                    best_height = intern_height;
                    best_icon_data.assign(data + i, data + i + size);
                }

                i += size; // Move to the next icon in the data
            }
        }

        if (width  != nullptr)
        {
            *width  = best_width;
        }

        if (height != nullptr)
        {
            *height = best_height;
        }

        free(reply);
        return best_icon_data;
    }

    auto window::get_icccm_class() const -> string
    {
        xcb_get_property_cookie_t const cookie = xcb_icccm_get_wm_class(conn, _window);
        xcb_icccm_get_wm_class_reply_t  wm_class_reply;

        string result;

        /* Retrieve the WM_CLASS property */
        if (xcb_icccm_get_wm_class_reply(conn, cookie, &wm_class_reply, nullptr))
        {
            result = string(wm_class_reply.class_name);
            xcb_icccm_get_wm_class_reply_wipe(&wm_class_reply);
        }
        else
        {
            loutEWin << "Failed to retrieve WM_CLASS for window" << '\n';
        }

        return result;
    }

    auto window::make_png_from_icon() const -> void
    {
        if (fs::exists(FS_ACC(ICONFOLDER, (get_icccm_class()))))
        {
            return;
        }

        u32 width;
        u32 height;

        vector<u32> const vec = get_best_quality_window_icon(&width, &height);

        Color_Bitmap const color_bitmap(width, height, vec);
        if (!fs::exists(ICON_FOLDER(get_icccm_class())))
        {
            file_system->create(ICON_FOLDER(get_icccm_class()));
        }

        if (file_system->check_status())
        {
            color_bitmap.exportToPng(PNG_PATH(get_icccm_class()).c_str());
        }
    }

    auto window::set_backround_png(char const* imagePath) const -> void
    {
        auto const image = imlib_load_image(imagePath);
        if (!image)
        {
            loutE << "Failed to load image: " << imagePath << '\n';
            return;
        }

        imlib_context_set_image(image);

        int const originalWidth  = imlib_image_get_width();
        int const originalHeight = imlib_image_get_height();

        // Calculate new size maintaining aspect ratio
        double const aspectRatio = static_cast<double>(originalWidth) / originalHeight;
        int          newHeight   = _height;
        int          newWidth    =  static_cast<int>(newHeight * aspectRatio);

        if (newWidth > _width)
        {
            newWidth  = _width;
            newHeight = static_cast<int>(newWidth / aspectRatio);
        }

        auto const scaledImage = imlib_create_cropped_scaled_image
        (
            0,
            0,
            originalWidth,
            originalHeight,
            newWidth,
            newHeight
        );

        /* Free original image */
        imlib_free_image();
        imlib_context_set_image(scaledImage);

        /* Get the scaled image data */
        u32* data = imlib_image_get_data();

        /* Create an XCB image from the scaled data */
        xcb_image_t* xcb_image = xcb_image_create_native
        (
            conn,
            newWidth,
            newHeight,
            XCB_IMAGE_FORMAT_Z_PIXMAP,
            screen->root_depth,
            nullptr,
            ~0,
            reinterpret_cast<u8*>(data)
        );

        u32 const pixmap = create_pixmap();
        u32 const gc     = create_graphics_exposure_gc();

        xcb_rectangle_t const rect = {0, 0, _width, _height};
        xcb_poly_fill_rectangle
        (
            conn,
            pixmap,
            gc,
            1,
            &rect
        );

        /* Init x and y */
        int x(0), y(0);
        if (newWidth != _width)
        {
            x = (_width - newWidth) / 2;
        }

        /* Calculate position to center the image */
        if (newHeight != _height)
        {
            y = (_height - newHeight) / 2;
        }

        /* Put the scaled image onto the pixmap at the calculated position */
        xcb_image_put
        (
            conn,
            pixmap,
            gc,
            xcb_image,
            static_cast<i16>(x),
            static_cast<i16>(y),
            0
        );

        xcb_flush(conn);

        /* Set the pixmap as the background of the window */
        change_attributes(XCB_CW_BACK_PIXMAP, &pixmap);
        xcb_flush(conn);

        // Free the GC
        xcb_free_gc(conn, gc);
        xcb_flush(conn);
        xcb_image_destroy(xcb_image);

        // Free scaled image
        imlib_free_image();
        clear();
    }

    auto window::create_pixmap() const -> u32
    {
        u32 const pixmap = xcb_generate_id(conn);
        xcb_create_pixmap
        (
            conn,
            screen->root_depth,
            pixmap,
            _window,
            _width,
            _height
        );

        xcb_flush(conn);
        return pixmap;
    }
}
