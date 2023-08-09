const BOARD: [[i32; 5]; 4] = [
    [0, 0, 1, 0, 1],
    [0, 0, 1, 1, 0],
    [1, 0, 0, 0, 1],
    [0, 1, 0, 0, 1],
];

fn fp1(r: i32, c: i32) -> i32 {
    match (r, c) {
        (-1, _) => 0,
        (_, -1) => 0,
        (x, y) => BOARD[r as usize][c as usize] + std::cmp::max(fp1(x - 1, y), fp1(x, y - 1)),
    }
}

fn fp2(r: i32, c: i32, mut t: [[i32; 5]; 4]) -> i32 {
    match (r, c) {
        (-1, _) => 0,
        (_, -1) => 0,
        (r, c) => {
            if t[r as usize][c as usize] != -1 {
                t[r as usize][c as usize]
            } else {
                let max = std::cmp::max(fp2(r - 1, c, t), fp2(r, c - 1, t));
                t[r as usize][c as usize] = BOARD[r as usize][c as usize] + max;
                t[r as usize][c as usize]
            }
        }
    }
}

fn main() {
    let _mtable = [[-1; 5]; 4];
    let ttable = [[-1; 5]; 4];

    let a: i32 = fp1(3, 4);
    assert_eq!(a, 5);
    println!("Naive recursive solution: {}", a);

    let b: i32 = fp2(3, 4, ttable);
    assert_eq!(a, 5);
    println!("Memoized recursive solution: {}", b);
}
