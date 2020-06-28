import glob

import numpy as np

from searcher import search

if __name__ == '__main__':
    # Get all paths
    query_paths = glob.glob("static/gt_files/*query.txt")
    good_paths = glob.glob("static/gt_files/*good.txt")
    ok_paths = glob.glob("static/gt_files/*ok.txt")
    junk_paths = glob.glob("static/gt_files/*junk.txt")

    mean_APs = []
    for i in range(len(query_paths)):
        fp_query = open(query_paths[i], encoding='utf-8')
        fp_good = open(good_paths[i], encoding='utf-8')
        fp_ok = open(ok_paths[i], encoding='utf-8')
        fp_junk = open(junk_paths[i], encoding='utf-8')

        query_list = []
        for line in fp_query.readlines():
            if line is not '\n':
                query_list.append(line.strip('\n'))
        good_list = []
        for line in fp_good.readlines():
            if line is not '\n':
                good_list.append(line.strip('\n'))
        ok_list = []
        for line in fp_ok.readlines():
            if line is not '\n':
                ok_list.append(line.strip('\n'))
        junk_list = []
        for line in fp_junk.readlines():
            if line is not '\n':
                junk_list.append(line.strip('\n'))

        average_precision = []
        for query in query_list:
            img_name = query + '.jpg'
            query_result = search(img_name)

            precision = []
            count = 0
            for result in query_result:
                result_name = result['image'].split('.')[0]

                good = 0
                if result_name in good_list or result_name in ok_list:
                    good += 1
                    count += 1
                    precision.append(good / count)
                elif result_name in junk_list:
                    count += 1
            average_precision.append(np.asarray(precision).mean())
        mean_AP = np.asarray(average_precision).mean()
        mean_APs.append(mean_AP)

        fp_query.close()
        fp_good.close()
        fp_ok.close()
        fp_junk.close()

    mAP = np.asarray(mean_APs).mean()
    print("Top 10 mean Average Precision: ", mAP)
