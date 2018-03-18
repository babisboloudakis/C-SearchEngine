Xaralampos
Mpoloudakis
1115201500103

-------------------------

1.How to run
2. Description
    2.1. Data structures
    2.2 User interface
3.Bugs

--------------------------

1. How to run:

    To run the program simply use the makefile like this
    $ make
    And then execute
    $ ./main -i inputFile -k K ( k is optional argument, 10 by default )

    There is also a make clean command to delete .o files as well as the executable
    $ make clean


2. Description:

    2.1 Data structures

        Map: A dynamically allocated array is used to store the documents from our input
        file. These documents are used in /search command.

        Trie: The most important data structure of the program, is a set of nodes that are organised
        in node lists. So, every node has a list of children, its data ( a character ) and a pointer
        to a posting list ( which is NULL, except when we are on a leaf node ). Trie is used in every 
        user command ( /search /df /tf )

        PostingList: It is a linked list of tupples ( id , count ) that represent the occurrences of a
        specific word in a specific documents. So (2,5) means that the word that is connected to this list
        exists 5 times on the document with id 2. It is used in every user command ( /tf /df /search ).

        Heap: A max-heap is used to store the results of a search query. The heap stores the documents
        of a /search query and sorts them by SCORE. When we are ready to print the results we extract
        the top (id,score) tupple from the heap, remove it, and make sure it is still a heap by sorting.

        WordList: It is a simple linked list of strings. It is used to store the arguments of the  user commands 


    2.2 User interface

        After the program build its data structures from the input file, the program enters an infinite
        loop state that reads and executes user commands.

            /search (arguments) to find documents that contain the words in arguments sorted by query score

            /df ( filter , optional ) to diplay document frequency vector, use filter argument to look for a 
            specific word 

            /tf id word     to display term frequency for a specific word on a specific document

            /exit   to quit the program and smoothly free the data structures 

3. Bugs:

    -   in /search the printing of the results isn't exactly like the example, however it's correct.

    -   there may be some weird inputs in user mode that make program crash which aren't handled, however
    most possible inputs throw errors and 100% of the correct commands run.

    -   there may be some search terms that crash the program, however I encountered this only a few times
    in a vast set of queries 