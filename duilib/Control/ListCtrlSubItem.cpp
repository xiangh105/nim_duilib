#include "ListCtrlSubItem.h"
#include "duilib/Control/ListCtrl.h"

namespace ui
{
ListCtrlSubItem::ListCtrlSubItem():
    m_pItem(nullptr),
    m_imageId(-1)
{
    m_nIconSpacing = GlobalManager::Instance().Dpi().GetScaleInt(2);
}

std::wstring ListCtrlSubItem::GetType() const { return L"ListCtrlSubItem"; }

void ListCtrlSubItem::SetAttribute(const std::wstring& strName, const std::wstring& strValue)
{
    if (strName == L"icon_spacing") {
        SetIconSpacing(_wtoi(strValue.c_str()), true);
    }
    else {
        __super::SetAttribute(strName, strValue);
    }
}

void ListCtrlSubItem::SetListCtrlItem(ListCtrlItem* pItem)
{
    m_pItem = pItem;
}

ListCtrlItem* ListCtrlSubItem::GetListCtrlItem() const
{
    ASSERT(m_pItem != nullptr);
    return m_pItem;
}

bool ListCtrlSubItem::SetCheckBoxVisible(bool bVisible)
{
    bool bRet = false;
    if (bVisible) {
        ListCtrlItem* pItem = GetListCtrlItem();
        if (pItem == nullptr) {
            return false;
        }
        ListCtrlCheckBox* pCheckBox = nullptr;
        if (GetItemCount() > 0) {
            pCheckBox = dynamic_cast<ListCtrlCheckBox*>(GetItemAt(0));
        }
        if (pCheckBox == nullptr) {
            pCheckBox = new ListCtrlCheckBox;
            AddItem(pCheckBox);
            ListCtrl* pListCtrl = pItem->GetListCtrl();            
            std::wstring checkBoxClass;
            if (pListCtrl != nullptr) {
                checkBoxClass = pListCtrl->GetCheckBoxClass();
            }
            ASSERT(!checkBoxClass.empty());
            pCheckBox->SetClass(checkBoxClass);
        }
        //�����ڱ߾࣬�����������ص�
        UiPadding textPadding = GetTextPadding();
        int32_t nCheckBoxWidth = pCheckBox->GetCheckBoxWidth();
        if ((nCheckBoxWidth > 0) && (textPadding.left < nCheckBoxWidth)) {
            textPadding.left = nCheckBoxWidth;
            SetTextPadding(textPadding, false);
        }
        pCheckBox->SetVisible(true);
    }
    else if (GetItemCount() > 0) {
        ListCtrlCheckBox* pCheckBox = dynamic_cast<ListCtrlCheckBox*>(GetItemAt(0));
        if (pCheckBox != nullptr) {
            UiPadding textPadding = GetTextPadding();
            int32_t nCheckBoxWidth = pCheckBox->GetCheckBoxWidth();
            if ((nCheckBoxWidth > 0) && (textPadding.left >= nCheckBoxWidth)) {
                textPadding.left -= nCheckBoxWidth;
                SetTextPadding(textPadding, false);
            }
            RemoveItemAt(0);
            bRet = true;
        }
    }
    return bRet;
}

bool ListCtrlSubItem::IsCheckBoxVisible() const
{
    if (GetItemCount() > 0) {
        CheckBox* pCheckBox = dynamic_cast<CheckBox*>(GetItemAt(0));
        if (pCheckBox != nullptr) {
            return pCheckBox->IsVisible();
        }
    }
    return false;
}

bool ListCtrlSubItem::SetCheckBoxSelect(bool bSelected, bool bPartSelect)
{
    if (GetItemCount() > 0) {
        CheckBox* pCheckBox = dynamic_cast<CheckBox*>(GetItemAt(0));
        if (pCheckBox != nullptr) {
            bool bChanged = pCheckBox->IsSelected() != bSelected;
            pCheckBox->SetSelected(bSelected);
            if (bSelected) {
                if (pCheckBox->IsPartSelected() != bPartSelect) {
                    pCheckBox->SetPartSelected(bPartSelect);
                    bChanged = true;
                }
            }
            if (bChanged) {
                pCheckBox->Invalidate();
            }
            return true;
        }
    }
    return false;
}

bool ListCtrlSubItem::GetCheckBoxSelect(bool& bSelected, bool& bPartSelect) const
{
    bSelected = false;
    bPartSelect = false;
    if (GetItemCount() > 0) {
        CheckBox* pCheckBox = dynamic_cast<CheckBox*>(GetItemAt(0));
        if (pCheckBox != nullptr) {
            bSelected = pCheckBox->IsSelected();
            if (bSelected) {
                bPartSelect = pCheckBox->IsPartSelected();
            }
            return true;
        }
    }
    return false;
}

ListCtrlCheckBox* ListCtrlSubItem::GetCheckBox() const
{
    ListCtrlCheckBox* pCheckBox = nullptr;
    if (GetItemCount() > 0) {
        pCheckBox = dynamic_cast<ListCtrlCheckBox*>(GetItemAt(0));
    }
    return pCheckBox;
}

void ListCtrlSubItem::SetImageId(int32_t imageId)
{
    if (m_imageId != imageId) {
        m_imageId = imageId;
        Invalidate();
    }
}

int32_t ListCtrlSubItem::GetImageId() const
{
    return m_imageId;
}

void ListCtrlSubItem::SetIconSpacing(int32_t nIconSpacing, bool bNeedDpiScale)
{
    if (bNeedDpiScale) {
        GlobalManager::Instance().Dpi().ScaleInt(nIconSpacing);
    }
    if (m_nIconSpacing != nIconSpacing) {
        m_nIconSpacing = nIconSpacing;
        if (m_nIconSpacing < 0) {
            m_nIconSpacing = 0;
        }
        Invalidate();
    }
}

int32_t ListCtrlSubItem::GetIconSpacing() const
{
    return m_nIconSpacing;
}

void ListCtrlSubItem::PaintText(IRender* pRender)
{
    //��Ҫ���Ƶ����ݰ�����ͼ�ꡢ����
    if (pRender == nullptr) {
        return;
    }
    //�ı�ǰ��ͼ��
    ImagePtr pItemImage;
    if ((m_imageId >= 0) && (m_pItem != nullptr)) {
        ListCtrl* pListCtrl = m_pItem->GetListCtrl();
        if (pListCtrl != nullptr) {
            pItemImage = pListCtrl->GetImageList().GetImageData(m_imageId);
            ASSERT(pItemImage != nullptr);
        }
    }
    if ((pItemImage != nullptr) && (pItemImage->GetImageCache() == nullptr)) {
        LoadImageData(*pItemImage);
        if (pItemImage->GetImageCache() == nullptr) {
            pItemImage = nullptr;
        }
        else {
            if ((pItemImage->GetImageCache()->GetWidth() <= 0) ||
                (pItemImage->GetImageCache()->GetHeight() <= 0)) {
                pItemImage = nullptr;
            }
        }
    }

    if (pItemImage == nullptr) {
        __super::PaintText(pRender);
        return;
    }

    int32_t nIconTextSpacing = GetIconSpacing();
    //ͼ�꿿��࣬���ְ�ԭ���ķ�ʽ����
    UiRect rc = GetRect();
    rc.Deflate(GetControlPadding());
    if (pItemImage != nullptr) {
        PaintImage(pRender, pItemImage.get(), L"", -1, nullptr, &rc, nullptr);
        rc.left += pItemImage->GetImageCache()->GetWidth();
        rc.left += nIconTextSpacing;
    }

    UiRect textRect = GetRect();
    textRect.Deflate(GetControlPadding());
    textRect.Deflate(GetTextPadding());
    if (pItemImage != nullptr) {
        textRect.left = std::max(textRect.left, rc.left);
    }
    DoPaintText(textRect, pRender);
}

}//namespace ui
