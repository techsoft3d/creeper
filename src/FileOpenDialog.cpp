#include <FileOpenDialog.h>

namespace {
    auto const kShowImportOptionsDialogSettingsKey = "FileOpen/ShowImportOptionsDialog";
    auto const kGeometrySettingsKey = "FileOpen/geometry";
    auto const kStateSettingsKey = "FileOpen/state";
    QString getFilter() {
        QStringList filters = {
            "HPS 3D (*.hsf *.obj *.stl *.pts *.ptx *.xyz)",
            "HPS 2D (*.ps *.psf)",
#ifdef USING_EXCHANGE
            "3D Studio Files (*.3ds)",
            "3DXML Files (*.3dxml)",
            "ACIS SAT Files (*.sat *.sab)",
            "CADDS Files (*_pd)",
            "CATIA V4 Files (*.model *.dlv *.exp *.session)",
            "CATIA V5 Files (*.CATPart *.CATProduct *.CATShape *.CATDrawing)",
            "CGR Files (*.cgr)",
            "Collada Files (*.dae)",
            "Creo/ProE Files (*.prt *.prt.* *.neu *.neu.* *.asm *.asm.* *.xas *.xpr)",
            "I-DEAS Files (*.arc *.unv *.mf1 *.prt *.pkg)",
            "IFC Files (*.ifc *.ifczip)",
            "IGES Files (*.igs *.iges)",
            "Inventor Files (*.ipt *.iam)",
            "JT Files (*.jt)",
            "KMZ Files (*.kmz)",
            "NX Unigraphics Files (*.prt)",
            "PDF Files (*.pdf)",
            "PRC Files (*.prc)",
            "Parasolid Files (*.x_t *.xmt *.x_b *.xmt_txt)",
            "Rhino Files (*.3dm)",
            "STEP Files (*.stp *.step *.stpz *.stp.z)",
            "SolidEdge Files (*.par *.asm *.pwd *.psm)",
            "SolidWorks Files (*.sldprt *.sldasm *.sldfpp *.asm)",
            "Universal 3D Files (*.u3d)",
            "VDA Files (*.vda)",
            "VRML Files (*.wrl *.vrml)",
            "XVL Files (*.xv3 *.xv0)",
            "All Files (*.*)"
#endif
        };

        return filters.join( ";;" );
    }
}

ts3d::FileOpenDialog::FileOpenDialog( QWidget *parent, QDir const &initialDir )
    : QFileDialog( parent ) {
    setWindowTitle( tr("File Open" ) );
    setFileMode( QFileDialog::FileMode::ExistingFiles );
    setOption( QFileDialog::DontUseNativeDialog );
    setNameFilter( getFilter() );
    selectNameFilter( "All Files (*.*)" );
    setDirectory( initialDir );
    setModal( true );

    auto cb = new QCheckBox( tr( "Show Import Options Dialog" ) );
    layout()->addWidget( cb );

    QSettings settings;
    _showImportOptions = settings.value( kShowImportOptionsDialogSettingsKey, false ).toBool();
    restoreGeometry( settings.value( kGeometrySettingsKey ).toByteArray() );
    restoreState( settings.value( kStateSettingsKey ).toByteArray() );

    cb->setChecked( _showImportOptions );
    connect( cb, &QCheckBox::stateChanged, [&](int state) {
        QSettings settings;
        _showImportOptions = (state == Qt::Checked);
        settings.setValue( kShowImportOptionsDialogSettingsKey, _showImportOptions );
    } );

}

ts3d::FileOpenDialog::~FileOpenDialog( void ) {

}

bool ts3d::FileOpenDialog::showImportOptions() const {
    return _showImportOptions;
}

void ts3d::FileOpenDialog::closeEvent( QCloseEvent *event ) {
    QSettings settings;
    settings.setValue( kGeometrySettingsKey, saveGeometry() );
    settings.setValue( kStateSettingsKey, saveState() );
    QFileDialog::closeEvent( event );
}
