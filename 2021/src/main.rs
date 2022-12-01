use std::env;
use std::error::Error;
use std::path::Path;

#[cfg(day01)]
use day01::solve;

#[cfg(day02)]
use day02::solve;

#[cfg(day01)]
mod day01;

#[cfg(day02)]
mod day02;

fn main() -> Result<(), Box<dyn Error>> {
    let args = env::args().last().unwrap();
    let path = Path::new(&args);

    solve(path)
}
