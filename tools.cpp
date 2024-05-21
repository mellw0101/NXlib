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
// Created by mellw on 5/21/24.
//

#include "globals.h"

#include "tools.h"
#include "lout.h"

namespace NXlib
{
    /**

        @class tools

    */

    /**

        @brief function that @return`s the length of a 'const char*'

    */
    size_t tools::slen(const char* s)
    {
        size_t i(0);
        for(; s[i]; ++i){}
        return i;
    }

    xcb_atom_t tools::get_atom(const char* name)
    {
        xcb_atom_t atom = XCB_NONE;

        xcb_intern_atom_reply_t *reply = xcb_intern_atom_reply
        (
            conn,
            xcb_intern_atom
            (
                conn,
                0,
                tools::slen(name),
                name
            ),
            nullptr
        );

        if (!reply)
        {
            loutE << "reply is nullptr." << loutEND;
            return atom;
        }

        atom = reply->atom;
        free(reply);

        return atom;
    }

    /**

        END @class tools

    */


    /**

        @class tools::iAtomC

    */

    tools::iAtomC::iAtomC(const bool only_if_exists, const char* name)
    : _cookie
    (
        xcb_intern_atom
        (
            conn,
            only_if_exists,
            tools::slen(name),
            name
        )
    )
    {}

    tools::iAtomC::operator xcb_intern_atom_cookie_t() const
    {
        return _cookie;
    }

    tools::iAtomC::operator const xcb_intern_atom_cookie_t&() const
    {
        return this->_cookie;
    };

    tools::iAtomC::operator xcb_intern_atom_cookie_t()
    {
        return _cookie;
    }

    xcb_intern_atom_cookie_t tools::iAtomC::cookie() const
    {
        return _cookie;
    }

    /**

        END @class tools::iAtomC

    */


    /**

        @class tools::iAtomR

    */

    tools::iAtomR::iAtomR(const iAtomC &cookie)
    {
        xcb_intern_atom_reply_t *reply = xcb_intern_atom_reply(conn, cookie.cookie(), nullptr);
        if (!reply)
        {
            // set_ERR_STATE(response_type, pad0, sequence, length, atom);
            return;
        }

        response_type = reply->response_type;
        pad0          = reply->pad0;
        sequence      = reply->sequence;
        length        = reply->sequence;
        atom          = reply->atom;

        free(reply);
    }

    tools::iAtomR::iAtomR(const bool only_if_exists, const char* name)
    {
        xcb_intern_atom_reply_t* reply = xcb_intern_atom_reply(conn, iAtomC(only_if_exists, name).cookie(), nullptr);
        if (!reply)
        {
            // set_ERR_STATE(response_type, pad0, sequence, length, atom);
            return;
        }

        response_type = reply->response_type;
        pad0          = reply->pad0;
        sequence      = reply->sequence;
        length        = reply->sequence;
        atom          = reply->atom;

        free(reply);
    }

    tools::iAtomR::operator xcb_atom_t() const
    {
        return atom;
    }

    tools::iAtomR::operator xcb_atom_t&()
    {
        return atom;
    }

    bool tools::iAtomR::is_not_valid() const
    {
        return (
            response_type == 1 << 7
        &&  pad0          == 1 << 7
        &&  sequence      == 1 << 7
        &&  length        == 1 << 7
        &&  atom          == 1 << 7);
    }

    u32 tools::iAtomR::Atom() const
    {
        return atom;
    }
}