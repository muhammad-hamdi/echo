#include "Studio.h"
#include "QCheckBox.cx"
#include "QComboBox.cx"
#include "QCursor.cx"
#include "QEvent.cx"
#include "QGraphicsItem.cx"
#include "QGraphicsScene.cx"
#include "QGraphicsView.cx"
#include "QHeaderView.cx"
#include "QLineEdit.cx"
#include "QMenu.cx"
#include "QSplitter.cx"
#include "QToolButton.cx"
#include "QTreeWidget.cx"
#include "QTreeWidgetItem.cx"
#include "QUiLoader.cx"
#include "QWidget.cx"

#define BIND_EDITOR_FUN(Fun) this->Fun = Echo::Fun

namespace Studio
{
    // init functions
    void AStudio::initFunctions()
    {
        BIND_EDITOR_FUN(qCheckBoxNew);
        
        // QComboBox->addItem(const QIcon &icon, const QString &text)
        BIND_EDITOR_FUN(qComboBoxAddItem);
        BIND_EDITOR_FUN(qComboBoxCurrentIndex);
        BIND_EDITOR_FUN(qComboBoxCurrentText);
        BIND_EDITOR_FUN(qComboBoxSetCurrentIndex);
        BIND_EDITOR_FUN(qComboBoxSetCurrentText);
        BIND_EDITOR_FUN(qComboBoxSetItemText);
        BIND_EDITOR_FUN(qComboBoxClear);
        
        // QCursor
        BIND_EDITOR_FUN(qCursorPos);
        
        // QEvent
        BIND_EDITOR_FUN(qObjectGetEventAll);
        BIND_EDITOR_FUN(qGraphicsItemGetEventAll);

		// get sender item
		BIND_EDITOR_FUN(qSenderItem);
		BIND_EDITOR_FUN(qGraphicsItemSceneRect);
		BIND_EDITOR_FUN(qGraphicsItemWidth);
		BIND_EDITOR_FUN(qGraphicsItemPos);
		BIND_EDITOR_FUN(qGraphicsItemSetPos);
		BIND_EDITOR_FUN(qGraphicsProxyWidgetSetPos);
		BIND_EDITOR_FUN(qGraphicsProxyWidgetSetZValue);
		BIND_EDITOR_FUN(qGraphicsItemSetZValue);
		BIND_EDITOR_FUN(qGraphicsItemSetVisible);
		BIND_EDITOR_FUN(qGraphicsItemUserData);
		BIND_EDITOR_FUN(qGraphicsItemSetUserData);
		BIND_EDITOR_FUN(qGraphicsItemSetToolTip);
		BIND_EDITOR_FUN(qGraphicsItemSetMoveable);
		BIND_EDITOR_FUN(qGraphicsSceneNew);
		BIND_EDITOR_FUN(qGraphicsSceneAddWidget);
		BIND_EDITOR_FUN(qGraphicsSceneAddLine);
		BIND_EDITOR_FUN(qGraphicsSceneAddRect);
		BIND_EDITOR_FUN(qGraphicsSceneAddPath);
		BIND_EDITOR_FUN(qGraphicsSceneAddSimpleText);
		BIND_EDITOR_FUN(qGraphicsSceneAddEclipse);
		BIND_EDITOR_FUN(qGraphicsSceneDeleteWidget);
		BIND_EDITOR_FUN(qGraphicsSceneDeleteItem);

		// disable viewport update
		BIND_EDITOR_FUN(qGraphicsViewDisableViewportAutoUpdate);
		BIND_EDITOR_FUN(qGraphicsViewSceneRect);
		BIND_EDITOR_FUN(qGraphicsViewSetScene);
		BIND_EDITOR_FUN(qGraphicsViewSetScale);

		// resize section
		BIND_EDITOR_FUN(qHeaderViewResizeSection);
		BIND_EDITOR_FUN(qHeaderViewSetSectionResizeMode);

		// new QLineEdit
		BIND_EDITOR_FUN(qLineEditNew);
		BIND_EDITOR_FUN(qLineEditSetText);
		BIND_EDITOR_FUN(qLineEditSetMaximumWidth);
		BIND_EDITOR_FUN(qLineEditSetCursorPosition);
		BIND_EDITOR_FUN(qLineEditText);
		BIND_EDITOR_FUN(qLineEditWidth);
		BIND_EDITOR_FUN(qLineEditHeight);

		// create a new QMenu
		BIND_EDITOR_FUN(qMenuNew);
		BIND_EDITOR_FUN(qMenuAddAction);
		BIND_EDITOR_FUN(qMenuExec);

		// modify qsplitter stretch factor
		BIND_EDITOR_FUN(qSplitterSetStretchFactor);

		// set tool button fixed width
		BIND_EDITOR_FUN(qToolButtonSetFixedWidth);
		BIND_EDITOR_FUN(qToolButtonSetIcon);
		BIND_EDITOR_FUN(qToolButtonSetIconSize);
		BIND_EDITOR_FUN(qToolButtonIsChecked);

		// load ui file by path. then return the widget
		BIND_EDITOR_FUN(qLoadUi);

		// invisible root item
		BIND_EDITOR_FUN(qTreeWidgetInvisibleRootItem);
		BIND_EDITOR_FUN(qTreeWidgetCurrentItem);
		BIND_EDITOR_FUN(qTreeWidgetHeader);
		BIND_EDITOR_FUN(qTreeWidgetCurrentColumn);
		BIND_EDITOR_FUN(qTreeWidgetWidth);
		BIND_EDITOR_FUN(qTreeWidgetClear);

		// create a new QTreeWidgetItem
		BIND_EDITOR_FUN(qTreeWidgetItemNew);
		BIND_EDITOR_FUN(qTreeWidgetItemParent);
		BIND_EDITOR_FUN(qTreeWidgetItemAddChild);
		BIND_EDITOR_FUN(qTreeWidgetItemSetText);
		BIND_EDITOR_FUN(qTreeWidgetItemText);
		BIND_EDITOR_FUN(qTreeWidgetItemSetIcon);
		BIND_EDITOR_FUN(qTreeWidgetItemUserData);
		BIND_EDITOR_FUN(qTreeWidgetItemSetUserData);
		BIND_EDITOR_FUN(qTreeWidgetItemSetExpanded);

		// connect signal slot
		BIND_EDITOR_FUN(qConnectObject);
		BIND_EDITOR_FUN(qConnectWidget);
		BIND_EDITOR_FUN(qConnectAction);
		BIND_EDITOR_FUN(qConnectGraphicsItem);
		BIND_EDITOR_FUN(qFindChild);
		BIND_EDITOR_FUN(qFindChildAction);
		BIND_EDITOR_FUN(qWidgetSetVisible);
		BIND_EDITOR_FUN(qWidgetSetEnable);
		BIND_EDITOR_FUN(qDeleteWidget);
    }
}
