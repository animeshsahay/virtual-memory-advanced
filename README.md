# virtual-memory-advanced
Assignment: Memory Management

Objectives:

This assignment will practice the following items:
1. Practise the address translation that is usually performed by the hardware.
2. Practise the management of a page table.
3. Practise the allocation of physical pages.
4. Understanding the page fault concept.


Overview:
This assignment is related to virtual memory management inside the operating system. Although, typically, an OS can support more than one process, you will only need to handle a single process in this assignment. You will practice multiple memory management concepts inside the user space. Since we cannot operate on real hardware at the OS level, this project aims to design a simulator that simulates memory management inside the user space.



In this assignment, we consider a tiny computing system that supports up to 1KB physical memory, and with 12-bit virtual addresses (4096 bytes). Suppose that the size of a virtual page and a physical frame is 128 bytes (i.e., with 7 address bits representing page offset). Prior to beginning your implementation, please think carefully about the following questions.

Note: you can proceed only when you fully understand the answers to these questions. Talk with your classmates, or ask for help from a TA or the instructor if you are confused.
(1) What is the maximum number of virtual pages for each process?	( Answer: 32 pages )
(2) How many physical pages (or frames) can be supported in total?	( Answer: 8 pages )
(3) How many entries are in the page table for each process, with one-level page table?	( Answer: 32 entries )
If you can understand all of these questions, now you can proceed to design a paging system that implements a one-level page table; we only use a single level for simplicity.

Part 1: 30 points
This component will simply get you started. Assume that the page table of the process is like the following picture.

pagetable

Note that only a few entries of the process' page table are listed, as we will only use the first seven entries in Part 1.

Create a directory called "assign1" for this assignment. Write a program called assign1part1.c for this part. The program will take only one parameter, the input sequence filename, which contains a sequence of virtual/logic memory accesses. Here, each address is stored as 8 bytes (unsigned long type). Your program should read and analyze each logical/virtual address, and translate it into the corresponding physical address based on the given page table, as shown in the above picture. Note: to simplify it, you can place the fixed page-to-frame mapping (as shown in the figure) into an array, before performing any address translation.

Each memory address is saved in a binary format. To verify that you can read the correct sequence of memory accesses, you can first print the address that you have analyzed. You can test your program with the given simple test sequence file (part1testsequence), where the first address should be 0x00000044, and the second one should be 0x00000224. Physical addresses for these two addresses (after the translation) should be 0x144 and 0x01A4.

You may also refer to the sample code to analyze the given sequence file. For each address in the sequence file, you will use the above given simple page table to perform the address translation, and generate a corresponding physical address. You will output the translated physical addresses into a new file, named output-part1test. This output-part1test file should have a similar format to the given part1testsequence file, as above (i.e., each physical address should use 8 bytes (as an unsigned long value) in the output file). In this assignment, we represent each logical/physical address using 64-bits (8 bytes) to enable the program to be more general.

Once you test your program correctly with the above simple test sequence, which contains only eight memory accesses, you should use the following sequence file (part1sequence) as the input file for the address sequence used to generate translated physical addresses, placing them in another file called output-part1. Then, you can utilize the md5sum utility to compute their corresponding checksum, via running "md5sum output-part1", and you only need to write the checksum of "output-part1" into the status.txt file.



Part 2: 40 points
In this part, you will design the page table and handle deal with allocations of physical machiens on the same machine as discussed above. You will create two new source files in this part: phyframes.c and pagetable.c, as well as a new main program, named assign1part2.c, plus any necessary header files. Here, phyframes.c is used to manage the physical frames, while pagetable.c will hold all functions that manages the page table for the process.

For this part, we will also assume the first physical frame is reserved for the OS, while other framess are initially available for the process. To manage physical frames, you will use a simple physical page allocation scheme:
You will allocate each physical page in the order of frame number initially, starting from 1, 2, 3, .... If physical frames are available, you will always allocate from these available frames at first.

