#ifndef UI_CONTROL_LIST_CTRL_HEADER_ITEM_H_
#define UI_CONTROL_LIST_CTRL_HEADER_ITEM_H_

#pragma once

#include "duilib/Control/Button.h"
#include "duilib/Control/CheckBox.h"
#include "duilib/Control/Split.h"
#include "duilib/Image/Image.h"

namespace ui
{

/** ListCtrl�ı�ͷ�ؼ�����ʾ��
*/
class ListCtrlHeaderItem:
    public ButtonBox
{
public:
    ListCtrlHeaderItem();
    virtual ~ListCtrlHeaderItem();

    /** ��ȡ�ؼ�����
    */
    virtual std::wstring GetType() const override;

    /** ��������
    */
    virtual void SetAttribute(const std::wstring& strName, const std::wstring& strValue) override;

    /** ��������
    */
    virtual void PaintText(IRender* pRender) override;

    /** ��ť����¼�
    */
    virtual void Activate() override;

public:
    /** ����ʽ
    */
    enum class SortMode
    {
        kNone, //��֧������
        kUp,   //����
        kDown  //����
    };

    /** ��������ʽ
    */
    void SetSortMode(SortMode sortMode);

    /** ��ȡ����ʽ
    */
    SortMode GetSortMode() const;

    /** ��������ͼ�꣺����
    */
    void SetSortedDownImage(const std::wstring& sImageString);

    /** ��������ͼ�꣺����
    */
    void SetSortedUpImage(const std::wstring& sImageString);

    /** ��ȡΨһID
    */
    size_t GetColomnId() const;

    /** ���ù�����Split�ؼ��ӿ�
    */
    void SetSplitBox(SplitBox* pSplitBox);

    /** ��ȡ������Split�ؼ��ӿ�
    */
    SplitBox* GetSplitBox() const;

    /** �����Ƿ����������п�
    */
    void SetColumnResizeable(bool bResizeable);

    /** ��ȡ�Ƿ����������п�
    */
    bool IsColumnResizeable() const;

    /** �����п�
    * @param [in] nWidth �п�ֵ
    * @param [in] bNeedDpiScale �Ƿ���Ҫ���п�ֵ����DPI����Ӧ
    */
    void SetColumnWidth(int32_t nWidth, bool bNeedDpiScale);

    /** ��ȡ�п�ֵ
    */
    int32_t GetColumnWidth() const;

    /** ����������ͼ��֮��ļ�������أ�
    */
    void SetIconSpacing(int32_t nIconSpacing, bool bNeedDpiScale);

    /** ��ȡ������ͼ��֮��ļ�������أ�
    */
    int32_t GetIconSpacing() const;

    /** ����ͼ����ʾ�������Ϸ���������ʾ
    */
    void SetShowIconAtTop(bool bShowIconAtTop);

    /** ��ȡͼ���Ƿ���ʾ�������Ϸ�
    */
    bool IsShowIconAtTop() const;

public:
    /** �����Ƿ���ʾCheckBox
    * @param [in] bVisible true��ʾ��ʾ��false��ʾ����
    */
    bool SetCheckBoxVisible(bool bVisible);

    /** �жϵ�ǰCheckBox�Ƿ�����ʾ״̬
    @return ����true��ʾCheckBox���ڣ����ҿɼ��� �������CheckBox������false
    */
    bool IsCheckBoxVisible() const;

    /** �Ƿ���CheckBox
    */
    bool HasCheckBox() const;

    /** ����CheckBox�Ĺ�ѡ״̬
    * @param [in] bSelected true��ʾ��ѡ��false��ʾ����ѡ
    * @param [in] ���bSelected��bPartSelectͬʱΪtrue����ʾ����ѡ��
    */
    bool SetCheckBoxSelect(bool bSelected, bool bPartSelect);

private:
    /** ͬ���п���UI�ؼ�����
    */
    void CheckColumnWidth();

protected:
    /** @name �϶���صĳ�Ա����
    * @{ */

    virtual bool ButtonDown(const EventArgs& msg) override;
    virtual bool ButtonUp(const EventArgs& msg) override;
    virtual bool MouseMove(const EventArgs& msg) override;
    virtual bool OnWindowKillFocus(const EventArgs& msg) override;//�ؼ������Ĵ���ʧȥ����

    /** �������λ�õ��������ؼ���λ��(�϶�������һ����)
    */
    void AdjustHeaderItemPos(const UiPoint& mousePt);

    /** ����϶�״̬
    */
    void ClearDragStatus();

    /** @} */

private:
    /** ����ͼ�꣺����
    */
    Image* m_pSortedDownImage;

    /** ����ͼ�꣺����
    */
    Image* m_pSortedUpImage;

    /** ������Split�ؼ��ӿ�
    */
    SplitBox* m_pSplitBox;

    /** ����ʽ
    */
    SortMode m_sortMode;

    /** �п�
    */
    int32_t m_nColumnWidth;

    /** �Ƿ������ı��п�
    */
    bool m_bColumnResizeable;

    /** ������ͼ��֮��ļ��(ͼ����ʾ�����ֵ��Ҳ�������ʱ)
    */
    int32_t m_nIconSpacing;

    /** ͼ����ʾ�������Ϸ���������ʾ
    */
    bool m_bShowIconAtTop;

private:
    /** @name �϶���صĳ�Ա����
    * @{ */

    /** �Ƿ�����������
    */
    bool m_bMouseDown;

    /** �Ƿ�����ק������
    */
    bool m_bInDragging;

    /** ԭ����͸����
    */
    uint8_t m_nOldAlpha;

    /** ��갴��ʱ�����λ��
    */
    UiPoint m_ptMouseDown;

    /** ��갴��ʱ�Ŀؼ���������
    */
    UiRect m_rcMouseDown;

    struct ItemStatus
    {
        Control* m_pItem = nullptr;
        UiRect m_rcPos;
        size_t m_index = Box::InvalidIndex;
    };

    /** ��갴��ʱ���������У�ÿ���ؼ���λ��
    */
    std::vector<ItemStatus> m_rcItemList;

    /** @} */
};

}//namespace ui

#endif //UI_CONTROL_LIST_CTRL_HEADER_ITEM_H_