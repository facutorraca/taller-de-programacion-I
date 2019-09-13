#ifndef _LOCK_H_
#define _LOCK_H_
#include <mutex>

class Lock {

 	std::mutex& m;

	public:

		explicit Lock(std::mutex& m);

		~Lock();

};

#endif
