# Rust Programming Language Handbook

## Chapter 4: Ownership and Borrowing
Rust’s central feature is ownership. All programs have to manage the way they use computer memory while running.
- Every value in Rust has an owner.
- There can only be one owner at a time.
- When the owner goes out of scope, the value will be dropped.

## Chapter 12: Building a Fast Command Line Network Parser
When building high-speed network parsers in Rust, zero-copy parsing using slices (`&[u8]`) avoids unnecessary allocations, drastically improving throughput. Always prefer iterators and borrowing over cloning strings or byte vectors in hot loops.
