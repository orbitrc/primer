use std::os::raw::c_char;
use std::ffi::CString;
use std::ffi::CStr;

#[repr(C)]
pub struct pr_code_point {
    cp: u32,
}

#[repr(C)]
pub struct pr_string {
    string: Box<String>,
    c_string: Box<CString>,
}

#[repr(C)]
pub struct pr_string_utf8_view {
    bytes: Vec<u8>,
}

#[no_mangle]
pub extern "C" fn pr_code_point_new(cp: u32) -> pr_code_point {
    pr_code_point {
        cp: cp,
    }
}

#[no_mangle]
pub extern "C" fn pr_string_new() -> *mut pr_string {
    let boxed = Box::new(pr_string {
        string: Box::new(String::new()),
        c_string: Box::new(CString::new("").unwrap()),
    });

    Box::into_raw(boxed)
}

#[no_mangle]
pub extern "C" fn pr_string_from_c_str(c_str: *const c_char) -> *mut pr_string {
    let c_str = unsafe { CStr::from_ptr(c_str) };
    let to_str = c_str.to_str().unwrap();

    let rust_str = to_str.to_owned();
    let boxed = Box::new(pr_string {
        string: Box::new(to_str.to_owned()),
        c_string: Box::new(CString::new(rust_str).unwrap()),
    });

    Box::into_raw(boxed)
}

#[no_mangle]
pub extern "C" fn pr_string_from_c_str_sized(c_str: *const c_char, len: u64) -> *mut pr_string {
    let rust_string: String = unsafe { String::from_raw_parts(
        c_str as *mut u8,
        len as usize,
        len as usize
    ) };

    let tmp = rust_string.to_owned();
    let boxed = Box::new(pr_string {
        string: Box::new(rust_string),
        c_string: Box::new(CString::new(tmp).unwrap()),
    });

    Box::into_raw(boxed)
}

#[no_mangle]
pub extern "C" fn pr_string_cloned(string: *const pr_string) -> *mut pr_string {
    let orig_boxed = unsafe { Box::from_raw(string as *mut pr_string) };

    let new_boxed = Box::new(pr_string {
        string: Box::new((*orig_boxed.string).clone()),
        c_string: Box::new((*orig_boxed.c_string).clone()),
    });

    Box::into_raw(orig_boxed);

    Box::into_raw(new_boxed)
}

#[no_mangle]
pub extern "C" fn pr_string_contains(_string: *const pr_string, sub: *const pr_string) -> bool {
    let full_boxed = unsafe {
        Box::from_raw(_string as *mut pr_string)
    };
    let sub_boxed = unsafe {
        Box::from_raw(sub as *mut pr_string)
    };
    let ret = full_boxed.string.contains(sub_boxed.string.as_str());

    Box::into_raw(sub_boxed);
    Box::into_raw(full_boxed);

    ret
}

#[no_mangle]
pub extern "C" fn pr_string_starts_with(_string: *const pr_string, sub: *const pr_string) -> bool {
    let full_boxed = unsafe { Box::from_raw(_string as *mut pr_string) };
    let sub_boxed = unsafe { Box::from_raw(sub as *mut pr_string) };

    let ret = full_boxed.string.starts_with(sub_boxed.string.as_str());

    Box::into_raw(sub_boxed);
    Box::into_raw(full_boxed);

    ret
}

#[no_mangle]
pub extern "C" fn pr_string_ends_with(_string: *const pr_string, sub: *const pr_string) -> bool {
    let full_boxed = unsafe { Box::from_raw(_string as *mut pr_string) };
    let sub_boxed = unsafe { Box::from_raw(sub as *mut pr_string) };

    let ret = full_boxed.string.ends_with(sub_boxed.string.as_str());

    Box::into_raw(sub_boxed);
    Box::into_raw(full_boxed);

    ret
}

#[no_mangle]
pub extern "C" fn pr_string_free(_string: *mut pr_string) {
    let boxed = unsafe { Box::from_raw(_string) };
    let _ = boxed.string;
    let _ = boxed.c_string;
}
