#ifndef UI_CORE_INATIVE_WINDOW_H_
#define UI_CORE_INATIVE_WINDOW_H_

#include "duilib/Core/Keyboard.h"
#include "duilib/Core/Callback.h"
#include "duilib/Core/UiTypes.h"
#include "duilib/Core/WindowMessage.h"
#include "duilib/Core/DpiManager.h"

namespace ui
{
/** 窗口消息过滤接口，用于截获窗口过程的消息，优先于Window类进行消息处理
*/
class IUIMessageFilter
{
public:
    /**  消息处理函数，处理优先级高于Window类的消息处理函数
    * @param [in] uMsg 消息内容
    * @param [in] wParam 消息附加参数
    * @param [in] lParam 消息附加参数
    * @param[out] bHandled 返回 false 则继续派发该消息，返回 true 表示不再派发该消息
    * @return 返回消息处理结果
    */
    virtual LRESULT FilterMessage(UINT uMsg, WPARAM wParam, LPARAM lParam, bool& bHandled) = 0;
};

class INativeWindow: public virtual SupportWeakCallback
{
public:
    /** 获取该窗口对应的DPI管理器
    */
    virtual const DpiManager& OnNativeGetDpi() const = 0;

    /** 获取窗口阴影的大小
    * @param [out] rcShadow 获取圆角的大小
    */
    virtual void OnNativeGetShadowCorner(UiPadding& rcShadow) const = 0;

    /** 获取窗口四边可拉伸范围的大小
    */
    virtual UiRect OnNativeGetSizeBox() const = 0;

    /** 获取窗口标题栏区域（可拖动区域），对应 XML 中 caption 属性
    */
    virtual const UiRect& OnNativeGetCaptionRect() const = 0;

    /** 判断一个点是否在放置在标题栏上的控件上
    */
    virtual bool OnNativeIsPtInCaptionBarControl(const UiPoint& pt) const = 0;

    /** 获取窗口最小范围，对应 XML 中 mininfo 属性
    * @param [in] bContainShadow 是否包含阴影范围，默认为 false
    */
    virtual UiSize OnNativeGetMinInfo(bool bContainShadow /*= false*/) const = 0;

    /** 获取窗口最大范围，对应 XML 中 maxinfo 属性
    * @param [in] bContainShadow 是否包含阴影范围，默认为 false
    */
    virtual UiSize OnNativeGetMaxInfo(bool bContainShadow /*= false*/) const = 0;

    /** 进入最大化状态
    */
    virtual void OnNativeWindowMaximized() = 0;

    /** 从最大化还原
    */
    virtual void OnNativeWindowRestored() = 0;

    /** 进入最小化状态
    */
    virtual void OnNativeWindowMinimized() = 0;

    /** 进入全屏状态
    */
    virtual void OnNativeWindowEnterFullScreen() = 0;

    /** 退出全屏状态
    */
    virtual void OnNativeWindowExitFullScreen() = 0;

    /** 当窗口即将被关闭时调用此函数，供子类中做一些收尾工作
    */
    virtual void OnNativePreCloseWindow() = 0;

    /** 当窗口已经关闭时调用此函数，供子类中做一些收尾工作
    */
    virtual void OnNativePostCloseWindow() = 0;

    /** 切换系统标题栏与自绘标题栏
    */
    virtual void OnNativeUseSystemCaptionBarChanged() = 0;

public:
    /** @name 窗口消息处理相关
     * @{
     */
     /** 在窗口销毁时会被调用，这是该窗口的最后一个消息（该类默认实现是清理资源，并调用OnDeleteSelf函数销毁该窗口对象）
     */
    virtual void OnNativeFinalMessage() = 0;

    /** 窗口消息的派发函数
    */
    virtual LRESULT OnNativeWindowMessage(UINT uMsg, WPARAM wParam, LPARAM lParam, bool& bHandled) = 0;

