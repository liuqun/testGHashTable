#include <stdio.h>
#include <unistd.h> // int system(char *);
#include <glib.h>

void foobar_do_something()
{
  system("sleep 2");
}

int main(void)
{
  /* GTimer 是精确到微秒级别的计时器 */
  GTimer *timer1;

  timer1 = g_timer_new();
  g_timer_start(timer1);
  foobar_do_something();
  g_timer_stop(timer1);
  gulong microseconds;
  printf("total = %9.7G milliseconds\n", g_timer_elapsed(timer1, &microseconds));
  printf("microseconds = %lu\n", microseconds);
  g_timer_destroy(timer1);
  return 0;
}

/* vi:set ts=2 sw=2 expandtab : */
