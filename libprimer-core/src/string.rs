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
