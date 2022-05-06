# coding=utf-8
import math
import tushare as ts
import pandas as pd
import matplotlib
import matplotlib.pyplot as plt
import numpy as np
# import talib

if __name__ == '__main__':
    matplotlib.rcParams['axes.unicode_minus'] = False
    matplotlib.rcParams['font.sans-serif'] = ['FangSong']
    ts.set_token('1e418a2f9c7492463adc10f8eed21b0a111a89d7bdd09c3d5f69976c')  # 若没有，需注册获取https://tushare.pro/register?reg=385920
    pro = ts.pro_api()
    df1 = pro.query('daily_basic', ts_code='', trade_date='20220505',
                    fields='ts_code,trade_date,total_mv,ps,pe,pb')  # 获取日期所有数据

    # 条
    df1 = df1[df1['pe'] > 20]
    df1 = df1[df1['pb'] > 8]
    df1 = df1[df1['ps'] > 17]
    df1 = df1[df1['total_mv'] < 5000000]
    # 排序选股
    df1 = df1.sort_values(by="pe", ascending=True)
    df1 = df1.head(1000)  # 按由低到高排，选前100名
    df1 = df1.sort_values(by="ps", ascending=True)
    df1 = df1.head(700)
    df1 = df1.sort_values(by="pb", ascending=True)
    df1 = df1.head(200)
    df1 = df1['ts_code']  # 获得一篮子股票
    df1.values.tolist()  # 转换成列表
    stock = ','.join(df1)  # 转换成浮点，用逗号隔开
    # df2= pro.query('daily_basic', ts_code=stock, trade_date='20200211',fields='ts_code,trade_date,total_mv,ps,pe,pb')

    cum = 0
    for i in df1:
        df = pro.query('daily', ts_code=i, start_date='20211105', end_date='20220505', fields='')

        df = df.sort_index()
        df.index = pd.to_datetime(df.trade_date, format='%Y-%m-%d')  # 设置日期索引
        ret = df.change / df.close
        dd = pd.Series(1, index=df.close.index)
        cumqq = ret * dd.shift(1).dropna()
        cum = (np.cumprod(1 + ret[cumqq.index[0:]]) - 1) / len(df1) + cum  # 等权重配置一篮子股票

    df12 = pro.index_daily(ts_code='000016.SH', start_date='20211105', end_date='20220505')
    df12 = df12.sort_index()
    df12.index = pd.to_datetime(df12.trade_date, format='%Y-%m-%d')  # 设置日期索引
    ret12 = df12.change / df12.close
    # 将顺序颠倒
    aq = pd.Series(1, index=df12.close.index)
    SmaRet = ret12 * aq.shift(1).dropna()
    cum12 = np.cumprod(1 + ret12[SmaRet.index[0:]]) - 1
    # 做空沪深300股指期货
    df3 = pro.fut_daily(ts_code='IH2206.CFX', start_date='20211105', end_date='20220505')
    df3.sort_index()
    df3.index = pd.to_datetime(df3.trade_date, format="%Y-%m-%d")
    ret13 = df3.change1 / df3.close
    sy = pd.Series(1, index=df3.close.index)
    sy2 = ret13 * sy.shift(1).dropna()
    cum13 = np.cumprod(1 + ret13[sy2.index[0:]]) - 1

    f = cum[-2] * 250 / len(df3.close) - cum13[-2] * 250 / len(df3.close)
    f1 = 100 * f  # 换成百分制
    plt.plot(cum12, label="000016.SH", color='b')
    plt.plot(cum - cum13, label="alph return", color="y")
    plt.plot(cum, label="portfolio", color='r')
    plt.title("alpha&beta strategy")
    plt.legend()
    print("alpha ：{:.2f}%".format(f1))
    plt.show()


