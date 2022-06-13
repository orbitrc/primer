use super::string::pr_string;

#[repr(C)]
pub struct pr_string_vector {
    vector: Vec<*mut pr_string>,
}

#[repr(C)]
pub struct pr_unicode_scalar_vector {
    vector: Vec<char>,
}

//===================
// String Vector
//===================

#[no_mangle]
pub extern "C" fn pr_string_vector_new() -> *mut pr_string_vector {
    let boxed = Box::new(pr_string_vector {
        vector: Vec::<*mut pr_string>::new(),
    });

    Box::into_raw(boxed)
}

#[no_mangle]
pub extern "C" fn pr_string_vector_free(vector: *mut pr_string_vector) {
    let _ = unsafe { Box::from_raw(vector) };
}

#[no_mangle]
pub extern "C" fn pr_string_vector_length(vector: *const pr_string_vector) -> u64 {
    let boxed = unsafe { Box::from_raw(vector as *mut pr_string_vector) };

    let ret = boxed.vector.len() as u64;

    Box::into_raw(boxed);

    ret
}

#[no_mangle]
pub extern "C" fn pr_string_vector_push(vector: *mut pr_string_vector, string: *mut pr_string) {
    let mut boxed = unsafe { Box::from_raw(vector) };

    boxed.vector.push(string);

    Box::into_raw(boxed);
}

#[no_mangle]
pub extern "C" fn pr_string_vector_get(vector: *const pr_string_vector, index: u64) -> *mut pr_string {
    let boxed = unsafe { Box::from_raw(vector as *mut pr_string_vector) };

    let string = boxed.vector[index as usize];

    Box::into_raw(boxed);

    string
}

//==========================
// Unicode Scalar Vector
//==========================

#[no_mangle]
pub extern "C" fn pr_unicode_scalar_vector_new() -> *mut pr_unicode_scalar_vector {
    let boxed = Box::new(pr_unicode_scalar_vector {
        vector: Vec::<char>::new(),
    });

    Box::into_raw(boxed)
}

#[no_mangle]
pub extern "C" fn pr_unicode_scalar_vector_free(vector: *mut pr_unicode_scalar_vector) {
    let _ = unsafe { Box::from_raw(vector) };
}

#[no_mangle]
pub extern "C" fn pr_unicode_scalar_vector_length(vector: *const pr_unicode_scalar_vector) -> u64 {
    let boxed = unsafe { Box::from_raw(vector as *mut pr_unicode_scalar_vector) };

    let ret = boxed.vector.len() as u64;

    Box::into_raw(boxed);

    ret
}

#[no_mangle]
pub extern "C" fn pr_unicode_scalar_vector_push(vector: *mut pr_unicode_scalar_vector, scalar: u32) {
    let mut boxed = unsafe { Box::from_raw(vector) };

    boxed.vector.push(char::from_u32(scalar).unwrap());

    Box::into_raw(boxed);
}

#[no_mangle]
pub extern "C" fn pr_unicode_scalar_vector_get(vector: *const pr_string_vector, index: u64) -> u32 {
    let boxed = unsafe { Box::from_raw(vector as *mut pr_unicode_scalar_vector) };

    let rust_char = boxed.vector[index as usize];

    Box::into_raw(boxed);

    rust_char as u32
}

