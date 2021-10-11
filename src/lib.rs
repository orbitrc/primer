pub mod json;
pub mod random;

#[cfg(test)]
mod tests {
    use super::json::JsonValue;

    #[test]
    fn json_value() {
        let null = JsonValue::Null;
        assert_eq!(null, JsonValue::Null);
    }
}
