use colored::Colorize;
use std::{
    fs::File,
    io::{BufRead, BufReader},
    thread::sleep,
    time::Duration,
};
use terminal_size::{Height, Width, terminal_size};

const TEST: &str = "\
.......S.......
...............
.......^.......
...............
......^.^......
...............
.....^.^.^.....
...............
....^.^...^....
...............
...^.^...^.^...
...............
..^...^.....^..
...............
.^.^.^.^.^...^.
...............
";

const VERTICAL_LINE: char = '│';

type Grid = Vec<Vec<char>>;

fn grid_from_file(filename: &str) -> Grid {
    let file = File::open(filename).unwrap();
    let reader = BufReader::new(file);
    reader
        .lines()
        .map(|res| res.unwrap().chars().collect())
        .collect()
}

fn grid_from_test(test_data: &str) -> Grid {
    test_data.lines().map(|res| res.chars().collect()).collect()
}

fn mark_grid(grid: &mut Grid, y: usize, x: usize) {
    let current = grid[y][x];
    if current == '.' {
        grid[y][x] = VERTICAL_LINE;
    } else if current == '^' {
        grid[y][x] = 'X';
    }
}

fn main() {
    let mut input_data = grid_from_file("input.txt");
    let mut test_data = grid_from_test(TEST);

    assert_eq!(21, part_one(&mut test_data));
    let answer_one = part_one(&mut input_data);
    println!("\n\t answer_one {answer_one}");
}

fn part_one(mut grid: &mut Grid) -> usize {
    let length = grid.len();
    let width = grid[1].len();

    pretty_print_grid(&grid, 0, true);
    for y in 1..length {
        for x in 0..width {
            let above = grid[y - 1][x];

            if above == 'S' {
                mark_grid(&mut grid, y, x);
            } else if above == VERTICAL_LINE {
                mark_grid(&mut grid, y, x);
            } else if above == 'X' {
                if x > 0 {
                    mark_grid(&mut grid, y, x - 1);
                }
                if x < width + 1 {
                    mark_grid(&mut grid, y, x + 1);
                }
            }
        }

        pretty_print_grid(&grid, y, false);
        sleep(Duration::from_millis(50));
    }

    let mut answer = 0;
    for line in grid {
        answer += line.iter().filter(|&&c| c == 'X').count()
    }

    answer
}

fn pretty_print_grid(grid: &Grid, color_till: usize, clean: bool) {
    let (width, height) = terminal_size()
        .map(|(Width(w), Height(h))| (w as usize, h as usize))
        .unwrap_or((80, 24));

    if grid[0].len() + 4 > width {
        println!("\t{}", "Terminal is not wide enough".red());
        return;
    }

    let padding_x = (width - grid[0].len() + 4) / 2;

    let height = height - 3;
    let raw_start = color_till.saturating_sub(height / 2);
    let max_start = grid.len().saturating_sub(height);
    let start = raw_start.min(max_start);
    let end = (start + height).min(grid.len());

    if clean {
        println!("{}", "\n".repeat(end - start + 2));
    }

    print!("\x1b[{}A", end - start + 2);

    println!(
        "{}",
        format!("{}╭{}╮", " ".repeat(padding_x), "─".repeat(grid.len() + 1)).bright_black()
    );

    for i in start..end {
        let row = &grid[i];
        let mut display = String::with_capacity(row.len() + 4);
        display.push_str(&"│ ".bright_black().to_string());

        for item in row {
            if item == &'S' || item == &'X' || item == &'│' {
                display.push_str(&if i <= color_till {
                    item.to_string().red().to_string()
                } else {
                    item.to_string()
                });
            } else {
                display.push_str(&item.to_string().bright_black().to_string());
            }
        }
        display.push_str(&" │".bright_black().to_string());
        println!("{}{}", " ".repeat(padding_x), display)
    }

    println!(
        "{}",
        format!("{}╰{}╯", " ".repeat(padding_x), "─".repeat(grid.len() + 1)).bright_black()
    );
}
