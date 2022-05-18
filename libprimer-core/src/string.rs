use std::os::raw::c_char;
use std::ffi::CString;

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
pub extern "C" fn pr_string_new() -> pr_string {
    pr_string {
        string: Box::new(String::new()),
        c_string: Box::new(CString::new("").unwrap()),
    }
}

#[no_mangle]
pub extern "C" fn pr_string_from_c_str(c_str: *const c_char) -> pr_string {
    let c_string = unsafe { CString::from_raw(c_str as *mut c_char) };
    let string = c_string.into_string().unwrap();

    let rust_str = string.to_owned();
    pr_string {
        string: Box::new(string),
        c_string: Box::new(CString::new(rust_str).unwrap()),
    }
}

#[no_mangle]
pub extern "C" fn pr_string_from_c_str_sized(c_str: *const c_char, len: u64) -> pr_string {
    let rust_string: String = unsafe { String::from_raw_parts(
        c_str as *mut u8,
        len as usize,
        len as usize
    ) };

    let tmp = rust_string.to_owned();
    pr_string {
        string: Box::new(rust_string),
        c_string: Box::new(CString::new(tmp).unwrap()),
    }
}

#[no_mangle]
pub extern "C" fn pr_string_contains(_string: pr_string, sub: pr_string) -> bool {
    _string.string.contains(sub.string.as_str())
}

#[no_mangle]
pub extern "C" fn pr_string_starts_with(_string: pr_string, sub: pr_string) -> bool {
    _string.string.starts_with(sub.string.as_str())
}

#[no_mangle]
pub extern "C" fn pr_string_ends_with(_string: pr_string, sub: pr_string) -> bool {
    _string.string.ends_with(sub.string.as_str())
}

#[no_mangle]
pub extern "C" fn pr_string_free(_string: pr_string) {
    // TODO: Free the boxed String instance.
    let _ = _string.string;
}
