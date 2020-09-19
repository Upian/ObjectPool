#include <iostream>
#include "ObjectPool.hpp"
#include <queue>
#include <time.h>

class TestObjectPool1 : public ObjectPool<TestObjectPool1, 10>{
public:
    TestObjectPool1() = default;
private:
    int i[1000];
    double d[1000];
};
class TestObjectPool2 {
public:
    TestObjectPool2() = default;
private:
    int i[1000];
    double d[1000];
};

const int testcase = 10000;

int main(void){
    std::cout << "Run" << std::endl;
    std::cout << "SIZE: " << sizeof(TestObjectPool1) << std::endl;

	clock_t start, end;
	start = clock();
	std::queue<TestObjectPool1*> queue1;
	for(int i=0; i<testcase; ++i){
		for(int j1=0; j1<testcase; ++j1){
			queue1.emplace(new TestObjectPool1);
		}
		for(int j1=0; j1<testcase; ++j1){
			delete queue1.front();
			queue1.pop();
		}
	}
	end = clock();
	std::cout << "ObjectPool: " << end - start << std::endl;
/////////////////////
	start = clock();
	std::queue<TestObjectPool2*> queue2;
	for(int i=0; i<testcase; ++i){
		for(int j1=0; j1<testcase; ++j1){
			queue2.emplace(new TestObjectPool2);
		}
		for(int j1=0; j1<testcase; ++j1){
			delete queue2.front();
			queue2.pop();
		}
	}
	end = clock();
	std::cout << "new: " << end - start << std::endl;

    return 0;
}
