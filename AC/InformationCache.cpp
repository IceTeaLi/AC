#include "InformationCache.h"

void InformationCache::insert(const std::string& data)
{
	std::unique_lock<std::mutex> lock(mx_);
	cache_.push_back(data);
	cv.notify_all();

}

std::string& InformationCache::get()
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
