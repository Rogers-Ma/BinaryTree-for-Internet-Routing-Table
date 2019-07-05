# Build a Binary Tree for an Internet Routing Table

Write a C program to build a binary tree for an Internet routing table, and then print the routing table entries (prefix/length, next 
hop) in Postorder (Left, Right, Root). Indent each line by the length of the prefix. The program uses STDIN to read entries from a file 
and output the results into another file. 

The test input file is A2-test-in.txt

The test output file is A2-test-out.txt

The input file is A2-input.txt

The output file is A2-output.txt


## Background: 
A routing entry or prefix/length has the format: (a.b.c.d/x, next hop), where a, b, c and d are integers with a range of 0-255. The 
length's range is 0-32.The next hop is an integer. All integers here are unsigned. 
Your can convert a.b.c.d to a binary string. For instance, 128.153.66.0/24 can be written in binary: 10000000 10011001 01000010 
00000000. The length value 24 means the 24 leading bits in the string 10000000 10011001 01000010. 
When you write your program, you need to place the (prefix/length, next hop) pair in the corresponding level of the binary tree 
indicated by the length.     

## Requirements:

a. Your program should run on polaris.clarkson.edu with the following commands. 
	
	gcc BinaryTree.c -o BinaryTree
	
	./BinaryTree < A2-input.txt > A2-output.txt
	

b. You should use the provided skeleton code and data structure to finish the assignment. No other libraries are allowed. However, you 
can define as many functions and variables as you need.  


c. Your program should pass the verification of Valgrind program to avoid memory leaks and other errors. Your valgrind command:

	valgrind ./BinaryTree < A2-input.txt > output.txt
	

## Your Valgrind report should look like as follows:

	==5478== HEAP SUMMARY:
	==5478==     in use at exit: 0 bytes in 0 blocks
	==5478==   total heap usage: 1,648,121 allocs, 1,648,121 frees, 39,440,857 bytes allocated
	==5478==
	==5478== All heap blocks were freed -- no leaks are possible
	==5478==
	==5478== For counts of detected and suppressed errors, rerun with: -v
	==5478== ERROR SUMMARY: 0 errors from 0 contexts (suppressed: 0 from 0)  
