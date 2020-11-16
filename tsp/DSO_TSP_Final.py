#!/usr/bin/env python
# coding: utf-8

# In[34]:


import numpy as np
import webbrowser
import os


# In[35]:


a = np.array([[0, 10, 12, 11, 14], [10, 0, 13, 15, 8], [12, 13, 0, 9, 14] , [11, 15, 9, 0, 16], [15, 8, 14, 16, 0]])
names = ['path from city 1' ,'path from city 2' ,'path from city 3', 'path from city 4', 'path from city 5']
namespossible = ['Possible path 1' ,'Possible path 2' ,'Possible path 3', 'Possible path 4']


# In[36]:


paths_list=[]
weights_list=[]
for i in range(0,5):
    temp=np.copy(a)
    temp[temp == 0] = 999999
    temp[:,i] = 999999
    out = min(temp[i,:])
    colOfMin = np.where(temp[i,:] == out)
    colOfMin=list(colOfMin)[0][0]
    rowOfMin=i
    temp[:,colOfMin] = 999999
    out1 = min(temp[colOfMin,:]) 
    rowOfMin1=colOfMin
    colOfMin1 = np.where(temp[colOfMin,:]== out1)
    colOfMin1=list(colOfMin1)[0][0]
    out2=min(temp[colOfMin1,:])
    rowOfMin2=colOfMin1
    colOfMin2 = np.where(temp[colOfMin1,:] == out2) 
    colOfMin2=list(colOfMin2)[0][0]
    temp[:,colOfMin2] = 999999;
    out3=min(temp[colOfMin2,:])
    rowOfMin3=colOfMin2
    colOfMin3 = np.where(temp[colOfMin2,:] == out3)
    colOfMin3=list(colOfMin3)[0][0]
    path=[i, colOfMin, colOfMin1, colOfMin2, colOfMin3, i] 
    path=[i+1 for i in path]
    weight=out+out1+out2+out3+a[colOfMin3,i]
    print(path)
    paths_list.append(path)
    print(weight)
    weights_list.append(weight)


# In[37]:


[i+1 for i in range(len(paths_list[0]))]


# In[42]:


from plotly.subplots import make_subplots
import plotly.graph_objects as go

fig = make_subplots(rows=2, cols=3)

fig.add_trace(
    go.Scatter(x=[i+1 for i in range(len(paths_list[0]))], y=paths_list[0],mode='markers+lines',name=' From City1(weight='+str(weights_list[0])+')'),
    row=1, col=1
)

fig.add_trace(
    go.Scatter(x=[i+1 for i in range(len(paths_list[1]))], y=paths_list[1],mode='markers+lines', name=' From City2(weight='+str(weights_list[1])+')'),
    row=1, col=2
)

fig.add_trace(
    go.Scatter(x=[i+1 for i in range(len(paths_list[2]))], y=paths_list[2],mode='markers+lines', name=' From City3(weight='+str(weights_list[2])+')'),
    row=1, col=3
)

fig.add_trace(
    go.Scatter(x=[i+1 for i in range(len(paths_list[3]))], y=paths_list[3],mode='markers+lines', name=' From City4(weight='+str(weights_list[3])+')'),
    row=2, col=1
)

fig.add_trace(
    go.Scatter(x=[i+1 for i in range(len(paths_list[4]))], y=paths_list[4],mode='markers+lines', name=' From City5(weight='+str(weights_list[4])+')'),
    row=2, col=2
)

fig.update_layout(title_text="Paths")
fig.write_html('plot_1.html')

webbrowser.open('file://' + os.path.realpath('plot_1.html'))


# In[30]:


x = int(input( 'choose the departure city: ' ))
paths_list=[]
weights_list=[]
city_list=[]
x=x-1
r=x
for c in range(0,5):
    temp=np.copy(a) 
    temp[temp == 0 ] = 999999
    temp[:,r]=999999
    if (temp[r,c]!=999999):
        out = temp[r,c] 
        rowOfMin=r
        colOfMin = np.where(temp[r,:] == out)
        colOfMin=list(colOfMin)[0][0]
        temp[:,colOfMin] = 999999

        out1 = min(temp[colOfMin,:])
        rowOfMin1=colOfMin
        colOfMin1 = np.where(temp[colOfMin,:] == out1) 
        colOfMin1=list(colOfMin1)[0][0]
        temp[:,colOfMin1] = 999999

        out2=min(temp[colOfMin1,:])
        rowOfMin2=colOfMin1
        colOfMin2 = np.where(temp[colOfMin1,:] == out2) 
        colOfMin2=list(colOfMin2)[0][0]
        temp[:,colOfMin2] = 999999

        out3=min(temp[colOfMin2,:])
        rowOfMin3=colOfMin2
        colOfMin3 = np.where(temp[colOfMin2,:] == out3) 
        colOfMin3=list(colOfMin3)[0][0]
        temp[:,colOfMin3] = 999999

        path=[x, colOfMin, colOfMin1, colOfMin2, colOfMin3, x] 
        path=[i+1 for i in path]
        weight=out+out1+out2+out3+a[colOfMin3,x] 
        print(path)
        paths_list.append(path)
        print(weight)
        weights_list.append(weight)
        city_list.append(c+1)
        temp[r,c]=999999


# In[43]:


from plotly.subplots import make_subplots
import plotly.graph_objects as go

fig = make_subplots(rows=2, cols=3)

fig.add_trace(
    go.Scatter(x=[i+1 for i in range(len(paths_list[0]))], y=paths_list[0],mode='markers+lines',name=' to City'+str(city_list[0])+'(weight='+str(weights_list[0])+')'),
    row=1, col=1
)

fig.add_trace(
    go.Scatter(x=[i+1 for i in range(len(paths_list[1]))], y=paths_list[1],mode='markers+lines', name=' to City'+str(city_list[1])+'(weight='+str(weights_list[1])+')'),
    row=1, col=2
)

fig.add_trace(
    go.Scatter(x=[i+1 for i in range(len(paths_list[2]))], y=paths_list[2],mode='markers+lines', name=' to City'+str(city_list[2])+'(weight='+str(weights_list[2])+')'),
    row=1, col=3
)

fig.add_trace(
    go.Scatter(x=[i+1 for i in range(len(paths_list[3]))], y=paths_list[3],mode='markers+lines', name=' to City'+str(city_list[3])+'(weight='+str(weights_list[3])+')'),
    row=2, col=1
)


fig.update_layout(title_text="Paths from city "+str(x+1))
fig.write_html('plot_2.html')
webbrowser.open('file://' + os.path.realpath('plot_2.html'))


# In[ ]:





# In[ ]:




