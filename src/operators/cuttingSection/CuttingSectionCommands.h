#pragma once

namespace ts3d {
    class CuttingSectionCommands {
    public:
        CuttingSectionCommands( void );
        virtual ~CuttingSectionCommands( void );

        bool setCanvas( const HPS::Canvas canvas );

        void addCuttingPlane( const HPS::Vector planeVector );
        void invertCuttingPlane( const HPS::Vector planeVector );
        void eraseCuttingPlane( const HPS::Vector planeVector );
        void setUnsetSectioning( const bool set);
        void showHidePlane( const bool show );
        void cancelCuttingSection( void );
        HPS::PlaneArray getCuttingPlanes( bool &setSectioning, bool &showPlanes );

    private:
        HPS::Canvas _canvas;
        HPS::OperatorPtr _operatorPtr;
    };
}
