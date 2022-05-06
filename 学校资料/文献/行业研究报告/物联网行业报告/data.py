import pandas as pd
import numpy as np
from sklearn.cluster import KMeans, k_means
from sklearn.decomposition import PCA
import matplotlib as mpl
import matplotlib.pyplot as plt
from scipy.spatial.distance import pdist, euclidean
from sklearn.metrics import silhouette_score
from scipy.spatial.distance import cdist

data = pd.read_excel(r"/Users/xushaoqian/Desktop/文献/行业研究报告/财务指标.xlsx", sheet_name=0)
adata = pd.DataFrame(columns=data.columns, index=data.index)
bdata = pd.DataFrame(columns=data.columns, index=data.index)
mpl.rc('font', family='PingFang HK')

for i in data.columns[0:]:
    for j in range(0, 130):
        if i == data.columns[0]:
            adata[i][j] = data[i][j]
        else:
            adata[i][j] = (data[i][j]-data[i].mean())/(data[i].std())


def getpcadata(sdata, comp):
    pcaclf = PCA(n_components=comp, whiten=True)
    pcaclf.fit(sdata)
    data_pca = pcaclf.transform(sdata)
    return data_pca


def drawkmodel(xdata, t):
    plt.figure(figsize=(10, 10))
    colors = ['g', 'r', 'y', 'b', 'c', 'm', 'k']
    markers = ['o', 's', 'd', 'h', 'v', 'H', 'D']
    kmeans_model = KMeans(n_clusters=t).fit(xdata)
    for i, l in enumerate(kmeans_model.labels_):
        plt.plot(xdata[i][0], xdata[i][1], color=colors[l], marker=markers[l], ls='None')
        plt.title(f'k-means聚类{t}簇图', fontsize=30)
    plt.show()


def dbi(data, cu):
    label = k_means(data, n_clusters=cu)[1]
    clusters = len(np.bincount(label))
    clusterk = [data[label == k] for k in range(clusters)]
    centroids = [np.mean(k, axis=0) for k in clusterk]
    s = [np.mean([euclidean(p, centroids[i]) for p in k]) for i, k in enumerate(clusterk)]
    ri = []
    for i in range(clusters):
        rij = []
        for j in range(clusters):
            if j != i:
                r = (s[i] + s[j]) / euclidean(centroids[i], centroids[j])
                rij.append(r)
        ri.append(max(rij))
    dbi = np.mean(ri)
    return dbi


def silhouette(data, cu):
    kmeans = KMeans(n_clusters=cu)
    result_list = kmeans.fit_predict(data)
    score = silhouette_score(data, result_list)
    return score


def elbowgraph(data):
    k = range(1, 8)
    meandistortions = []
    for i in k:
        kmeans = KMeans(n_clusters=i)
        kmeans.fit(data)
        meandistortions.append(sum(np.min(cdist(data, kmeans.cluster_centers_, 'euclidean'), axis=1))
                               / data.shape[0])
    plt.plot(k, meandistortions, 'bx-')
    plt.xlabel('聚簇数')
    plt.ylabel(u'样本距质心的平均距离')
    plt.title('"肘部"观察图', fontsize=20)
    plt.show()


bdata = getpcadata(adata[adata.columns[1:]], 2)
# dbilist = []
# silhouettelist = []
# for i in range(2, 7):
#     dbilist.append(dbi(bdata, i))
#     silhouettelist.append(silhouette(bdata, i))


def exportdata(data1, data2):
    list1 = []
    list2 = []
    for i in range(0, len(data1)):
        list1.append(data1[i])
        list2.append(data2[i])
    list1 = np.array(list1)
    list2 = np.array(list2)
    list3 = np.array(list(zip(list2, list1))).reshape(len(list1), 2)
    list3 = pd.DataFrame(list3)
    writer = pd.ExcelWriter('savelist.xlsx')
    list3.to_excel(writer, 'page1')
    writer.save()
    return list3


label = k_means(bdata, n_clusters=5)[1]
clusters = len(np.bincount(label))
clusterk = [bdata[label == k] for k in range(clusters)]
centroids = [np.mean(k, axis=0) for k in clusterk]
clusterk1 = [data[label == k] for k in range(clusters)]
centroids1 = pd.DataFrame([np.mean(k, axis=0) for k in clusterk1])
distance = pd.DataFrame([[euclidean(bdata[i], centroids[label[i]]), label[i]]for i in range(130)])
writer1 = pd.ExcelWriter('savelist1.xlsx')
writer2 = pd.ExcelWriter('savelist2.xlsx')
centroids1.to_excel(writer1, 'page1')
distance.to_excel(writer2, 'page1')
# writer1.save()
# writer2.save()

print(np.mean(data))
