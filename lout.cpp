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

#include "lout.h"

#include <vector>
#include <utility>

// For strerror
#include <cstring>

// For errno
#include <cerrno>
#include <fstream>

#include "TIME.h"
#include "sstream"
#include <type_traits>

using namespace std;


/// @class LogQueue

Lout::Lout() = default;

void LogQueue::push(const LogMessage &message)
{
    lock_guard<mutex> guard(mutex_);
    queue_.push(message);
}

Lout& Lout::operator<<(const event_type_obj_t &event_type)
{
    buffer << "event_type" << '(' << log_BLUE << event_type.value << log_RESET << ')';
    return *this;
}

bool LogQueue::try_pop(LogMessage &message)
{
    lock_guard<mutex> guard(mutex_);
    if (queue_.empty())
    {
        return false;
    }

    message = queue_.front();
    queue_.pop();
    return true;
}

/// END @class LogQueue


/// @class Lout

Lout& Lout::operator<<(const LogLevel logLevel)
{
    currentLevel = logLevel;
    return *this;
}

Lout& Lout::operator<<(const FuncNameWrapper &funcName)
{
    currentFunction = funcName.value;
    return* this;
}

Lout& Lout::operator<<(const line_obj_t &line)
{
    current_line = line.line;

    return *this;
}

Lout& Lout::operator<<(const file_name_obj_t &name)
{
    current_file = name.value;
    return* this;
}

Lout& Lout::operator<<(const window_obj_t &window)
{
    buffer << "[" << log_BLUE << "WINDOW_ID" << log_RESET << ":" << loutNUM(window.value) << "] ";
    return* this;
}

Lout& Lout::operator<<(ostream& (*pf)(ostream&))
{
    if (pf == static_cast<ostream& (*)(ostream&)>(endl))
    {
        logMessage();

        // Reset the buffer for new messages
        buffer = ostringstream();
    }

    return* this;
}

Lout& Lout::operator<<(const char c)
{
    if (c == '\n')
    {
        logMessage();
        buffer = std::ostringstream(); // Reset the buffer for new messages
    }
    else
    {
        buffer << c;
    }

    return* this;
}

Lout& Lout::operator<<(const errno_msg_t &err)
{
    buffer << err.value;
    return* this;
}

template<typename T>
enable_if_t<is_arithmetic_v<T>, Lout&>
Lout::operator<<(T value)
{
    buffer << loutNUM(value);
    return* this;
}

template<typename T>
enable_if_t<!is_arithmetic_v<T>, Lout&>
Lout::operator<<(const T &message)
{
    buffer << message;
    return* this;
}

void Lout::logMessage()
{
    lock_guard<mutex> guard(log_mutex);

    if (ofstream file("/home/mellw/nlog", ios::app); file)
    {
        file << TIME::mili() << ":" << getLogPrefix(currentLevel) << ":" << log_YELLOW << "[Line:" << current_line << "]" << log_RESET << ":" << log_MEGENTA << "[" << currentFunction << "]" << log_RESET << ": " << buffer.str() << "\n";
    }
}

string Lout::getLogPrefix(const LogLevel level)
{
    switch (level)
    {
        case INFO:
        {
            return string(log_GREEN) + "[INFO]" + log_RESET;
        }

        case INFO_PRIORITY:
        {
            return string(log_CYAN) + "[INFO_PRIORITY]" + log_RESET;
        }

        case WARNING:
        {
            return string(log_YELLOW) + "[WARNING]" + log_RESET;
        }

        case ERROR:
        {
            return string(log_RED) + "[ERROR]" + log_RESET;
        }

        case FUNCTION:
        {
            return string(log_MEGENTA) + "[FUNC]" + log_RESET;
        }

        default:
        {
            return to_string(level);
        }
    }
}

/// END @class Lout


/**

    Helper Functions to correcly order elements so that the log
    message always is orderd 'DATE' 'TIME' 'LOG_LEVEL' 'FUNCTION_NAME' 'LINE'

*/

FuncNameWrapper func(const char* name)
{
    return FuncNameWrapper{name};
}

file_name_obj_t file_name(const char* name)
{
    return file_name_obj_t{name};
}

line_obj_t line(const int _line)
{
    return line_obj_t{_line};
}

window_obj_t window_id(const uint32_t wid)
{
    return window_obj_t{wid};
}

errno_msg_t errno_msg(const char* str)
{
    const string s = string(str) + ": " + strerror(errno) + " (errno: " + to_string(errno) + ")";
    return {s};
}
