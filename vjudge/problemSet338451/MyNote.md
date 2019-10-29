# HUST-ACM 2019新生B class训练题

专题：贪心算法 日期：2019-10-27

## Problem A  

## Problem B  
经典题目

垃圾测试机不认识`sync_with_stdio`，太屑了（）  
```c++
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
```

## Problem C  
对于任何Remote Judge或者远程OJ，提交之前一定要先选C++11/C++14！

## Problem I @Uva1153
显然，参考之前的上班问题，这次贪心和生产量无关（无论多少生产量都算作一个订单），只是和ddl有关。  
ddl结束的越早，以后作更多东西的可能越大；或者说ddl结束的迟，那很多事情就做不了了。  
预先进行排序可以减少回溯次数，使用优先级队列可以方便的找出当前选择的订单中耗时最多的项目。  
因为预先排序，后遍历到的项目的ddl一定不会比之前的小，所以如果这时候后遍历的项的

