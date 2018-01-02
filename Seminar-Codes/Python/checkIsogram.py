# This method checks if given string is isogram
# For example "abcz" is isogram
# But "babzc" isn't
def check_isogram(st):
    dict = []
    for i in st:
        if i in dict:
            return False
        else:
            dict.append(i)
    return True
