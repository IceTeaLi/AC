#pragma once

#include <string>
#include <mutex>
#include <deque>
#include <condition_variable>

static const std::string CONTROLLER_TAG = "[Controller]";
static const std::string ERROR_TAG = "[ERROR]";
static const std::string GOOD_TAG = "[GOOD]";
static const std::string DONE_TAG = "[DONE]";


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
	std::string get();
	void clear();
	~InformationCache() = default;
private:
	InformationCache()=default;


	std::deque<std::string> cache_;
};

