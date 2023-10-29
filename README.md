# Operating-System-CSE316
operating system 



You are given a task to implement a program that uses threads to perform two separate operations concurrently, where one thread generates random numbers and puts them into a buffer, and the other thread retrieves the numbers from the buffer and computes the average. Your task is to write a program that performs the following steps:

1.	Create two threads: one for producing numbers and the other for computing the average.
2.	Initialize a buffer that can hold a specified number of integers.
3.	The producer thread should generate a random integer and put it in the buffer. It should wait if the buffer is full.
4.	The consumer thread should retrieve an integer from the buffer and add it to a sum variable. It should wait if the buffer is empty.
5.	After retrieving all numbers from the buffer, the consumer thread should calculate the average and print it out.
6.	The program should run until all numbers are produced, consumed, and averaged.
Your program should use synchronization primitives, such as semaphores or mutexes, to ensure that the threads are properly coordinated and do not access the buffer or the sum variable simultaneously. Additionally, you may want to include options to specify the buffer size, the range of random numbers to generate, and the number of integers to produce and consume.
