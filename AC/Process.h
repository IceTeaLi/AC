#include <Windows.h>
#include <string>
#include <vector>
#include <stdexcept>

namespace ac
{
	namespace process
	{
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
			

		private:
			int _start();
			void _createProcess();
			void _createJob(HANDLE hProcess);
			void _stop();
			void _suspend(bool suspend);
			void _processlist(std::vector<DWORD>& list);

		};


		inline void ac::process::Process::start()
		{
			if (_start()==-1)
			{
				throw "Process start failed.";
				CloseHandle(_hJob);
			}
		}

		inline void ac::process::Process::stop()
		{
			try
			{
				_stop();
			}
			catch (const std::exception & e)
			{
				e.what();
				std::vector<DWORD> list;
				_processlist(list);

				bool clear = true;
				for (auto& id : list)
				{
					HANDLE hProcess = OpenProcess(PROCESS_TERMINATE,FALSE,id);
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
			CloseHandle(_hJob);
		}

		inline void ac::process::Process::suspend(bool suspend)
		{
			_suspend(suspend);
		}

	}
}