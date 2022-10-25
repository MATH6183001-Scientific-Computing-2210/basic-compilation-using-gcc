# 04-include-library

In this project, you'll learn that there is an argument of `gcc` denoted as `-I`.

Previously in [02-multiple-files](https://github.com/MATH6183001-Scientific-Computing-2210/basic-compilation-using-gcc/tree/main/02-multiple-files), you use:
```
#include "libs/my_library.h"
```
to include the `my_library.h` that is stored inside the directory libs. 

With the argument `-I` during the compilation, you can do the following in your C file.
```
#include "my_library.h"
```
But, when you compile it, you need to do:
```
gcc -c main.c -I libs/
```