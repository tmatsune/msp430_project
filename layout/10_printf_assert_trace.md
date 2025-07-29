printf if s built-in function from the stdio library that takes a format string, replaces placeholders with actual 
values, and displays the final result to the console (or output device)
    - printf -> C library -> System Call -> Operating system kernel -> terminal/consol window 

Printf library formats the string. parses the string and replaces placeholders (like %d) with acutal values and
produces a fully formatted string internally. and outputs char by char calling my _putchar function for each char 
in the formatted string. My _puthcar sends the char to hardware. This function is where you actually connect to 
UART driver. printf library itseld is hardware agnostic. doesn't know anything about UART or consoles. just calls
my output function to print chars. 

assert: 
    - Detect conditions that should never happen during execution (invalid input, logic errors)
    - if condition fails prints an error message (with file & line info), and then halts the program or trigger a breakpoint
        to help debugging 
trace:
    - Log debug or info error messages during program execution, showing status, variable values ot errors 
    - pints messages with file & line info to a terminal (UART) to track what your program is doing 


