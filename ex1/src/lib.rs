pub fn sum_largest(input: &str) -> u64 {
    input
        .split("\n\n")
        .map(|chunk| {
            chunk
                .trim()
                .split('\n')
                .map(|l| l.trim().parse::<u64>().unwrap())
                .sum()
        })
        .max()
        .unwrap()
}

pub fn sum_largest_three(input: &str) -> u64 {
    let mut totals = input
        .split("\n\n")
        .map(|chunk| {
            chunk
                .trim()
                .split('\n')
                .map(|l| l.trim().parse::<u64>().unwrap())
                .sum()
        })
        .collect::<Vec<_>>();

    totals.sort();
    let len = totals.len();
    totals[len - 3..len].iter().sum()
}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn test_part_one() {
        let input = include_str!("../test.input");
        assert_eq!(sum_largest(input), 24000);
    }

    #[test]
    fn part_one() {
        let input = include_str!("../input");
        assert_eq!(sum_largest(input), 66616);
    }

    #[test]
    fn test_part_two() {
        let input = include_str!("../test.input");
        assert_eq!(sum_largest_three(input), 45000);
    }

    #[test]
    fn part_two() {
        let input = include_str!("../input");
        assert_eq!(sum_largest_three(input), 199172);
    }
}
