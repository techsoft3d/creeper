#pragma once
namespace ts3d {
    class TreeWidget;
    class TreeDockWidget : public QDockWidget {
        Q_OBJECT;
    public:
        TreeDockWidget( QWidget *parent );
        virtual ~TreeDockWidget( void );
    
    public slots:
        void onActiveMdiSubWindowChanged( QMdiSubWindow *subWindow );

    private:
        QHash<QMdiSubWindow*, QPointer<TreeWidget>> _treeWidgets;
        QPointer<QMdiSubWindow> _lastActiveSubWindow;
    };
}