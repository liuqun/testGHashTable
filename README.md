# Project README
* C/C++ source code should be put into [sub-directory src](./src)

# How to compile this project:

1. Development tools:
```
sudo apt-get install build-essential cmake libssl-dev libglib2.0-dev
```

2. Generate Makefile:
```
cmake .
```

3. Compile:
```
make
```

# 哈希表 GHashTable 使用说明
- [样例代码](tests/test-hash-table.c)
- [英文手册](https://developer.gnome.org/glib/stable/glib-Hash-Tables.html)
- 头文件: /usr/include/glib-2.0/glib/ghash.h

# 双向队列 GQueue 使用说明
- [英文手册](https://developer.gnome.org/glib/stable/glib-Double-ended-Queues.html)
- 头文件: /usr/include/glib-2.0/glib/gqueue.h