Once there are no free physical frames, you will need to use one page replacement policy to choose a physical frame to be replaced. Currently, let's use the LRU policy, which means the page that was Least Recently Used (accessed) will be the first to be replaced.



Note that once a frame is selected to be replaced, you should do two things:
First, you should update the old page table entry such that no two virtual pages are pointing to the same physical frame. In reality, it is better to quickly locate which page table entry is actually pointing to this physical frame, typically called as ``reverse mapping''. However, you may search the whole page table of all active processes (one process in the assignment) to find out this, with significant performance overhead.
Second, you should change the page table entry of the target page to point to the frame. If you are using the "reverse mapping" mechanism, you should also set up the reverse mapping correctly.
You can use any mechanism discussed in the class to implement the strict LRU mechanism, such as counter mechanism or stack mechanism (with doubly linked list), but not second-chance algorithm. Importantly, you should update the corresponding information upon each access.

The input sequence of the program is the same as that used in Part 1. Thus, you should be able to utilize the same analyzing function to obtain the corresponding virtual address, then translate it to a physical address with your implemented page table.

In the end, you can use the same function as in Part 1 to output the translated physical address sequence into a file. For the following input sequence part2sequence, the program should generate output to a file named output-part2.

Similar to Part 1, you only need to report the md5sum checksum of output-part2, and write it to status.txt file. In addition, your program should record the number of page faults encountered for the given access sequence, and this number should be reported in status.txt file too.

Part 3: 30 bonus points
Designing your page table for a general scenario

For this part, instead of working on a specified machine (as described above), you will re-design the part2 so that it can work on any machine. That is, the size of virtual memory and physical memory can be just input parameters, and the same for the size of page/frame. To receive these bonus points, you should list whether you have implemented Part 3 in your status.txt file. Also, you should briefly explain how your implemented this part, in comparison to the first two parts.

You should create a new main program, named assign1part3.c, and your program should accept the following parameters:

./assign1 <SizeOfPage> <SizeOfVirtualMemory> <SizeOfPhysicalMemory> <SequenceFile>

 	SizeOfPage	size of each physical frame and virtual page (in bytes)
 	SizeOfVirtualMemory	size of virtual memory (in bytes)
 	SizeOfPhysicalMemory	size of physical memory (in bytes)
 	SequenceFile	name of the input file containing the sequence of virtual addresses to translate


To test your program's Part 3 functions, you can use the parameters specified in "Part 2" as follows:
./assign1 128 4096 1024 part2sequence

For this case, your program should generate the same output file as in Part 2.

In addition, you need to run your program with the following parameters and report the md5sum results and number of page faults for the following 2 executions in the status.txt:

./assign1 256 4096 1024 part2sequence

./assign1 128 4096 2048 part2sequence


Submission guideline

You will create a directory---assign1 directory---at first. In this directory, you will further have source directory and status.txt file.

source directory: mandatory
This directory should include all of your source code (*.c, *.h, etc.) as well as a Makefile. Without source code, you can earn only 50% of the total points, at most.


status.txt: manadatory
You should include a status report in a file named status.txt. This status report should state whether you have completed Part 1, Part 2 or Part 3 successfully. For each part, please include the md5sum checksums for each of the given input sequences. For Part 2, you should also include the number of page faults for the input sequence. For Part 3, please include the required description to receive the bonus points. Please also provide a brief description of why is or is not working, as well as what progress was made on the non-working part(s).
There will be a severe penalty (50% off) if your status.txt does not align with your source code. Further, if there is no status.txt present in your submission, you will only receive 50% points.

Please be aware that you will get partial credits, even if you didn't finish all parts correctly. Thus, please submit anything that you already have, but specifying your status in status.txt file.

Finally, please compress the whole directory into a file naming "assign1-XXXX.zip". XXXX should be replaced with your name.

You will submit only through the moodle and we don't accept the printed submission. As described before, you can submit the assignment late, but with 10% off every day.
