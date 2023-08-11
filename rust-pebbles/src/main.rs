const ROWS: usize = 4;
const COLS: usize = 5;

const BOARD: [[i32; COLS]; ROWS] = [
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

fn fp2(r: i32, c: i32, mut t: [[i32; COLS]; ROWS]) -> i32 {
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

fn fp3(r: i32, c: i32, mut t: [[i32; COLS]; ROWS]) -> i32 {
    match (r, c) {
        (0, 0) => BOARD[r as usize][c as usize],
        (a, b) => {
            for i in 0..=a {
                for j in 0..=b {
                    match (i, j) {
                        (0, 0) => t[0][0] = BOARD[0][0],
                        (0, x) => t[0][x as usize] = t[0][(x - 1) as usize] + BOARD[0][x as usize],
                        (x, 0) => t[x as usize][0] = t[(x - 1) as usize][0] + BOARD[x as usize][0],
                        (x, y) => {
                            t[x as usize][y as usize] = (std::cmp::max(
                                t[(x - 1) as usize][y as usize],
                                t[x as usize][(y - 1) as usize],
                            )) + BOARD[x as usize][y as usize];
                        }
                    }
                }
            }
            t[r as usize][c as usize]
        }
    }
}

fn main() {
    // initializes the table to contain all -1's
    let mtable = [[-1; COLS]; ROWS];
    let ttable = [[-1; COLS]; ROWS];

    let a: i32 = fp1(3, 4);
    assert_eq!(a, 5);
    println!("Naive recursive solution    : {}", a);

    let b: i32 = fp2(3, 4, mtable);
    assert_eq!(b, 5);
    println!("Memoized recursive solution : {}", b);

    let c: i32 = fp3(3, 4, ttable);
    assert_eq!(c, 5);
    println!("Tabulized iterative solution: {}", c);
}
