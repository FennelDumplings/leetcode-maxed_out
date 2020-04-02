DST_FOLD=build/

prob1: prob1_easy_Two-Sum.cpp
	g++ src/prob1_easy_Two-Sum.cpp -o ${DST_FOLD}prob1_easy_Two-Sum.out -std=c++11

prob2: prob2_medium_Add-Two-Numbers.cpp
	g++ src/prob2_medium_Add-Two-Numbers.cpp -o ${DST_FOLD}prob2_medium_Add-Two-Numbers.out -std=c++11 -Iinclude

prob3: prob3_medium_longest-substring-without-repeating-characters.cpp
	g++ src/-g3 prob3_medium_longest-substring-without-repeating-characters.cpp -o ${DST_FOLD}prob3_medium_longest-substring-without-repeating-characters.out -std=c++11

prob7: prob7_easy_reverse-integer.cpp
	g++ src/prob7_easy_reverse-integer.cpp -o ${DST_FOLD}prob7_easy_reverse-integer.out -std=c++11

prob9: prob9_palindrome-number.cpp
	g++ src/prob9_palindrome-number.cpp -o ${DST_FOLD}prob9_palindrome-number.out -std=c++11

prob13: prob13_easy_roman-to-integer.cpp
	g++ src/prob13_easy_roman-to-integer.cpp -g -Wall -o ${DST_FOLD}prob13_easy_roman-to-integer.out -std=c++11

prob15: prob15_medium_3Sum.cpp
	g++ src/prob15_medium_3Sum.cpp -g -Wall -o ${DST_FOLD}prob15_medium_3Sum.out -std=c++11

prob18: prob18_medium_4Sum.cpp
	g++ src/prob18_medium_4Sum.cpp -g -Wall -o ${DST_FOLD}prob18_medium_3Sum.out -std=c++11

prob54: prob54_medium_spiral-matrix.cpp
	g++ src/prob54_medium_spiral-matrix.cpp -g -Wall -o ${DST_FOLD}prob54_medium_spiral-matrix.out -std=c++11

prob155: prob155_easy_Min-Stack.cpp
	g++ src/prob155_easy_Min-Stack.cpp -g -Wall -o ${DST_FOLD}prob155_easy_Min-Stack.out -std=c++11

prob324: prob324_medium_Wiggle-Sort.cpp
	g++ src/prob324_medium_Wiggle-Sort.cpp -g -Wall -o ${DST_FOLD}prob324_medium_Wiggle-Sort.out -std=c++11

prob239: prob239_hard_Sliding-Window-Maximum.cpp
	g++ src/prob239_hard_Sliding-Window-Maximum.cpp -g -Wall -o ${DST_FOLD}prob239_hard_Sliding-Window-Maximum.out -std=c++11

