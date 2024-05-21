//
// Created by mellw on 5/21/24.
//

#include "TIME.h"

using namespace std;

string TIME::get()
{
    // Get the current time
    const auto & now = chrono::system_clock::now();
    const auto & in_time_t = chrono::system_clock::to_time_t(now);

    // Convert time_t to tm as local time
    tm buf{};
    localtime_r(&in_time_t, &buf);

    // Use stringstream to format the time
    ostringstream ss;
    ss << "[" << put_time(&buf, "%Y-%m-%d %H:%M:%S") << "]";

    return ss.str();
}

string TIME::mili()
{
    // Get the current time point
    const auto now = chrono::system_clock::now();

    // Convert to time_t for seconds and tm for local time
    const auto in_time_t = chrono::system_clock::to_time_t(now);
    tm buf{};
    localtime_r(&in_time_t, &buf);

    // Use stringstream to format the time
    std::ostringstream ss;
    ss << "[" << put_time(&buf, "%Y-%m-%d %H:%M:%S");

    // Calculate milliseconds (now time since epoch minus time_t converted back to time since epoch)
    auto since_epoch = now.time_since_epoch();
    const auto s = chrono::duration_cast<chrono::seconds>(since_epoch);
    since_epoch -= s;
    const auto ms = chrono::duration_cast<chrono::milliseconds>(since_epoch);

    // Append milliseconds to the formatted string, correctly placing the closing square bracket
    ss << "." << setfill('0') << setw(3) << ms.count() << "]";

    return ss.str();
}