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

impl<R: RangeBounds<u8> + SampleRange<u8>> Random<R> for u8 {
    fn random(range: R) -> u8 {
        thread_rng().gen_range(range)
    }
}

impl<R: RangeBounds<i16> + SampleRange<i16>> Random<R> for i16 {
    fn random(range: R) -> i16 {
        thread_rng().gen_range(range)
    }
}

impl<R: RangeBounds<u16> + SampleRange<u16>> Random<R> for u16 {
    fn random(range: R) -> u16 {
        thread_rng().gen_range(range)
    }
}

impl<R: RangeBounds<i32> + SampleRange<i32>> Random<R> for i32 {
    fn random(range: R) -> i32 {
        thread_rng().gen_range(range)
    }
}

impl<R: RangeBounds<u32> + SampleRange<u32>> Random<R> for u32 {
    fn random(range: R) -> u32 {
        thread_rng().gen_range(range)
    }
}

impl<R: RangeBounds<i64> + SampleRange<i64>> Random<R> for i64 {
    fn random(range: R) -> i64 {
        thread_rng().gen_range(range)
    }
}

impl<R: RangeBounds<u64> + SampleRange<u64>> Random<R> for u64 {
    fn random(range: R) -> u64 {
        thread_rng().gen_range(range)
    }
}

impl<R: RangeBounds<f32> + SampleRange<f32>> Random<R> for f32 {
    fn random(range: R) -> f32 {
        thread_rng().gen_range(range)
    }
}

impl<R: RangeBounds<f64> + SampleRange<f64>> Random<R> for f64 {
    fn random(range: R) -> f64 {
        thread_rng().gen_range(range)
    }
}

#[no_mangle]
pub extern "C" fn pr_random(start: i64, end: i64, exclusive: bool) -> i64 {
    match exclusive {
        true => i64::random(start..end),
        false => i64::random(start..=end),
    }
}

#[no_mangle]
pub extern "C" fn pr_random_u(start: u64, end: u64, exclusive: bool) -> u64 {
    match exclusive {
        true => u64::random(start..end),
        false => u64::random(start..=end),
    }
}
