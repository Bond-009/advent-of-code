use std::str::FromStr;
use std::error::Error;
use std::fs;
use std::path::Path;

#[derive(PartialEq, Debug)]
enum Command {
    Forward(i32),
    Down(i32),
    Up(i32)
}

#[derive(Debug)]
struct ParseCommandError;

impl FromStr for Command {
    type Err = ParseCommandError;

    fn from_str(s: &str) -> Result<Self, Self::Err> {
        let i = s.find(' ').ok_or(ParseCommandError)?;
        let num = s[i + 1..].parse::<i32>().map_err(|_| ParseCommandError)?;
        match &s[..i] {
            "forward" => Ok(Command::Forward(num)),
            "down" => Ok(Command::Down(num)),
            "up" => Ok(Command::Up(num)),
            _ => Err(ParseCommandError)
        }
    }
}

#[cfg(part1)]
pub fn solve(path: &Path) -> Result<(), Box<dyn Error>> {
    let data = fs::read_to_string(path)?;
    let mut hor = 0;
    let mut depth = 0;
    for command in data.lines().filter_map(|x| x.parse::<Command>().ok()) {
        match command {
            Command::Forward(v) => hor += v,
            Command::Down(v) => depth += v,
            Command::Up(v) => depth -= v
        }
    }

    println!("{}", hor * depth);
    Ok(())
}

#[cfg(part2)]
pub fn solve(path: &Path) -> Result<(), Box<dyn Error>> {
    let data = fs::read_to_string(path)?;
    let mut aim = 0;
    let mut hor = 0;
    let mut depth = 0;
    for command in data.lines().filter_map(|x| x.parse::<Command>().ok()) {
        match command {
            Command::Forward(v) => {
                hor += v;
                depth += aim * v;
            },
            Command::Down(v) => aim += v,
            Command::Up(v) => aim -= v
        }
    }

    println!("{}", hor * depth);
    Ok(())
}
