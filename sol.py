import sys 
import math
import heapq

# solve stack overflow
from types import GeneratorType
def bootstrap(f, stack=[]):
    def wrappedfunc(*args, **kwargs):
        if stack:
            return f(*args, **kwargs)
        else:
            to = f(*args, **kwargs)
            while True:
                if type(to) is GeneratorType:
                    stack.append(to)
                    to = next(to)
                else:
                    stack.pop()
                    if not stack:break
                    to = stack[-1].send(to)
            return to
    return wrappedfunc

# input = lambda: sys.stdin.readline().rstrip()
def I():
    return input()

def II():
    return int(input())

def MII():
    return map(int, input().split())

def LMII():
    return list(map(int, input().split()))
#-------------------head-----------------#
# list []
# tuple ()
# dict {}
# set set()
# 可变: list dict set
# 不可变: str tuple
# enumerate zip 遍历技巧\n# we can change the world!

 what
