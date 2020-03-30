#pragma once
#include <HPSWidget.h>
namespace ts3d {
    class TreeWidget : public QTreeView {
        Q_OBJECT;
    public:
        TreeWidget( QWidget *parent, HPSWidget *hpsWidget );
        virtual ~TreeWidget( void );

        void setCADModel( HPS::CADModel cadModel );
    protected slots:
        virtual void selectionChanged( QItemSelection const &selected, QItemSelection const &deselected ) override;
    
    private:
        HPS::CADModel _cadModel;
        QPointer<HPSWidget> _hpsWidget;
    };
}
