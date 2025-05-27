pub use crate::error::CoreError;

pub type Result<T> = core::result::Result<T, CoreError>;

// Generic Wrapper tuple struct for newtype pattern
// pub struct W<T>(pub T);
