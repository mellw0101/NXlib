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




#include "prof.h"


using namespace std;


namespace NXlib
{
    /*********************************************************************
    *****************<<          ProfilerStats        >>******************
    *********************************************************************/

    void ProfilerStats::record(const double value)
    {
        values.push_back(value);
    }

    double ProfilerStats::mean() const
    {
        if (values.empty())
        {
            return 0.0;
        }

        const double sum = accumulate(values.begin(), values.end(), 0.0);
        return sum / static_cast<double>(values.size());
    }

    double ProfilerStats::stddev() const
    {
        if (values.size() < 2)
        {
            return 0.0;
        }

        double mean_val = mean();
        const double sq_sum = std::accumulate(values.begin(), values.end(), 0.0, [mean_val](double a, double b) { return a + (b - mean_val) * (b - mean_val); });
        return std::sqrt(sq_sum / static_cast<double>(values.size()));
    }

    double ProfilerStats::min() const
    {
        return values.empty() ? 0.0 : *ranges::min_element(values.begin(), values.end());
    }

    double ProfilerStats::max() const
    {
        return values.empty() ? 0.0 : *ranges::max_element(values.begin(), values.end());
    }

    size_t ProfilerStats::count() const
    {
        return values.size();
    }

    /*********************************************************************
    *****************<<        GlobalProfiler         >>******************
    *********************************************************************/

    void GlobalProfiler::record(string const &name, double const duration)
    {
        stats[name].record(duration);
    }

    string makeNamePadding(const string& s)
    {
        stringstream ss;
        for (int i = 0; (i + s.length()) < 30; ++i)
        {
            ss << ' ';
        }

        return ss.str();
    }

    string mili()
    {
        // Get the current time point
        const auto now = chrono::system_clock::now();

        // Convert to time_t for seconds and tm for local time
        const auto in_time_t = chrono::system_clock::to_time_t(now);
        tm buf{};
        localtime_r(&in_time_t, &buf);

        // Use stringstream to format the time
        ostringstream ss;
        ss << "[" << put_time(&buf, "%Y-%m-%d %H:%M:%S");

        // Calculate milliseconds (now time since epoch minus time_t converted back to time since epoch)
        auto since_epoch = now.time_since_epoch();
        const auto s = std::chrono::duration_cast<std::chrono::seconds>(since_epoch);
        since_epoch -= s;
        const auto ms = std::chrono::duration_cast<std::chrono::milliseconds>(since_epoch);

        // Append milliseconds to the formatted string, correctly placing the closing square bracket
        ss << "." << setfill('0') << setw(3) << ms.count() << "]";

        return ss.str();
    }

    void GlobalProfiler::report(string const &filename) const
    {
        ofstream file(filename, ios::app);
        file << "\n\nProfiling report: " << mili() << '\n';
        for (const auto & [fst, snd] : stats)
        {
            file <<
                fst << makeNamePadding(fst) <<
                ": Mean = " << snd.mean()   << " ms, " << /* makeDoublePadding(pair.second.mean())   << */
                "Stddev = " << snd.stddev() << " ms, " << /* makeDoublePadding(pair.second.stddev()) << */
                "   Min = " << snd.min()    << " ms, " << /* makeDoublePadding(pair.second.min())    << */
                "   Max = " << snd.max()    << " ms, " << /* makeDoublePadding(pair.second.max())    << */
                " Count = " << snd.count()  <<           /* makeDoublePadding(pair.second.count())  << */
            "\n";
        }

        file.close();

        for (const auto &i : stats)
        {
            ofstream File("/home/mellw/gprof/" + i.first, ios::app);
            File <<
                i.second.mean()   << ':' <<
                i.second.stddev() << ':' <<
                i.second.min()    << ':' <<
                i.second.max()    << ':' <<
                i.second.count()  << ':' <<
            "\n";
        }
    }

    GlobalProfiler *GlobalProfiler::createNewGprof()
    {
        return new GlobalProfiler;
    }

    void init_gProf()
    {
        gProf = GlobalProfiler::createNewGprof();
    }

    /*********************************************************************
    *****************<<            AutoTimer          >>******************
    *********************************************************************/

    AutoTimer::AutoTimer(string name)
    : name(move(name)), start(chrono::high_resolution_clock::now())
    {}

    AutoTimer::~AutoTimer()
    {
        const auto end = chrono::high_resolution_clock::now();
        const chrono::duration<double, milli> duration = end - start;
        gProf->record(name, duration.count());
    }

    /* Register at-exit handler to generate the report */
    void setupReportGeneration()
    {
        atexit([]
        {
            gProf->report("/home/mellw/profiling_report.txt");
        });
    }
} // NXlib