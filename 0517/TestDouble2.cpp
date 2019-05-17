#include <stdio.h>
#include <string>


// 아래 코드 구현방식은 테스트 대역을 적용하기 어렵습니다.
// => 테스트 대역을 적용할 수 있는 설계가 있습니다.
// FileSystem: 협력 객체(외부 의존물)

// * 협력 객체와 강한 결합이 형성되어 있으면 안됩니다.
// '강한 결합?'
//   : 협력 객체를 이용할 때, 구체적인 타입에 의존할 때

// * 테스트 대역을 적용하기 위해서는, 협력 객체와 약한(느슨한) 결합이 형성되어 있어야 합니다.
//  => 약한 결합
//    : 인터페이스나 추상 클래스를 통해 협력 객체를 이용하도록 변경할 필요가 있습니다.
//  => 틈새(seam) 만들기
//  
//    : 절대 협력 객체를 직접 생성하면 안됩니다.
//      new의 연산은 구체적인 타입을 지정해야 하는 연산입니다.
//  => 외부에서 생성해서 전달 받아야 합니다.
//  => DI(Dependency Injection): 의존성 주입

// 주입 방법 2가지
//  1) 생성자
//    : 의존하는 협력 객체가 반드시 필수적인 경우, 생성자를 통해 전달합니다.
//  2) 멤버 함수(메소드)
//    : 의존하는 협력 객체가 함수 호출시에만 필요하면, 함수의인자로 전달합니다.

// 의존성 주입의 문제점
//  => 보일러플레이트
//   : 반드시 필요하지만, 반복적으로 발생하는 코드 
#if 0
User -> Level
     -> Address
     -> Money

User(new Level, new Address, new Money)
// => 위처럼 직접 협력 객체를 생성해서 주입하는 코드를 작성하는 것을 '가난한 자의 의존성 주입'이라고 합니다.
// => 의존성 주입 프레임워크
//   : 의존성 주입으로 발생하는 보일러플레이트를 없애는 역활
//     Dagger2(Google)
#endif


// 1. 인터페이스 도입
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
	// 생성자의 인자가 한개인 경우, 반드시 생성자를 명시적으로 만들어야 한다.
	explicit Logger(IFileSystem* p = nullptr) : fs(p) {
		if (fs == nullptr) {
			fs = new FileSystem;
		}
	}

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
		// IFileSystem* fs = new FileSystem;
		return fs->IsValid(filename);
	}
};

#include <gtest/gtest.h>

class StubFileSystem : public IFileSystem {
public:
	virtual bool IsValid(const std::string& name) override {
		return true;
	}
};

class LoggerTest : public ::testing::Test {
protected:
	Logger* logger;
	StubFileSystem* stub;
	virtual void SetUp() override {
		stub = new StubFileSystem;
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
