# 02-multiple-files

In this project, we try to compile a main file that has a dependency that we write ourselves.
The idea is that inside our main file, we will call a custom function that we define in a header file, and its implemention is written in another file C file.
In CS, there is this best practice whenever you integrate multiple modules, you need to first write an interface as a contract between those modules.
For example, the interface can be as simple as:
```c
int Addition(int a, int b);
```
which implies that the function name is `Addition` and it accepts two variables where both types are `int`. 
The function also returns an `int` type.

## How to

1. Compile the library first

    ```sh
    gcc  -o my_library.o -c libs/my_library.c
    ```

2. Compile the main file

    ```sh
    gcc -o main.o -c main.c
    ```

3. Link all files

    ```sh
    gcc -o main.out main.o my_library.o
    ```

4. Run the executable

    ```sh
    ./main.out
    ```

    You should see:
    ```
    14 + 12 = 26
    ```


