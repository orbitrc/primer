use std::os::raw::c_char;
use std::ffi::{CStr, CString};

use serde_json;

pub type JsonValue = serde_json::Value;
pub type Map = serde_json::map::Map<String, JsonValue>;
pub type JsonNumber = serde_json::Number;
pub use serde_json::json;

#[repr(u8)]
#[allow(non_camel_case_types)]
#[derive(Clone, Copy)]
pub enum pr_json_type {
    PR_JSON_TYPE_NULL = 0,
    PR_JSON_TYPE_BOOL = 1,
    PR_JSON_TYPE_INT = 2,
    PR_JSON_TYPE_DOUBLE = 3,
    PR_JSON_TYPE_STRING = 4,
    PR_JSON_TYPE_ARRAY = 5,
    PR_JSON_TYPE_OBJECT = 6,
}

#[repr(C)]
pub struct pr_json_value {
    pub value: Box<JsonValue>,
    pub c_string: Box<CString>,
    pub json_type: pr_json_type,
}

#[no_mangle]
pub extern "C" fn pr_json_value_to_bool(json: pr_json_value) -> bool {
    match json.json_type {
        pr_json_type::PR_JSON_TYPE_BOOL => {
            match *(json.value) {
                JsonValue::Bool(true) => {
                    return true;
                },
                JsonValue::Bool(false) => {
                    return false;
                },
                _ => {
                    return false;
                }
            }
        },
        _ => {
            return false;
        },
    }
}

#[no_mangle]
pub extern "C" fn pr_json_value_to_int(json: pr_json_value) -> i64 {
    match json.json_type {
        pr_json_type::PR_JSON_TYPE_INT => {
            let opt = (*(json.value)).as_i64();
            match opt {
                Some(val) => { return val; },
                None => { return 0; },
            }
        },
        _ => {
            return 0;
        },
    }
}

#[no_mangle]
pub extern "C" fn pr_json_value_to_double(json: pr_json_value) -> f64 {
    match json.json_type {
        pr_json_type::PR_JSON_TYPE_DOUBLE => {
            let opt = (*(json.value)).as_f64();
            match opt {
                Some(val) => { return val; },
                None => { return 0.0; },
            }
        },
        pr_json_type::PR_JSON_TYPE_INT => {
            let opt = (*(json.value)).as_f64();
            match opt {
                Some(val) => { return val; },
                None => { return 0.0; },
            }
        },
        _ => {
            return 0.0;
        },
    }
}

#[no_mangle]
pub extern "C" fn pr_json_value_to_string(json: pr_json_value) -> *const c_char {
    match json.json_type {
        pr_json_type::PR_JSON_TYPE_STRING => {
            match *(json.value) {
                JsonValue::String(val) => {
                    val.as_ptr() as *const c_char
                },
                _ => {
                    return std::ptr::null();
                }
            }
        },
        _ => {
            return std::ptr::null();
        }
    }
}

#[no_mangle]
pub extern "C" fn pr_json_null_new() -> pr_json_value {
    pr_json_value {
        value: Box::new(JsonValue::Null),
        c_string: Box::new(CString::new("").unwrap()),
        json_type: pr_json_type::PR_JSON_TYPE_NULL,
    }
}

#[no_mangle]
pub extern "C" fn pr_json_bool_new(value: bool) -> pr_json_value {
    pr_json_value {
        value: Box::new(JsonValue::Bool(value)),
        c_string: Box::new(CString::new("").unwrap()),
        json_type: pr_json_type::PR_JSON_TYPE_BOOL,
    }
}

#[no_mangle]
pub extern "C" fn pr_json_int_new(value: i64) -> pr_json_value {
    pr_json_value {
        value: Box::new(JsonValue::Number(JsonNumber::from(value))),
        c_string: Box::new(CString::new("").unwrap()),
        json_type: pr_json_type::PR_JSON_TYPE_INT,
    }
}

#[no_mangle]
pub extern "C" fn pr_json_double_new(value: f64) -> pr_json_value {
    let opt = JsonNumber::from_f64(value);

    match opt {
        Some(val) => pr_json_value {
            value: Box::new(JsonValue::Number(val)),
            c_string: Box::new(CString::new("").unwrap()),
            json_type: pr_json_type::PR_JSON_TYPE_DOUBLE,
        },
        None => pr_json_value {
            value: Box::new(JsonValue::Null),
            c_string: Box::new(CString::new("").unwrap()),
            json_type: pr_json_type::PR_JSON_TYPE_NULL,
        }
    }
}

#[no_mangle]
pub extern "C" fn pr_json_string_new(value: *const c_char) -> pr_json_value {
    let c_str = unsafe { CStr::from_ptr(value) };
    let rust_str = c_str.to_str().unwrap();

    pr_json_value {
        value: Box::new(JsonValue::String(rust_str.to_owned())),
        c_string: Box::new(c_str.to_owned()),
        json_type: pr_json_type::PR_JSON_TYPE_STRING,
    }
}

#[no_mangle]
pub extern "C" fn pr_json_array_new() -> pr_json_value {
    pr_json_value {
        value: Box::new(json!([])),
        c_string: Box::new(CString::new("").unwrap()),
        json_type: pr_json_type::PR_JSON_TYPE_ARRAY,
    }
}

#[no_mangle]
pub extern "C" fn pr_json_array_push_back(array: *mut pr_json_value, value: pr_json_value) {
    let json_type = unsafe { (*array).json_type };

    match json_type {
        pr_json_type::PR_JSON_TYPE_ARRAY => {},
        _ => {
            return;
        }
    }

    let opt = unsafe { (*array).value.as_array() };
    match opt {
        Some(vec) => {
            let mut vec = vec.to_owned();
            vec.push(*value.value);
            unsafe {
                (*array).value = Box::new(JsonValue::Array(vec));
            }
        },
        None => {},
    }
}
