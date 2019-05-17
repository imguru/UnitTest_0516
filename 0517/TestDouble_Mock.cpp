#include <stdio.h>
#include <string>
#include <vector>

// 분산 로거
enum DLogLevel {
	INFO, WARN, ERROR,
};

struct DLogTarget {
	virtual void Write(DLogLevel level, const std::string& message) = 0;
	virtual ~DLogTarget() {}
};

class DLog {
	std::vector<DLogTarget*> targets;
public:
	void AddTarget(DLogTarget* p) { 
		targets.push_back(p);
	}

	void Write(DLogLevel level, const std::string& message) {
		for (DLogTarget* e : targets) {
	//		e->Write(level, message);
		}
	}
};

//----------------------------------------------
#include <gtest/gtest.h>
#include <gmock/gmock.h>
// Mock Object Pattern
// : 함수를 호출하였을 때, 발생하는 부수 효과를 관찰할 수 없어서, 테스트 안된 요구사항이 있다.
// => 행위 기반 검증
//  : 메소드의 호출에 관련된 정보를 바탕으로 검증을 수행
//    1) 메소드 호출 여부
//    2) 메소드 호출 횟수
//    3) 메소드 호출 순서
//     => Mock Framework
//      Java: jMock, EasyMock, Mockito
//        => 동적으로 모의 객체를 생성합니다.

//      C++: Google Mock
//        => 정적으로 만들어야 합니다.
//        => 인터페이스가 제공하는 모든 멤버 함수에 대해서 수동으로 코드를 작성해야 합니다.
//        => 매크로를 제공합니다.
//            MOCK_METHOD{인자개수}(함수 이름, 함수 타입);

// DLogTarget - Mock Object
// void Write(DLogLevel level, const std::string& message);
class MockDLogTarget : public DLogTarget {
public:
	MOCK_METHOD2(Write, 
	  void(DLogLevel level, const std::string& message)); 
};

class DLogTest : public ::testing::Test {};

TEST_F(DLogTest, writeTest) {
	// Arrange
	DLog log;
	MockDLogTarget mock1, mock2;
	log.AddTarget(&mock1);
	log.AddTarget(&mock2);
	DLogLevel level = INFO;
	std::string message = "test_message";

	// Expect(Assert)
	EXPECT_CALL(mock1, Write(level, message));
	EXPECT_CALL(mock2, Write(level, message));

	// Act
	log.Write(level, message);
}










