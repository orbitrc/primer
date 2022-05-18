pub mod json;
pub mod random;
pub mod range;
pub mod string;

#[cfg(test)]
mod tests {
    use std::ffi::CString;

    use super::json::JsonValue;
    use super::json::Map;
    use super::json::JsonNumber;
    use super::json::json;

    use super::string::*;

    use super::random::Random;

    #[test]
    fn json_value() {
        let null = JsonValue::Null;
        assert_eq!(null, JsonValue::Null);
    }

    #[test]
    fn json_object() {
        let mut map: Map = Map::new();
        map.insert(String::from("Foo"),
            JsonValue::Number(JsonNumber::from(42)));
        let object = JsonValue::Object(map);
        let j = json!({
            "Foo": 42,
        });
        assert_eq!(object, j);
    }

    #[test]
    fn json_double() {
        let j = json!({
            "int": 42,
            "double": 42.3,
        });

        assert_eq!(j["int"], 42);
        assert_eq!(j["double"].is_f64(), true);
    }

    #[test]
    fn pr_json_array() {
        let mut arr = super::json::pr_json_array_new();
        let num = super::json::pr_json_int_new(42);
        let null = super::json::pr_json_null_new();
        super::json::pr_json_array_push_back(&mut arr as *mut super::json::pr_json_value, num);
        super::json::pr_json_array_push_back(&mut arr as *mut super::json::pr_json_value, null);
        assert_eq!(
            arr.value.as_array().unwrap(),
            json!([42, JsonValue::Null]).as_array().unwrap()
        );
    }

    #[test]
    fn pr_string_construct() {
        let rust_c_string = CString::new("Hello").unwrap();
        let c_string_ptr = rust_c_string.into_raw();

        let _pr_string = pr_string_from_c_str(c_string_ptr);

        pr_string_free(_pr_string);
    }

    #[test]
    fn pr_string_contains_() {
        let rust_c_string = CString::new("Lorem ipsum dolor").unwrap();
        let c_string_ptr = rust_c_string.into_raw();

        let pr_string_full = pr_string_from_c_str(c_string_ptr);

        let rust_c_string = CString::new("ipsum").unwrap();
        let c_string_ptr = rust_c_string.into_raw();

        let pr_string_part = pr_string_from_c_str(c_string_ptr);

        assert_eq!(pr_string_contains(pr_string_full, pr_string_part), true);

        // Free.
        pr_string_free(pr_string_part);
        pr_string_free(pr_string_full);
    }

    #[test]
    fn rand_both_exclusive_inclusive() {
        let _random_exclusive = i8::random(0..5);
        let _random_inclusive = i8::random(0..=5);
    }

    #[test]
    fn rand_not_nan_or_infinity() {
        let random_number = f64::random(0.0..=1.0);
        assert_ne!(random_number, f64::NAN);
        assert_ne!(random_number, f64::INFINITY);
    }
}
