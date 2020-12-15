#!/usr/bin/env python3


from dataclasses import dataclass, field
from pathlib import Path
from typing import Set, Tuple, List, Dict, Iterable, Union


@dataclass
class Bag:
    name: str
    children: Set[Tuple[str, int]] = field(default_factory=set, init=False)
    descendants: Set[Tuple[str, int]] = field(default_factory=set, init=False, repr=False)

    def has_childen(self) -> bool:
        return len(self.children) > 0

    def has_desired(self) -> bool:
        return "shiny_gold" in [p[0] for p in self.descendants]


def get_insides(line: str) -> Tuple[str, List[Tuple[str, int]]]:
    cut = line.strip().split(" bags contain ")
    key = cut[0].replace(" ", "_")
    raw = line.strip().split(" bags contain ")[1]
    if "no other" in raw:
        return key, []
    raws = raw.replace(" bags", "").replace(".", "").replace(" bag", "").split(", ")
    fixed = [(r[2:].replace(" ", "_"), int(r[:2])) for r in raws]
    return key, fixed


def part1(d: Dict[str, Bag]) -> int:
    return sum([v.has_desired() for k, v in d.items()])


def unroll(d: Dict[str, Bag], names: Iterable[str]) -> List[str]:
    result = []
    for name in names:
        for subbag in d[name].children:
            result += [subbag[0] for _ in range(subbag[1])]
    return result


def part2(d: Dict[str, Bag]) -> int:
    unrolled = []
    running = ["shiny_gold"]
    while running:
        running = unroll(d, running)
        unrolled += running
    return len(unrolled)


def main():
    lines = Path("data/day7.dat").read_text().strip().split("\n")
    dicted = {}
    for line in lines:
        k, v = get_insides(line)
        b = Bag(name=k)
        for vv in v:
            b.children.add(vv)
        dicted[k] = b

    for k, v in dicted.items():
        children_to_check = list(v.children)
        while len(children_to_check) > 0:
            current = children_to_check.pop()
            new = list(dicted[current[0]].children)
            dicted[k].descendants.add(current)
            children_to_check += new

    print("part 1:", part1(dicted))
    print("part 2:", part2(dicted))


if __name__ == "__main__":
    main()
