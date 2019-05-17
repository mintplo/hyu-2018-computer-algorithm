CC=gcc
C_FLAGS=-g -O0
TARGET=main
TARGET_OBJ=main.o
TARGET_SORT_OBJ= bubblesort.o quicksort.o countsort.o

all: $(TARGET)

.c.o:
	$(CC) -c $(C_FLAGS) $<

$(TARGET): $(TARGET_OBJ) $(TARGET_SORT_OBJ)
	$(CC) $(C_FLAGS) -o $(TARGET) $^

clean:
	rm -rf $(TARGET) $(TARGET_OBJ) $(TARGET_SORT_OBJ) output.txt
