use std::collections::HashSet;

pub fn one(input: &str) -> u64 {
    input
        .trim()
        .split('\n')
        .map(|line| {
            let half = line.len() / 2;
            (&line[0..half], &line[half..])
        })
        .map(|(left, right)| {
            let l_chars: HashSet<_> = left.chars().collect();
            let r_chars: HashSet<_> = right.chars().collect();

            *l_chars.intersection(&r_chars).next().unwrap()
        })
        .map(|c| match c {
            'a'..='z' => c as u64 - 96,
            'A'..='Z' => c as u64 - 64 + 26,
            _ => unreachable!(),
        })
        .sum()
}

pub fn two(input: &str) -> u64 {
    let lines: Vec<_> = input.trim().split('\n').collect();
    lines
        .chunks_exact(3)
        .map(|chunk| {
            let one_chars: HashSet<_> = chunk[0].chars().collect();
            let two_chars: HashSet<_> = chunk[1].chars().collect();
            let three_chars: HashSet<_> = chunk[2].chars().collect();

            let i: HashSet<_> = one_chars.intersection(&two_chars).copied().collect();
            *i.intersection(&three_chars).next().unwrap()
        })
        .map(|c| match c {
            'a'..='z' => c as u64 - 96,
            'A'..='Z' => c as u64 - 64 + 26,
            _ => unreachable!(),
        })
        .sum()
}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn test_part_one() {
        let input = include_str!("../../test.input");
        assert_eq!(one(input), 157);
    }

    #[test]
    fn part_one() {
        let input = include_str!("../../input");
        assert_eq!(one(input), 8176);
    }

    #[test]
    fn test_part_two() {
        let input = include_str!("../../test.input");
        assert_eq!(two(input), 70);
    }

    #[test]
    fn part_two() {
        let input = include_str!("../../input");
        assert_eq!(two(input), 8176);
    }
}
