#include "Process.h"
#include "StringConvert.h"
#include <TlHelp32.h>
#include <stdexcept>
#include <iostream>

#define MAX_PROCESS_IDS 20

ac::process::Process::Process(const std::string& address)
	:_address(address)
{
	_hJob = NULL;
	_jobli = { 0 };
	ZeroMemory(&_pi, sizeof(PROCESS_INFORMATION));
	_si.cb = sizeof(STARTUPINFO);
	ZeroMemory(&_si, sizeof(STARTUPINFO));
	_status = NotRunning;
}

ac::process::Process::~Process()
{
	CloseHandle(_pi.hProcess);
	CloseHandle(_pi.hThread);
}

int ac::process::Process::_start()
{
	try{
		_createProcess();
	}catch (const std::exception& e){
		std::cerr << e.what() << std::endl;
		std::cerr << GetLastError() << std::endl;
		return -1;
	}

	try{
		_createJob(_pi.hProcess);
	}catch (const std::exception& e){
		std::cerr << e.what() << std::endl;
		std::cerr << GetLastError() << std::endl;
		TerminateProcess(_pi.hProcess,0);
		return -1;
	}

	if (ResumeThread(_pi.hThread) == -1)
	{
		_stop();
		return -1;
	}	
	_status = Running;
	return 1;
}

void ac::process::Process::_createProcess()
{
	if (_address == "")
		throw std::invalid_argument("Invaild process address was inputed[empty address].");
#ifdef UNICODE
	std::wstring w_str = StringConvert::ansiStringToWideString(_address);
	int ret = CreateProcess(NULL,
		const_cast<LPWSTR>(w_str.c_str()),
		NULL,
		NULL,
		FALSE,
		CREATE_SUSPENDED,
		NULL,
		NULL,
		&_si,
		&_pi
	);
#elif
	int ret = CreateProcess(NULL,
		const_cast<LPSTR>(_address.c_str()),
		NULL,
		NULL,
		FALSE,
		CREATE_SUSPENDED,
		NULL,
		NULL,
		&si,
		&pi
	);
#endif // UNICODE
	if (!ret)
	{
		throw std::runtime_error("Create process failed.");
	}	
}

void ac::process::Process::_createJob(HANDLE hProcess)
{
	_hJob = CreateJobObject(NULL,TEXT("WorkStation"));
	if (_hJob == NULL)
		throw std::runtime_error("Create job Failed.");
	_jobli.LimitFlags = JOB_OBJECT_LIMIT_KILL_ON_JOB_CLOSE;
	SetInformationJobObject(_hJob, JobObjectBasicLimitInformation, &_jobli, sizeof(_jobli));
	auto ret = AssignProcessToJobObject(_hJob, hProcess);
	if (ret == 0)
		throw std::runtime_error("Assign process failed.");
}

void ac::process::Process::_stop()
{
	auto ret = TerminateJobObject(_hJob, 0);
	if (!ret)
		throw std::runtime_error("Terminate Job Failed.");
	_status = NotRunning;
}

void ac::process::Process::_suspend(bool suspend)
{
	std::vector<DWORD> temp_list = {};
	_processlist(temp_list);
	if (temp_list.empty())
		throw std::invalid_argument("Invaild process list was inputed[empty].");
	for (auto& process : temp_list)
	{
		HANDLE hSnapshot = CreateToolhelp32Snapshot(TH32CS_SNAPTHREAD, process);
		if (hSnapshot != INVALID_HANDLE_VALUE)
		{
			THREADENTRY32 te = { sizeof(te) };
			BOOL fOK = Thread32First(hSnapshot, &te);
			while (fOK)
			{
				if (te.th32OwnerProcessID == process)
				{
					HANDLE hThread = OpenThread(THREAD_SUSPEND_RESUME, FALSE, te.th32ThreadID);
					if (hThread != NULL)
					{
						if (suspend)
						{
							SuspendThread(hThread);
						}							
						else 
							ResumeThread(hThread);
						CloseHandle(hThread);
					}
				}
				fOK = Thread32Next(hSnapshot, &te);
			}
		}
		else
			throw std::runtime_error("INVALID_HANDLE_VALUE in suspend.");
		CloseHandle(hSnapshot);
	}
	if (suspend)
		_status = Status::Suspending;
	_status = Status::Running;
}

void ac::process::Process::_processlist(std::vector<DWORD>& list)
{
	std::vector<DWORD> temp_list = {};
	DWORD cb = sizeof(JOBOBJECT_BASIC_PROCESS_ID_LIST) + (MAX_PROCESS_IDS - 1) * sizeof(DWORD);
	PJOBOBJECT_BASIC_PROCESS_ID_LIST _pjblist = reinterpret_cast<PJOBOBJECT_BASIC_PROCESS_ID_LIST>(_alloca(cb));
	_pjblist->NumberOfAssignedProcesses = MAX_PROCESS_IDS;
	QueryInformationJobObject(_hJob, JobObjectBasicProcessIdList, _pjblist, cb, &cb);
	for (unsigned pos = 0; pos < static_cast<unsigned>(_pjblist->NumberOfProcessIdsInList); ++pos)
	{
		temp_list.push_back(static_cast<DWORD>(_pjblist->ProcessIdList[pos]));
	}
	list = temp_list;
}
