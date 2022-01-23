use std::ops::Range;

#[repr(C)]
pub struct pr_range {
    range: Box<Range<i64>>,
}

//====================
// Constructor
//====================
#[no_mangle]
pub extern "C" fn pr_range_new_i8_(start: i8, end: i8) -> pr_range {
    let boxed = Box::new(start as i64..end as i64);

    pr_range {
        range: boxed,
    }
}

#[no_mangle]
pub extern "C" fn pr_range_new_i8(start: i8, end: i8) -> pr_range {
    let boxed = Box::new(start as i64..end as i64);

    pr_range {
        range: boxed,
    }
}

#[no_mangle]
pub extern "C" fn pr_range_new_u8(start: u8, end: u8) -> pr_range {
    let boxed = Box::new(start as i64..end as i64);

    pr_range {
        range: boxed,
    }
}

#[no_mangle]
pub extern "C" fn pr_range_new_i16(start: i16, end: i16) -> pr_range {
    let boxed = Box::new(start as i64..end as i64);

    pr_range {
        range: boxed,
    }
}

#[no_mangle]
pub extern "C" fn pr_range_new_u16(start: u16, end: u16) -> pr_range {
    let boxed = Box::new(start as i64..end as i64);

    pr_range {
        range: boxed,
    }
}

#[no_mangle]
pub extern "C" fn pr_range_new_i32(start: i32, end: i32) -> pr_range {
    let boxed = Box::new(start as i64..end as i64);

    pr_range {
        range: boxed,
    }
}

#[no_mangle]
pub extern "C" fn pr_range_new_u32(start: u32, end: u32) -> pr_range {
    let boxed = Box::new(start as i64..end as i64);

    pr_range {
        range: boxed,
    }
}

#[no_mangle]
pub extern "C" fn pr_range_new_i64(start: i64, end: i64) -> pr_range {
    let boxed = Box::new(start..end);

    pr_range {
        range: boxed,
    }
}

#[no_mangle]
pub extern "C" fn pr_range_new_u64(start: u64, end: u64) -> pr_range {
    let boxed = Box::new(start as i64..end as i64);

    pr_range {
        range: boxed,
    }
}

//===================
// Destructor
//===================

#[no_mangle]
pub extern "C" fn pr_range_free(range: pr_range) {
    let ptr = Box::into_raw(range.range);

    unsafe {
        Box::from_raw(ptr);
    }
}

//===================
// Member access
//===================

#[no_mangle]
pub extern "C" fn pr_range_start(range: pr_range) -> i64 {
    range.range.start
}

#[no_mangle]
pub extern "C" fn pr_range_end(range: pr_range) -> i64 {
    range.range.end
}
