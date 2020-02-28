DST_FOLD=build/

prob1: prob1_easy_Two-Sum.cpp
	g++ prob1_easy_Two-Sum.cpp -o ${DST_FOLD}prob1_easy_Two-Sum.out -std=c++11

prob2: prob2_medium_Add-Two-Numbers.cpp
	g++ prob2_medium_Add-Two-Numbers.cpp -o ${DST_FOLD}prob2_medium_Add-Two-Numbers.out -std=c++11 -Iinclude

prob3: prob3_medium_longest-substring-without-repeating-characters.cpp
	g++ -g3 prob3_medium_longest-substring-without-repeating-characters.cpp -o ${DST_FOLD}prob3_medium_longest-substring-without-repeating-characters.out -std=c++11

prob7: prob7_easy_reverse-integer.cpp
	g++ prob7_easy_reverse-integer.cpp -o ${DST_FOLD}prob7_easy_reverse-integer.out -std=c++11

prob9: prob9_palindrome-number.cpp
	g++ prob9_palindrome-number.cpp -o ${DST_FOLD}prob9_palindrome-number.out -std=c++11

prob13: prob13_easy_roman-to-integer.cpp
	g++ prob13_easy_roman-to-integer.cpp -g -Wall -o ${DST_FOLD}prob13_easy_roman-to-integer.out -std=c++11

prob15: prob15_medium_3Sum.cpp
	g++ prob15_medium_3Sum.cpp -g -Wall -o ${DST_FOLD}prob15_medium_3Sum.out -std=c++11

prob18: prob18_medium_4Sum.cpp
	g++ prob18_medium_4Sum.cpp -g -Wall -o ${DST_FOLD}prob18_medium_3Sum.out -std=c++11

prob54: prob54_medium_spiral-matrix.cpp
	g++ prob54_medium_spiral-matrix.cpp -g -Wall -o ${DST_FOLD}prob54_medium_spiral-matrix.out -std=c++11

prob155: prob155_easy_Min-Stack.cpp
	g++ prob155_easy_Min-Stack.cpp -g -Wall -o ${DST_FOLD}prob155_easy_Min-Stack.out -std=c++11

prob324: prob324_medium_Wiggle-Sort.cpp
	g++ prob324_medium_Wiggle-Sort.cpp -g -Wall -o ${DST_FOLD}prob324_medium_Wiggle-Sort.out -std=c++11

