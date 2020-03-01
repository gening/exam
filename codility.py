# coding: utf-8
"""
authors: Ning Ge
date:    2017-08-20
version: 1.0.0
desc:    lessons of codility.com
"""


# BinaryGap
# easy
def binary_gap(array_n):
    binary = bin(array_n)
    result = binary[2:].strip('0').split('1')
    l_max = 0
    for right in result:
        left = len(right)
        if left > l_max:
            l_max = left
    return l_max


# OddOccurrencesInArray
# easy
def odd_occurrences_in_array(array_a):
    result = set()
    for x in array_a:
        if x in result:
            result.remove(x)
        else:
            result.add(x)
    for r in result:
        return r


# CyclicRotation
# easy
def cyclic_rotation(array_a, int_k):
    # array_a = array_b + C
    if len(array_a) > 0:
        k = int_k % len(array_a)
        array_b = array_a[: -k]
        array_c = array_a[-k:]
        return array_c + array_b
    else:
        return array_a


# TapeEquilibrium
# easy
def tape_equilibrium(array_a):
    sum_of_a = sum(array_a)
    diff_min = 1000 * len(array_a)
    right = sum_of_a
    for i in range(len(array_a) - 1):
        right = right - array_a[i]
        diff = abs(sum_of_a - 2 * right)
        if diff < diff_min:
            diff_min = diff
    return diff_min


# PermMissingElem
# easy
def perm_missing_elem(array_a):
    array_a.sort()
    if len(array_a) == 0:
        return 1
    else:
        if array_a[0] != 1:
            return 1
        if array_a[-1] != len(array_a) + 1:
            return len(array_a) + 1
        for i in range(len(array_a) - 1):
            if array_a[i + 1] != array_a[i] + 1:
                return array_a[i] + 1


# FrogJmp
# easy
def frog_jmp(int_x, int_y, int_d):
    n = (int_y - int_x) // int_d
    if (int_y - int_x) % int_d > 0:
        n += 1
    return n


# MissingInteger
# easy
def missing_integer(array_a):
    array_a.sort()
    result = 1
    for a in array_a:
        if a < result:
            pass
        elif a == result:
            result += 1
        else:
            return result
    return result


# PermCheck
# easy
def perm_check(array_a):
    array_a.sort()
    if array_a[0] != 1:
        return 0
    if array_a[-1] != len(array_a):
        return 0
    for i in range(len(array_a) - 1):
        if array_a[i + 1] == array_a[i]:
            return 0
    return 1


# FrogRiverOne
# easy
def frog_river_one(int_x, array_a):
    path = [0] * int_x
    sum_of_array = 0
    for i in range(len(array_a)):
        if array_a[i] <= int_x:
            if path[array_a[i] - 1] == 0:
                path[array_a[i] - 1] = 1
                sum_of_array += 1
        if sum_of_array == int_x:
            return i
    return -1


# MaxCounters
# medium
def max_counters(int_n, array_a):
    result = [0] * int_n
    min_value = 0
    max_value = 0
    for i in range(len(array_a)):
        if 1 <= array_a[i] <= int_n:
            if result[array_a[i] - 1] < min_value:
                result[array_a[i] - 1] = min_value + 1
            else:
                result[array_a[i] - 1] += 1
            if result[array_a[i] - 1] > max_value:
                max_value = result[array_a[i] - 1]
        if array_a[i] == int_n + 1:
            min_value = max_value
    for j in range(len(result)):
        if result[j] < min_value:
            result[j] = min_value
    return result


# PassingCars
# easy
def passing_cars(array_a):
    result = 0
    counter = 0
    for i in range(1, len(array_a) + 1):
        if array_a[-i] == 0:
            result += counter
            if result > 1000000000:
                return -1
        else:
            counter += 1
    return result


# CountDiv
# easy
def count_div(array_a, array_b, int_k):
    start = array_a // int_k
    end = array_b // int_k
    return end - start + (1 if array_a % int_k == 0 else 0)


# MinAvgTwoSlice
# medium 90%
def min_avg_two_slice(array_a):
    avg_min = 10000
    pos = -1
    for p in range(len(array_a) - 1):
        avg2 = (array_a[p] + array_a[p + 1]) * 1.0 / 2
        if avg2 < avg_min:
            avg_min = avg2
            pos = p
        if p + 2 < len(array_a):
            avg3 = (array_a[p] + array_a[p + 1] + array_a[p + 2]) * 1.0 / 3
            if avg3 < avg_min:
                avg_min = avg3
                pos = p
    return pos


# GenomicRangeQuery
# medium