    /** 窗口消息的派发函数(用户自定义消息)
    */
    virtual LRESULT OnNativeUserMessage(UINT uMsg, WPARAM wParam, LPARAM lParam, bool& bHandled) = 0;

    /** 处理DPI变化的系统通知消息
    * @param [in] nNewDPI 新的DPI值
    * @param [in] rcNewWindow 新的窗口位置（建议值）
    */
    virtual void OnNativeProcessDpiChangedMsg(uint32_t nNewDPI, const UiRect& rcNewWindow) = 0;

    /** 窗口大小发生改变(WM_SIZE)
    * @param [in] sizeType 触发窗口大小改变的类型
    * @param [in] newWindowSize 新的窗口大小（宽度和高度）
    * @param [out] bHandled 消息是否已经处理，返回 true 表明已经成功处理消息，不需要再传递给窗口过程；返回 false 表示将消息继续传递给窗口过程处理
    * @return 返回消息的处理结果，如果应用程序处理此消息，应返回零
    */
    virtual LRESULT OnNativeSizeMsg(WindowSizeType sizeType, const UiSize& newWindowSize, bool& bHandled) = 0;

    /** 窗口移动(WM_MOVE)
    * @param [in] ptTopLeft 窗口客户端区域左上角的 x 坐标和 y 坐标（坐标为屏幕坐标）
    * @param [out] bHandled 消息是否已经处理，返回 true 表明已经成功处理消息，不需要再传递给窗口过程；返回 false 表示将消息继续传递给窗口过程处理
    * @return 返回消息的处理结果，如果应用程序处理此消息，应返回零
    */
    virtual LRESULT OnNativeMoveMsg(const UiPoint& ptTopLeft, bool& bHandled) = 0;

    /** 窗口绘制(WM_PAINT)
    * @param [out] bHandled 消息是否已经处理，返回 true 表明已经成功处理消息，不需要再传递给窗口过程；返回 false 表示将消息继续传递给窗口过程处理
    * @return 返回消息的处理结果，如果应用程序处理此消息，应返回零
    */    
    virtual LRESULT OnNativePaintMsg(bool& bHandled) = 0;

    /** 窗口获得焦点(WM_SETFOCUS)
    * @param [out] bHandled 消息是否已经处理，返回 true 表明已经成功处理消息，不需要再传递给窗口过程；返回 false 表示将消息继续传递给窗口过程处理
    * @return 返回消息的处理结果，如果应用程序处理此消息，应返回零
    */
    virtual LRESULT OnNativeSetFocusMsg(bool& bHandled) = 0;

    /** 窗口失去焦点(WM_KILLFOCUS)
    * @param [out] bHandled 消息是否已经处理，返回 true 表明已经成功处理消息，不需要再传递给窗口过程；返回 false 表示将消息继续传递给窗口过程处理
    * @return 返回消息的处理结果，如果应用程序处理此消息，应返回零
    */
    virtual LRESULT OnNativeKillFocusMsg(bool& bHandled) = 0;

    /** 输入法开始生成组合字符串(WM_IME_STARTCOMPOSITION)
    * @param [out] bHandled 消息是否已经处理，返回 true 表明已经成功处理消息，不需要再传递给窗口过程；返回 false 表示将消息继续传递给窗口过程处理
    * @return 返回消息的处理结果，如果应用程序处理此消息，应返回零
    */
    virtual LRESULT OnNativeImeStartCompositionMsg(bool& bHandled) = 0;

    /** 输入法结束组合(WM_IME_ENDCOMPOSITION)
    * @param [out] bHandled 消息是否已经处理，返回 true 表明已经成功处理消息，不需要再传递给窗口过程；返回 false 表示将消息继续传递给窗口过程处理
    * @return 返回消息的处理结果，如果应用程序处理此消息，应返回零
    */
    virtual LRESULT OnNativeImeEndCompositionMsg(bool& bHandled) = 0;

