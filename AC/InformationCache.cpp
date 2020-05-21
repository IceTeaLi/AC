#include "InformationCache.h"
#include <time.h>
void InformationCache::insert(const std::string& data)
{
	time_t sys_time;
	time(&sys_time);
	auto convert_sys_time = localtime(&sys_time);
	std::string content = "["
		+ std::to_string(convert_sys_time->tm_hour) + ":"
		+ std::to_string(convert_sys_time->tm_min) + ":"
		+ std::to_string(convert_sys_time->tm_sec)
		+ "]"
		+ data;
	std::unique_lock<std::mutex> lock(mx_);
	cache_.push_back(content);
	cv.notify_all();

}

std::string InformationCache::get()
{
	std::unique_lock<std::mutex> lock(mx_);
	cv.wait(lock, [this]() {return !cache_.empty(); });
	auto data = cache_.front();
	cache_.pop_front();
	return data;
}

void InformationCache::clear()
{
	std::lock_guard<std::mutex> lock(mx_);
	cache_.clear();
}
