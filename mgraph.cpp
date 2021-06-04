#include "mgraph.h"
#include<fstream>
#include<QMessageBox>
#include<QObject>
#include<QStack>
MGraph::MGraph()
{
    numEdges=0;
    numNodes=0;
}
void MGraph::create()
{
    /*
    vexs[0].name="思源楼";vexs[0].information="这是思源楼";
    vexs[1].name="思源西楼";vexs[1].information="这是思西";
    vexs[2].name="思源东楼";vexs[2].information="这是思东";
    vexs[3].name="九教";vexs[3].information="这是九教";
    vexs[4].name="嘉园";vexs[4].information="这是嘉园";
   // FILE* fp=fopen("arcdata.txt","r");
   // arc[][].length={(0,2,0,0,0),(2,0,3,0,0),(0,3,0,1,0),(0,0,1,0,5),(0,0,0,5,0)};*/
    int a[25]={000,002,100,100,100,
               002,000,003,100,100,
               100,003,000,001,100,
               100,100,001,000,005,
               100,100,100,005,000};
    for(int i=0;i<5;i++)
        for(int j=0;j<5;j++)
        {
            arc[i][j].length=a[i*5+j];
        }
    using namespace std;
    ifstream num_file;
    int num=0;
    num_file.open("numNode.txt");
    if(!num_file.is_open())
        QMessageBox::information(NULL,"warn",QObject::tr("false"));
    num_file>>num;
    num_file.close();
    numEdges=5;//未定
    numNodes=num;
    for(int i=0;i<num;i++)
    {
        vexs[i].id=i;
    }
    ifstream name_file;
    ifstream infor_file;
    string* name1=new string[num];
    string* infor1=new string[num];
    name_file.open("data.txt");
    infor_file.open("information.txt");
    if(!name_file.is_open())
        QMessageBox::information(NULL,"warn",QObject::tr("false"));
        for(int i=0;i<num;i++)
        {
            name_file>>name1[i];
            infor_file>>infor1[i];
        }        
    name_file.close();
    infor_file.close();
    for(int i=0;i<num;i++)
    {
        vexs[i].name=QString::fromStdString(name1[i]);
        vexs[i].information=QString::fromStdString(infor1[i]);
    }
    return;
}

bool MGraph::search(int _id, vextype &res)
{
    for(int i=0;i<numNodes;i++)
    {
        if(_id==vexs[i].id)
        {
            res=vexs[i];
            return true;
        }
    }
    return false;
}
bool MGraph::search(QString _name, vextype &res)
{
    for(int i=0;i<numNodes;i++)
    {
        if(_name==vexs[i].name)
        {
            res=vexs[i];
            return true;
        }
    }
    return false;
}
bool MGraph::search(int _level, QVector<vextype> &res)
{
    bool result=false;
    for(int i=0;i<numNodes;i++)
    {
        if(_level==vexs[i].level)
        {
            res.push_back(vexs[i]);
            result=true;
        }
    }
    return result;
}
void MGraph::get_shortest(vextype vex1, vextype vex2, QString &res)
{
    int dis[1000];
    bool vis[1000];
    memset(vis,0,sizeof(vis));
    memset(dis,0,sizeof(dis));
    int pre[1000];
    for(int i=0;i<numEdges;i++)
    {
        dis[i]=arc[vex1.id][i].length;
        if(dis[i]!=999999)
            pre[i]=vex1.id;
        else
            pre[i]=i;
    }
    vis[vex1.id]=true;
    dis[vex1.id]=0;
    for(int i=0;i<numNodes;i++)
    {
        int minn;
        minn=99999;
        int minnum;
        for(int j=0;j<numNodes;j++)
        {
            if(dis[j]<minn&&vis[j]==false)
            {
                minn=dis[j];
                minnum=j;
            }
        }
        vis[minnum]=true;
        for(int k=0;k<numNodes;k++)
        {
            if(dis[minnum]+arc[minnum][k].length<dis[k])
            {
                dis[k]=dis[minnum]+arc[minnum][k].length;
                pre[k]=minnum;
            }
        }
    }
    int temp=vex2.id;
    QStack<int>pathway;
    int cnt=0;
    while(temp!=vex1.id)
    {
        pathway.push(temp);
        temp=pre[temp];
        cnt++;
    }
    pathway.push(temp);
    cnt++;
    while(!pathway.empty())
    {
        cnt--;
        res=res+vexs[pathway.top()].name;
        if(cnt)
            res=res+"->";
        pathway.pop();
    }
    res=res+",总距离为";
    res=res+QString::number(dis[vex2.id]);
}
