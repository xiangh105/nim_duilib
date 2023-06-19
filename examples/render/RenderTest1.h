#pragma once

// duilib
#include "duilib/duilib.h"

namespace ui {

class RenderTest1 : public ui::Control
{
public:
	RenderTest1();
	virtual ~RenderTest1();

public:
	/**
	* @brief ������
	* @param[in] ������
	* @return ������
	*/
	virtual void AlphaPaint(IRender* pRender, const UiRect& rcPaint);

	/**
	* @brief ���ƿؼ�����ں���
	* @param[in] pRender ָ����������
	* @param[in] rcPaint ָ����������
	* @return ��
	*/
	virtual void Paint(IRender* pRender, const UiRect& rcPaint);

	/**
	* @brief ���ƿؼ�������ں���
	* @param[in] pRender ָ����������
	* @param[in] rcPaint ָ����������
	* @return ��
	*/
	virtual void PaintChild(IRender* pRender, const UiRect& rcPaint);

};

} //end of namespace ui