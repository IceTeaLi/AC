#pragma once
#include <mutex>
#include <condition_variable>
#include <deque>
#include <string>


template<typename T>
class MessageCache
{
	std::mutex mx;
	std::condition_variable cv;
	std::deque<T> cache;
public:
	MessageCache() = default;
	~MessageCache() = default;

	const T get();
	void insert(const T&);
	void clear();
	bool empty() const;
};


template<typename T>
inline const T MessageCache<T>::get()
{
	std::unique_lock<std::mutex> lock(mx);
	cv.wait(lock, [this]() {return !empty(); });
	auto data = cache.front();
	cache.pop_front();
	return data;
}

template<typename T>
inline void MessageCache<T>::insert(const T& data)
{
	std::unique_lock<std::mutex> lock(mx);
	cache.push_back(data);
	cv.notify_all();
}

template<typename T>
inline void MessageCache<T>::clear()
{
	std::lock_guard<std::mutex> lock(mx);
	cache.clear();
}

template<typename T>
inline bool MessageCache<T>::empty() const
{
	return cache.empty();
}

typedef struct MyMessage
{
	uint32_t dwData;
	std::string content;
}MyMessage;

/**
*@brief store message cache
*
* single instance
*/
class Cache
{
public:
	/**
	*@brief get Cache instance
	*/
	static Cache& get_instance()
	{
		static Cache cache;
		return cache;
	}
	
	static const int STATUS_MESSAGE = 0x00;		///< status message identifier
	static const int RESULTS_MESSAGE = 0x01;		///< results message identifier

	/**
	*@brief insert message to cache
	*@param const std::string&: message content
	*@param int message type identifier[STATUS_MESSAGE,RESULTS_MESSAGE]
	*/
	void insert(const MyMessage& data,int message_type);
	/**
	*@brief get message from cache
	*@param int message type identifier[STATUS_MESSAGE,RESULTS_MESSAGE]
	*@return const std::string&: message from cache
	*/
	const MyMessage get(int message_type);
	/**
	*@brief clear cache
	*@param int message type identifier[STATUS_MESSAGE,RESULTS_MESSAGE]
	*/
	void clear(int message_type);
private:
	Cache()=default;
	~Cache()=default;

	MessageCache<MyMessage> status_cache_;			///< message cache 
	MessageCache<MyMessage> results_cache_;			///< message cache 
};