def genomic_range_query(array_s, array_p, array_q):
    n = len(array_s)
    a = [-1] * n
    c = [-1] * n
    g = [-1] * n
    for i in range(n):
        if i > 0:
            a[i] = a[i - 1]
            c[i] = c[i - 1]
            g[i] = g[i - 1]
        if array_s[i] == 'array_a':
            a[i] = i
        elif array_s[i] == 'C':
            c[i] = i
        elif array_s[i] == 'G':
            g[i] = i
    result = []
    for k in range(len(array_p)):
        p = array_p[k]
        q = array_q[k]
        if a[q] >= p:
            result.append(1)
        elif c[q] >= p:
            result.append(2)
        elif g[q] >= p:
            result.append(3)
        else:
            result.append(4)
    return result


# MaxProductOfThree
# easy
def max_product_of_three(array_a):
    array_a = sorted(array_a)
    return max(array_a[-1] * array_a[-2] * array_a[-3], array_a[0] * array_a[1] * array_a[-1])


def max_product_of_three2(array_a):
    positive = []
    negative = []
    for a in array_a:
        if a > 0:
            positive.append(a)
        else:
            negative.append(a)
    positive.sort()
    negative.sort()
    result = None
    if len(positive) >= 3:
        p = positive[-3] * positive[-2] * positive[-1]
        if result is None or p > result:
            result = p
    if len(positive) >= 2 and len(negative) >= 1:
        p = positive[0] * positive[1] * negative[-1]
        if result is None or p > result:
            result = p
    if len(positive) >= 1 and len(negative) >= 2:
        p = positive[-1] * negative[0] * negative[1]
        if result is None or p > result:
            result = p
    if len(negative) >= 3:
        p = negative[-3] * negative[-2] * negative[-1]
        if result is None or p > result:
            result = p
    return result


# Triangle
# easy
def triangle(array_a):
    array_a.sort()
    for i in range(len(array_a) - 2):
        p = array_a[i]
        q = array_a[i + 1]
        r = array_a[i + 2]
        if p + q > r and q + r > p and r + p > q:
            return 1
    return 0


# NumberOfDiscIntersections
# medium 56%


# Brackets
# easy
def brackets(array_s):
    stack = []
    for s in array_s:
        if s in '([{':
            stack.append(s)
        else:
            if len(stack) > 0:
                prev = stack.pop()
            else:
                return 0
            if s == ')' and prev == '(':
                pass
            elif s == ']' and prev == '[':
                pass
            elif s == '}' and prev == '{':
                pass
            else:
                return 0
    if len(stack) > 0:
        return 0
    return 1


# Fish
# easy
def fish(array_a, array_b):
    result_i = []
    result_b = []
    for q, b_q in enumerate(array_b):
        if q == 0:
            result_i.append(q)
            result_b.append(b_q)
            continue
        while b_q == 0 and len(result_b) > 0:
            if result_b[-1] == 1:
                b_p = result_b.pop()
                p = result_i.pop()
                if array_a[p] > array_a[q]:
                    q = p
                    b_q = b_p
                else:
                    p = q
                    b_p = b_q
            else:
                break
        result_i.append(q)
        result_b.append(b_q)
    return len(result_i)


# StoneWall
# easy
def stone_wall(array_h):
    count = 0
    base = []
    for i in range(len(array_h)):
        while len(base) > 0 and array_h[i] < base[-1]:
            base.pop()
        if len(base) == 0 or array_h[i] > base[-1]:
            base.append(array_h[i])
            count += 1
    return count


# MaxProfit
# easy 66%
def max_profit(array_a):
    profit = 0
    profit_max = 0
    for i in range(1, len(array_a)):
        profit = max(0, profit + array_a[i] - array_a[i - 1])
        profit_max = max(profit, profit_max)
    return profit_max


# Leader
# The leader of this sequence is the element
# whose value occurs more than n/2 times.
# Let’s create an empty stack onto which
# we will be pushing consecutive elements.
# After each such operation we check whether the two
# elements at the top of the stack are dierent.
# If they are, we remove them from the stack.
def golden_leader(array_a):
    n = len(array_a)
    size = 0
    value = None
    for k in range(n):
        if size == 0:
            size += 1
            value = array_a[k]
        else:
            if value != array_a[k]:
                size -= 1
            else:
                size += 1
    candidate = -1
    if size > 0:
        candidate = value
    leader = -1
    count = 0
    for k in range(n):
        if array_a[k] == candidate:
            count += 1
    if count > n // 2:
        leader = candidate
    return leader
