import re
from dataclasses import dataclass
from typing import List

input = '../input/02.txt'
input_a = '../input/02a.txt'


@dataclass
class Policy:
    lo: int
    hi: int
    ch: str
    pw: str


def policy_packager(file: str) -> List[Policy]:
    policies = []
    with open(file) as f:
        for line in f:
            it = re.finditer(r'\w+', line)
            # TODO: This is hideous. Does python have `emplace`-like semantics?
            policy = Policy(int(next(it)[0]), int(next(it)[0]), next(it)[0], next(it)[0])
            policies.append(policy)
    return policies


def count_valid_passwords(policies: List[Policy]) -> int:
    good = 0
    for p in policies:
        seen = 0
        for c in p.pw:
            if c == p.ch:
                seen += 1
        if p.lo <= seen <= p.hi:
            good += 1
    return good


def count_valid_passwords_redux(policies: List[Policy]) -> int:
    good = 0
    for p in policies:
        x = p.pw[p.lo - 1] == p.ch
        y = p.pw[p.hi - 1] == p.ch
        if x ^ y:
            good += 1
    return good


def main():
    policies = policy_packager(input)
    good_stuff = count_valid_passwords(policies)
    print(good_stuff)
    more_good_stuff = count_valid_passwords_redux(policies)
    # not 750
    print(more_good_stuff)


if __name__ == '__main__':
    main()
