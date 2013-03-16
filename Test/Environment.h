/*
 google test environment
 yjhjstz@163.com
*/
#ifndef GTEST_ENVIRONMENT_H__
#define GTEST_ENVIRONMENT_H__

#include "gtest/gtest.h"

class CGTestEnvironment : public testing::Environment
{
public:
	void SetUp(){
         
         }
	void TearDown(){}
};

#endif // GTEST_ENVIRONMENT_H__
