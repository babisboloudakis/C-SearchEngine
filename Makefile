default: main.o trie.o list.o postingList.o wordList.o heap.o
	@echo "Compiling..."
	gcc -o main main.o trie.o list.o postingList.o wordList.o heap.o -lm

main.o: ./src/main.c
	gcc -c ./src/main.c

trie.o: ./src/trie.c
	gcc -c ./src/trie.c

list.o: ./src/list.c
	gcc -c ./src/list.c

postingList.o: ./src/postingList.c
	gcc -c ./src/postingList.c

wordList.o: ./src/wordList.c
	gcc -c ./src/wordList.c

heap.o: ./src/heap.c 
	gcc -c ./src/heap.c