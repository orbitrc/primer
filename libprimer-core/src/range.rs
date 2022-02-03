use super::random::Random;

#[repr(C)]
pub struct pr_range {
    start: i64,
    end: i64,
    exclusive: bool,
}

//====================
// Constructor
//====================
#[no_mangle]
pub extern "C" fn pr_range_new(start: i64, end: i64, exclusive: bool) -> pr_range {
    pr_range {
        start: start as i64,
        end: end as i64,
        exclusive: exclusive,
    }
}

//===================
// Destructor
//===================

#[no_mangle]
pub extern "C" fn pr_range_free(_range: pr_range) {
}

//===================
// Member access
//===================

#[no_mangle]
pub extern "C" fn pr_range_start(range: pr_range) -> i64 {
    range.start
}

#[no_mangle]
pub extern "C" fn pr_range_end(range: pr_range) -> i64 {
    range.end
}

#[no_mangle]
pub extern "C" fn pr_range_exclusive(range: pr_range) -> bool {
    range.exclusive
}

#[no_mangle]
pub extern "C" fn pr_range_contains(range: pr_range, value: i64) -> bool {
    match range.exclusive {
        true => (range.start..range.end).contains(&value),
        false => (range.start..=range.end).contains(&value),
    }
}

#[no_mangle]
pub extern "C" fn pr_range_random(range: pr_range) -> i64 {
    match range.exclusive {
        true => i64::random(range.start..range.end),
        false => i64::random(range.start..=range.end),
    }
}

#[no_mangle]
pub extern "C" fn pr_range_random_u(range: pr_range) -> u64 {
    match range.exclusive {
        true => u64::random(range.start as u64..range.end as u64),
        false => u64::random(range.start as u64..=range.end as u64),
    }
}
