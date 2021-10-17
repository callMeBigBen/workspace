# a simple thread pool which provides asynchronous task execution

# features
1. vector-based RingBuffer as task container. 
2. lockfree offset management by exploiting std::atomic and CAS

# env
1. C++ 11 or higher
2. pthread

# testing
1. tested under SPMC model and SPSC model