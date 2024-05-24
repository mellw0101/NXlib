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




#include "Pid_Manager.h"
#include "lout.h"


namespace NXlib
{
    string Pid_Manager::pid_status(pid_t pid)
    {
        string   line_str = "/proc/" + to_string(pid) + "/status";
        ifstream file;
        file.open(line_str);
        string       var;
        stringstream buffer;
        while (getline(file, var))
        {
            buffer << var << '\n';
        }
        string result;
        result = buffer.str();

        loutI << result << '\n';
        file.close();

        return string{};
    }

    string Pid_Manager::get_process_name_by_pid(pid_t const pid)
    {
        string const path = "/proc/" + std::to_string(pid) + "/comm";

        if (ifstream commFile(path); commFile.good())
        {
            string name;
            getline(commFile, name);
            return name;
        }

        return "Process not found";
    }

    string Pid_Manager::pid_cmd_line(pid_t pid)
    {
        string   line_str = "/proc/" + to_string(pid) + "/cmdline";
        ifstream file;
        file.open(line_str);
        string       var;
        stringstream buffer;
        while (getline(file, var))
        {
            buffer << var << '\n';
        }
        string result;
        result = buffer.str();

        loutI << result << '\n';
        string   test = result;
        ifstream iss(test);
        string   token;

        vector<string> parts;
        while (getline(iss, token, ' '))
        {
            parts.push_back(token);
        }
        if (parts.size() == 1)
        {
            file.close();
            return "mainPid";
        }
        file.close();

        return string{};
    }

    string Pid_Manager::get_correct_process_name(const string& launchName)
    {
        DIR*           dir;
        struct dirent* ent;
        string         path;
        string         line;

        vector<string> parts;
        for (int i(0), start(0); i < launchName.length(); ++i)
        {
            if (launchName[i] == '-')
            {
                string s = launchName.substr(start, i - start);
                parts.push_back(s);
                start = i + 1;
            }

            if (i == (launchName.length() - 1))
            {
                string s = launchName.substr(start, i - start);
                parts.push_back(s);
            }
        }

        for (auto const& part : parts)
        {
            if ((dir = opendir("/proc")) != nullptr)
            {
                while ((ent = readdir(dir)) != nullptr)
                {
                    // Check if the directory is a PID
                    if (ent->d_type == DT_DIR)
                    {
                        path = string("/proc/") + ent->d_name + "/comm";
                        if (ifstream comm(path.c_str()); comm.good())
                        {
                            getline(comm, line);
                            if (line == part)
                            {
                                return part;
                            }
                        }
                    }
                }

                closedir(dir);
            }
        }

        return string{};
    }

    bool Pid_Manager::is_process_running(const pid_t pid)
    {
        struct stat statBuf{};
        string const procPath = "/proc/" + to_string(pid);
        return (stat(procPath.c_str(), &statBuf) == 0);
    }

    bool Pid_Manager::send_signal(pid_t const pid, i32 const signal)
    {
        return kill(pid, signal) == 0;
    }

    bool Pid_Manager::send_sigterm(pid_t const pid, const string &name)
    {
        if (kill(pid, SIGTERM) == -1)
        {
            loutE << ERRNO_MSG("Error sending SIGTERM") << " Process " << name << pid << loutEND;
            return false;
        }

        int   status;
        pid_t result = waitpid(pid, &status, 0); // Wait for the process to change state
        if (result == -1)
        {
            loutE << ERRNO_MSG("Error waiting for process") << " Process " << name << pid << loutEND;
            return false;
        }
        if (!is_process_running(pid)) /* Check if the child exited normally */
        {
            loutI << "Process " << name << pid << " terminated successfully with exit status " <<
                WEXITSTATUS(status) << loutEND;
            return true;
        }
        else
        {
            loutI << "Process " << name << pid << " did not terminate successfully." << loutEND;
            return false;
        }
    }

    void Pid_Manager::send_sigkill(pid_t const pid, string const & name)
    {
        if (send_signal(pid, SIGKILL))
        {
            loutI << "SIGKILL signal sent to process " << name << pid << " for forceful termination." <<
                loutEND;
        }
        else
        {
            loutE << "Failed to send SIGKILL to process " << name << pid << loutEND;
        }
    }

    void Pid_Manager::kill_pid(pid_t const pid, const string& name)
    {
        if (is_process_running(pid))
        {
            if (!send_sigterm(pid, name))
            {
                loutI << "Process " << name << pid << " still running forcefully killing" << loutEND;
                send_sigkill(pid, name);
            }
        }
    }

    void Pid_Manager::check_vec()
    {
        for (int i = 0; i < _pid_vec.size(); ++i)
        {
            if (!is_process_running(_pid_vec[i].pid))
            {
                tools::remove_element_from_vec(_pid_vec, i);
            }
        }
    }

    void Pid_Manager::add_pid(pid_t const pid)
    {
        _pid_vec.push_back({pid, get_process_name_by_pid(pid)});
        check_vec();
    }

    void Pid_Manager::kill_all_pids()
    {
        for (auto const & [pid, name] : _pid_vec)
        {
            if (name == "code") continue;
            kill_pid(pid, name);
        }
    }

    void Pid_Manager::check_pid(pid_t const pid)
    {
        if (pid == 0) return;

        bool found = false;
        for (auto const & [vec_pid, name] : _pid_vec)
        {
            if (pid == vec_pid)
            {
                found = true;
                break;
            }
        }

        if (!found)
        {
            add_pid(pid);
        }
    }

    void Pid_Manager::remove_pid(pid_t const pid)
    {
        for (int i = 0; i < _pid_vec.size(); ++i)
        {
            if (_pid_vec[i].pid == pid)
            {
                tools::remove_element_from_vec(_pid_vec, i);
            }
        }
    }

    void Pid_Manager::list_pids()
    {
        check_vec();
        for (auto const & [pid, name] : _pid_vec)
        {
            loutI << "pid" << pid << " name: " << name << loutEND;
        }

        loutI << "Total running pids" << _pid_vec.size() << loutEND;
    }
}
