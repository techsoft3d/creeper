#pragma once
#include <operators/cuttingSection/CuttingSectionSlots.h>

namespace ts3d {
    class CuttingSectionDockWidget : public QDockWidget {
        Q_OBJECT;
    public:
        CuttingSectionDockWidget( QWidget *parent );
        virtual ~CuttingSectionDockWidget( void );

    public slots:
        void onActiveMdiSubWindowChanged( void );
        void onPlaneX( bool on );
        void onPlaneY( bool on );
        void onPlaneZ( bool on );
        void onSetUnsetSectioning( bool set );
        void onShowHidePlanes( bool show );
        void onCancel();

    private:
        const QString _addPlaneLabel = tr( "Add %1 plane", "Label of Add X/Y/Z plane button" );
        const QString _erasePlaneLabel = tr( "Erase %1 plane", "Label of Erase X/Y/Z plane button" );
        const QString _invertLabel = tr( "Invert", "Label of Invert cutting plane checkbox" );
        const QString _hidePlanesLabel = tr( "Hide cutting plane(s)", "Label of Hide cutting plane(s) button" );
        const QString _setSectioningLabel = tr( "Set sectioning", "Label of Set sectioning button" );
        const QString _unsetSectioningLabel = tr( "Unset sectioning", "Label of Unset sectioning button" );
        const QString _showPlaneLabel = tr( "Show cutting plane(s)", "Label of Show cutting plane(s) button" );
        const QString _cancelLabel = tr( "Cancel Cutting Section", "Label of Cancel Cutting Section button" );

        CuttingSectionSlots *_cuttingSectionSlots;

        QPushButton *_planeButtonX;
        QPushButton *_planeButtonY;
        QPushButton *_planeButtonZ;

        QCheckBox * _invertButtonX;
        QCheckBox * _invertButtonY;
        QCheckBox * _invertButtonZ;

        QPushButton *_setUnsetSectioningButton;
        QPushButton *_showHidePlaneButton;
        QPushButton *_cancelButton;

        void updateWidgets( void );
    };
}
