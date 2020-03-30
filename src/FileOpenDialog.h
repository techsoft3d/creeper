#pragma once

namespace ts3d {
    class FileOpenDialog : public QFileDialog {
        Q_OBJECT;
    public:
        FileOpenDialog( QWidget *parent, QDir const &initialDir );
        virtual ~FileOpenDialog( void );

        bool showImportOptions( void )  const;

    protected:
        void closeEvent( QCloseEvent *event );

    private:
        bool _showImportOptions;
    };
}