    /** 设置光标(WM_SETCURSOR)
    * @param [out] bHandled 消息是否已经处理，返回 true 表明已经成功处理消息，不需要再传递给窗口过程；返回 false 表示将消息继续传递给窗口过程处理
    * @return 如果应用程序处理了此消息，它应返回 TRUE 以停止进一步处理或 FALSE 以继续
    */
    virtual LRESULT OnNativeSetCursorMsg(bool& bHandled) = 0;

    /** 通知窗口用户希望显示上下文菜单(WM_CONTEXTMENU)，用户可能单击了鼠标右键 (在窗口中右键单击) ，按下了 Shift+F10 或按下了应用程序键， (上下文菜单键) 某些键盘上可用。
    * @param [in] pt 鼠标所在位置，客户区坐标, 如果是(-1,-1)表示用户键入了 SHIFT+F10
    * @param [out] bHandled 消息是否已经处理，返回 true 表明已经成功处理消息，不需要再传递给窗口过程；返回 false 表示将消息继续传递给窗口过程处理
    * @return 返回消息的处理结果，如果应用程序处理此消息，应返回零
    */
    virtual LRESULT OnNativeContextMenuMsg(const UiPoint& pt, bool& bHandled) = 0;

    /** 键盘按下(WM_KEYDOWN 或者 WM_SYSKEYDOWN)
    * @param [in] vkCode 虚拟键盘代码
    * @param [in] modifierKey 按键标志位，参见 Keyboard.h中的enum ModifierKey定义
    * @param [out] bHandled 消息是否已经处理，返回 true 表明已经成功处理消息，不需要再传递给窗口过程；返回 false 表示将消息继续传递给窗口过程处理
    * @return 返回消息的处理结果，如果应用程序处理此消息，应返回零
    */
    virtual LRESULT OnNativeKeyDownMsg(VirtualKeyCode vkCode, uint32_t modifierKey, bool& bHandled) = 0;

    /** 键盘按下(WM_KEYUP 或者 WM_SYSKEYUP)
    * @param [in] vkCode 虚拟键盘代码
    * @param [in] modifierKey 按键标志位，参见 Keyboard.h中的enum ModifierKey定义
    * @param [out] bHandled 消息是否已经处理，返回 true 表明已经成功处理消息，不需要再传递给窗口过程；返回 false 表示将消息继续传递给窗口过程处理
    * @return 返回消息的处理结果，如果应用程序处理此消息，应返回零
    */
    virtual LRESULT OnNativeKeyUpMsg(VirtualKeyCode vkCode, uint32_t modifierKey, bool& bHandled) = 0;

    /** 键盘按下(WM_CHAR)
    * @param [in] vkCode 虚拟键盘代码
    * @param [in] modifierKey 按键标志位，参见 Keyboard.h中的enum ModifierKey定义
    * @param [out] bHandled 消息是否已经处理，返回 true 表明已经成功处理消息，不需要再传递给窗口过程；返回 false 表示将消息继续传递给窗口过程处理
    * @return 返回消息的处理结果，如果应用程序处理此消息，应返回零
    */
    virtual LRESULT OnNativeCharMsg(VirtualKeyCode vkCode, uint32_t modifierKey, bool& bHandled) = 0;

    /** 快捷键消息（WM_HOTKEY）
    * @param [in] hotkeyId 热键的ID
    * @param [in] vkCode 虚拟键盘代码
    * @param [in] modifierKey 按键标志位，参见 Keyboard.h中的enum ModifierKey定义
    * @param [out] bHandled 消息是否已经处理，返回 true 表明已经成功处理消息，不需要再传递给窗口过程；返回 false 表示将消息继续传递给窗口过程处理
    * @return 返回消息的处理结果，如果应用程序处理此消息，应返回零
    */
    virtual LRESULT OnNativeHotKeyMsg(int32_t hotkeyId, VirtualKeyCode vkCode, uint32_t modifierKey, bool& bHandled) = 0;

