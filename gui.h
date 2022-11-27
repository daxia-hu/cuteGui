#ifndef GUI_H
#define GUI_H
#include "stdint.h"
typedef enum
{
    PAGE_TYPE_NORMAL,  //普通界面
    PAGE_TYPE_MSEEAGE, //弹窗类界面
} UIPAGE_TYPE;
typedef enum
{
    INIT_PARAM_RESET,   //返回重新绘制界面
    INIT_PARAM_RECORD,  //按照上次的参数返回
}UIPAGE_INIT_PARAM;
typedef struct Gui_t Gui;
/* 界面初始化处理函数 */
typedef void (*uiInitHandle)(Gui *gui,uint8_t type);
/* 界面退出处理函数 */
typedef void (*uiExitHandle)(Gui *gui);
/* 界面业务处理函数 */
typedef void (*uiWorkHandle)(Gui *gui);
/* 界面事件处理函数 */
typedef void (*uiEventHandle)(Gui *gui, uint32_t event, uint32_t param);

typedef struct PageNode_t
{
    uint16_t pageType;   //界面类型
    uint16_t pageBack;   //界面的历史界面
    uiInitHandle init;   //界面构造函数、界面的绘制、数据的填充
    uiExitHandle exit;   //界面退出的析构函数
    uiWorkHandle work;   //界面需要循环执行的业务函数如动画
    uiEventHandle event; //界面的时间回调函数
} PageNode;
typedef struct Gui_t
{
    PageNode **nodeList; //调度器挂载的界面列表
    uint16_t num;        //总挂载的界面个数
    uint16_t page;       //当前显示的界面
    void *uiPtr;         //界面包含的参数指针 可以在界面之间进行参数传递
} Gui;

/**
 * @brief ui调度器初始化 
 */
void GuiInit(Gui *gui,PageNode ** pageList,uint16_t page,uint16_t num,void *uiPtr);
/**
 * @brief UI界面跳转指定界面，被跳转的界面需要重新更新参数
 */
void GuiTrans(Gui *gui, uint16_t page);
/**
 * @brief UI界面返回指定界面，被返回的界面不需要重新更新参数 
 */
void GuiBack(Gui *gui,uint16_t page);
/**
 * @brief 记录界面的历史界面 只有弹窗界面才能记录历史界面，且只能记录一层
 */
void GuiRecord(Gui *gui,uint16_t page,uint16_t backNode);
/**
 * @brief 返回历史界面 
 */
void GuiBackRecord(Gui *gui,uint16_t page);
/**
 * @brief 界面业务执行函数 
 */
void GuiWork(Gui *gui);
/**
 * @brief 界面事件处理函数 
 */
void GuiEvent(Gui *gui,uint32_t event,uint32_t param);
#endif