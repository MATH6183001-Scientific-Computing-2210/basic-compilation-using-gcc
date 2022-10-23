# 03-makefile

In the [02-multiple-files](https://github.com/MATH6183001-Scientific-Computing-2210/basic-compilation-using-gcc/tree/main/02-multiple-files) tutorial, suppose that you want to change your library, so whenever you change it, you need to perform the compilation process from the beginning, which is very cumbersome.
In Linux, you can use Linux command `make` and a `Makefile` file. 

As of now, please learn the basic concept of `make` from the Internet.
Only two basic concepts that you need to know for now.
First, the following is a protype of a Makefile.
```
target: prerequisites
<TAB> recipe
```
Note that you could replace `target`, `prerequisites`, and `recipe` according to your need.
The idea is that later you can run `make <target>` to run the `recipe`. 
And, if the `prerequisites` are not achieved yet, then `make` will execute the recipe for the `prerequisites` first. 
(Please be patient if you don't understand it now. Perhaps, it'll be clearer once you can successfully run it.)

The second concept is that you can define and assign a variable, e.g.,:
```
CC = gcc
```
which later you can call in, for example, a recipe as follows:
```
all: my_library.o 
	${CC} -c main.c
```
We usually do this if we have multiple version of `gcc` command.

## Requirements

My `make` version is as follows.

```
GNU Make 4.2.1
```

## How to

1. Compile

    To compile, you can just run:
    ```sh
    make
    ```
    Then, you can run the executables as:
    ```sh
    ./main.out
    ```

2. Clean

    If you want to remove object files and the executable file, you can run:
    ```sh
    make clean
    ```

3. Experiment

    Now try changing the code and run the Makefile again, see if you notice any difference in the execution steps.