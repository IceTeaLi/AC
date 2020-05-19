#include "MessageCache.h"

void Cache::insert(const std::string& data, int message_type)
{
	if (message_type == Cache::STATUS_MESSAGE)
		status_cache_.insert(data);
	else
		results_cache_.insert(data);
}

const std::string& Cache::get(int message_type)
{
	return message_type ? results_cache_.get() : status_cache_.get();
}

void Cache::clear(int message_type)
{
	return message_type ? results_cache_.clear() : status_cache_.clear();
}