    /** 旋转鼠标滚轮(WM_MOUSEWHEEL)
    * @param [in] wheelDelta 滚轮旋转的距离，以 WHEEL_DELTA (120) 的倍数或除法表示。 正值表示滚轮向前旋转（远离用户）；负值表示滚轮向后旋转（朝向用户）
    * @param [in] pt 鼠标所在位置，客户区坐标
    * @param [in] modifierKey 按键标志位，参见 Keyboard.h中的enum ModifierKey定义
    * @param [out] bHandled 消息是否已经处理，返回 true 表明已经成功处理消息，不需要再传递给窗口过程；返回 false 表示将消息继续传递给窗口过程处理
    * @return 返回消息的处理结果，如果应用程序处理此消息，应返回零
    */
    virtual LRESULT OnNativeMouseWheelMsg(int32_t wheelDelta, const UiPoint& pt, uint32_t modifierKey, bool& bHandled) = 0;

    /** 鼠标移动消息（WM_MOUSEMOVE）
    * @param [in] pt 鼠标所在位置，客户区坐标
    * @param [in] modifierKey 按键标志位，参见 Keyboard.h中的enum ModifierKey定义
    * @param [out] bHandled 消息是否已经处理，返回 true 表明已经成功处理消息，不需要再传递给窗口过程；返回 false 表示将消息继续传递给窗口过程处理
    * @return 返回消息的处理结果，如果应用程序处理此消息，应返回零
    */
    virtual LRESULT OnNativeMouseMoveMsg(const UiPoint& pt, uint32_t modifierKey, bool& bHandled) = 0;

    /** 鼠标悬停消息（WM_MOUSEHOVER）
    * @param [in] pt 鼠标所在位置，客户区坐标
    * @param [in] modifierKey 按键标志位，参见 Keyboard.h中的enum ModifierKey定义
    * @param [out] bHandled 消息是否已经处理，返回 true 表明已经成功处理消息，不需要再传递给窗口过程；返回 false 表示将消息继续传递给窗口过程处理
    * @return 返回消息的处理结果，如果应用程序处理此消息，应返回零
    */
    virtual LRESULT OnNativeMouseHoverMsg(const UiPoint& pt, uint32_t modifierKey, bool& bHandled) = 0;

    /** 鼠标离开消息（WM_MOUSELEAVE）
    * @param [out] bHandled 消息是否已经处理，返回 true 表明已经成功处理消息，不需要再传递给窗口过程；返回 false 表示将消息继续传递给窗口过程处理
    * @return 返回消息的处理结果，如果应用程序处理此消息，应返回零
    */
    virtual LRESULT OnNativeMouseLeaveMsg(bool& bHandled) = 0;

    /** 鼠标左键按下消息（WM_LBUTTONDOWN）
    * @param [in] pt 鼠标所在位置，客户区坐标
    * @param [in] modifierKey 按键标志位，参见 Keyboard.h中的enum ModifierKey定义
    * @param [out] bHandled 消息是否已经处理，返回 true 表明已经成功处理消息，不需要再传递给窗口过程；返回 false 表示将消息继续传递给窗口过程处理
    * @return 返回消息的处理结果，如果应用程序处理此消息，应返回零
    */
    virtual LRESULT OnNativeMouseLButtonDownMsg(const UiPoint& pt, uint32_t modifierKey, bool& bHandled) = 0;

    /** 鼠标左键弹起消息（WM_LBUTTONUP）
    * @param [in] pt 鼠标所在位置，客户区坐标
    * @param [in] modifierKey 按键标志位，参见 Keyboard.h中的enum ModifierKey定义
    * @param [out] bHandled 消息是否已经处理，返回 true 表明已经成功处理消息，不需要再传递给窗口过程；返回 false 表示将消息继续传递给窗口过程处理
    * @return 返回消息的处理结果，如果应用程序处理此消息，应返回零
    */
    virtual LRESULT OnNativeMouseLButtonUpMsg(const UiPoint& pt, uint32_t modifierKey, bool& bHandled) = 0;

