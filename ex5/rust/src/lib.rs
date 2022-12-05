use std::collections::HashMap;

pub enum CrateMover {
    _9000,
    _9001,
}

pub fn solve(input: &str, mover: CrateMover) -> String {
    let mut map: HashMap<usize, Vec<char>> = HashMap::new();

    let mut chunks = input.split("\n\n");
    let top = chunks.next().unwrap();

    top.split('\n').for_each(|line| {
        line.chars()
            .enumerate()
            .filter(|(_i, c)| ('A'..='Z').contains(c))
            .for_each(|(i, c)| {
                let index = 1 + (i - 1) / 4;
                map.entry(index)
                    .and_modify(|v| v.insert(0, c))
                    .or_insert_with(|| vec![c]);
            });
    });

    let moves = chunks.next().unwrap();
    moves.trim().split('\n').for_each(|line| {
        let mut cmds = line.split(' ');
        cmds.next().expect("move");
        let count: usize = cmds.next().expect("count").parse().expect("int");
        cmds.next().expect("from");
        let from: usize = cmds.next().expect("from").parse().expect("int");
        cmds.next().expect("to");
        let to: usize = cmds.next().expect("to").parse().expect("int");

        let from_vec = map.get_mut(&from).expect("not in map");
        let from_len = from_vec.len();
        let transfer = from_vec.split_off(from_len - count);
        let to_vec = map.get_mut(&to).expect("not in map");

        match mover {
            CrateMover::_9000 => {
                for item in transfer.into_iter().rev() {
                    to_vec.push(item);
                }
            }
            CrateMover::_9001 => {
                to_vec.extend_from_slice(&transfer);
            }
        }
    });

    let max = *map.keys().max().unwrap();
    (1..=max)
        .filter_map(|i| map.get(&i))
        .map(|v| v[v.len() - 1])
        .collect()
}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn test_part_one() {
        let input = include_str!("../../test.input");
        assert_eq!(&solve(input, CrateMover::_9000), "CMZ");
    }

    #[test]
    fn part_one() {
        let input = include_str!("../../input");
        assert_eq!(&solve(input, CrateMover::_9000), "QGTHFZBHV");
    }

    #[test]
    fn test_part_two() {
        let input = include_str!("../../test.input");
        assert_eq!(&solve(input, CrateMover::_9001), "MCD");
    }

    #[test]
    fn part_two() {
        let input = include_str!("../../input");
        assert_eq!(&solve(input, CrateMover::_9001), "MGDMPSZTM");
    }
}
