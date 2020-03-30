#pragma once

namespace ts3d {
    class CommandLineOptions {
    public:
        static CommandLineOptions &instance( void );

        enum class Status {
            Ok,
            Error,
            Version,
            Help
        };

        Status parse( void );
        QString getErrorText( void ) const;
        QString getHelpText( void ) const;
    private:
        CommandLineOptions( void );

        QCommandLineParser _parser;
        QCommandLineOption _version;
        QCommandLineOption _help;

#ifdef USING_EXCHANGE
        /*! \name Exchange Toolkit Options
         * @{
         */
    public:
        bool isExchangePathSet( void ) const;
        QString getExchangePath( void ) const;
    private:
        QCommandLineOption _exchangePath;
        /*! @} */
#endif

    };
}
