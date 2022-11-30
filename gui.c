#include "gui.h"
/**
 * @brief ui调度器初始化 
 */
void Gui_Init(Gui *gui,PageNode ** pageList,uint16_t page,uint16_t num,void *uiPtr)
{
    gui->nodeList = pageList;
    gui->num = num;
    gui->page = page;
    gui->uiPtr = uiPtr;
}
//带切换类型的界面切换
static void Gui_TransType(Gui *gui,uint16_t page,uint8_t type)
{
    if(NULL != gui->nodeList[gui->page]->exit)
    {
        gui->nodeList[gui->page]->exit(gui);
    }
    gui->page = page;
    if(NULL != gui->nodeList[gui->page]->init)
    {
        gui->nodeList[gui->page]->init(gui,type);
    }
}
/**
 * @brief UI界面跳转指定界面，被跳转的界面需要重新更新参数
 */
void Gui_Trans(Gui *gui, uint16_t page)
{
    GuiTransType(gui, page, INIT_PARAM_RESET);
}
/**
 * @brief UI界面返回指定界面，被返回的界面不需要重新更新参数 
 */
void Gui_Back(Gui *gui,uint16_t page)
{
    if(NULL != gui->nodeList[gui->page]->exit)
    {
        gui->nodeList[gui->page]->exit(gui);
    }
    gui->page = page;
    if(NULL != gui->nodeList[gui->page]->init)
    {
        gui->nodeList[gui->page]->init(gui,INIT_PARAM_RECORD);
    }
}
/**
 * @brief 记录界面的历史界面 只有弹窗界面才能记录历史界面，且只能记录一层
 */
void Gui_Record(Gui *gui,uint16_t page,uint16_t backNode)
{
    if(PAGE_TYPE_MSEEAGE != gui->nodeList[page]->pageType)
    {
        //只有弹窗界面才能记录历史界面
        return;
    }
    if (PAGE_TYPE_MSEEAGE == gui->nodeList[backNode]->pageType)
    {
        //如果历史界面是个弹窗界面，则返回历史界面的历史界面
        gui->nodeList[page]->pageBack = gui->nodeList[backNode]->pageBack;
    }
    else
    {
        gui->nodeList[page]->pageBack = backNode;
    }
}
/**
 * @brief 返回历史界面 
 */
void Gui_BackRecord(Gui *gui,uint16_t page)
{
    GuiTransType(gui, page, INIT_PARAM_RECORD);
}
/**
 * @brief 界面业务执行函数 
 */
void Gui_Work(Gui *gui)
{
    if(NULL != gui->nodeList[gui->page]->work)
    {
        gui->nodeList[gui->page]->work(gui);
    }
}
/**
 * @brief 界面事件处理函数 
 */
void Gui_Event(Gui *gui,uint32_t event,uint32_t param)
{
    if(NULL != gui->nodeList[gui->page]->event)
    {
        gui->nodeList[gui->page]->event(gui,event,param);
    }
}