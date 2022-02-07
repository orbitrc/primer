pub mod json;
pub mod random;
pub mod range;

#[cfg(test)]
mod tests {
    use super::json::JsonValue;
    use super::json::Map;
    use super::json::JsonNumber;
    use super::json::json;

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
