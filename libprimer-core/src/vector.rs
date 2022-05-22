use super::string::pr_string;

#[repr(C)]
pub struct pr_string_vector {
    vector: Vec<*mut pr_string>,
}

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
