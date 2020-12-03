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


def show_me_the_money_part_two(big_money):
    for expense in big_money:
        target = magic_number - expense
        for x in big_money:
            is_this_it = target - x
            if is_this_it == x or is_this_it == expense:
                # TODO: Is this actually impossible?
                print(f'is_this_it={is_this_it} which equals expense={expense} or x={x}')
                continue
            if is_this_it in big_money:
                return expense, x, is_this_it
    print('huh?')
    return None


if __name__ == '__main__':
    lol = get_input(input1)
    ans = show_me_the_money(lol)
    print(ans[0] * ans[1])
    ans2 = show_me_the_money_part_two(lol)
    print(ans2[0] * ans2[1] * ans2[2])

