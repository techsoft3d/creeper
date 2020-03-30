#include <FileOpener.h>

    
// static 
ts3d::FileOpener *ts3d::FileOpener::instance( void ) {
    static FileOpener *_instance = nullptr;
    if(nullptr == _instance) {
        _instance = new FileOpener();
    }
    return _instance;
}

void ts3d::FileOpener::openFile( QString const &filename ) {
    _cancelled = false;
    emit begin( filename );

    QFileInfo file_info( filename );
    if(!file_info.exists() || file_info.isDir()) {
        emit failure( QObject::tr( "The selected file doesn't exist.", "File open error" ) );
        emit complete();
        return;
    }

    auto model = HPS::Factory::CreateModel( qPrintable( filename ) );
    HPS::CADModel cadModel;
    auto success = false;
    auto is_hps_filetype = false;
    auto const extension = file_info.suffix();
    try {
        if(extension == "hsf") {
            is_hps_filetype = true;
            auto iok = HPS::Stream::ImportOptionsKit();
            iok.SetSegment( model.GetSegmentKey() );
            iok.SetAlternateRoot( model.GetLibraryKey() );
            iok.SetPortfolio( model.GetPortfolioKey() );
            success = handleNotifier( HPS::Stream::File::Import( qPrintable( filename ), iok ) );
        } else if(extension == "obj") {
            is_hps_filetype = true;
            auto iok = HPS::OBJ::ImportOptionsKit();
            iok.SetSegment( model.GetSegmentKey() );
            iok.SetPortfolio( model.GetPortfolioKey() );
            success = handleNotifier( HPS::OBJ::File::Import( qPrintable( filename ), iok ) );
        } else if(extension == "stl") {
            is_hps_filetype = true;
            auto iok = HPS::STL::ImportOptionsKit::GetDefault();
            iok.SetSegment( model.GetSegmentKey() );
            success = handleNotifier( HPS::STL::File::Import( qPrintable( filename ), iok ) );
        } else if(extension == "pts" || extension == "ptx" || extension == "xyz") {
            is_hps_filetype = true;
            auto iok = HPS::PointCloud::ImportOptionsKit();
            iok.SetSegment( model.GetSegmentKey() );
            success = handleNotifier( HPS::PointCloud::File::Import( qPrintable( filename ), iok ) );
        } 
        if(is_hps_filetype) {
            if(success) {
                emit modelOpened( model, filename );
            }
        } else {
            model.Delete();
#ifdef USING_EXCHANGE
            // default to exchange reader
            auto iok = HPS::Exchange::ImportOptionsKit::GetDefault();
            iok.SetBRepMode( HPS::Exchange::BRepMode::BRepAndTessellation );
            auto notifer = HPS::Exchange::File::Import( qPrintable( filename ), iok );
            if((success = handleNotifier( notifer ))) {
                emit cadModelOpened( notifer.GetCADModel(), filename );
            }
#else
            emit failure( QObject::tr( "Unable to open the selected file format." ) );
#endif
        }
    } catch(HPS::IOException e) {
        emit failure( e.what() );
    }
    emit complete();
}

void ts3d::FileOpener::cancel( void ) {
    _cancelled = true;
}

ts3d::FileOpener::FileOpener( void )
    :QObject( qApp ) {
}

// virtual 
ts3d::FileOpener::~FileOpener( void ) {
}

bool ts3d::FileOpener::handleNotifier( HPS::IONotifier notifier ) {
    auto success = false;
    auto percent_complete = 0.f;
    auto status = notifier.Status( percent_complete );
    emit progressChanged( percent_complete );
    while(HPS::IOResult::InProgress == status && !_cancelled) {
        // progress dialog
        status = notifier.Status( percent_complete );
        emit progressChanged( percent_complete );
        qApp->processEvents( QEventLoop::AllEvents, 500 );
    }

    if(_cancelled) {
        notifier.Cancel();
        notifier.Wait();
        return false;
    }

    if(status == HPS::IOResult::Failure) {
        emit failure( tr( "Unable to open the selected file format." ) );
    } else if(status == HPS::IOResult::FileNotFound) {
        emit failure( tr( "The selected file doesn't exist." ) );
    } else if ( HPS::IOResult::UnsupportedFormat == status ){
        emit failure(tr( "Unsupported file format." ));
    }
    else {
        success = true;
    }

    notifier.Wait();
    return success;
}
