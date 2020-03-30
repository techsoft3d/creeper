#include "CommandLineOptions.h"

// static
ts3d::CommandLineOptions &ts3d::CommandLineOptions::instance( void ) {
    static CommandLineOptions _instance;
    return _instance;
}

ts3d::CommandLineOptions::Status ts3d::CommandLineOptions::parse( void ) {
    if( ! _parser.parse( QCoreApplication::arguments() ) ) {
        return Status::Error;
    }

    if( _parser.isSet( _version ) ) {
        return Status::Version;
    }

    if( _parser.isSet( _help ) ) {
        return Status::Help;
    }

    return Status::Ok;
}

QString ts3d::CommandLineOptions::getErrorText( void ) const {
    return _parser.errorText();
}

QString ts3d::CommandLineOptions::getHelpText( void ) const {
    return _parser.helpText();
}


bool ts3d::CommandLineOptions::isExchangePathSet( void ) const {
    return _parser.isSet(_exchangePath);
}

QString ts3d::CommandLineOptions::getExchangePath( void ) const {
    return _parser.value(_exchangePath);
}

ts3d::CommandLineOptions::CommandLineOptions( void )
    : _version( _parser.addVersionOption() ),
      _help( _parser.addHelpOption() ),
      _exchangePath( {"x", "exchange_path"}, QObject::tr("CommandLineOptions", "Specifies the root folder of the Exchange installation." ), "exchange" ) {

    _parser.setApplicationDescription( QObject::tr("CommandLineOptions", "This project is a sample implementation of a cross platform HOOPS Viewer." ) );
    _parser.addOption( _exchangePath );
}
