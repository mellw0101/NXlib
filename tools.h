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




#ifndef TOOLS_H
#define TOOLS_H




#include "globals.h"

#include <xcb/xcb.h>
#include <string>

using namespace std;


namespace NXlib
{
    class tools
    {
    public:
        static size_t     slen(const char* s);
        static xcb_atom_t get_atom(const char* name);
        static string     get_cur_user();

        class iAtomC
        {
        private:
            xcb_intern_atom_cookie_t _cookie{};

        public:
            iAtomC(bool only_if_exists, const char* name);
            explicit operator xcb_intern_atom_cookie_t() const;
            explicit operator const xcb_intern_atom_cookie_t&() const;

            explicit operator xcb_intern_atom_cookie_t();

            [[nodiscard]] xcb_intern_atom_cookie_t cookie() const;
        };

        class iAtomR
        {
        private:
            uint8_t    response_type;
            uint8_t    pad0;
            uint16_t   sequence;
            u32        length;
            xcb_atom_t atom;

        public:
            explicit iAtomR(const iAtomC &cookie);
            iAtomR(bool only_if_exists, const char* name);
            explicit operator xcb_atom_t() const;
            explicit operator xcb_atom_t &();
            [[nodiscard]] bool is_not_valid() const;
            [[nodiscard]] u32 Atom() const;
        };
    };
}


#endif //TOOLS_H
