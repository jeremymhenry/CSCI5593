import os
import matplotlib.pyplot as plt
import subprocess
import pandas as pd
from sklearn import preprocessing
timing=[]
os.system('gcc mainpy.c -o mainpy')
for i in range(1, 2000):
    i=subprocess.check_output("./mainpy", shell=True);
    timing.append(i.decode('ascii'))
t=pd.DataFrame(timing)
t.to_csv('result.csv')
