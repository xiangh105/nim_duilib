#ifndef UI_CONTROL_LIST_CTRL_H_
#define UI_CONTROL_LIST_CTRL_H_

#pragma once

#include "duilib/Box/VirtualListBox.h"
#include "duilib/Control/Label.h"
#include "duilib/Control/Split.h"
#include "duilib/Box/ListBoxItem.h"
#include "duilib/Image/Image.h"

namespace ui
{

//列表数据项UI显示相关类
class ListCtrlItem;
class ListCtrlHeader;
class ListCtrlHeaderItem;

//列表数据管理类
class ListCtrlData;
class ListCtrlItemProvider;

/** ListCtrl控件
*/
class ListCtrl: public VBox
{
    friend class ListCtrlHeader;
public:
	ListCtrl();
	virtual ~ListCtrl();

	/** 获取控件类型
	*/
	virtual std::wstring GetType() const override;
	virtual void SetAttribute(const std::wstring& strName, const std::wstring& strValue) override;

public:
    /** 在指定位置添加一列
    * @param [in] nCol 在第几列以后插入该列，如果是-1，表示在最后追加一列
    * @param [in] nColumnWidth 列宽
    * @param [in] text 表头的文本
    * @param [in] bSortable 是否允许排序
    * @param [in] bResizeable 是否允许通过拖动调整列宽
    * @param [in] bNeedDpiScale 是否对列宽nColumnWidth值做DPI自适应
    * @return 返回这一列的表头控件接口
    */
    ListCtrlHeaderItem* InsertColumn(int32_t nCol, int32_t nColumnWidth, const std::wstring& text,
                                     bool bSortable = false, bool bResizeable = false, 
                                     bool bNeedDpiScale = true);

    /** 获取列的个数
    */
    size_t GetColumnCount() const;

    /** 获取列宽度
    * @param [in] columnIndex 列索引序号：[0, GetColumnCount())
    */
    int32_t GetColumnWidth(size_t columnIndex) const;

    /** 获取列表头的控件接口
    * @param [in] columnIndex 列索引序号：[0, GetColumnCount())
    */
    ListCtrlHeaderItem* GetColumnItem(size_t columnIndex) const;

    /** 获取列表头的控件接口
    * @param [in] columnId 列的ID值，通过ListCtrlHeaderItem::GetColomnId()函数获取
    */
    ListCtrlHeaderItem* GetColumnItemById(size_t columnId) const;

    /** 获取表头控件接口, 在控件初始化以后才有值
    */
    ListCtrlHeader* GetListCtrlHeader() const;

public:


protected:
    /** 控件初始化
    */
    virtual void DoInit() override;

    /** 设置ListCtrlHeader的属性Class
    */
    void SetListCtrlHeaderClass(const std::wstring& className);

    /** ListCtrlHeaderItem的属性Class
    */
    void SetListCtrlHeaderItemClass(const std::wstring& className);
    std::wstring GetListCtrlHeaderItemClass() const;

    /** ListCtrlHeader/SplitBox的属性Class
    */
    void SetListCtrlHeaderSplitBoxClass(const std::wstring& className);
    std::wstring GetListCtrlHeaderSplitBoxClass() const;

    /** ListCtrlHeader/SplitBox/Control的属性Class
    */
    void SetListCtrlHeaderSplitControlClass(const std::wstring& className);
    std::wstring GetListCtrlHeaderSplitControlClass() const;

protected:
    /** 调整列的宽度（拖动列宽调整，每次调整两个列的宽度）
    * @param [in] nColumnId1 第一列的ID
    * @param [in] nColumnId2 第二列的ID
    */
    void OnColumnWidthChanged(size_t nColumnId1, size_t nColumnId2);

    /** 对列排序
    * @param [in] nColumnId 列的ID
    * @param [in] bSortedUp 如果为true表示升序，如果为false表示降序
    */
    void OnColumnSorted(size_t nColumnId, bool bSortedUp);

private:
	/** 初始化标志
	*/
	bool m_bInited;

	/** 表头控件
	*/
	ListCtrlHeader* m_pListCtrlHeader;

	/** 列表数据展示
	*/
	ListCtrlData* m_pListCtrlData;

	/** 列表数据管理
	*/
	std::unique_ptr<ListCtrlItemProvider> m_spItemProvider;

    /** ListCtrlHeader的属性Class
    */
    UiString m_headerClass;

    /** ListCtrlHeaderItem的属性Class
    */
    UiString m_headerItemClass;

    /** ListCtrlHeader/SplitBox的属性Class
    */
    UiString m_headerSplitBoxClass;

    /** ListCtrlHeader/SplitBox/Control的属性Class
    */
    UiString m_headerSplitControlClass;
};

/** ListCtrl子项控件
*/
class ListCtrlItem : public ListBoxItem
{
public:
    /** 获取控件类型
    */
    virtual std::wstring GetType() const override { return L"ListCtrlItem"; }

};

/** ListCtrl的表头控件的显示项
*/
class ListCtrlHeaderItem:
    public Button
{
public:
    ListCtrlHeaderItem();
    virtual ~ListCtrlHeaderItem();

    /** 获取控件类型
    */
    virtual std::wstring GetType() const override;

    /** 设置属性
    */
    virtual void SetAttribute(const std::wstring& strName, const std::wstring& strValue) override;

    /** 绘制文字
    */
    virtual void PaintText(IRender* pRender) override;

    /** 按钮点击事件
    */
    virtual void Activate() override;

public:
    /** 排序方式
    */
    enum class SortMode
    {
        kNone, //不支持排序
        kUp,   //升序
        kDown  //降序
    };

    /** 设置排序方式
    */
    void SetSortMode(SortMode sortMode);

    /** 获取排序方式
    */
    SortMode GetSortMode() const;

    /** 设置排序图标：降序
    */
    void SetSortedDownImage(const std::wstring& sImageString);

    /** 设置排序图标：升序
    */
    void SetSortedUpImage(const std::wstring& sImageString);

    /** 获取唯一ID
    */
    size_t GetColomnId() const;

    /** 设置关联的Split控件接口
    */
    void SetSplitBox(SplitBox* pSplitBox);

    /** 获取关联的Split控件接口
    */
    SplitBox* GetSplitBox() const;

    /** 设置是否允许调整列宽
    */
    void SetColumnResizeable(bool bResizeable);

    /** 获取是否允许调整列宽
    */
    bool IsColumnResizeable() const;

    /** 设置列宽
    * @param [in] nWidth 列宽值
    * @param [in] bNeedDpiScale 是否需要对列宽值进行DPI自适应
    */
    void SetColumnWidth(int32_t nWidth, bool bNeedDpiScale);

    /** 获取列宽值
    */
    int32_t GetColumnWidth() const;

    /** 设置文字与图标之间的间隔（像素）
    */
    void SetIconSpacing(int32_t nIconSpacing, bool bNeedDpiScale);

    /** 获取文字与图标之间的间隔（像素）
    */
    int32_t GetIconSpacing() const;

private:
    /** 同步列宽与UI控件宽度
    */
    void CheckColumnWidth();

private:
    /** 排序图标：降序
    */
    Image* m_pSortedDownImage;

    /** 排序图标：升序
    */
    Image* m_pSortedUpImage;

    /** 关联的Split控件接口
    */
    SplitBox* m_pSplitBox;

    /** 排序方式
    */
    SortMode m_sortMode;

    /** 列宽
    */
    int32_t m_nColumnWidth;

    /** 是否允许改变列宽
    */
    bool m_bColumnResizeable;

    /** 文字与图标之间的间隔
    */
    int32_t m_nIconSpacing;
};

/** ListCtrl的表头控件
*/
class ListCtrlHeader : public ListBoxItemH
{
    friend class ListCtrlHeaderItem;
public:
    ListCtrlHeader();

    /** 获取控件类型
    */
    virtual std::wstring GetType() const override;

public:
    /** 在指定位置添加一列
    *  表头控件的基本结构如下：
    *   <ListCtrlHeader>
    *       <ListCtrlHeaderItem/>
    *       <SplitBox> <Control/> </SplitBox>
    *       ..
    *       <ListCtrlHeaderItem/>
    *       <SplitBox> <Control/> </SplitBox>
    *   </ListCtrlHeader>
    * @param [in] nCol 在第几列以后插入该列，如果是-1，表示在最后追加一列
    * @param [in] nColumnWidth 列宽
    * @param [in] text 表头的文本
    * @param [in] bSortable 是否允许排序
    * @param [in] bResizeable 是否允许通过拖动调整列宽
    * @param [in] bNeedDpiScale 是否对列宽nColumnWidth值做DPI自适应
    * @return 返回这一列的表头控件接口
    */
    ListCtrlHeaderItem* InsertColumn(int32_t nCol, int32_t nColumnWidth, const std::wstring& text,
                                     bool bSortable = false, bool bResizeable = false, 
                                     bool bNeedDpiScale = true);

    /** 获取列的个数
    */
    size_t GetColumnCount() const;

    /** 获取列宽度
    * @param [in] columnIndex 列索引序号：[0, GetColumnCount())
    */
    int32_t GetColumnWidth(size_t columnIndex) const;

    /** 获取列表头的控件接口
    * @param [in] columnIndex 列索引序号：[0, GetColumnCount())
    */
    ListCtrlHeaderItem* GetColumnItem(size_t columnIndex) const;

    /** 获取列表头的控件接口
    * @param [in] columnId 列的ID值，通过ListCtrlHeaderItem::GetColomnId()函数获取
    */
    ListCtrlHeaderItem* GetColumnItemById(size_t columnId) const;

    /** 获取列宽度和列索引序号
    * @param [in] columnId 列的ID值，通过ListCtrlHeaderItem::GetColomnId()函数获取
    * @param [out] columnIndex 列的序号：[0, GetColumnCount())，代表第几列
    * @param [out] nColumnWidth 列的宽度值
    */
    bool GetColumnInfo(size_t columnId, size_t& columnIndex, int32_t& nColumnWidth) const;

public:

    /** 设置关联的ListCtrl接口
    */
    void SetListCtrl(ListCtrl* pListCtrl);

protected:
    /** 拖动列表头改变列宽的事件响应函数
    * @param [in] pLeftHeaderItem 左侧的列表头控件接口
    * @param [in] pRightHeaderItem 右侧的列表头控件接口
    */
    void OnHeaderColumnResized(Control* pLeftHeaderItem, Control* pRightHeaderItem);

    /** 点击列表头触发排序的事件响应函数
    * @param [in] pHeaderItem 列表头控件接口
    */
    void OnHeaderColumnSorted(ListCtrlHeaderItem* pHeaderItem);

private:
    /** 关联的ListCtrl接口
    */
    ListCtrl* m_pListCtrl;
};

}//namespace ui

#endif //UI_CONTROL_LIST_CTRL_H_
