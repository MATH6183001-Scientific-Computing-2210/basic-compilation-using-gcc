# 01-single-file

Here we're going to investigate how a file is transformed at every step before it can be executed by an operating system (e.g., Linux).
The main tool that I use is **gcc**, which is a **collection** of tools to compile C codes. 
My gcc version is 9.4.0-1ubuntu1~20.04.1.
(This is important if you see error that I am not experiencing).
The steps will be explained next.


There are 4 steps in a C code compilation, i.e.,:

1. Preprocessing

    Preprocessing means that gcc will prepare a C file by adding more information that is used by the subsequent steps.
    Specifically, it will output bunch of lines with the following format.

    ```
    # linenum filename flags
    ```

    It has a special meaning. If you're interested please refer to (herea at p 56)[https://gcc.gnu.org/onlinedocs/cpp.pdf]. 
    Let's look at the example. 

    In Linux, you can run the following command to find a proper argument for a given task, e.g., preprocessing.

    ```sh
    gcc --help | grep -i "preprocess"
    ```

    (grep is another command in Linux where you can use to search a keyword. Since I use the pipe notation '|', it means I pass the output from gcc --help as the input for the grep command. The argument -i means that we search the keyword in the case-insensitive mode.)
    The output in my machine is like the following.

    ```
    -Wp,<options>            Pass comma-separated <options> on to the preprocessor.
    -Xpreprocessor <arg>     Pass <arg> on to the preprocessor.
    -E                       Preprocess only; do not compile, assemble or link.
    ```

    Therefore, we will use the argument -E to perform the preprocessing.
    Let's start with the main file that does not have any dependency.

    ```sh
    gcc -E main_without_dependency.c
    ```

    In my machine I'm getting the following output.

    ```
    # 1 "main_without_dependency.c"
    # 1 "<built-in>"
    # 1 "<command-line>"
    # 31 "<command-line>"
    # 1 "/usr/include/stdc-predef.h" 1 3 4
    # 32 "<command-line>" 2
    # 1 "main_without_dependency.c"
    int main (void) {
    }
    ```

    What we can learn from here is that gcc will include /usr/include/stdc-predef.h by default regardless if it is explicitly written or not. Second takeaway is that the directory /usr/include/ stores many h files ('h' means header).

    Now, let's compare it with the other file.

    ```sh
    gcc -E main_with_dependency_predetermined_dir.c | head -n 10
    ```

    (Note that the command head -n 10 implies that I'm only going to see the first 10 lines.) The output is:

    ```
    # 1 "main_with_dependency_predetermined_dir.c"
    # 1 "<built-in>"
    # 1 "<command-line>"
    # 31 "<command-line>"
    # 1 "/usr/include/stdc-predef.h" 1 3 4
    # 32 "<command-line>" 2
    # 1 "main_with_dependency_predetermined_dir.c"
    # 1 "/usr/include/stdio.h" 1 3 4
    # 27 "/usr/include/stdio.h" 3 4
    # 1 "/usr/include/x86_64-linux-gnu/bits/libc-header-start.h" 1 3 4
    ```

    Starting from the line that contains 
    ```
    # 32 "<command-line>" 2
    ```
    they are different. 
    You'll see a nested dependencies starting from stdio.h to  libc-header-start.h and so on.
    Please open /usr/include/stdio.h and you'll see that inside the code it includes `#include <bits/libc-header-start.h>`

    Next, in C, the notation '#' is referred to as directive or a special instruction.
    (Read [C Programming/Preprocessor directives and macros](https://en.wikibooks.org/wiki/C_Programming/Preprocessor_directives_and_macros) for more detailed information).
    `#include` is a directive that enables you to link multiple files instead of writing a very long, cluttered file.
    With `#include`, you can use either `#include <stdio.h>` or `#include "stdio.h"`.
    The notation `<>` implies that the gcc will search in the /usr/include directory, while notation `""` implies that the gcc will search in the current directory.
    Let's compare it with the following.
    ```sh
    gcc -E main_with_dependency_local_dir.c | head -n 10
    ```
    
    The output goes like this.
    ```
    # 1 "main_with_dependency_local_dir.c"
    # 1 "<built-in>"
    # 1 "<command-line>"
    # 31 "<command-line>"
    # 1 "/usr/include/stdc-predef.h" 1 3 4
    # 32 "<command-line>" 2
    # 1 "main_with_dependency_local_dir.c"
    # 1 "stdio.h" 1
    # 2 "main_with_dependency_local_dir.c" 2
    ```

    Notice that instead of `"/usr/include/stdio.h"`, you see `"stdio.h"`, which implies it searches in the current directory instead of in the directory `/usr/include/`.


2. Compilation

    Then, after you have a preprocessed file, then gcc will compile the file to a machine language called assembly.
    Note that your assembly code will be different depending on your machine. 
    For example, in my server, by running the command:

    ```sh
    gcc -S main_without_dependency.c
    ```

    you'll see:
    ```
    .file   "main_without_dependency.c"
            .text
            .globl  main
            .type   main, @function
    main:
    .LFB0:
            .cfi_startproc
            endbr64
            pushq   %rbp
            .cfi_def_cfa_offset 16
            .cfi_offset 6, -16
            movq    %rsp, %rbp
            .cfi_def_cfa_register 6
            movl    $0, %eax
            popq    %rbp
            .cfi_def_cfa 7, 8
            ret
            .cfi_endproc
    .LFE0:
            .size   main, .-main
            .ident  "GCC: (Ubuntu 9.4.0-1ubuntu1~20.04.1) 9.4.0"
            .section        .note.GNU-stack,"",@progbits
            .section        .note.gnu.property,"a"
            .align 8
            .long    1f - 0f
            .long    4f - 1f
            .long    5
    0:
            .string  "GNU"
    1:
            .align 8
            .long    0xc0000002
            .long    3f - 2f
    2:
            .long    0x3
    3:
            .align 8
    4:
    ```

    Then, try to run the same command in other linux system for example on [labs-play-with-docker](https://labs.play-with-docker.com/).
    You'll see the following.
    ```
    .file   "main.c"
            .text
            .globl  main
            .type   main, @function
    main:
    .LFB0:
            .cfi_startproc
            pushq   %rbp
            .cfi_def_cfa_offset 16
            .cfi_offset 6, -16
            movq    %rsp, %rbp
            .cfi_def_cfa_register 6
            movl    $0, %eax
            popq    %rbp
            .cfi_def_cfa 7, 8
            ret
            .cfi_endproc
    .LFE0:
            .size   main, .-main
            .ident  "GCC: (Alpine 11.2.1_git20220219) 11.2.1 20220219"
            .section        .note.GNU-stack,"",@progbits
    ```

    This tells you that gcc bridges communication between a C code (which is more human friendly compared to assembly) to different machines that talk different machine languages.
    (Please refer to [intro to assembly by Intel](https://www.intel.com/content/dam/develop/external/us/en/documents/introduction-to-x64-assembly-181178.pdf) if you want to overwhelm yourselves.)
    
3. Assemble

    Now, given a machine language, the gcc will convert it to an object file having a binary format. To do this, you can run:

    ```sh
    gcc -c main_without_dependency.s
    ```

    It will output `main_without_dependency.o`.
    In Linux, you can use command `file` to determine type of file.

    Running:

    ```sh
    file main_without_dependency.o
    ```

    will output:

    ```
    main_without_dependency.o: ELF 64-bit LSB relocatable, x86-64, version 1 (SYSV), not stripped
    ```

    If you insist to read it, then you can use:

    ```
    hexdump -C main_without_dependency.o
    ```

    Let's investigate only one row.

    ```
    00000000  7f 45 4c 46 02 01 01 00  00 00 00 00 00 00 00 00  |.ELF............|
    ```

    `00000000` here shows your memory address. 
    The second `0` store the byte value `45` written in hexadecimal format. 
    Then, you can refer to [ASCII table](https://upload.wikimedia.org/wikipedia/commons/0/0f/Dot_printer_ASCII.png) to validate the 45 in hex format is the same as letter E.

    Now, what if you want to return it back to an assembly file.
    Try to run the following.
    ```
    objdump -D main_without_dependency.o
    ```

4. Linking

    For now, it is not that relevant to explain linker in this project as we don't focus on multiple files having many dependencies.
    But anyway, try the following to generate an executable file.
    
    ```sh
    gcc -o  main.out main_without_dependency.o
    ```

    It will outout `main.out`.
    If you're in Linux, you can check if it is executable or not if you run:
    
    ```
    ls -la main.out
    ```

    And, it will output:

    ```
    -rwxrwxr-x
    ```

    where `x` indicates that the file is executable.

    Then, in order to run the executable file, type the following.

    ```
    ./main.out
    ```

    You won't see anything tho as we don't write any logic in the file. :D
    
