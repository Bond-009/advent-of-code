use std::env;
use std::error::Error;

fn main() -> Result<(), Box<dyn Error>> {
    println!("cargo:rerun-if-env-changed=AOCDAY");
    println!("cargo:rerun-if-env-changed=AOCPART");

    if let Ok(version) = env::var("AOCDAY") {
        let version = version.parse::<u32>()?;
        match version {
            1..=2 => println!("cargo:rustc-cfg=day{:02}", version),
            _ => panic!("Not a valid day")
        };
    } else {
        panic!("No date specified");
    }

    if let Ok(version) = env::var("AOCPART") {
        let version = version.parse::<u32>()?;
        match version {
            1..=2 => println!("cargo:rustc-cfg=part{}", version),
            _ => panic!("Not a valid part")
        };
    } else {
        panic!("No part specified");
    }

    Ok(())
}
