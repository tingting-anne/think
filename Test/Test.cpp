#include <stdio.h>
#include <assert.h>

#include "Environment.h"
#include "msgqueue.h"


TEST(QueueTest, Initializes) 
{
    THINK::CMsgQueue<int> a;
	
}

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

