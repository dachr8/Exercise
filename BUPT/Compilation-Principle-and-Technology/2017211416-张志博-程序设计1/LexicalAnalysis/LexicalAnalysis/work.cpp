#pragma warning(disable:4996)
#include "work.h"
#include "tools.h"
#include "data.h"
#include "deal.h"


constexpr auto ST = 0;          //��ʼ״̬
constexpr auto LOOKAHEAD = 1;   //����ǰ��̽
constexpr auto STRING = 2;      //�ַ�
constexpr auto DIGIT = 3;       //����
constexpr auto WORD = 5;        //����
constexpr auto PREPROCESS = 6;  //Ԥ�������
constexpr auto LETTER = 7;      //�����ַ�
constexpr auto ARIOPE = 8;      //���������
constexpr auto PUNCTUATION = 9; //���
constexpr auto COMMENT = 10;    //ע��

constexpr auto CHR_DIG = 1;      //����
constexpr auto CHR_WOR = 2;      //����
constexpr auto CHR_STR = 3;      //�ַ�����ʼ
constexpr auto CHR_LET = 4;      //�ַ���ʼ
constexpr auto CHR_PRE = 5;      //Ԥ����
constexpr auto CHR_RET = 6;      //�س�
constexpr auto CHR_SPACE = 7;    //�ո�
constexpr auto CHR_ARIOPE = 8;   //���������
constexpr auto CHR_PUNC = 9;     //���
constexpr auto CHR_SEP = 10;     //�ָ���
constexpr auto CHR_LOGOPE = 11;  //�߼������
constexpr auto CHR_BITOPE = 12;  //λ����
constexpr auto CHR_COMMENT = 13; //ע��
constexpr auto CHR_LOOKAHEAD = 14;

KeyList keylist;
SignalTable signalTable;

char buffer[2][BUFFERLEN];

bool currentBuffer, forwardBuffer;
char* curPt, * forwardPt;
FILE* sourcePointer, * targetPointer, * errorListPointer;

int lineCount;       // ����
int charCount;       // �ַ���
int keywordCount;    // �ؼ�����
int identifierCount; // ��ʶ����
int numberCount;     // ����
int letterCount;     // �ַ���
int stringCount;     // �ַ�����
int operatorCount;   // ��������
int delimiterCount;  // �����


extern void init(char* filename, char* sourceFile) {
	keylist.initializeFromFile(filename);
	signalTable.setName(sourceFile);
	buffer[0][BUFFERLEN - 1] = 4;
	buffer[1][BUFFERLEN - 1] = 4;
	curPt = buffer[currentBuffer];
	forwardPt = buffer[currentBuffer];

	currentBuffer = false;
	forwardBuffer = false;

	lineCount = 1;
	charCount = 0;
	keywordCount = 0;
	identifierCount = 0;
	numberCount = 0;
	letterCount = 0;
	stringCount = 0;
	operatorCount = 0;
	delimiterCount = 0;

	sourcePointer = fopen(sourceFile, "r+");
	char* errorFile = (char*)malloc(strlen(sourceFile) + 9);
	char* p = sourceFile, * pt = errorFile;
	while ((*p) != '.') {
		*pt = *p;
		p++;
		pt++;
	}
	if (pt != 0)
		strcpy(pt, "_error.txt");
	if (errorFile != 0)
		errorListPointer = fopen(errorFile, "w+");
	char* targetFile = (char*)malloc(strlen(sourceFile) + 9);
	if (targetFile != 0)
		strcpy(targetFile, "Lexical_");
	p = sourceFile; pt = targetFile + 8;
	while ((*p) != '\0') {
		*pt = *p;
		pt++;
		p++;
	}
	*pt = '\0';
	if (targetFile != 0)
		targetPointer = fopen(targetFile, "w+");
	free(targetFile);
	free(errorFile);
}

static int tellType(char c) {
	if ((c <= '9' && c >= '0') || c == '-')
		return CHR_DIG;
	if ((c <= 'Z' && c >= 'A') || (c <= 'z' && c >= 'a') || c == '_')
		return CHR_WOR;
	if (c == '"')
		return CHR_STR;
	if (c == '\'')
		return CHR_LET;
	if (c == '#')
		return CHR_PRE;
	if (c == '\n')
		return CHR_RET;
	if (c == ' ' || c == '\t')
		return CHR_SPACE;
	if (c == '(' || c == ')' || c == '{' || c == '}' || c == '[' || c == ']' || c == ';' || c == '?' || c == ':' || c == ',' || c == '.')
		return CHR_PUNC;
	if (c == '/' || c == '<' || c == '>' || c == '=' || c == '+' || c == '-' || c == '|' || c == '&' || c == '*' || c == '%' || c == '!' || c == '^')
		return CHR_LOOKAHEAD;
}

extern void work(char* sourceFile) {
	fread(buffer[currentBuffer], 1, BUFFERLEN - 1, sourcePointer);

	int state = ST;
	char lastchr = 0;
	char c;
	int t;
	while (*curPt != '\0') {
		updateBuffer();

		switch (state) {
			case ST:
				c = *curPt;
				t = tellType(c);
				switch (t) {
					case CHR_LET:
						state = LETTER;
						break;
					case CHR_PRE:
						state = PREPROCESS;
						break;
					case CHR_RET:
						while (*curPt == '\n') {
							curPt++;
							forwardPt++;
							updateBuffer();
							curPt = forwardPt;
							lineCount++;
						}
						break;
					case CHR_SPACE:
						while (*curPt == ' '|| *curPt == '\t') {
							curPt++;
							forwardPt++;
							updateBuffer();
							curPt = forwardPt;
						}
						break;
					case CHR_STR:
						state = STRING;
						break;
					case CHR_WOR:
						state = WORD;
						break;
					case CHR_DIG:
						state = DIGIT;
						break;
					case CHR_LOOKAHEAD:
						state = LOOKAHEAD;
						break;
					case CHR_PUNC:
						state = PUNCTUATION;
						break;
				}
				break;
			case LETTER:
				dealwithChar();
				curPt++;
				forwardPt++;
				updateBuffer();
				curPt = forwardPt;
				state = ST;
				break;
			case LOOKAHEAD:
				t = dealwithLookAhead();
				if (t == -1) {
					forwardPt++;
					updateBuffer();
					curPt = forwardPt;
					state = ST;
				} else {
					state = t;
				}
				break;
			case STRING:
				dealwithString();
				state = ST;
				break;
			case DIGIT:
				dealwithNum();
				state = ST;
				break;
			case WORD:
				dealwithWord();
				state = ST;
				break;
			case PREPROCESS:
				dealwithPreprocess();
				state = ST;
				break;
			case PUNCTUATION:
				dealwithPunctuation();
				state = ST;
				break;
			case COMMENT:
				dealwithComment();
				state = ST;
				break;
		}
	}
	fclose(targetPointer);
	fclose(sourcePointer);
	fclose(errorListPointer);
	cout << "���������\t" << lineCount << endl;
	cout << "�ַ�������\t" << charCount << endl;
	cout << "����������\t" << keywordCount << endl;
	cout << "��ʶ������\t" << identifierCount << endl;
	cout << "�������\t" << delimiterCount << endl;
	cout << "�ַ�������\t" << letterCount << endl;
	cout << "�ַ�������\t" << stringCount << endl;
}
