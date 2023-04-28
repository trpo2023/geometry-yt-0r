APP_NAME = geometry
LIB_NAME = libgeometry
INC_NAME = calculate_circle

CC = gcc
CFLAGS = -Wall -Wextra -Werror
CPPFLAGS = -MMD

LIB_PATH = src/$(LIB_NAME)
SRC_PATH = src/$(APP_NAME)
OUT_LIB_PATH = obj/src/$(LIB_NAME)
OUT_SRC_PATH = obj/src/$(APP_NAME)

all: bin/$(APP_NAME)

bin/$(APP_NAME): $(OUT_SRC_PATH)/$(APP_NAME).o $(OUT_LIB_PATH)/$(LIB_NAME).a
	$(CC) $(CFLAGS) -o $@ $^

$(OUT_LIB_PATH)/$(LIB_NAME).a: $(OUT_LIB_PATH)/$(INC_NAME).o
	ar rcs $@ $^

$(OUT_SRC_PATH)/$(APP_NAME).o: $(SRC_PATH)/$(APP_NAME).c
	$(CC) -c $(CFLAGS) $< $(CPPFLAGS) -o $@ -I $(LIB_PATH) 

$(OUT_LIB_PATH)/$(INC_NAME).o: $(LIB_PATH)/$(INC_NAME).c $(LIB_PATH)/$(INC_NAME).h
	$(CC) -c $(CFLAGS) $< $(CPPFLAGS) -o $@ -I $(LIB_PATH)

.PHONY: test
test: test/test

test/test: test/$(APP_NAME)_test.o test/main.o
	$(CC) $(CFLAGS) $(CPPFLAGS) -o $@ $^
	@echo ------------------------------------------------ ; cd test/ && ./test

test/$(APP_NAME)_test.o: test/$(APP_NAME)_test.c thirdparty/ctest.h
	$(CC) -c $(CFLAGS) $< $(CPPFLAGS) -o $@ -I thirdparty -I $(LIB_PATH)

test/main.o: test/main.c test/$(APP_NAME)_test.o thirdparty/ctest.h
	$(CC) -c $(CFLAGS) $< $(CPPFLAGS) -o $@ -I thirdparty -I $(LIB_PATH)

.PHONY: clean
clean: 
	rm -rf bin/$(APP_NAME)
	rm -rf $(OUT_SRC_PATH)/*.d
	rm -rf $(OUT_SRC_PATH)/*.o
	rm -rf $(OUT_LIB_PATH)/*.d
	rm -rf $(OUT_LIB_PATH)/*.o
	rm -rf $(OUT_LIB_PATH)/*.a
	rm -rf test/*.d
	rm -rf test/*.o
	rm -rf test/test

SRCS := $(shell find . -type f -name '*.c')
HDRS := $(shell find . -type f -name '*.h')

format:
	clang-format -i $(SRCS) $(HDRS)

# -include $(OUT_SRC_PATH)/$(APP_NAME).d $(OUT_LIB_PATH)/$(INC_NAME).d
.PHONY: all test clean format
