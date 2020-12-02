input1 = '../input/01.txt'
magic_number = 2020


def get_input(file_name):
    with open(file_name) as f:
        stuff = set([int(line) for line in f])
    return stuff


def show_me_the_money(big_money):
    for expense in big_money:
        is_this_it = magic_number - expense
        if is_this_it in big_money:
            return expense, is_this_it
    print('wtf')
    return None


if __name__ == '__main__':
    lol = get_input(input1)
    ans = show_me_the_money(lol)
    print(ans[0] * ans[1])

