import re

if __name__ == '__main__':
    corpus = open('corpus.txt', 'r')
    output = open('2017211416.txt', 'w')
    pattern = re.compile(r'.{,3}因为.*所以.{,3}')  # Regular expression object

    result_list = []
    num_list = []  # Used to store the number of rows
    for i, line in enumerate(corpus, start=1):
        if pattern.findall(line):
            result_list.append(line)
            num_list.append(i)

    for i, each in enumerate(result_list):
        tmp = [str(num_list[i])]
        split0 = each.split('因为', 1)[0][-3:]  # 靠左分割，分割次数为1
        while len(split0) < 3:
            split0 += '　'  # 长度补全 全角空格
        tmp.append(split0)
        tmp.append('*因为*')
        tmp.append(each.split('因为', 1)[1].rsplit('所以', 1)[0])
        tmp.append('&所以&')
        tmp.append(each.rsplit('所以', 1)[1][:3])  # 所以后三个自负
        output.write('\t'.join(tmp) + '\n')  # 插入空格和换行符
