# -*- coding: utf-8 -*-
"""
Created on Thu Jun  8 18:19:14 2017

@author: Katsuaki Kawashima
"""

"""
◇スミルノフグラブス検定による外れ値検出
　 対象となる行列（n行1列）をクリップボードにコピーしてプログラムを実行する．
  元の行列から外れ値が除外された配列内の平均値がクリップボードにコピーされます．
  外れ値が検出されなかった場合は，平均値が算出されません．
"""


import numpy as np
import pandas as pd
from scipy import stats


data = pd.read_clipboard(header=None)
trans_data = data.dropna(axis = 1)
    

N = len(trans_data)    
alpha = 0.05
test = np.array(data)#元データ
test2 = []#検定統計量
outlier = []
while True:
    
    t = stats.t.isf(alpha/2, N-2)
    SignificantPoint = (N - 1) / np.sqrt(N) * np.sqrt( t*t / (N -2 + t*t) )
    
    ave = np.average(test)
    std = np.std(test)
    N = len(test)
    for i in range (N):
        test2.append((test[i] - ave) / std)
    
    test2 = np.array(test2)
    test_max = np.max(test2)
    test_min = np.min(test2)
    
    if( abs(test_max) > abs(test_min)):
        test_value = abs(test_max)
    else:
        test_value = abs(test_min)
   
   
    #統計検定量 > 有意点ならはずれ値とみなす
    if test_value > SignificantPoint:
        index = np.where(abs(test2) == test_value)

       
        outlier.append(test[index])
        test = np.delete(test, index[0], 0)  
        
        #初期化
        test2 = []
    else:
        break

print("はずれ値:{}".format(outlier))

if len(outlier) > 0:
    data_filtered = data[data[0] < np.min(outlier)]#元の配列からはずれ値を除いたもの．
    data_filtered.mean().to_clipboard(header=None,index=False)#結果がクリップボードに保存される