def fib(n):
    if n <= 1:
        Result = n
    else:
        Result = fib(n - 1) + fib(n - 2)
    return Result

print (fib(10))