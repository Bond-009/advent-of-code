use std::error::Error;
use std::fs;
use std::path::Path;

fn get_input(path: &Path) -> Result<Vec<u16>, Box<dyn Error>> {
    let data = fs::read_to_string(path)?;
    Ok(data.lines().filter_map(|x| x.parse::<u16>().ok()).collect())
}

#[cfg(part1)]
pub fn solve(path: &Path) -> Result<(), Box<dyn Error>> {
    let values = get_input(path)?;
    let mut last = u16::MAX;
    let mut larger = 0;
    for v in values {
        if v > last {
            larger += 1;
        }

        last = v;
    }

    println!("{}", larger);
    Ok(())
}

#[cfg(part2)]
pub fn solve(path: &Path) -> Result<(), Box<dyn Error>> {
    let values = get_input(path)?;
    let mut increase = 0;
    for i in 0..(values.len() - 3) {
        if values[i] < values[i + 3] {
            increase += 1;
        }
    }

    println!("{}", increase);
    Ok(())
}
