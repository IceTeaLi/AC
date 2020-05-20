#include "MessageCache.h"

void Cache::insert(const MyMessage& data, int message_type)
{
	if (message_type == Cache::STATUS_MESSAGE)
		status_cache_.insert(data);
	else
		results_cache_.insert(data);
}

const MyMessage Cache::get(int message_type)
{
	if (message_type == Cache::STATUS_MESSAGE)
		return status_cache_.get();
	if (message_type == Cache::RESULTS_MESSAGE)
		return results_cache_.get();
	return {};
}

void Cache::clear(int message_type)
{
	return message_type ? results_cache_.clear() : status_cache_.clear();
}
