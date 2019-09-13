#ifndef _LOCK_H_
#define _LOCK_H_

#include <mutex>

class Lock {

 	std::mutex& mtx;

	public:

		explicit Lock(std::mutex& mtx);

		~Lock();

};

#endif
