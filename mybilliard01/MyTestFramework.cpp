#include "stdafx.h"
#include "MyTestFramework.h"

int main(int argc, char **argv)
{
  ::testing::InitGoogleTest(&argc, argv);
  const int rst = RUN_ALL_TESTS();
  if( rst != 0 )
      getchar();
  return rst;
}
