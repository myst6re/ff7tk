//    SPDX-FileCopyrightText: 2012 - 2022 Chris Rizzitello <sithlord48@gmail.com>
//    SPDX-License-Identifier: LGPL-3.0-or-later

#include <ItemList.h>

#include <QHeaderView>
#include <QScrollBar>

#include <FF7Item>
#include <ItemPreview>
#include <ItemSelector>

bool ItemList::eventFilter(QObject *obj, QEvent *ev)
{
    Q_UNUSED(obj) //our object will be the itemlist always in this eventFilter.
    int row = -1;
    auto item = itemAt(mapFromGlobal(viewport()->cursor().pos()));

    if(item)
        row = item->row();

    if (ev->type() == QEvent::ToolTip) { // ToolTip Event. Create a Tooltip
        if (createdTooltip) { // If we have a tooltip open we need to close it first.
            destroyTooltip();
        }

        //Invalid Row were done here.
        if(row == -1)
            return true;
        //The Cursor is off the viewport and on a scrollbar (or beyond)
        if (mapFromGlobal(cursor().pos()).x() > viewport()->width()
         || mapFromGlobal(cursor().pos()).y() > viewport()->height()) {
            return true;
        }

        //If the row contains a non Empty Item then show a tooltip
        if (FF7Item::itemId(itemlist.at(row)) != FF7Item::EmptyItem) {
            //make an ItemPreview, but give it A ToolTip Flags so it looks/acts as one
            itemPreview = new ItemPreview(Qt::ToolTip);
            itemPreview->setItem(FF7Item::itemId(itemlist.at(row)));
            itemPreview->setGeometry(QRect(cursor().pos(), itemPreview->contentsRect().size()));
            itemPreview->show();
            createdTooltip = true;
        }
    return true;
    } else if (ev->type() == QEvent::HoverLeave) { //HoverLeave Event. Clean up our tooltips.
        if (!createdTooltip)
            return true;

        if (row == -1) {
            destroyTooltip();
            return true;
        }

        if(FF7Item::itemId(itemlist.at(row)) != itemPreview->id()) {
            // If we have a tooltip  And the item is not the current one, we need to close it.
            // Check for current row because when a new tooltip is created
            // a hoverLeave Event is triggered for the tableItem when the tooltip is placed under the cursor.
            destroyTooltip();
        }
        return true;
    } else { // All other Events.
        return false;  //We have not handled this event, pass it along
    }
}

void ItemList::destroyTooltip()
{
    itemPreview->close();
    createdTooltip = false;
}

void ItemList::destroySelector()
{
    disconnect(itemSelector);
    itemSelector->deleteLater();
    itemSelector = nullptr;
}
void ItemList::changeEvent(QEvent *e)
{
    if (e->type() == QEvent::LanguageChange)
        itemupdate();
    QTableWidget::changeEvent(e);
}

ItemList::ItemList(QWidget *parent)
    : QTableWidget(parent)
    , itemSelector (new ItemSelector(this))
    , itemQtyLimit(127)
    , createdTooltip(false)

{
    setObjectName("ItemList");
    installEventFilter(this);
    createdTooltip = false;
    itemQtyLimit = 127;
    setRowCount(320);
    setIconSize(QSize(fontMetrics().height(), fontMetrics().height()));
    setColumnCount(3);
    setEditTriggers(QAbstractItemView::NoEditTriggers);// thats a long 0
    setContextMenuPolicy(Qt::NoContextMenu);
    setSelectionMode(QAbstractItemView::NoSelection);
    setColumnWidth(0, itemSelector->combo_type_width());
    setColumnWidth(1, itemSelector->combo_item_width());
    setColumnWidth(2, itemSelector->qty_width());
    setFixedWidth(itemSelector->width() + verticalScrollBar()->sizeHint().width() + 7);
    itemSelector->deleteLater();
    itemSelector = nullptr;
    connect(this, &QTableWidget::currentCellChanged, this, &ItemList::listSelectionChanged);
    horizontalHeader()->close();
    verticalHeader()->close();
    verticalScrollBar()->setToolTip(QString());//negate custom tooltip
    for (int i = 0; i < 320; i++)
        itemlist.append(FF7Item::EmptyItemData);   //initlize the data.
    itemupdate();// redraw Display After data init.
}

