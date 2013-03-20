#include <stdio.h>
#include <assert.h>
/*
class Foo{
public:
   int StatusIsOK()
{
	return 0;
}
};
*/
#include "Environment.h"
/*
TEST(FooTest, InitializesCorrectly) {
     Foo foo;
     EXPECT_TRUE(foo.StatusIsOK());
	
}
*/
extern void testComponent();
int main(int argc, char* argv[])
{
    	printf("LibThink Start %s!\n",__TIME__);
    	testComponent();
    	testing::AddGlobalTestEnvironment(new CGTestEnvironment);
	testing::InitGoogleTest(&argc, argv);
	int ret = RUN_ALL_TESTS();
   
    	return ret;
}

