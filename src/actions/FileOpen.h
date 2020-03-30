#pragma once

#include <FileOpenDialog.h>

namespace ts3d {
    class FileOpen : public QAction {
        Q_OBJECT;
    public:
        FileOpen( QObject *owner );
        virtual ~FileOpen( void );

    private:
        QPointer<FileOpenDialog> _fileOpenDialog;
    };
}
