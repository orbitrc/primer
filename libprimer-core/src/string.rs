use std::os::raw::c_char;
use std::ffi::CString;
use std::ffi::CStr;

use seshat::unicode::Ucd;

use super::vector::pr_string_vector;
use super::vector::pr_string_vector_new;
use super::vector::pr_string_vector_push;
use super::vector::pr_unicode_scalar_vector;
use super::vector::pr_unicode_scalar_vector_new;
use super::vector::pr_unicode_scalar_vector_push;

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
    let mut v: Vec<u8> = vec![];
    for i in 0..len {
        unsafe {
            v.push(*c_str.offset(i as isize) as u8);
        }
    }

    let rust_string = String::from_utf8(v).unwrap();
    // CString containing null-character is invalid.
    let mut null_terminated = rust_string.clone();
    if let Some(pos) = rust_string.find('\0') {
        null_terminated = rust_string[..pos].to_string();
    }

    let boxed = Box::new(pr_string {
        string: Box::new(rust_string.to_owned()),
        c_string: Box::new(CString::new(null_terminated).unwrap()),
    });

    Box::into_raw(boxed)
}

pub fn pr_string_from_rust_string(string: String) -> *mut pr_string {
    let boxed = Box::new(pr_string {
        string: Box::new(string.to_owned()),
        c_string: Box::new(CString::new(string).unwrap()),
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
pub extern "C" fn pr_string_eq(_string: *const pr_string, other: *const pr_string) -> bool {
    let this_boxed = unsafe { Box::from_raw(_string as *mut pr_string) };
    let other_boxed = unsafe { Box::from_raw(other as *mut pr_string) };

    let ret = *this_boxed.string == *other_boxed.string;

    Box::into_raw(this_boxed);
    Box::into_raw(other_boxed);

    ret
}

#[no_mangle]
pub extern "C" fn pr_string_lt(_string: *const pr_string, other: *const pr_string) -> bool {
    let this_boxed = unsafe { Box::from_raw(_string as *mut pr_string) };
    let other_boxed = unsafe { Box::from_raw(other as *mut pr_string) };

    let ret = *this_boxed.string < *other_boxed.string;

    Box::into_raw(this_boxed);
    Box::into_raw(other_boxed);

    ret
}

#[no_mangle]
pub extern "C" fn pr_string_gt(_string: *const pr_string, other: *const pr_string) -> bool {
    let this_boxed = unsafe { Box::from_raw(_string as *mut pr_string) };
    let other_boxed = unsafe { Box::from_raw(other as *mut pr_string) };

    let ret = *this_boxed.string > *other_boxed.string;

    Box::into_raw(this_boxed);
    Box::into_raw(other_boxed);

    ret
}

#[no_mangle]
pub extern "C" fn pr_string_trim(_string: *const pr_string) -> *mut pr_string {
    let boxed = unsafe { Box::from_raw(_string as *mut pr_string) };

    let trimmed = boxed.string.trim();

    let string = Box::new(pr_string {
        string: Box::new(trimmed.to_owned()),
        c_string: Box::new(CString::new(trimmed).unwrap()),
    });

    Box::into_raw(boxed);

    Box::into_raw(string)
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
pub extern "C" fn pr_string_split(_string: *const pr_string, delim: *const pr_string) -> *mut pr_string_vector {
    let boxed = unsafe { Box::from_raw(_string as *mut pr_string) };
    let delim_boxed = unsafe { Box::from_raw(delim as *mut pr_string) };

    let splitted = boxed.string.split(delim_boxed.string.as_str());

    // Create vector.
    let v = pr_string_vector_new();

    // Push splitted strings to the vector.
    for s in splitted {
        let pr_s = pr_string_from_rust_string(s.to_string());
        pr_string_vector_push(v, pr_s);
    }

    Box::into_raw(boxed);
    Box::into_raw(delim_boxed);

    v
}

#[no_mangle]
pub extern "C" fn pr_string_c_str(_string: *const pr_string) -> *const c_char {
    let boxed = unsafe { Box::from_raw(_string as *mut pr_string) };

    let raw = boxed.c_string.as_ptr();

    Box::into_raw(boxed);

    raw
}

#[no_mangle]
pub extern "C" fn pr_string_add(_string: *const pr_string, other: *const pr_string) -> *mut pr_string {
    let src_boxed = unsafe { Box::from_raw(_string as *mut pr_string) };
    let dst_boxed = unsafe { Box::from_raw(other as *mut pr_string) };

    let added = (*(src_boxed.string)).to_owned() + &(*(dst_boxed.string));
    let boxed = Box::new(pr_string {
        string: Box::new(added.clone()),
        c_string: Box::new(CString::new(added).unwrap()),
    });

    Box::into_raw(src_boxed);
    Box::into_raw(dst_boxed);

    Box::into_raw(boxed)
}

#[no_mangle]
pub extern "C" fn pr_string_unicode_scalars(string: *const pr_string) -> *mut pr_unicode_scalar_vector {
    let boxed = unsafe { Box::from_raw(string as *mut pr_string) };

    let chars = boxed.string.chars();

    let v = pr_unicode_scalar_vector_new();

    for ch in chars {
        pr_unicode_scalar_vector_push(v, ch as u32);
    }

    Box::into_raw(boxed);

    v
}

#[no_mangle]
pub extern "C" fn pr_string_free(_string: *mut pr_string) {
    let boxed = unsafe { Box::from_raw(_string) };
    let _ = boxed.string;
    let _ = boxed.c_string;
}

//=============
// Unicode
//=============
#[no_mangle]
pub extern "C" fn pr_unicode_version() -> *mut pr_string {
    let version = seshat::unicode::UNICODE_VERSION.to_string();
    let pr_s = pr_string_from_rust_string(version);

    pr_s
}

#[no_mangle]
pub extern "C" fn pr_unicode_scalar_na(scalar: u32) -> *mut pr_string {
    let rust_char = char::from_u32(scalar).unwrap();
    let na = rust_char.na();
    let pr_s = pr_string_from_rust_string(na);

    pr_s
}
