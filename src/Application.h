#pragma once

namespace ts3d {
    /*!
    \class Application
    \ingroup toplevel_objects
    \brief This object is the highest level owning object in the entire application.

    This object is a singleton whose instance is accessible via the ts3d::Application::instance() method.
    Upon creation, the application initializes the HOOPS toolkits and the ts3d::MainWindow child widget.
    */

    class Application : public QApplication {
        Q_OBJECT;
    public:
        /*! \brief Access to the global instance of this object.
        */
        static Application *instance( void );
        
        /*! \brief Initializer for the global instance of this object.

        This function is called only once by \c main. For practical
        purposes, this should be consider private.
        */
        static bool initializeInstance( int &argc, char *argv[] );

        /*! \brief Used to destroy the global instance of this object.

        This function is called once by \c main. For practical
        purposes, this should be consider private.
        */
        static void destroyInstance( void );

        /*! \brief Getter for the shared global style segment that
        is used for the highlight state.
        */
        HPS::SegmentKey getHighlightStyleSegment( void ) const;

        /*! \brief Getter for the shared global portfolio key.
        */
        HPS::PortfolioKey getPortfolioKey( void ) const;

        /*! \brief Getter for the name of the style used for
        highlighting. The highlight style segment is used in 
        the portfolio with this name.
        */
        HPS::UTF8 getHighlightStyleName( void ) const;

    private:
        /*! \brief Constructor

        The constructor, among other things, initializes and configures
        licensing of the HOOPS toolkits.
        */
        Application( int &argc, char *argv[] );

        /*! \brief Destructor
        */
        virtual ~Application( void );

        /*! \brief The static singleton instance variable.
        */
        static Application *_instance;

        /*! \brief The one and only instance of the HPS::World.
        */
        HPS::World _world;

        /*! \brief The highlight segment key.
        */
        HPS::SegmentKey _highlightSegmentKey;

        /*! \brief The portfolio key.
        */
        HPS::PortfolioKey _portfolioKey;
    };
}