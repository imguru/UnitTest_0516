// Test Double(테스트 대역)
//  : 테스트 환경 통제하기 위해 사용한다.

// 테스트 대역 종류 4가지
// 1) Test Stub
// 2) Fake Object
// 3) Test Spy
// 4) Mock Object
// => xUnit Test Pattern

// 테스트 대역이 적용될 수 있는 설계
// SUT
#include <stdio.h>
#include <string>

// 문제점
//  : 아래 코드는 테스트의 목적과 상관없이 협력객체에 의해서 테스트의 결과가 변경될 수 있다.
//  => SUT(CUT)를 격리시켜서, 테스트의 결과가 SUT에 의해서 결정될 수 있도록 해야 한다.

// ext, NTFS, xfs ...
class FileSystem {
public:
	bool IsValid(const std::string& name) { return false; }
};

class Logger {
public:
	// file.log
	// : 확장자를 제외한 파일의 이름이 5글자 이상이어야 한다.
	bool IsValidFilename(const std::string& filename) {
		//--------------------------------
		int index = filename.find_last_of(".");
		std::string name = filename.substr(0, index);

		if (name.size() < 5) {
			return false;
		}

		//--------------------------------
		FileSystem* fs = new FileSystem;
		return fs->IsValid(filename);
	}
};

#include <gtest/gtest.h>

class LoggerTest : public ::testing::Test {
protected:
	Logger* logger;
	virtual void SetUp() override {
		logger = new Logger;
	}

	virtual void TearDown() override {
		delete logger;
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
