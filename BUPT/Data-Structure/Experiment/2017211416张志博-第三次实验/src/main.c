// Keyword search question requirements
//任选一篇txt格式的英文文档；
//用户输入任意一个英文单词，可以在该英文文档中检索这个英文单词，如果找到，则给出该英文单词出现的次数和所有位置，如果没有找到返回检索失败；
//用户输入可以用命令行方式，所选的英文文档路径也用命令行输入；
//采用BM算法进行检索（Boyer - Moore算法是一种基于后缀匹配的模式串匹配算法，后缀匹配就是模式串从右到左开始比较，但模式串的移动还是从左到右的。）
//需要提交设计报告和源代码，要求和《实验一》一样
//补充：输入的单词中包括通配字符；

//通配字符：？是任何字符

#include "BoyerMoore.h"

int main(void) {
	FILE *fp;
	char filename[FILENAME_MAX];
	int len;

	puts("Wildcard characters: '?' is any character.");
	printf("Please enter the selected document path:");
	scanf_s("%s", filename, FILENAME_MAX);

	// Get the text length
	fopen_s(&fp, filename, "r");
	for (len = 0; !feof(fp); ++len)
		fgetc(fp);
	fclose(fp);

	// Variable length structure
	TString *text = malloc(sizeof(TString) + sizeof(char)*len);
	if (!text)
		exit(1);
	text->length = len;

	// Read the file as a string using fopen_s, fgets, fclose
	fopen_s(&fp, filename, "r");
	for (int i = 0; i < text->length; ++i)                      // Use fgetc to get the text string and its length
		text->ch[i] = fgetc(fp);
	fclose(fp);


	printf("\nPlease enter the English word you want to search (Enter \\ to quit):");
	bool continue_flag = true;
	while (continue_flag) {
		SString pattern;
		scanf_s("%s", pattern.ch, PATTERN_LEN);                 // Use scanf_s to get the pattern string

		if (pattern.ch[0] == '\\')
			continue_flag = false;
		else {
			pattern.length = strlen(pattern.ch);                // Use strlen to get current length of the string
			if (!keywordSearch_BM(text, pattern))
				exit(2);
			printf("\nPlease enter the English word you want to search (Enter \\ to quit):");
		}
	}

	free(text);

	return 0;
}