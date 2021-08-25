//从i到j的路径经过点k以后变短了
for(int k=0;k<n;++k)
    for(int i=0;i<n;++i)
        for(int j=0;j<n;++j)
            if(v[i][j]>v[i][k]+v[k][j])
            v[i][j]=v[i][k]+v[k][j];