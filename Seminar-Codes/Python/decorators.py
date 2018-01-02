# This seminar was about decorators
# You can get more info about this topic here :
# https://www.python-course.eu/python3_memoization.php


# This is decorator of fib function 
# For memoize function values 
# And don't repeate calculation
def memoize(f):
    cache = {}
    def f_(*args):
        n = args[0]
        if n not in cache:
            cache[n] = f(*args)
        return cache[n]
    return f_

# This is decorator of fib function for debugging
# When function enters recursively it prints "in" 
# And after returnin value it prints "out"
def logging(f):
    def f_(*args):
        print("in", args[0])
        res = f(*args)
        print("out", args[0])
        return res
    return f_

@logging
@memoize
def fib(n):
    if n < 2:
        return n
    else:
        return fib(n - 2) + fib(n - 1)

