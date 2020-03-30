#include <Application.h>
#include <tree/ExchangeCadModelTreeItem.h>
#include <tree/AbstractTreeItemModel.h>
#include <tree/TreeWidget.h>

ts3d::TreeWidget::TreeWidget( QWidget *parent, HPSWidget *hpsWidget )
    : QTreeView( parent ),
    _hpsWidget( hpsWidget ) {
    setSelectionMode( SelectionMode::ExtendedSelection );
}

// virtual
ts3d::TreeWidget::~TreeWidget( void ) {

}

void ts3d::TreeWidget::setCADModel( HPS::CADModel cadModel ) {
    if(cadModel == _cadModel) {
        return;
    }
    
    if(!cadModel.Empty()) {
        AbstractTreeItem *root_item = nullptr;
        switch(cadModel.Type()) {
        case HPS::Type::ExchangeCADModel:
            root_item = new ExchangeCadModelTreeItem( nullptr, cadModel );
            break;
        default:
            root_item = new ComponentTreeItem( nullptr, cadModel );
            break;
        }
        if(root_item) {
            auto model = new AbstractTreeItemModel( this, root_item );
            setModel( model );
        }
    } else {
        setModel( nullptr );
    }
    _cadModel = cadModel;
}

void ts3d::TreeWidget::selectionChanged( QItemSelection const &selected, QItemSelection const &deselected ) {
   
    HPS::HighlightOptionsKit hok;
    hok.SetStyleName( Application::instance()->getHighlightStyleName() );
    
    auto windowKey = _hpsWidget->getCanvas().GetWindowKey();
    auto highlight_changed = false;
    for(auto model_index : deselected.indexes()) {
        if(auto componentItem = dynamic_cast<ComponentTreeItem*>(static_cast<AbstractTreeItem*>(model_index.internalPointer()))) {
            auto component = componentItem->getComponent();
            for(auto key : component.GetKeys()) {
                windowKey.GetHighlightControl().Unhighlight( key, hok );
                highlight_changed = true;
            }
        }
    }

    for(auto model_index : selected.indexes()) {
        if(auto componentItem = dynamic_cast<ComponentTreeItem*>(static_cast<AbstractTreeItem*>(model_index.internalPointer()))) {
            auto component = componentItem->getComponent();
            for(auto key : component.GetKeys()) {
                windowKey.GetHighlightControl().Highlight( key, hok );
                highlight_changed = true;
            }
        }
    }
    
    if(highlight_changed) {
        _hpsWidget->getCanvas().Update();
    }
}
