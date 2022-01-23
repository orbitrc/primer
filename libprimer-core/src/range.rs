use std::ops::Range;

#[repr(C)]
struct pr_range {
    range: Box<Range>,
}

//====================
// Constructor
//====================
#[no_mangle]
pub extern "C" fn pr_range_new_i8(start: i8, end: i8) -> *mut pr_range {
    let boxed = Box::new((start..end));

    Box::new(pr_range {
        range: boxed,
    }).into_raw()
}

#[no_mangle]
pub extern "C" fn pr_range_new_u8(start: u8, end: u8) -> *mut pr_range {
    let boxed = Box::new((start..end));

    Box::new(pr_range {
        range: boxed,
    }).into_raw()
}

#[no_mangle]
pub extern "C" fn pr_range_new_i16(start: i16, end: i16) -> *mut pr_range {
    let boxed = Box::new((start..end));

    Box::new(pr_range {
        range: boxed,
    }).into_raw()
}

#[no_mangle]
pub extern "C" fn pr_range_new_u16(start: u16, end: u16) -> *mut pr_range {
    let boxed = Box::new((start..end));

    Box::new(pr_range {
        range: boxed,
    }).into_raw()
}

#[no_mangle]
pub extern "C" fn pr_range_new_i32(start: i32, end: i32) -> *mut pr_range {
    let boxed = Box::new((start..end));

    Box::new(pr_range {
        range: boxed,
    }).into_raw()
}

#[no_mangle]
pub extern "C" fn pr_range_new_u32(start: u32, end: u32) -> *mut pr_range {
    let boxed = Box::new((start..end));

    Box::new(pr_range {
        range: boxed,
    }).into_raw()
}

#[no_mangle]
pub extern "C" fn pr_range_new_i64(start: i64, end: i64) -> *mut pr_range {
    let boxed = Box::new((start..end));

    Box::new(pr_range {
        range: boxed,
    }).into_raw()
}

#[no_mangle]
pub extern "C" fn pr_range_new_u64(start: u64, end: u64) -> *mut pr_range {
    let boxed = Box::new((start..end));

    Box::new(pr_range {
        range: boxed,
    }).into_raw()
}

//===================
// Destructor
//===================
#[no_mangle]
pub extern "C" fn pr_range_free(range: *mut pr_range) {
    unsafe {
        Box::from_raw(range);
    }
}
