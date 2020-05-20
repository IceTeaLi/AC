#pragma once

#include <string>
#include <mutex>
#include <deque>
#include <condition_variable>
class InformationCache
{
	std::mutex mx_;
	std::condition_variable cv;
public:
	static InformationCache& get_instance()
	{
		static InformationCache information;
		return information;
	}

	void insert(const std::string& data);
	std::string& get();
	void clear();

private:
	InformationCache()=default;
	~InformationCache()=default;

	std::deque<std::string> cache_;
};

