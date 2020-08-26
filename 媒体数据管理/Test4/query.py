from os.path import join
import matplotlib.pyplot as plt  # plt 用于显示图片
from os import walk
import numpy as np
from cv2 import cv2 

query = cv2.imread('E:\\cpp\\homewrok\\mediadata\\test\\0\\0_10.jpg', 0)
folder = 'E:\\cpp\\homewrok\\mediadata\\train\\0'
query = cv2.resize(query, (50, 50))
descriptors = []
# 获取特征数据文件名
for (dirpath, dirnames, filenames) in walk(folder):
    for f in filenames:
        if f.endswith("npy"):
            descriptors.append(f)
    # print(descriptors)

# 使用SIFT算法生成要匹配图像的关键点和描述符
sift = cv2.xfeatures2d.SIFT_create()
query_kp, query_ds = sift.detectAndCompute(query, None)

# 创建FLANN匹配器
index_params = dict(algorithm=0, trees=5)
search_params = dict(checks=100)  # 指定递归遍历的次数
flann = cv2.FlannBasedMatcher(index_params, search_params)

potential_culprits = {}
for d in descriptors:
    # 将图像query与特征数据文件的数据进行匹配
    tmp = np.load(join(folder, d))
    if tmp.size <= 128:  # 不加判断有断言错误
        continue
    matches = flann.knnMatch(query_ds, np.load(join(folder, d)), k=2)
    # 清除错误匹配
    good = []
    for m, n in matches:  # m,n分别是两个与原图像特征点最相邻的两个匹配
        if m.distance < 0.7 * n.distance:
            good.append(m)
    # 输出每张图片与目标图片的匹配数目
    # print("img is %s ! matching rate is (%d)" % (d, len(good)))
    potential_culprits[d] = len(good)

# 获取最多匹配数目的图片
max_matches = None
potential_suspect = None
for culprit, matches in potential_culprits.items():
    if max_matches is None or matches > max_matches:
        max_matches = matches
        potential_suspect = culprit

print("potential suspect is %s" % potential_suspect.replace("npy", "").upper())
plt.subplot(121)
plt.imshow(plt.imread('E:\\cpp\\homewrok\\mediadata\\test\\0\\0_3.jpg'))
plt.title('target_image')
plt.subplot(122)
plt.imshow(plt.imread(join(folder, potential_suspect.replace("npy", "jpg").upper())))
plt.title('result_image')
plt.show()
