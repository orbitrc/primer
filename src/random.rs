use std::ops::Range;
use std::ops::RangeBounds;

use rand::{Rng, thread_rng};
use rand::distributions::uniform::SampleRange;

/// Random trait provides random method to numeric types.
pub trait Random<R: RangeBounds<Self>> {
    fn random(range: R) -> Self where Self: Sized;
}

impl<R: RangeBounds<i8> + SampleRange<i8>> Random<R> for i8 {
    fn random(range: R) -> i8 {
        thread_rng().gen_range(range)
    }
}

impl Random for u8 {
    fn random(range: Range<u8>) -> u8 {
        thread_rng().gen_range(range)
    }
}

impl Random for i16 {
    fn random(range: Range<i16>) -> i16 {
        thread_rng().gen_range(range)
    }
}

impl Random for u16 {
    fn random(range: Range<u16>) -> u16 {
        thread_rng().gen_range(range)
    }
}

impl Random for i32 {
    fn random(range: Range<i32>) -> i32 {
        thread_rng().gen_range(range)
    }
}

impl Random for u32 {
    fn random(range: Range<u32>) -> u32 {
        thread_rng().gen_range(range)
    }
}

impl Random for i64 {
    fn random(range: Range<i64>) -> i64 {
        thread_rng().gen_range(range)
    }
}

impl Random for u64 {
    fn random(range: Range<u64>) -> u64 {
        thread_rng().gen_range(range)
    }
}

impl Random for f32 {
    fn random(range: Range<f32>) -> f32 {
        thread_rng().gen_range(range)
    }
}

impl Random for f64 {
    fn random(range: Range<f64>) -> f64 {
        thread_rng().gen_range(range)
    }
}

