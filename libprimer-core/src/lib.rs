pub mod json;
pub mod random;
pub mod range;
pub mod string;
pub mod vector;

#[cfg(test)]
mod tests {
    use std::ffi::CString;

    use super::json::JsonValue;
    use super::json::Map;
    use super::json::JsonNumber;
    use super::json::json;

    use super::string::*;

    use super::random::Random;

    use super::vector::*;

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
        // From c_str.
        let rust_c_string = CString::new("Hello").unwrap();
        let c_string_ptr = rust_c_string.into_raw();

        let _pr_string: *mut pr_string = pr_string_from_c_str(c_string_ptr);

        pr_string_free(_pr_string);

        // From c_str with size.
        let rust_c_string = CString::new("World").unwrap();
        let c_string_ptr = rust_c_string.into_raw();

        let _pr_string: *mut pr_string = pr_string_from_c_str_sized(
            c_string_ptr, 5);

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

        assert_eq!(
            pr_string_contains(
                pr_string_full as *const pr_string,
                pr_string_part as *const pr_string
            ),
            true
        );

        // Free.
        pr_string_free(pr_string_part);
        pr_string_free(pr_string_full);
    }

    #[test]
    fn pr_string_split_() {
        let pr_s = pr_string_from_rust_string(String::from("A;B;C"));
        let pr_delim = pr_string_from_rust_string(String::from(";"));
        let split = pr_string_split(pr_s, pr_delim);
        assert_eq!(pr_string_vector_length(split), 3);

        let a = pr_string_vector_get(split, 0);
        let comp_a = pr_string_from_rust_string(String::from("A"));
        assert_eq!(pr_string_eq(a, comp_a), true);

        pr_string_free(comp_a);
        pr_string_free(a);
        pr_string_free(pr_delim);
        pr_string_free(pr_s);
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

    #[test]
    fn pr_vector_construct() {
        let v = pr_string_vector_new();
        pr_string_vector_free(v);
    }

    #[test]
    fn pr_unicode_scalar_vector_construct() {
        let v = pr_unicode_scalar_vector_new();
        pr_unicode_scalar_vector_free(v);
    }
}
