pub mod json;
pub mod random;

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
            JsonValue::Number(JsonNumber::from_f64(42.0).unwrap()));
        map["Foo"] = json!(42);
        let object = JsonValue::Object(map);
        let j = json!({
            "Foo": 42,
        });
        assert_eq!(object, j);
    }

    #[test]
    fn rand_not_nan_or_infinity() {
        let random_number = f64::random(0.0..1.0);
        assert_eq!(random_number, f64::NAN);
        assert_eq!(random_number, f64::INFINITY);
    }
}
