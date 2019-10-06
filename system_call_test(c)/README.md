# Simple attempt in C

+ Generating valid system calls. This function enables the model to generate valid systems calls.

This is the very first function I should do. The idea is that, since we know that system calls are basicly shapes like syscall(Nr,...) and the syscall_Nr for every system call can be found, we can generate valid system call with the numbers and valid other parameters.

The idea is to define a structure parameter, which includes the systcall_Nr and other parameters. Using each member of parameter as the parameter of function syscall(...), we are able to successfully call a system call.

For this simple attempt, I use syscall_Nr = 0 and 1, which stands read(...) and write(...). I think the parameters they require are the same, thus we need to define only one kind of structure.

Function paraGen(void* buf, int n) generates structure parameter for n times. Except buf, other parameters are generated randomly, therefore we can collect information under different cases.

We use errno to gether error code and we can use "...> a.txt" to log our data.

