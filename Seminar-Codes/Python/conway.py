# This function generates new row
# Of conway's sequence from previous one
def get_conway(lst):
    if len(lst) == 1:
        return [1, lst[0]]
    ans = get_conway(lst[1:])
    if lst[1] == lst[0]:
        ans[0] = ans[0] + 1
        return ans
    else:
        return [1, lst[0]] + ans

# This function generates row-th row of conways sequence
# If first row is [n]
# for example conway_seq(1, 2) is [1, 1] and conway_seq(1, 3) is [2, 1]
# You can get more info here:
# https://en.wikipedia.org/wiki/Look-and-say_sequence
def conway_seq(n, row):
    if row == 1:
        return [n]
    lst = conway_seq(n, row - 1)
    return get_conway(lst)