    /** 鼠标左键双击消息（WM_LBUTTONDBLCLK）
    * @param [in] pt 鼠标所在位置，客户区坐标
    * @param [in] modifierKey 按键标志位，参见 Keyboard.h中的enum ModifierKey定义
    * @param [out] bHandled 消息是否已经处理，返回 true 表明已经成功处理消息，不需要再传递给窗口过程；返回 false 表示将消息继续传递给窗口过程处理
    * @return 返回消息的处理结果，如果应用程序处理此消息，应返回零
    */
    virtual LRESULT OnNativeMouseLButtonDbClickMsg(const UiPoint& pt, uint32_t modifierKey, bool& bHandled) = 0;

    /** 鼠标右键按下消息（WM_RBUTTONDOWN）
    * @param [in] pt 鼠标所在位置，客户区坐标
    * @param [in] modifierKey 按键标志位，参见 Keyboard.h中的enum ModifierKey定义
    * @param [out] bHandled 消息是否已经处理，返回 true 表明已经成功处理消息，不需要再传递给窗口过程；返回 false 表示将消息继续传递给窗口过程处理
    * @return 返回消息的处理结果，如果应用程序处理此消息，应返回零
    */
    virtual LRESULT OnNativeMouseRButtonDownMsg(const UiPoint& pt, uint32_t modifierKey, bool& bHandled) = 0;

    /** 鼠标右键弹起消息（WM_RBUTTONUP）
    * @param [in] pt 鼠标所在位置，客户区坐标
    * @param [in] modifierKey 按键标志位，参见 Keyboard.h中的enum ModifierKey定义
    * @param [out] bHandled 消息是否已经处理，返回 true 表明已经成功处理消息，不需要再传递给窗口过程；返回 false 表示将消息继续传递给窗口过程处理
    * @return 返回消息的处理结果，如果应用程序处理此消息，应返回零
    */
    virtual LRESULT OnNativeMouseRButtonUpMsg(const UiPoint& pt, uint32_t modifierKey, bool& bHandled) = 0;

    /** 鼠标右键双击消息（WM_RBUTTONDBLCLK）
    * @param [in] pt 鼠标所在位置，客户区坐标
    * @param [in] modifierKey 按键标志位，参见 Keyboard.h中的enum ModifierKey定义
    * @param [out] bHandled 消息是否已经处理，返回 true 表明已经成功处理消息，不需要再传递给窗口过程；返回 false 表示将消息继续传递给窗口过程处理
    * @return 返回消息的处理结果，如果应用程序处理此消息，应返回零
    */
    virtual LRESULT OnNativeMouseRButtonDbClickMsg(const UiPoint& pt, uint32_t modifierKey, bool& bHandled) = 0;

    /** 窗口丢失鼠标捕获（WM_CAPTURECHANGED）
    * @param [out] bHandled 消息是否已经处理，返回 true 表明已经成功处理消息，不需要再传递给窗口过程；返回 false 表示将消息继续传递给窗口过程处理
    * @return 返回消息的处理结果，如果应用程序处理此消息，应返回零
    */
    virtual LRESULT OnNativeCaptureChangedMsg(bool& bHandled) = 0;

    /** 窗口关闭消息（WM_CLOSE）
    * @param [in] wParam 消息的wParam参数
    * @param [out] bHandled 消息是否已经处理，返回 true 表明已经成功处理消息，不需要再传递给窗口过程；返回 false 表示将消息继续传递给窗口过程处理
    * @return 返回消息的处理结果，如果应用程序处理此消息，应返回零
    */
    virtual LRESULT OnNativeWindowCloseMsg(uint32_t wParam, bool& bHandled) = 0;

    /** @}*/

};

} // namespace ui

#endif // UI_CORE_INATIVE_WINDOW_H_
