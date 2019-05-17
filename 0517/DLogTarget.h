#ifndef DLOGTARGET_H
#define DLOGTARGET_H

#include <string>

enum DLogLevel {
	INFO, WARN, ERROR,
};

struct DLogTarget {
	virtual void Write(DLogLevel level, const std::string& message) = 0;
	virtual ~DLogTarget() {}
};

#endif
