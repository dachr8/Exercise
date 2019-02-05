// Keyword search question requirements
//��ѡһƪtxt��ʽ��Ӣ���ĵ���
//�û���������һ��Ӣ�ĵ��ʣ������ڸ�Ӣ���ĵ��м������Ӣ�ĵ��ʣ�����ҵ����������Ӣ�ĵ��ʳ��ֵĴ���������λ�ã����û���ҵ����ؼ���ʧ�ܣ�
//�û���������������з�ʽ����ѡ��Ӣ���ĵ�·��Ҳ�����������룻
//����BM�㷨���м�����Boyer - Moore�㷨��һ�ֻ��ں�׺ƥ���ģʽ��ƥ���㷨����׺ƥ�����ģʽ�����ҵ���ʼ�Ƚϣ���ģʽ�����ƶ����Ǵ����ҵġ���
//��Ҫ�ύ��Ʊ����Դ���룬Ҫ��͡�ʵ��һ��һ��
//���䣺����ĵ����а���ͨ���ַ���

//ͨ���ַ��������κ��ַ�

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