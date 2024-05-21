//
// Created by mellw on 5/21/24.
//

#include "globals.h"
#include "window.h"
#include "prof.h"
#include "lout.h"
#include "tools.h"

namespace NXlib
{
    void window::make_window(const window_size_t &window_size)
    {
        _window = xcb_generate_id(conn);
        if (_window == 0L) return;

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

        xcb_flush(conn);
    }

    window::operator unsigned int() const
    {
        return _window;
    }

    // Overload the assignment operator for 'unsigned int'
    window& window::operator=(const unsigned int new_window)
    {
        _window = new_window;
        return* this;
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
        AutoTimer timer(__func__);

        xcb_get_window_attributes_cookie_t const cookie = xcb_get_window_attributes(conn, _window);
        xcb_get_window_attributes_reply_t* reply = xcb_get_window_attributes_reply(conn, cookie, nullptr);
        if (!reply)
        {
            loutEWin << "Unable to get window attributes" << '\n';
            return false;
        }

        bool const isMapped = (reply->map_state == XCB_MAP_STATE_VIEWABLE);
        free(reply);

        return isMapped;
    }

    // Function to fetch and check the _MOTIF_WM_HINTS property
    bool window::check_frameless_window_hint() const
    {
        AutoTimer timer("window::check_frameless_window_hint()");

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
                loutEWin << "No _MOTIF_WM_HINTS property found." << loutEND;
            }

            free(reply);
        }

        return is_frameless;
    }
}