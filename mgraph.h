#ifndef MGRAPH_H
#define MGRAPH_H
#include<QVector>
#include<QString>
#define SIDEWORK 1//人行道
#define NON_SIDEWORK -1//非人行道
#define BOTH 0//不限类型的路
#define MAXVEX 100//最大顶点数
typedef struct vextype
{
    /*顶点类型定义，存储顶点相关信息*/
    QString name;//景点名称
    int id;//景点代号
    int level;//景点等级
    QString information;//景点简介
}vextype;
typedef int rodetype;
typedef struct arctype
{
    /*边类型定义，存储边相关信息*/
    int length;//路径长度
    rodetype type;//路类型
}arctype;

class MGraph
{
public:
    vextype vexs[MAXVEX]; /* 顶点表 */
    arctype arc[MAXVEX][MAXVEX];/* 邻接矩阵，可看作边表 */
    int numNodes, numEdges; /* 图中当前的顶点数和边数  */
public:
    MGraph();
    /*从文件读取图的相关信息并建立图*/
    void create();

    /*查询景点信息,景点信息存储在res中;
     *成功返回true,失败返回false*/
    bool search(QString _name, vextype& res);//根据景点名称查找
    bool search(int _id, vextype& res);//根据景点代号查找

    /*根据景点等级查询所有满足条件的景点，景点信息存储在res中;
     *成功返回true,失败返回false*/
    bool search(int _level, QVector<vextype> &res);

    /*求出vex1和vex2的最短路径,路径信息存储在res中*/
    void get_shortest(vextype vex1, vextype vex2, QString& res);

    /*求出vex1和vex的所有路径，路径信息存储在res中*/
    void get_all(vextype vex1, vextype vex2, QVector<QString>& res);

    /*将新的景点信息存入图中
     *存储图信息的文件也要更新
     *成功返回true,失败返回false
     *如何存入？参数未定*/
    bool append(vextype vex);

    /*修改景点的信息
     *成功返回true,失败返回false
     *存储图的文件也要更新*/
    bool vexname_modify(vextype& vex, QString newname);//修改景点名称
    bool vexinfor_modify(vextype& vex, QString newinfor);//修改景点简介
    /*修改两景点道路的信息
     *判断两景点是否邻接
     *成功返回true,失败返回false
     *存储图的文件也要更新*/
    bool arclen_modfiy(vextype vex1, vextype vex2, int newlen);//修改道路长度
    bool arctype_modfiy(vextype vex1, vextype vex2, rodetype newtype);//修改道路类型

    /*剩余问题
     * 存储两顶点之间的方向信息
     * 新顶点的插入
     * 求图的关节点
     */

};

#endif // MGRAPH_Hr
