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




#ifndef GLOBALS_H
#define GLOBALS_H


#include <algorithm>
#include <chrono>
#include <cmath>
#include <cstdint>
#include <dirent.h>
#include <fcntl.h>
#include <fstream>
#include <iomanip>
#include <map>
#include <numeric>
#include <sstream>
#include <string>
#include <vector>
#include <sys/stat.h>
#include <sys/wait.h>

#include <xcb/xcb.h>
#include <xcb/xproto.h>
#include <xcb/xcb_ewmh.h>
#include <xcb/xcb_keysyms.h>
#include <xcb/xcb_image.h>

#include <Imlib2.h>

extern xcb_connection_t*      conn;
extern xcb_screen_t*          screen;
extern xcb_ewmh_connection_t* ewmh;

using namespace std;
static string user;
#define USER \
    user
#define USER_PATH_PREFIX(__address) \
    "/home/" + user + __address
#define USER_PATH_PREFIX_C_STR(__address) \
    string("/home/" + user + __address).c_str()

using u64 = uint64_t;
using u32 = uint32_t;
using u16 = uint16_t;
using u8  = uint8_t;

static constexpr u64 u64MAX = 0xFFFFFFFFFFFFFFFF;
static constexpr u32 u32MAX = 0xFFFFFFFF;
static constexpr u16 u16MAX = 0xFFFF;
static constexpr u8  u8MAX  = 0xFF;

using i64 = int64_t;
using i32 = int32_t;
using i16 = int16_t;
using i8  = int8_t;

using std_size_t = long unsigned int;

static constexpr u32 GC_FONT_MASK = XCB_GC_FOREGROUND | XCB_GC_BACKGROUND | XCB_GC_FONT;
static constexpr u32 GC_MASK      = XCB_GC_FOREGROUND | XCB_GC_BACKGROUND | XCB_GC_GRAPHICS_EXPOSURES;

static auto constexpr DEFAULT_FONT = "7x14";

#endif //GLOBALS_H
