from pathlib import Path
import copy

test_data = """..@@.@@@@.
@@@.@.@.@@
@@@@@.@.@@
@.@@@@..@.
@@.@@@@.@@
.@@@@@@@.@
.@.@.@.@@@
@.@@@.@@@@
.@@@@@@@@.
@.@.@@@.@."""

def read_file(path: str):
    return Path(path).read_text(encoding='utf-8')

def part_one(arr: list[str]):
    modified_arr = copy.deepcopy(arr)
    # for line in arr:
        # print(line)
    answer = 0
    for y in range(len(arr)):
        row_chars = list(arr[y])
        for x in range(len(arr[0])):
            neighbours = 0

            if x > 0 and arr[y][x-1] == "@":
                neighbours += 1
            if x+1 < len(arr[y]) and arr[y][x+1] == "@":
                neighbours += 1
            if y > 0 and arr[y-1][x] == "@":
                neighbours += 1
            if y+1 < len(arr) and arr[y+1][x] == "@":
                neighbours += 1
            

            if x > 0 and y > 0 and arr[y-1][x-1] == "@":
                neighbours += 1
            if x+1 < len(arr[y]) and y+1 < len(arr) and arr[y+1][x+1] == "@":
                neighbours += 1
            if y > 0 and x+1 < len(arr[y]) and arr[y-1][x+1] == "@":
                neighbours += 1
            if x > 0 and y+1 < len(arr) and arr[y+1][x-1] == "@":
                neighbours += 1

            if arr[y][x] == "@" and neighbours < 4:
                answer += 1
                row_chars[x] = "x"
                # print(f" {x}, {y} ")

        modified_arr[y] = "".join(row_chars)

    return answer, modified_arr

def main():
    data = read_file('input.txt').splitlines()
    answer_one, _ = part_one(data)
    print(f"answer_one is {answer_one}")

    answer_two = 0
    current_answer = 0
    data_two = data

    while True:
        current_answer, data_two = part_one(data_two)        
        answer_two += current_answer
        # print(f"answer is {answer_two}")
        if current_answer == 0:
            break

    print(f"answer_two is {answer_two}")


main()
