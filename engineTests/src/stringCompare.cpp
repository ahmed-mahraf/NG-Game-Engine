#include "stringCompare.h"

//<!test for true actual value
TEST(StrCompare, CStrEqual) {
	EXPECT_STREQ(expectVal, actualValTrue);
}
//<!test for false actual value
TEST(StrCompare, CStrNotEqual) {
	EXPECT_STREQ(expectVal, actualValFalse);
}