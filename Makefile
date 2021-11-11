CC=g++

CFLAGS = -lubsan -D NDEBUG -g -std=c++14 -fmax-errors=1 -Wall -Wextra -Weffc++ -Waggressive-loop-optimizations -Wc++0x-compat -Wc++11-compat -Wc++14-compat -Wcast-align -Wcast-qual -Wchar-subscripts -Wconditionally-supported -Wconversion  -Wctor-dtor-privacy -Wempty-body -Wfloat-equal -Wformat-nonliteral -Wformat-security -Wformat-signedness -Wformat=2 -Winline  -Wlogical-op -Wmissing-declarations  -Wnon-virtual-dtor -Wopenmp-simd -Woverloaded-virtual -Wpacked -Wpointer-arith -Wredundant-decls -Wshadow -Wsign-conversion -Wsign-promo -Wstack-usage=8192  -Wstrict-null-sentinel -Wstrict-overflow=2 -Wsuggest-attribute=noreturn -Wsuggest-final-methods -Wsuggest-final-types  -Wsuggest-override -Wswitch-default -Wswitch-enum -Wsync-nand -Wundef  -Wunreachable-code -Wunused -Wuseless-cast -Wvariadic-macros -Wno-literal-suffix -Wno-missing-field-initializers -Wno-narrowing -Wno-old-style-cast -Wno-varargs -fcheck-new -fsized-deallocation  -fstack-protector -fstrict-overflow   -flto-odr-type-merging -fno-omit-frame-pointer -fPIE -fsanitize=address  -fsanitize=alignment -fsanitize=bool -fsanitize=bounds -fsanitize=enum  -fsanitize=float-cast-overflow -fsanitize=float-divide-by-zero -fsanitize=integer-divide-by-zero -fsanitize=leak -fsanitize=nonnull-attribute -fsanitize=null -fsanitize=object-size -fsanitize=return -fsanitize=returns-nonnull-attribute -fsanitize=shift -fsanitize=signed-integer-overflow -fsanitize=undefined -fsanitize=unreachable -fsanitize=vla-bound -fsanitize=vptr -lm -pie

all: global 

global: list.o list_tests.o errors_and_logs.o general.o main.o
	g++ list.o list_tests.o errors_and_logs.o general.o main.o -o list.exe $(CFLAGS)

list.o: list/list.cpp
	$(CC) list/list.cpp -c  $(CFLAGS)

list_tests.o: list/list_tests.cpp
	$(CC) list/list_tests.cpp -c  $(CFLAGS)

main.o: main.cpp
	$(CC) main.cpp -c $(CFLAGS)

errors_and_logs.o: logs/errors_and_logs.cpp
	$(CC) logs/errors_and_logs.cpp -c $(CFLAGS)

general.o: general/general.cpp
	$(CC) general/general.cpp -c $(CFLAGS)

clean:
	rm *.o  

deletepng:
	rm /mnt/c/users/rust2/appdata/local/temp/list_images/*.png

makeimagesdir: 
	mkdir /mnt/c/users/rust2/appdata/local/temp/list_images
