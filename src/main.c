#include <stdio.h>
#include <stdlib.h>
#include <glib.h>

// 双向链表API冒烟测试
//
// 被测试的API头文件: glib.h
//
// 编译步骤: 详见项目顶层目录 README 自述文档...
//
// 测试用例设计思路:
// 1. 创建一个空的双向链表 GQueue *queue;
// 2. 调用g_queue_push_tail()操作, 将若干个数据块输入双向链表;
// 3. 执行test_print(), 遍历双向链表内部所有节点, 打印全部内容;
// 4. 对双向链表进行g_queue_pop_head()/g_queue_pop_tail(), 此处掐头去尾各去掉一个数据块;
// 5. 重复一次步骤3, 打印双向链表的内容;
// 6. 对双向链表执行1次g_queue_push_head()操作, 恢复之前的头节点;
// 7. 重复一次步骤3, 打印双向链表的内容;
// 8. 对双向链表再执行1次g_queue_push_head()操作, 插一个节点到双向链表头部;
// 9. 重复一次步骤3, 打印双向链表的内容;
// 最后: 释放为测试用例分配的所有内存


/* 临时定义 MyBuffer 数据结构, 仅用于存储测试数据 */
#define MY_BUFFER_DEFAULT_CAPACITY 16
typedef struct MyBuffer_ {
  unsigned long used_bytes;
  unsigned long capacity;
  char data[MY_BUFFER_DEFAULT_CAPACITY];
} MyBuffer;


static
void dump_buffer(gpointer buff_, gpointer fp_)
{
  MyBuffer *b = (MyBuffer *)buff_;
  FILE *fp = (FILE *) fp_;
  unsigned long i;

  fprintf(fp, "%lu, %lu, {", b->used_bytes, b->capacity);
  for (i = 0; i < b->used_bytes; i++) {
    fprintf(fp, "%c", b->data[i]);
  }
  fprintf(fp, "}\n");
}

// 测试函数test_print(): 利用foreach遍历函数打印双向链表queue中的所有数据
static
void test_print(GQueue *queue)
{
  g_queue_foreach(queue, dump_buffer, stdout);
}

int main(void)
{
  GQueue *queue;

  // 0. 初始化N组buffer数据块备用
  const size_t N = 5;
  MyBuffer a[N];

  for (size_t i = 0; i < N; i++) {
    a[i].capacity = MY_BUFFER_DEFAULT_CAPACITY;
    a[i].used_bytes = i+1;
    for (size_t j = 0; j < a[i].used_bytes; j++) {
      a[i].data[j] = 'A' + i;
    }
  }

  // 1. 初始化双向链表queue
  queue = g_queue_new();

  // 2. 将N组测试数据块插入双向链表queue
  for (size_t i = 0; i < N; i++) {
    g_queue_push_tail(queue, &(a[i]));
  }

  // 3. 打印queue的内部数据
  printf("queue 内部数据为: {\n");
  test_print(queue);
  printf("}\n");

  // 4. 对双向链表进行pop操作, 此处掐头去尾各去掉一个
  g_queue_pop_head(queue);
  g_queue_pop_tail(queue);

  // 5. 再次打印queue的内部数据
  printf("掐头去尾之后 queue 内部数据为: {\n");
  test_print(queue);
  printf("}\n");

  // 6. 对双向链表的头进行一次push操作, 还原原来的头结点
  g_queue_push_head(queue, &a[0]);

  // 7. 再次打印queue的内部数据
  printf("恢复头部之后 queue 内部数据为: {\n");
  test_print(queue);
  printf("}\n");

  // 8. 对双向链表的头进行一次push操作, 把之前的尾结点强行装在头部
  g_queue_push_head(queue, &a[N-1]);

  // 9. 再次打印queue的内部数据
  printf("头部再插入一个点之后 queue 内部数据为: {\n");
  test_print(queue);
  printf("}\n");

  /* 最后释放测试用到的内存 */
  // 释放双向链表queue
  g_queue_free(queue);
}
/* vi:set ts=2 sw=2 expandtab : */
