#ifndef UI_CONTROL_COMBO_H_
#define UI_CONTROL_COMBO_H_

#pragma once

#include "duilib/Core/Box.h"

namespace ui 
{
	class ListBox;
	class CComboWnd;
class UILIB_API Combo : public Box
{
    friend class CComboWnd;
public:
	Combo();
	Combo(const Combo& r) = delete;
	Combo& operator=(const Combo& r) = delete;

	/// 重写父类方法，提供个性化功能，请参考父类声明
	virtual std::wstring GetType() const override;
#if defined(ENABLE_UIAUTOMATION)
	virtual UIAControlProvider* GetUIAProvider() override;
#endif
	virtual bool AddItem(Control* pControl) override;
	virtual bool RemoveItem(Control* pControl) override;
	virtual bool RemoveItemAt(size_t iIndex) override;
	virtual void RemoveAllItems() override;
	virtual void Activate() override;
	virtual void SetAttribute(const std::wstring& strName, const std::wstring& strValue) override;
	virtual void PaintText(IRenderContext* pRender) override;

	/** 该控件是否可以放置在标题栏上（以用于处理NC消息响应）
	 * @return 返回 true 表示可以，false 表示不可以
	 */
	virtual bool CanPlaceCaptionBar() const override;

	/**
	 * @brief 获取当前选择项文本
	 * @return 返回当前选择项文本
	 */
    std::wstring GetText() const;

	/**
	* @brief 获取文字边距
	* @return 返回文字的边距信息
	*/
	UiRect GetTextPadding() const;

	/**
	* @brief 设置文字边距信息
	* @param[in] rc 边距信息
	* @return 无
	*/
	void SetTextPadding(UiRect rc);

	/**
	 * @brief 获取当前所属的 List 对象
	 * @return 返回所属的 List 对象指针
	 */
	ListBox* GetListBox() { return m_pLayout.get(); }

	/**
	 * @brief 获取下拉框属性信息
	 * @return 返回字符串形式的属性信息
	 */
    std::wstring GetDropBoxAttributeList();

	/**
	 * @brief 设置下拉框的属性信息
	 * @param[in] pstrList 转义后的 XML 格式属性列表
	 * @return 无
	 */
    void SetDropBoxAttributeList(const std::wstring& pstrList);

	/**
	 * @brief 获取下拉框容器大小
	 * @return 返回容器大小
	 */
    UiSize GetDropBoxSize() const;

	/**
	 * @brief 设置下拉框容器大小
	 * @param[in] szDropBox 要设置的大小信息
	 * @return 无
	 */
    void SetDropBoxSize(UiSize szDropBox);
	
	/**
	 * @brief 设置 Combobox 是否向上弹出
	 * @param[in] top 为 true 则向上弹出，false 为默认向下弹出
	 * @return 无
	 */
	void SetPopupTop(bool top) { m_bPopupTop = top; };
	
	/**
	 * @brief 判断 Combobox 弹出模式是否是向上弹出
	 * @return 返回 true 表示向上弹出，否则为 false
	 */
	bool IsPopupTop() const { return m_bPopupTop; };

	/**
	 * @brief 选择一个子项
	 * @param[in] iIndex 要选择的子项索引
	 * @param[in] bTrigger 是否触发选择事件
	 * @return 返回 true 表示成功，否则为 false
	 */
	bool SelectItem(int iIndex, bool bTrigger = false);

	/**
	 * @brief 获取指定索引下的子项控件
	 * @param[in] iIndex 要获取的子项索引
	 * @return 返回控件指针
	 */
	Control* GetItemAt(int iIndex);

	/**
	 * @brief 获取当前选择项索引
	 * @return 返回当前选择项索引
	 */
	int GetCurSel() const { return m_iCurSel; }

	/**
	 * @brief 获取所有子项数量
	 * @return 返回所有子项数量
	 */
	virtual int GetItemCount() const override;
    
	/**
	 * @brief 监听子项被选择事件
	 * @param[in] callback 子项被选择后触发的回调函数
	 * @return 无
	 */
	void AttachSelect(const EventCallback& callback) { AttachEvent(kEventSelect, callback);}	//mod by djj

	/**
	 * @brief 监听下拉窗关闭事件
	 * @param[in] callback 下拉窗关闭后触发的回调函数
	 * @return 无
	 */
	void AttachWindowClose(const EventCallback& callback) { AttachEvent(kEventWindowClose, callback); }

private:
	/**
	 * @brief 默认的子项被选择处理函数
	 * @param[in] args 参数列表
	 * @return 始终返回 true
	 */
	bool OnSelectItem(const EventArgs& args);

	/**
	 * @brief 选择一个子项
	 * @param[in] iIndex 要选择的子项索引
	 * @return 返回 true 表示成功，否则为 false
	 */
	bool SelectItemInternal(int iIndex);

protected:
	CComboWnd *m_pWindow;
	std::unique_ptr<ListBox> m_pLayout;
    int m_iCurSel;  
	UiSize m_szDropBox;
	std::wstring m_sDropBoxAttributes;
	bool m_bPopupTop;
	UiRect	m_rcTextPadding;	//add by djj
};

} // namespace ui

#endif // UI_CONTROL_COMBO_H_
