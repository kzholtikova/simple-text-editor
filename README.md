# Simple Text Editor: the basics of Procedural and Structural Programming
## Purpose of work
Understand the basics of procedural and structural programming by having hands-on experience
in using these paradigms. Learn how the memory management works inside the process,
understand the virtual memory concept and typical issues with memory allocation and
deallocation, learn the basic data types.

## Task
Develop a console-based text editor that will have the below functionality:
1. Append text symbols to the end.
```
> Choose the command:
> 1
> Enter text to append: Hello, text editor!
```
2. Start the new line/
```
> Choose the command:
> 2
> New line is started
```
3. Use files to loading/saving the information.
```
> Choose the command:
> 3
> Enter the file name for saving: MyFile.txt
> Text has been saved successfully
Choose the command:
> 4
> Enter the file name for loading: MyFile.txt
> Text has been loaded successfully
```
4. Print the current text to console.
```
> Choose the command:
> 5
> Hello, text editor!
```
5. Insert the text by line and symbol index.
```
> Choose the command:
> 6
> Choose line and index: 0 6
> Enter text to insert: my > Choose the command:
> 5
> Hello, my text editor!
```
6. Search (please note that text can be found more than once).
```
> Choose the command:
> 7
> Enter text to search: Hello
> Text is present in this position: 0 0
```
7. Clearing the console.
   In this case you should clean the console before each command start.

## Task milestones
1. Implement input command parser.
   This step should include printing the help information, reading the command from a user and
   answering something like `The command is not implemented`.
2. Implement text memory storage.
   When we are talking about low level memory-efficient programming you need to consider the
   following format of the text memory storage: `M y t e x t \0`
   The `\0` symbol means `NULL`. So when we are reading this memory cell, we have a value `\0`
   and that means end of the string. Please don’t confuse with the `0` character with value 48=0x30 in
   ASCII table.
   Also, while implementing this part of the program, you should consider a case when it will be
   needed to insert some value in the middle of the already existed text. Thus, please use dynamic
   arrays or linked list (depending on your decision and thinking of efficiency). Another case is
   adding a new line of text that can be done by using 2-dimensional arrays or a linked list that
   contains lines.
3. Implement text memory printing to console.
   Here we need to iterate through the whole data structure and print each symbol.
4. Implement the logic to save text to file.
   This is similar to 3 but instead of standard console output it is needed to use the file descriptor.
```
#include <stdio.h>
int main()
{
    FILE* file;
    file = fopen("myfile.txt", "w");
    if (file != NULL)
    {
        fputs("Hello, files world!", file);
        fclose(file);
    }
    return 0;
}
```
5. Implement the logic to load text from file.
```
#include <stdio.h>
int main()
{
    FILE* file;
    char mystring[100];
    file = fopen("MyFile.txt", "r");
    if (file == NULL)
    {
        printf("Error opening file");
    }
    else
    {
        if (fgets(mystring, 100, file) != NULL)
        {
            printf("%s", mystring);
        }
        fclose(file);
    }
    return 0;
}
```
6. Implement substring search mechanism.
   For this you need to iterate through the whole text document and make a comparison of each
   symbol with the given substring. Please note that you need to find all matched substring, not the
   first/last one.
7. Implement substring insertion mechanism.
   You need to insert a substring by using line and symbol indexing (the insertion position). In this
   case you need to consider memory reallocation and moving, for example: `m a p \0`
   We’re going to insert a substring `hash` to line 0 and starting from 0 element, thus we need to
   allocate 4 additional cells first: `m a p \0    `
   Then we need to move this data: `   m a p \0`
   And then to insert the substring to the beginning: `h a s h m a p \0`
8. Implement the console clearing mechanism.

## Control questions
1. What is structural programming paradigm?
2. What is procedural programming paradigm?
3. Which primitive data types do you know? Key differences between them?
4. Which segments does the process memory have?
5. What is the virtual memory space?
6. How to allocate the memory in each segment?
7. How to reallocate the memory in case we don’t have enough space?
8. What is a runtime stack?

## Evaluation
- Appending text to the end  - 1
- Starting a new line - 1
- Saving and loading from file - 2
- Printing the current text - 1
- Inserting text by line and symbol index - 1
- Search algorithm - 1
- Correct git usage flow (3+ meaningful commits) - 1
- Theory (test) - 1
- Test plan creation and following - 1
- (Extra point) Unlimited size of the text rows and columns - 1
  **Total:** 10 + 1

Please note you should follow the structural and procedural paradigms as well as answer
theoretical questions and explain your code to the teacher. Otherwise, the final point will
be reduced.

## Links
PLPP – Programming Languages Principles and Paradigms book
CSAPP – Computer Systems A Programming Perspective book
1. Structural programming: PLPP Chapter 6 (Sequence control commands, structured
   programming)
2. Procedural programming: PLPP Chapter 7 (Subprograms)
3. Data types: CSAPP 2.1-2.4
4. Runtime stack: CSAPP 3.7.1
5. Memory management: PLPP Chapter 5
6. Virtual memory: 1.7.3
7. Files: CSAPP 1.7.4
8. File opening/writing/closing API in C: https://cplusplus.com/reference/cstdio/fopen/
