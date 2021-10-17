pub mod json;
pub mod random;

#[cfg(test)]
mod tests {
    use super::json::JsonValue;
    use super::json::Map;
    use super::json::JsonNumber;
    use super::json::json;

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
        let object = JsonValue::Object(map);
        let j = json!({
            "Foo": 42.0,
        });
        assert_eq!(object, j);
    }
}
