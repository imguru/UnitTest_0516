#include <stdio.h>
#include <string>

struct IFileSystem {
	virtual bool IsValid(const std::string& name) = 0;
	virtual ~IFileSystem() {}
};

class FileSystem : public IFileSystem {
public:
	virtual bool IsValid(const std::string& name) override { 
		return false; 
	}
};

class Logger {
	IFileSystem* fs;
public:
	explicit Logger(IFileSystem* p = nullptr) : fs(p) {
		if (fs == nullptr) {
			fs = new FileSystem;
		}
	}

	bool IsValidFilename(const std::string& filename) {
		//--------------------------------
		int index = filename.find_last_of(".");
		std::string name = filename.substr(0, index);

		if (name.size() < 5) {
			return false;
		}

		//--------------------------------
		// IFileSystem* fs = new FileSystem;
		return fs->IsValid(filename);
	}
};

#include <gtest/gtest.h>
#include <gmock/gmock.h>

class StubFileSystem : public IFileSystem {
public:
	MOCK_METHOD1(IsValid, bool(const std::string&));
};

using ::testing::_;
using ::testing::Return;
class LoggerTest : public ::testing::Test {
protected:
	Logger* logger;
	StubFileSystem* stub;
	virtual void SetUp() override {
		stub = new StubFileSystem;
		// 함수가 호출되었을 때의 결과를 지정하는 것이 가능합니다. => Stub
		ON_CALL(*stub, IsValid(_)).WillByDefault(Return(true));

		logger = new Logger(stub);
	}

	virtual void TearDown() override {
		delete logger;
		delete stub;
	}
};

TEST_F(LoggerTest, IsValidFilename_NameShorterThan5Chars_RetrunsFalse) {
	// Logger logger;
	std::string filename = "bad.log";

	bool actual = logger->IsValidFilename(filename);

	ASSERT_FALSE(actual) << "파일명이 다섯글자 미만일 때";
}

TEST_F(LoggerTest, IsValidFilename_NameLongerThan5Chars_ReturnsTrue) {
	// Logger logger;
	std::string filename = "goood.log";
	
	bool actual = logger->IsValidFilename(filename);

	ASSERT_TRUE(actual) << "파일명이 다섯글자 이상일 때";
}
