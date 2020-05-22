#include <Windows.h>
#include <string>
#include <vector>
#include <stdexcept>

enum Status
{
	NotRunning,
	Running,
	Suspending
};


class Process
{
	Status _status;
	const std::string _address;
	HANDLE _hJob;

	JOBOBJECT_BASIC_LIMIT_INFORMATION _jobli;
	PROCESS_INFORMATION _pi;
	STARTUPINFO _si;
public:
	Process(const std::string& address);
	~Process();

	inline void start();
	inline void stop();
	inline void suspend(bool suspend);
	inline DWORD wait(DWORD dwTimeout);
	inline const std::string app_address()const { return _address; };

private:
	int _start();
	void _createProcess();
	void _createJob(HANDLE hProcess);
	void _stop();
	void _suspend(bool suspend);
	void _processlist(std::vector<DWORD>& list);
};


inline void Process::start()
{
	if (_start() == -1)
	{
		throw "Process start failed.";	
	}
}

inline void Process::stop()
{
	try
	{
		_stop();
	}
	catch (std::exception& e)
	{
		e.what();
		std::vector<DWORD> list;
		_processlist(list);

		bool clear = true;
		for (auto& id : list)
		{
			HANDLE hProcess = OpenProcess(PROCESS_TERMINATE, FALSE, id);
			if (hProcess != NULL)
				TerminateProcess(hProcess, 0);
			else
				clear = false;
		}
		if (clear == false)
		{
			throw std::runtime_error("Force Terminate Failed,Some processes may not be terminated. ");
		}
	}
}

inline void Process::suspend(bool suspend)
{
	_suspend(suspend);
}

inline DWORD Process::wait(DWORD dwTimeout)
{
	return WaitForSingleObject(_pi.hProcess, dwTimeout);
}

