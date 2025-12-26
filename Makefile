TARGET  := main
SRC     := src/main.c

all: $(TARGET)
run: $(TARGET)

$(TARGET): $(SRC)
	gcc $^ -o $@ -I./raylib-5.5_linux_amd64/include/ \
		-L./raylib-5.5_linux_amd64/lib/ \
		-l:libraylib.a \
		-lm

run:
	./$(TARGET)

setup:
	bear -- make clean all

clean:
	rm -rf $(TARGET)
