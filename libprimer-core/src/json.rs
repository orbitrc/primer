use std::os::raw::c_char;
use std::ffi::CStr;

use serde_json;

pub type JsonValue = serde_json::Value;
pub type Map = serde_json::map::Map<String, JsonValue>;
pub type JsonNumber = serde_json::Number;
pub use serde_json::json;

#[repr(u8)]
#[allow(non_camel_case_types)]
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
    value: Box<JsonValue>,
    json_type: pr_json_type,
}

#[no_mangle]
pub extern "C" fn pr_json_null_new() -> pr_json_value {
    pr_json_value {
        value: Box::new(JsonValue::Null),
        json_type: pr_json_type::PR_JSON_TYPE_NULL,
    }
}

#[no_mangle]
pub extern "C" fn pr_json_bool_new(value: bool) -> pr_json_value {
    pr_json_value {
        value: Box::new(JsonValue::Bool(value)),
        json_type: pr_json_type::PR_JSON_TYPE_BOOL,
    }
}

#[no_mangle]
pub extern "C" fn pr_json_int_new(value: i64) -> pr_json_value {
    pr_json_value {
        value: Box::new(JsonValue::Number(JsonNumber::from(value))),
        json_type: pr_json_type::PR_JSON_TYPE_INT,
    }
}

#[no_mangle]
pub extern "C" fn pr_json_double_new(value: f64) -> pr_json_value {
    let opt = JsonNumber::from_f64(value);

    match opt {
        Some(val) => pr_json_value {
            value: Box::new(JsonValue::Number(val)),
            json_type: pr_json_type::PR_JSON_TYPE_DOUBLE,
        },
        None => pr_json_value {
            value: Box::new(JsonValue::Null),
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
        json_type: pr_json_type::PR_JSON_TYPE_STRING,
    }
}
