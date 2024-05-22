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

#include "window.h"
#include "lout.h"
#include "tools.h"
#include "color.h"
#include "NXlib.h"

using namespace std;
namespace NXlib
{
    /// @class window

    /// PUBLIC:

    u32 window::get_window_u32() const
    {
        return _window;
    }

    window::operator u32() const
    {
        return this->_window;
    }

    // Overload the assignment operator for 'unsigned int'
    window& window::operator=(u32 const new_window)
    {
        _window = new_window;
        return *this;
    }

    void window::make_window(const window_size_t &window_size)
    {
        _window = xcb_generate_id(conn);
        if (_window == u32MAX) return;

        xcb_create_window
        (
            conn,
            0L,
            _window,
            window_size.parent,
            window_size.x,
            window_size.y,
            window_size.width,
            window_size.height,
            0,
            XCB_WINDOW_CLASS_INPUT_OUTPUT,
            0L,
            0,
            nullptr
        );

        _parent = window_size.parent;
        _x      = window_size.x;
        _y      = window_size.y;
        _width  = window_size.width;
        _height = window_size.height;

        xcb_flush(conn);
    }

    void window::map() const
    {
        xcb_map_window(conn, _window);
        xcb_flush(conn);
    }

    void window::unmap() const
    {
        xcb_unmap_window(conn, _window);
        xcb_flush(conn);
    }

    bool window::is_mapped() const
    {
        xcb_get_window_attributes_cookie_t const cookie = xcb_get_window_attributes(conn, _window);
        xcb_get_window_attributes_reply_t* reply = xcb_get_window_attributes_reply(conn, cookie, nullptr);
        if (!reply)
        {
            // loutEWin << "Unable to get window attributes" << loutEND;
            return false;
        }

        bool const isMapped = (reply->map_state == XCB_MAP_STATE_VIEWABLE);
        free(reply);

        return isMapped;
    }

    // Function to fetch and check the _MOTIF_WM_HINTS property
    bool window::check_frameless_window_hint() const
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

    bool window::is_EWMH_fullscreen() const
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

    bool window::is_active_EWMH_window() const
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

    void window::set_active_EWMH_window() const
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

    void window::set_EWMH_fullscreen_state() const
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

    void window::unset_EWMH_fullscreen_state() const
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

    u32 window::get_transient() const
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

    u32 window::get_pid() const
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
            // loutEWin << "Unable to find _NET_WM_PID atom." << '\n';
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

    string window::get_net_wm_name_by_req() const
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

    void window::change_back_pixel(u32 const pixel) const
    {
        u32 const values[1] = {pixel};
        xcb_change_window_attributes(conn, _window, XCB_CW_BACK_PIXEL, values);
        xcb_flush(conn);
    }

    void window::apply_event_mask(u32 const mask) const
    {
        u32 const data[1] = {mask};
        xcb_configure_window(conn, _window, XCB_CW_EVENT_MASK, data);
        xcb_flush(conn);
    }

    void window::clear() const
    {
        xcb_clear_area(conn, 0, _window, 0, 0, _width, _height);
        xcb_flush(conn);
    }

    void window::set_backround_color(u8 const input_color)
    {
        if (!color) return;
        _color = input_color;
        change_back_pixel(color->get(input_color));
    }

    void window::change_background_color(u8 const input_color)
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
    void window::focus() const
    {
        xcb_set_input_focus(conn, XCB_INPUT_FOCUS_POINTER_ROOT, _window, XCB_CURRENT_TIME);
        xcb_flush(conn);

        set_active_EWMH_window();

        if (!is_active_EWMH_window())
        {
            // loutEWin << "Failed to make window active EWMH window" << loutEND;
            return;
        }
    }

    void window::raise() const
    {
        u32 constexpr data[1] = {XCB_STACK_MODE_ABOVE};
        xcb_configure_window(conn, _window, XCB_CONFIG_WINDOW_STACK_MODE, data);
        xcb_flush(conn);
    }

    void window::reparent(u32 const new_parent, i16 const x, i16 const y) const
    {
        xcb_reparent_window(conn, _window, new_parent, x, y);
        xcb_flush(conn);
    }

    bool window::is_active_input_focus() const
    {
        u32 const focused_window = NXlib::get_input_focus_window();

        if (focused_window == _window)
        {
            return true;
        }

        return false;
    }

    void window::draw_text_8(const char *str, u8 const text_color, u8 const background_color, const char* font_name, i16 const x, i16 const y)
    {
        if (!_font)
        {
            _font = open_font(font_name);
        }

        if (_font_gc)
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

    void window::create_font_gc(u8 const text_color, u8 const background_color, u32 const font)
    {
        _font_gc = xcb_generate_id(conn);
        u32 const data[3] = {color->get(text_color), color->get(background_color), font};

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
}