use std::collections::HashMap;

pub fn traverse(input: &str) -> (u64, u64) {
    let mut sizes: HashMap<String, u64> = HashMap::new();
    let mut dir_stack: Vec<String> = vec![];
    let mut assert_ls = false;

    for line in input.trim().split('\n') {
        if assert_ls {
            assert_ls = false;
            assert_eq!(line, "$ ls");
            continue;
        }
        if line == "$ cd .." {
            dir_stack.pop().expect("cannot go dir up");
            continue;
        }
        if line.starts_with("$ cd") {
            assert_ls = true;
            dir_stack.push(line[5..].to_string());
            continue;
        }
        if line.starts_with("dir ") {
            continue;
        }
        let mut pieces = line.split(' ');
        let size: u64 = pieces.next().unwrap().parse().unwrap();
        for i in 1..=dir_stack.len() {
            let path = dir_stack[..i].join("/");
            sizes.entry(path).and_modify(|v| *v += size).or_insert(size);
        }
    }

    let sum_small = sizes
        .iter()
        .filter(|(_k, v)| **v <= 100000)
        .map(|(_k, v)| *v)
        .sum();

    let disk_size = 70000000;
    let need_free = 30000000;
    let delete_at_least = need_free + sizes["/"] - disk_size;
    let delete_dir = sizes
        .into_iter()
        .filter(|(_k, v)| *v >= delete_at_least)
        .map(|(_k, v)| v)
        .min()
        .unwrap();

    (sum_small, delete_dir)
}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn test_both() {
        let input = include_str!("../../test.input");
        assert_eq!(traverse(input), (95437, 24933642));
    }

    #[test]
    fn both() {
        let input = include_str!("../../input");
        assert_eq!(traverse(input), (1644735, 1300850));
    }
}
