// LexicalAnalysis.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
// 程序设计1
// 题目：词法分析程序的设计与实现
// 实验内容：设计并实现C语言的词法分析程序，要求实现如下功能。
// （1）可以识别出用C语言编写的源程序中的每个单词符号，并以记号的形式输出每个单词符号。
// （2）可以识别并跳过源程序中的注释。
// （3）可以统计源程序中的语句行数、各类单词的个数、以及字符总数，并输出统计结果。
// （4）检查源程序中存在的词法错误，并报告错误所在的位置。
// （5）对源程序中出现的错误进行适当的恢复，使词法分析可以继续进行，对源程序进行一次扫描，即可检查并报告源程序中存在的所有词法错误。
// 实现要求：分别用以下两种方法实现。
// 方法1：采用C/C++作为实现语言，手工编写词法分析程序。
// 方法2：编写LEX源程序，利用LEX编译程序自动生成词法分析程序。

#include <stdio.h>

int main(void) {

	int state = 0;
	do {
		switch (state) {
			case 0: // Initial state
				token = '';
				get_char();
				get_nbc();
				switch (C) {
					case 'a':
					case 'b':
					case 'c':
					case 'd':
					case 'e':
					case 'f':
					case 'g':
					case 'h':
					case 'i':
					case 'j':
					case 'k':
					case 'l':
					case 'm':
					case 'n':
					case 'n':
					case 'o':
					case 'p':
					case 'q':
					case 'r':
					case 's':
					case 't':
					case 'u':
					case 'v':
					case 'w':
					case 'x':
					case 'y':
					case 'z':
						state = 1; // Set identifier state
						break;
					case '0':
					case '1':
					case '2':
					case '3':
					case '4':
					case '5':
					case '6':
					case '7':
					case '8':
					case '9':
						state = 2; // Set constant state
						break;
					case '<':
						state = 8; // Set the '<' state
						break
					case '>':
						state = 9; // Set the '>' state
						break;
					case ':':
						state = 10; // Set the ':' state
						break;
					case '/':
						state = 11; // Set the '/' state
						break;
					case '=':
						state = 0;
						return (relop, EQ); // Return the token of '='
						break;
					case '+':
						state = 0;
						return ('+', -); // Return the token of '+'
						break;
					case '-':
						state = 0;
						return ('-', -); // Return the token of '-'
						break;
					case '*':
						state = 0;
						return ('*', -); // Return the token of '*'
						break;
					case '(':
						state = 0;
						return ('(', -); // Return the token of '('
						break;
					case ')':
						state = 0;
						return (')', -); // Return the token of ')'
						break;
					case ';':
						state = 0;
						return (';', -); // Return the token of ';'
						break;
					case '\'':
						state = 0;
						return ('\'', -); // Return the token of '''
						break;
					default:
						state = 13; // Set error state
						break;
				}
				break;
			case 1: // Identifier state
				cat();
				get_char();
				if (letter() || digit())
					state = 1;
				else {
					retract();
					state = 0;
					iskey = reserve(); // Check keyword list
					if (iskey != -1)   // Identifyed keywords
						return (iskey, -);
					else {             // User-defined identifiers are identified
						identry = table_insert();
						return (ID, identry); // Return the identifier pointer of the identifier in the symbol table
					}
				}
				break;
			case 2: // Constant state
				cat();
				get_char();
				switch (C) {
					case '0':
					case '1':
					case '2':
					case '3':
					case '4':
					case '5':
					case '6':
					case '7':
					case '8':
					case '9':
						state = 2;
						break;
					case '.':
						state = 3;
						break;
					case 'E':
						state = 5;
						break;
					default: // Identify the entire constant
						retract();
						state = 0;
						return (NUM, SToI(token)); // Return integer
						break;
				}
				break;
			case 3: // Decimal point status
				cat();
				get_char();
				if (digit)
					state = 4;
				else {
					error();
					state = 0;
				}
				break;
			case 4: // Decimal state
				cat();
				get_char();
				switch (C) {
					case '0':
					case '1':
					case '2':
					case '3':
					case '4':
					case '5':
					case '6':
					case '7':
					case '8':
					case '9':
						state = 4;
						break;
					case 'E':
						state = 5;
						break;
					default: // Recognize decimals
						retract();
						state = 0;
						return (NUM, SToF(token)); // Return decimal
						break;
				}
				break;
			case 5: // Exponential state
				cat();
				get_char();
				switch (C) {
					case '0':
					case '1':
					case '2':
					case '3':
					case '4':
					case '5':
					case '6':
					case '7':
					case '8':
					case '9':
						state = 7;
						break;
					case '-':
						state = 6;
						break;
					default:
						retract();
						error();
						state = 0;
						break;
				}
				break;
			case '6':
				cat();
				get_char();
				if (digit)
					state = 7;
				else {
					retract();
					error();
					state = 0;
				}
				break;
			case '7':
				cat();
				get_char();
				if (digit)
					state = 7;
				else {
					retract();
					error();
					state = 0;
					return (NUM, SToF(token)); // Return unsigned number
				}
				break;
			case '8': // '<' State
				cat();
				get_char();
				switch (C) {
					case '=':
						cat();
						state = 0;
						return (relop, LE);// Return '<=' token
						break;
					case '>':
						cat();
						state = 0;
						return (relop, NE); // Return '<>' token
						break;
					default:
						retract();
						state = 0;
						return (relop, LT); // Return '<' token
						break;
				}
				break;
			case '9': // '>' State
				cat();
				get_char();
				if (C == '=') {
					cat();
					state = 0;
					return (relop, GE); // Return '>=' token
				}
		}
	} while (C != eof);
	return 0;
}

