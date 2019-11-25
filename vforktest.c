#include "types.h"
#include "stat.h"
#include "user.h"

int n = 0;

void
vforktest(void)
{
  int pid = 0;
  printf(1, "vfork test\n");
  pid = vfork();

  if (pid < 0)
    return;
  if (pid == 0) {
    pid = vfork();
    if (pid < 0)
      return;
    if (pid == 0) {
      printf(1, "GRANDCHILD-PA1: %d\n", getpaddr((int)&n));
      n = 1;
      printf(1, "GRANDCHILD-PA2: %d\n", getpaddr((int)&n));
      exit();
    }
    if (pid > 0) {
      printf(1, "CHILD-PA1: %d\n", getpaddr((int)&n));
      wait();
      printf(1, "CHILD-PA2: %d\n", getpaddr((int)&n));
      n=2;
      printf(1, "CHILD-PA3: %d\n", getpaddr((int)&n));
      exit();
    }
  }
  if (pid > 0) {
    printf(1, "PARENT-PA1: %d\n", getpaddr((int)&n));
    wait();
    printf(1, "PARENT-PA2: %d\n", getpaddr((int)&n));
    n=3;
    printf(1, "PARENT-PA3: %d\n", getpaddr((int)&n));
  }
  printf(1, "vfork test complete\n");
}

int
main(void)
{
  vforktest();
  exit();
}
