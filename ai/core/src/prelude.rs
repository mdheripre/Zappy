pub use crate::error::CoreError;

pub type Result<T> = core::result::Result<T, CoreError>;