// 运行程序: Ctrl + F5 或调试 >“开始执行(不调试)”菜单
// 调试程序: F5 或调试 >“开始调试”菜单

// 入门使用技巧: 
//   1. 使用解决方案资源管理器窗口添加/管理文件
//   2. 使用团队资源管理器窗口连接到源代码管理
//   3. 使用输出窗口查看生成输出和其他消息
//   4. 使用错误列表窗口查看错误
//   5. 转到“项目”>“添加新项”以创建新的代码文件，或转到“项目”>“添加现有项”以将现有代码文件添加到项目
//   6. 将来，若要再次打开此项目，请转到“文件”>“打开”>“项目”并选择 .sln 文件
// LexicalAnalysis.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <stdio>

int main(void) {
	int state = 0;
	do {
		switch (state) {
			case 0: // Initial state
				token = "";
				get_char();
				get_nbc();
				switch (C) {
					case 'a':
					case 'b':
					case 'c':
					case 'd':
					case 'e':
					case 'f':
					case 'g':
					case 'h':
					case 'i':
					case 'j':
					case 'k':
					case 'l':
					case 'm':
					case 'n':
					case 'n':
					case 'o':
					case 'p':
					case 'q':
					case 'r':
					case 's':
					case 't':
					case 'u':
					case 'v':
					case 'w':
					case 'x':
					case 'y':
					case 'z':
						state = 1; // Set identifier state
						break;
					case '0':
					case '1':
					case '2':
					case '3':
					case '4':
					case '5':
					case '6':
					case '7':
					case '8':
					case '9':
						state = 2; // Set constant state
						break;
					case '<':
						state = 8; // Set the '<' state
						break
					case '>':
						state = 9; // Set the '>' state
						break;
					case ':':
						state = 10; // Set the ':' state
						break;
					case '/':
						state = 11; // Set the '/' state
						break;
					case '=':
						state = 0;
						return (relop, EQ); // Return the token of '='
						break;
					case '+':
						state = 0;
						return ('+', -); // Return the token of '+'
						break;
					case '-':
						state = 0;
						return ('-', -); // Return the token of '-'
						break;
					case '*':
						state = 0;
						return ('*', -); // Return the token of '*'
						break;
					case '(':
						state = 0;
						return ('(', -); // Return the token of '('
						break;
					case ')':
						state = 0;
						return (')', -); // Return the token of ')'
						break;
					case ';':
						state = 0;
						return (';', -); // Return the token of ';'
						break;
					case '\'':
						state = 0;
						return ('\'', -); // Return the token of '''
						break;
					default:
						state = 13; // Set error state
						break;
				}
				break;
			case 1: // Identifier state
				cat();
				get_char();
				if (letter() || digit())
					state = 1;
				else {
					retract();
					state = 0;
					iskey = reserve(); // Check keyword list
					if (iskey != -1)   // Identifyed keywords
						return (iskey, -);
					else {             // User-defined identifiers are identified
						identry = table_insert();
						return (ID, identry); // Return the identifier pointer of the identifier in the symbol table
					}
				}
				break;
			case 2: // Constant state
				cat();
				get_char();
				switch (C) {
					case '0':
					case '1':
					case '2':
					case '3':
					case '4':
					case '5':
					case '6':
					case '7':
					case '8':
					case '9':
						state = 2;
						break;
					case '.':
						state = 3;
						break;
					case 'E':
						state = 5;
						break;
					default: // Identify the entire constant
						retract();
						state = 0;
						return (NUM, SToI(token)); // Return integer
						break;
				}
				break;
			case 3: // Decimal point status
				cat();
				get_char();
				if (digit)
					state = 4;
				else {
					error();
					state = 0;
				}
				break;
			case 4: // Decimal state
				cat();
				get_char();
				switch (C) {
					case '0':
					case '1':
					case '2':
					case '3':
					case '4':
					case '5':
					case '6':
					case '7':
					case '8':
					case '9':
						state = 4;
						break;
					case 'E':
						state = 5;
						break;
					default: // Recognize decimals
						retract();
						state = 0;
						return (NUM, SToF(token)); // Return decimal
						break;
				}
				break;
			case 5: // Exponential state
				cat();
				get_char();
				switch (C) {
					case '0':
					case '1':
					case '2':
					case '3':
					case '4':
					case '5':
					case '6':
					case '7':
					case '8':
					case '9':
						state = 7;
						break;
					case '-':
						state = 6;
						break;
					default:
						retract();
						error();
						state = 0;
						break;
				}
				break;
			case '6':
				cat();
				get_char();
				if (digit)
					state = 7;
				else {
					retract();
					error();
					state = 0;
				}
				break;
			case '7':
				cat();
				get_chat();
				if (digit)
					state = 7;
				else {
					retract();
					error();
					state = 0;
					return (NUM, SToF(token)); // Return unsigned number
				}
				break;
			case '8': // '<' State
				cat();
				get_char();
				switch (C) {
					case '=':
						cat();
						state = 0;
						return (relop, LE);// Return '<=' token
						break;
					case '>':
						cat();
						state = 0;
						return (relop, NE); // Return '<>' token
						break;
					default:
						retract();
						state = 0;
						return (relop, LT); // Return '<' token
						break;
				}
				break;
			case '9': // '>' State
				cat();
				get_char();
				if (C == '=') {
					cat();
					state = 0;
					return (relop, GE); // Return '>=' token
				} else {
					retract();
					state = 0;
					return (relop, GT); // Return '>=' token
				}
				break;
			case 10: // ':' State
				cat();
				get_char();
				if (C == '=') {
					cat();
					state = 0;
					return (assign_op, -); // Return ':=' token
				} else {
					retract();
					state = 0;
					return (':', -); // Return ':' token
				}
				break;
			case 11: // '/' State
				cat();
				get_char();
				if (C == '*')
					state = 12;
				else {
					retract();
					state = 0;
					return ('/', -); // Return '/' token
				}
				break;
			case 12: // Comment processing state
				get_char();
				while (C != '*')
					get_char();
				get_char();
				if (C == '/') // End of comment processing
					state = 0;
				else
					state = 12;
				break;
			case 12: // Error handling state
				error();
				state = 0;
				break;
		}
	} while (C != eof); // The source end flag is not scanned, and the loop continues
	
	return 0;
}

// 运行程序: Ctrl + F5 或调试 >“开始执行(不调试)”菜单
// 调试程序: F5 或调试 >“开始调试”菜单

// 入门使用技巧: 
//   1. 使用解决方案资源管理器窗口添加/管理文件
//   2. 使用团队资源管理器窗口连接到源代码管理
//   3. 使用输出窗口查看生成输出和其他消息
//   4. 使用错误列表窗口查看错误
//   5. 转到“项目”>“添加新项”以创建新的代码文件，或转到“项目”>“添加现有项”以将现有代码文件添加到项目
//   6. 将来，若要再次打开此项目，请转到“文件”>“打开”>“项目”并选择 .sln 文件
