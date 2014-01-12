#include <stdio.h>
#include <assert.h>

#include "Environment.h"

extern void testComponent();
extern int test_hash();
extern int test_bloom(int argc, char* argv[]);
extern int test_btree();
 
int main(int argc, char* argv[])
{
    	printf("LibThink Start %s!\n",__TIME__);
    	testComponent();
//		test_hash();
	//	test_bloom(argc, argv);
        test_btree(); 
    	testing::AddGlobalTestEnvironment(new CGTestEnvironment);
		testing::InitGoogleTest(&argc, argv);
		int ret = RUN_ALL_TESTS();
   
    	return ret;
}

