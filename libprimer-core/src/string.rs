use std::os::raw::c_char;
use std::ffi::CString;

#[repr(C)]
pub struct pr_code_point {
    cp: u32,
}

#[repr(C)]
pub struct pr_string {
    string: Box<String>,
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
pub extern "C" fn pr_string_from_c_str(c_str: *const c_char) -> pr_string {
    let c_string = unsafe { CString::from_raw(c_str as *mut c_char) };
    let string = c_string.into_string().unwrap();

    pr_string {
        string: Box::new(string),
    }
}
