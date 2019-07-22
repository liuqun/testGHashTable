#include <stdio.h>
#include <gmodule.h>

int main(void)
{
  struct MyData {
    int id;
    char name[50];
  };
  struct MyData *p;
  struct MyData data[4] = {
    {1, "Alice"},
    {2, "Bob"},
    {3, "Cindy"},
    {4, "Dave"},
  };
  GHashTable *ht = g_hash_table_new(g_int_hash, g_int_equal);

  for (p=&data[0]; p<=&data[3]; p++) {
    gpointer key = (gpointer) &(p->id);
    gpointer value = (gpointer) p;
    g_hash_table_insert(ht, key, value);
  }
  printf("Hash table has %d nodes\n", g_hash_table_size(ht));
  {
    gint x;
    struct MyData *value;

    x = 1;
    value = g_hash_table_lookup(ht, &x);
    printf("Test lookup key x=%d, found: value->name=%s\n", x, value->name);
    x = 2;
    value = g_hash_table_lookup(ht, &x);
    printf("Test lookup key x=%d, found: value->name=%s\n", x, value->name);
    x = 3;
    value = g_hash_table_lookup(ht, &x);
    printf("Test lookup key x=%d, found: value->name=%s\n", x, value->name);

    x = data[3].id;
    value = g_hash_table_lookup(ht, &x);
    printf("Test look up key x=%d, found: value->name=%s\n", x, value->name);

    /* Crack data struct */
    {
      printf("Before cracking data: data[3].id=%d\n", data[3].id);
      data[3].id = 1;
      printf("After cracked: edit data[3].id=%d\n", data[3].id);
      value = g_hash_table_lookup(ht, &x);
      if (!value) {
        printf("Can not find x=%d\n", x);
      } else {
        printf("Test look up key x=%d, found: value->name=%s\n", x, value->name);
      }
    }
  }

  g_hash_table_remove_all(ht);
  printf("After remove all nodes, the hash table has %d node(s)\n", g_hash_table_size(ht));
  g_hash_table_unref(ht);
  return 0;
}

/* vi:set ts=2 sw=2 expandtab : */
