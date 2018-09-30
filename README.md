## Project Description

Time analysis and comparision of concurrent mergesort with normal mergesort.

## Compile and Run

- Compile code using gcc command
- After compilation, run './a.out'


## Time comparison of Concurrent and Normal mergesort

### For n = 10^5

- Normal mergesort - 0.001 second
- Concurrent mergesort - 17.83 second

### For n = 10^7

- Normal mergesort - 0.044 second
- Concurrent mergesort - It will not be able to run on normal computer because it will fork too much for this big input.

## Analysis

- Expectation - Concurrent mergesort would run faster because of shared memory.
- Result - Simple mergesort is running faster than concurrent mergesort.
- Reason about above result - 
    - Concurrent mergesort is accessing left array and right array simultaneously.
    - When concurrent mergesort is accessing left array, left array is loaded into cache memory. Simultaneously, concurrent mergesort tries to access right array then cache miss would happen . Because of cache miss happens multiple times, execution of code slows down.
    - Whereas in simple mergesort, 2 or 3 elements of left and right array is accessing at a time. therefore that elements can stay in cache and retrieval time of those elements is much lesser than retrieval time of elements in concurrent mergesort.

