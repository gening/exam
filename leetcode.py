# coding: utf-8


def length_of_longest_sub_string(s):
    """
    :type s: str
    :rtype: int
    """
    d = dict()
    l_max = len(s)
    for i in range(l_max):
        c = s[i]
        if c in d:
            d[c].append(i)
        else:
            d[c] = [i]
    flag = []
    for c in d:
        if len(d[c]) >= 2:
            flag += d[c]
    flag = sorted(flag)
    flag.insert(0, 0)
    flag.append(l_max)
    local_max = 0
    for j in range(len(flag) - 1):
        length = flag[j + 1] - flag[j]
        if length > local_max:
            local_max = length
    return local_max


print(length_of_longest_sub_string('abcabcbb'))
