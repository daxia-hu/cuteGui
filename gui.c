#include "gui.h"
/**
 * @brief ui调度器初始化 
 */
void GuiInit(Gui *gui,PageNode ** pageList,uint16_t page,uint16_t num,void *uiPtr)
{
    gui->nodeList = pageList;
    gui->num = num;
    gui->page = page;
    gui->uiPtr = uiPtr;
}
//带切换类型的界面切换
static void GuiTransType(Gui *gui,uint16_t page,uint8_t type)
{
    gui->nodeList[gui->page]->exit(gui);
    gui->page = page;
    gui->nodeList[gui->page]->init(gui,type);
}
/**
 * @brief UI界面跳转指定界面，被跳转的界面需要重新更新参数
 */
void GuiTrans(Gui *gui, uint16_t page)
{
    GuiTransType(gui, page, INIT_PARAM_RESET);
}
/**
 * @brief UI界面返回指定界面，被返回的界面不需要重新更新参数 
 */
void GuiBack(Gui *gui,uint16_t page)
{
    gui->nodeList[gui->page]->exit(gui);
    gui->page = page;
    gui->nodeList[gui->page]->init(gui,INIT_PARAM_RECORD);
}
/**
 * @brief 记录界面的历史界面 只有弹窗界面才能记录历史界面，且只能记录一层
 */
void GuiRecord(Gui *gui,uint16_t page,uint16_t backNode)
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
void GuiBackRecord(Gui *gui,uint16_t page)
{
    GuiTransType(gui, page, INIT_PARAM_RECORD);
}
/**
 * @brief 界面业务执行函数 
 */
void GuiWork(Gui *gui)
{
    gui->nodeList[gui->page]->work(gui);
}
/**
 * @brief 界面事件处理函数 
 */
void GuiEvent(Gui *gui,uint32_t event,uint32_t param)
{
    gui->nodeList[gui->page]->event(gui,event,param);
}