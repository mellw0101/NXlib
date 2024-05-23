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


#include "globals.h"

#include "Key_Codes.h"

#include <map>

using namespace std;

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

    Key_Codes::Key_Codes(): keysyms(nullptr) {}

    Key_Codes::~Key_Codes()
    {
        free(keysyms);
    }

    void Key_Codes::init()
    {
        keysyms = xcb_key_symbols_alloc(conn);
        if (keysyms)
        {
            map<uint32_t, xcb_keycode_t *> const key_map =
            {
                { KEY_CODES::NXlib_KEY_A, &a },
                { KEY_CODES::NXlib_KEY_B, &b },
                { KEY_CODES::NXlib_KEY_C, &c },
                { KEY_CODES::NXlib_KEY_D, &d },
                { KEY_CODES::NXlib_KEY_E, &e },
                { KEY_CODES::NXlib_KEY_F, &f },
                { KEY_CODES::NXlib_KEY_G, &g },
                { KEY_CODES::NXlib_KEY_H, &h },
                { KEY_CODES::NXlib_KEY_I, &i },
                { KEY_CODES::NXlib_KEY_J, &j },
                { KEY_CODES::NXlib_KEY_K, &k },
                { KEY_CODES::NXlib_KEY_L, &l },
                { KEY_CODES::NXlib_KEY_M, &m },
                { KEY_CODES::NXlib_KEY_N, &n },
                { KEY_CODES::NXlib_KEY_O, &o },
                { KEY_CODES::NXlib_KEY_P, &p },
                { KEY_CODES::NXlib_KEY_Q, &q },
                { KEY_CODES::NXlib_KEY_R, &r },
                { KEY_CODES::NXlib_KEY_S, &s },
                { KEY_CODES::NXlib_KEY_T, &t },
                { KEY_CODES::NXlib_KEY_U, &u },
                { KEY_CODES::NXlib_KEY_V, &v },
                { KEY_CODES::NXlib_KEY_W, &w },
                { KEY_CODES::NXlib_KEY_X, &x },
                { KEY_CODES::NXlib_KEY_Y, &y },
                { KEY_CODES::NXlib_KEY_Z, &z },

                { KEY_CODES::NXlib_KEY_SPACE_BAR, &space_bar },
                { KEY_CODES::NXlib_KEY_ENTER,     &enter     },
                { KEY_CODES::NXlib_KEY_DELETE,    &_delete   },

                { KEY_CODES::NXlib_KEY_F11,          &f11       },
                { KEY_CODES::NXlib_KEY_F12,          &f12       },
                { KEY_CODES::NXlib_KEY_N_1,          &n_1       },
                { KEY_CODES::NXlib_KEY_N_2,          &n_2       },
                { KEY_CODES::NXlib_KEY_N_3,          &n_3       },
                { KEY_CODES::NXlib_KEY_N_4,          &n_4       },
                { KEY_CODES::NXlib_KEY_N_5,          &n_5       },
                { KEY_CODES::NXlib_KEY_R_ARROW,      &r_arrow   },
                { KEY_CODES::NXlib_KEY_L_ARROW,      &l_arrow   },
                { KEY_CODES::NXlib_KEY_U_ARROW,      &u_arrow   },
                { KEY_CODES::NXlib_KEY_D_ARROW,      &d_arrow   },
                { KEY_CODES::NXlib_KEY_TAB,          &tab       },
                { KEY_CODES::NXlib_KEY_SUPER_L,      &super_l   },
                { KEY_CODES::NXlib_KEY_MINUS,        &minus     },
                { KEY_CODES::NXlib_KEY_UNDERSCORE,   &underscore}
            };

            for (auto const & [fst, snd] : key_map)
            {
                if (xcb_keycode_t* keycode = xcb_key_symbols_get_keycode(keysyms, fst))
                {
                    *(snd) = *keycode;
                    free(keycode);
                }
            }
        }
    }
}
