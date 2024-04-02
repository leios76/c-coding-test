extern "C" {
    fn scanf(fmt: *const u8, ...) -> i32;
}

fn main() {
    let mut a: i32 = 0;
    let mut b: i32 = 0;
    unsafe { scanf("%d %d".as_ptr(), &mut a, &mut b) };
    println!("{}", a + b);
}