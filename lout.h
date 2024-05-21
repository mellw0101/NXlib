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

#ifndef LOUT_H
#define LOUT_H


#include <utility>
#include <string>
#include <cstdint>
#include <mutex>
#include <queue>
#include <cstdint>
#include <string>
#include <sstream>
#include <string>
#include <fstream>
#include <string>
#include <string>
#include <chrono>
#include <iomanip>
#include <sstream>
#include <xcb/xproto.h>
#include <mutex>
#include <queue>

#include "TIME.h"

using namespace std;

// ANSI escape codes for colors
constexpr string log_RED = "\033[1;31m";
constexpr string log_GREEN = "\033[1;32m";
constexpr string log_YELLOW = "\033[1;33m";
constexpr string log_BLUE = "\033[1;34m";
constexpr string log_MEGENTA = "\033[1;35m";
constexpr string log_CYAN = "\033[1;36m";
constexpr string log_WHITE = "\033[1;37m";
constexpr string log_BOLD = "\033[1m";
constexpr string log_UNDERLINE = "\033[4m";
constexpr string log_RESET = "\033[0m";

enum LogLevel
{
	INFO,
	INFO_PRIORITY,
	WARNING,
	ERROR,
	FUNCTION
};

typedef struct {
    string value;
} FuncNameWrapper;

typedef struct {
	string value;
} file_name_obj_t;

typedef struct {
	int line;
} line_obj_t;

typedef struct {
    LogLevel level;
    string function;
    int line;
    string message;
    // Include a timestamp if you prefer logging it to be handled by the logger rather than each log call
} LogMessage;

typedef struct {
    uint32_t value;
} window_obj_t;

typedef struct {
	string value;
} errno_msg_t;

class LogQueue
{
public:
	void push(const LogMessage& message);

	bool try_pop(LogMessage& message);

private:
	mutex mutex_;
	queue<LogMessage> queue_;
};

class Lout
{
/* Defines 	 */
    #define loutNUM(__variable) \
        "(\033[33m" << __variable << "\033[0m)"

	#define loutCFUNC(__calling_function) \
		"calling_function(\033[35m" << __calling_function << "\033[0m)"

	#define lout_error_code(__error_code) \
		"\033[31merror_code\033[0m" << __error_code

	#define loutCEcode(__error_code) \
		lout_error_code(__error_code) << " " << loutCFUNC(__calling_function)

	#define loutPath(__path) \
		"(\033[32m" << __path << "\033[0m)"

	#define loutUser(__user) \
		"(" << log_BLUE << __user << log_RESET << ")"

	#define loutEND \
		'\n'

	#define Var_(_Var) #_Var << ' ' << _Var

public:
/* Methods 	 */
    Lout() = default;

	Lout& operator<<(LogLevel logLevel);

	/*Lout& operator<<(const event_type_obj_t &event_type)
	{
		buffer << "event_type" << '(' << log_BLUE << event_type.value << log_RESET << ')';
		return *this;
	}*/

	Lout& operator<<(const FuncNameWrapper &funcName);

	Lout& operator<<(const line_obj_t &line);

	/**
	 *
	 * Add this into the logMessage function to append it to the log message
	 *
	 */
	Lout& operator<<(const file_name_obj_t &name);

    Lout& operator<<(const window_obj_t &window);

	Lout& operator<<(ostream& (*pf)(ostream&));

	Lout& operator<<(char c);

	Lout& operator<<(const errno_msg_t &err);

    template<typename T>
    enable_if_t<is_arithmetic_v<T>, Lout&>
    operator<<(T value);

    template<typename T>
    enable_if_t<!is_arithmetic_v<T>, Lout&>
    operator<<(const T &message);

private:
/* Variabels */
	LogLevel currentLevel{};
	string currentFunction{};
	string current_file{};
	int current_line{};
	ostringstream buffer{};
	mutex log_mutex;

/* Methods 	 */
	void logMessage()
	{
		lock_guard<mutex> guard(log_mutex);

		if (ofstream file("/home/mellw/nlog", ios::app); file)
		{
			file << TIME::mili() << ":" << getLogPrefix(currentLevel) << ":" << log_YELLOW << "[Line:" << current_line << "]" << log_RESET << ":" << log_MEGENTA << "[" << currentFunction << "]" << log_RESET << ": " << buffer.str() << "\n";
		}
	}

	static string getLogPrefix(LogLevel level);
};
static class Lout lout;

// Utility function for wrapping function names
FuncNameWrapper func(const char* name);

file_name_obj_t file_name(const char* name);

line_obj_t line(int _line);

window_obj_t window_id(uint32_t wid);

errno_msg_t errno_msg(const char* str);

#define FUNC func(__func__)
#define LINE line(__LINE__)
#define FILE_NAME file_name(__FILE__)
#define WINDOW_ID window_id(_window)
#define ERRNO_MSG(__msg) errno_msg(__msg)
#define EVENT_TYPE(__event_type) event_type(__event_type)

#define WINDOW_ID_BY_INPUT(__window) \
	window_id(__window)

/* LOG DEFENITIONS */
#define loutWin(__window) \
	lout << INFO << LINE << FUNC << WINDOW_ID_BY_INPUT(__window) << loutEND

/**
 * @brief Macro to log info to the log file
 *        using the lout class
 */
#define loutI \
    lout << INFO << FUNC << LINE

/**
 *
 * @brief Used to log info related to window actions
 *
 * NOTE: ONLY USE THIS INSIDE THE 'window' CLASS AS VAR '_window' IS A MEMBER
 *
 */
#define loutIWin \
    loutI << WINDOW_ID

/**
 * @brief Macro to log an error to the log file
 *        using the lout class
 */
#define loutE \
	lout << ERROR << FUNC << LINE

#define loutErrno(__msg) \
	loutE << ERRNO_MSG(__msg) << '\n'

/**
 *
 * @brief Used to log errors related to window actions
 *
 * NOTE: ONLY USE THIS INSIDE THE 'window' CLASS AS VAR '_window' IS A MEMBER
 *
 */
#define loutEWin \
    loutE << WINDOW_ID

#define loutEerror_code(__calling_function, __error_code) \
	loutE << loutCFUNC(__calling_function) << " " << lout_error_code(__error_code)

/**
 * @brief Macro to log a warning to the log file
 *        using the lout class
 */
#define loutW \
    lout << WARNING << FUNC << LINE

/**
 *
 * @brief Used to log warnings related to window actions
 *
 * NOTE: ONLY USE THIS INSIDE THE 'window' CLASS AS VAR '_window' IS A MEMBER
 *
 */
#define loutWWin \
    loutW << WINDOW_ID

/**
 * @brief Macro to log priority info to the log file
 *        using the lout class
 */
#define loutIP \
    lout << INFO_PRIORITY << FUNC << LINE

#define loutCUser(__user) \
	loutI << "Current USER" << loutUser(__user) << '\n'


#endif //LOUT_H
