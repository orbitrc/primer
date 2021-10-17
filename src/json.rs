use serde_json;

pub type JsonValue = serde_json::Value;
pub type Map = serde_json::map::Map<String, JsonValue>;
pub type Number = serde_json::Number;
pub use serde_json::json;