void ItemList::setMaximumItemQty(int maxQty)
{
    itemQtyLimit = maxQty;
    //check that any items Qty is not greater then the new Qty. if so fix it.
    for (int i = 0; i < 320; i++) {
        //qty not above limit and item is not empty.
        if ((FF7Item::itemQty(itemlist.at(i)) > itemQtyLimit) && (itemlist.at(i) != FF7Item::EmptyItemData))
            itemlist.replace(i, FF7Item::itemEncode(FF7Item::itemId(itemlist.at(i)), quint8(itemQtyLimit)));
    }
    itemupdate();
}

void ItemList::setItems(const QList<quint16> &items)
{
    itemlist = items;

    if (itemSelector) {
        destroySelector();
    }

    if (createdTooltip) {
        destroyTooltip();
    }

    itemupdate();
    setCurrentCell(-1, -1);
}

void ItemList::itemSelector_changed(quint16 item)
{
    if (createdTooltip) {
        destroyTooltip();
    }

    itemlist.replace(sender()->objectName().toInt(), item);
    if (item == FF7Item::EmptyItemData) {
        QTableWidgetItem *newItem = new QTableWidgetItem(QString(), 0);
        setItem(sender()->objectName().toInt(), 0, newItem);
        newItem = new QTableWidgetItem(tr("-------EMPTY--------"), 0);
        setItem(sender()->objectName().toInt(), 1, newItem);
        setRowHeight(sender()->objectName().toInt(), fontMetrics().height() + 9);
        newItem = new QTableWidgetItem(QString(), 0);
        setItem(sender()->objectName().toInt(), 2, newItem);
    }
    Q_EMIT itemsChanged(itemlist);
}

void ItemList::itemupdate()
{
    clearContents();
    for (int i = 0; i < 320; i++)
        updateItem(i);
}

void ItemList::listSelectionChanged(int row, int colum, int prevRow, int prevColum)
{
    Q_UNUSED(prevColum)

    if (itemSelector)
        destroySelector();

    if (createdTooltip)
        destroyTooltip();

    if (colum < 0 || row < 0)
        return;   //Ingore if selecting -1 (clearContents)

    if (prevRow >= 0) {
        removeCellWidget(prevRow, 0);
        updateItem(prevRow);   //update the previews Row so its filled again.
    }

    if (!itemSelector) {
        itemSelector = new ItemSelector(this);
        itemSelector->setEditableItemCombo(editableItemCombo);
        itemSelector->setFixedWidth(width() - verticalScrollBar()->sizeHint().width() - 7);
        connect(itemSelector, &ItemSelector::itemChanged, this, &ItemList::itemSelector_changed);
    }
    itemSelector->setMaximumQty(itemQtyLimit);
    itemSelector->setObjectName(QString::number(row));
    itemSelector->setCurrentItem(itemlist.at(row));
    setItem(row, 0, new QTableWidgetItem(QString(), 0));
    setItem(row, 1, new QTableWidgetItem(QString(), 0));
    setItem(row, 2, new QTableWidgetItem(QString(), 0));
    setCellWidget(row, 0, itemSelector);
}

void ItemList::updateItem(int row)
{
    QTableWidgetItem *newItem;
    if (itemlist.at(row) == FF7Item::EmptyItemData) {
        newItem = new QTableWidgetItem(QString(), 0);
        setItem(row, 0, newItem);
        newItem = new QTableWidgetItem(tr("-------EMPTY--------"), 0);
        setItem(row, 1, newItem);
        newItem = new QTableWidgetItem(QString(), 0);
        setItem(row, 2, newItem);
    } else if (FF7Item::itemId(itemlist.at(row)) > 319) {
        newItem = new QTableWidgetItem(QString(), 0);
        setItem(row, 0, newItem);
        newItem = new QTableWidgetItem(tr("-------BAD ID-------"), 0);
        setItem(row, 1, newItem);
        newItem = new QTableWidgetItem(QString(), 0);
        setItem(row, 2, newItem);
    } else {
        QString qty;
        //Replaced by new item engine. (Vegeta_Ss4)
        newItem = new QTableWidgetItem(FF7Item::icon(FF7Item::itemId(itemlist.at(row))), QString(), 0);
        setItem(row, 0, newItem);
        newItem = new QTableWidgetItem(FF7Item::name(FF7Item::itemId(itemlist.at(row))), 0);
        setItem(row, 1, newItem);
        newItem = new QTableWidgetItem(qty.setNum(FF7Item::itemQty(itemlist.at(row))), 0);
        setItem(row, 2, newItem);
    }
    setRowHeight(row, fontMetrics().height() + 9);
}

void ItemList::setEditableItemCombo(bool editable)
{
    editableItemCombo = editable;
}
