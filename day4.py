#!/usr/bin/env python

from pathlib import Path
import re


HEX_RE = re.compile(r"^#([a-f]|[0-9]){6}$")
PID_RE = re.compile(r"^[0-9]{9}$")

REQUIRED_KEYS = (
    "byr",
    "iyr",
    "eyr",
    "hgt",
    "hcl",
    "ecl",
    "pid",
)


def good_byr(passport):
    val = passport["byr"]
    try:
        yr = int(val)
    except ValueError:
        return False
    return yr >= 1920 and yr <= 2002


def good_iyr(passport):
    val = passport["iyr"]
    try:
        yr = int(val)
    except ValueError:
        return False
    return yr >= 2010 and yr <= 2020


def good_eyr(passport):
    val = passport["eyr"]
    try:
        yr = int(val)
    except ValueError:
        return False
    return yr >= 2020 and yr <= 2030


def good_hgt(passport):
    val = passport["hgt"]
    if val.endswith("cm"):
        h = int(val[:-2])
        return (h >= 150 and h <= 193)
    elif val.endswith("in"):
        h = int(val[:-2])
        return (h >= 59 and h <= 76)
    return False


def good_hcl(passport):
    val = passport["hcl"]
    re_res = HEX_RE.match(val)
    return re_res is not None


def good_ecl(passport):
    val = passport["ecl"]
    return val in ("amb", "blu", "brn", "gry", "grn", "hzl", "oth")


def good_pid(passport):
    val = passport["pid"]
    re_res = PID_RE.match(val)
    return re_res is not None


def passport_to_dict(passport):
    d = {}
    for entry in passport.split():
        k, v = entry.split(":")
        d[k] = v
    return d


def keys_check(passport):
    keys = passport.keys()
    for entry in REQUIRED_KEYS:
        if entry not in keys:
            return 0
    return 1


def values_check(passport):
    if not keys_check(passport):
        return False
    checks = [
        good_byr(passport),
        good_iyr(passport),
        good_eyr(passport),
        good_hgt(passport),
        good_hcl(passport),
        good_ecl(passport),
        good_pid(passport),
    ]
    return sum(checks) == len(checks)


def main():
    input_file = Path("day4.dat")
    passports = input_file.read_text().split("\n\n")
    n_good1 = 0
    n_good2 = 0
    for passport in passports:
        p = passport_to_dict(passport)
        n_good1 += keys_check(p)
        n_good2 += values_check(p)

    print(n_good1, n_good2)


if __name__ == "__main__":
    main()
