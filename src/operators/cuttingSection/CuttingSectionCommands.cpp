#include <operators/cuttingSection/CuttingSectionCommands.h>

ts3d::CuttingSectionCommands::CuttingSectionCommands( void ) {
    _operatorPtr = nullptr;
}

ts3d::CuttingSectionCommands::~CuttingSectionCommands( void ) {

}

bool ts3d::CuttingSectionCommands::setCanvas( const HPS::Canvas canvas ) {
    _canvas = canvas;
    _operatorPtr = nullptr;

    // Get assigned Cutting Section operator
    HPS::OperatorPtrArray operators;
    _canvas.GetFrontView().GetOperatorControl().Show( HPS::Operator::Priority::High, operators );

    for ( unsigned int i = 0; i < operators.size(); i++ ) {
        HPS::UTF8 name = operators[i]->GetName();
        if ( "HPS_CuttingSectionOperator" == name ) {
            _operatorPtr = operators[i];
            return true;
        }
    }

    return false;
}

void ts3d::CuttingSectionCommands::addCuttingPlane( const HPS::Vector planeVector )
{
    std::shared_ptr<HPS::CuttingSectionOperator> cuttingSectionOprPtr;
    HPS::PlaneArray cuttingPlanes;

    if ( nullptr == _operatorPtr) {
        // Create new cutting section operator and activate
        _operatorPtr = HPS::OperatorPtr( new HPS::CuttingSectionOperator() );
        _canvas.GetFrontView().GetOperatorControl().Push( _operatorPtr, HPS::Operator::Priority::High );

        cuttingSectionOprPtr = std::dynamic_pointer_cast<HPS::CuttingSectionOperator>( _operatorPtr );
    } else {
        // Edit existing cutting section
        cuttingSectionOprPtr = std::dynamic_pointer_cast<HPS::CuttingSectionOperator>( _operatorPtr );
        cuttingPlanes = cuttingSectionOprPtr->GetPlanes();

        for ( unsigned int i = 0; i < cuttingPlanes.size(); i++ ) {
            HPS::Plane plane = cuttingPlanes[i];
            // If same vector's plane exists, exit
            if ( ( plane.a ==  planeVector.x && plane.b ==  planeVector.y && plane.c ==  planeVector.z ) ||
                 ( plane.a == -planeVector.x && plane.b == -planeVector.y && plane.c == -planeVector.z ) ) {
                return;
            }
        }
    }

    // Get bounding box of the model
    HPS::SprocketPath sprocket_path(
                _canvas,
                _canvas.GetAttachedLayout(),
                _canvas.GetFrontView(),
                _canvas.GetFrontView().GetAttachedModel());
    HPS::KeyPath key_path = sprocket_path.GetKeyPath();

    HPS::BoundingKit bounding;
    key_path.ShowNetBounding( bounding );

    HPS::SimpleSphere sphere;
    HPS::SimpleCuboid cube;
    bounding.ShowVolume( sphere, cube );

    HPS::Point center_point = sphere.center;

    // Add new cutting plane
    cuttingPlanes.push_back( HPS::Plane( planeVector, center_point ) );

    cuttingSectionOprPtr->SetPlanes( cuttingPlanes );

    _canvas.Update();
}

void ts3d::CuttingSectionCommands::invertCuttingPlane( const HPS::Vector planeVector ) {
    if ( nullptr == _operatorPtr)
        return;

    std::shared_ptr<HPS::CuttingSectionOperator> cuttingSectionOprPtr= std::dynamic_pointer_cast<HPS::CuttingSectionOperator>( _operatorPtr );
    HPS::PlaneArray cuttingPlanes = cuttingSectionOprPtr->GetPlanes();

    for ( unsigned int i = 0; i < cuttingPlanes.size(); i++ ) {
        HPS::Plane plane = cuttingPlanes[i];
        if ( plane.a == -planeVector.x && plane.b == -planeVector.y && plane.c == -planeVector.z ) {
            cuttingPlanes[i].a *= -1;
            cuttingPlanes[i].b *= -1;
            cuttingPlanes[i].c *= -1;
            cuttingPlanes[i].d *= -1;

            cuttingSectionOprPtr->SetPlanes( cuttingPlanes );

            _canvas.Update();
            return;
        }

    }
}

void ts3d::CuttingSectionCommands::eraseCuttingPlane( const HPS::Vector planeVector ) {
    if ( nullptr == _operatorPtr)
        return;

    std::shared_ptr<HPS::CuttingSectionOperator> cuttingSectionOprPtr = std::dynamic_pointer_cast<HPS::CuttingSectionOperator>( _operatorPtr );
    HPS::PlaneArray cuttingPlanes = cuttingSectionOprPtr->GetPlanes();

    for ( unsigned int i = 0; i < cuttingPlanes.size(); i++ ) {
        HPS::Plane plane = cuttingPlanes[i];
        // If same vector's plane exists, elase the plane
        if ( ( plane.a ==  planeVector.x && plane.b ==  planeVector.y && plane.c ==  planeVector.z ) ||
             ( plane.a == -planeVector.x && plane.b == -planeVector.y && plane.c == -planeVector.z ) ) {
            cuttingPlanes.erase( cuttingPlanes.begin() + i );
            cuttingSectionOprPtr->SetPlanes( cuttingPlanes );

            _canvas.Update();
        }
    }
}

void ts3d::CuttingSectionCommands::setUnsetSectioning( const bool set ) {
    if ( nullptr == _operatorPtr )
        return;

    std::shared_ptr<HPS::CuttingSectionOperator> cuttingSectionOprPtr = std::dynamic_pointer_cast<HPS::CuttingSectionOperator>( _operatorPtr );
    cuttingSectionOprPtr->SetSectioning(set);

    _canvas.Update();
}

void ts3d::CuttingSectionCommands::showHidePlane( const bool show ) {
    if ( nullptr == _operatorPtr )
        return;

    std::shared_ptr<HPS::CuttingSectionOperator> cuttingSectionOprPtr = std::dynamic_pointer_cast<HPS::CuttingSectionOperator>( _operatorPtr );
    cuttingSectionOprPtr->SetPlaneVisibility(show);

    _canvas.Update();
}

void ts3d::CuttingSectionCommands::cancelCuttingSection( void ) {
    if ( nullptr == _operatorPtr )
        return;

    _canvas.GetFrontView().GetOperatorControl().Pop( HPS::Operator::Priority::High, _operatorPtr );

    _operatorPtr = nullptr;
    _canvas.Update();
}

HPS::PlaneArray ts3d::CuttingSectionCommands::getCuttingPlanes( bool &setSectioning, bool &showPlanes ) {
    HPS::PlaneArray cuttingPlanes;
    showPlanes = true;

    if ( nullptr == _operatorPtr )
        return cuttingPlanes;

    std::shared_ptr<HPS::CuttingSectionOperator> cuttingSectionOprPtr = std::dynamic_pointer_cast<HPS::CuttingSectionOperator>( _operatorPtr );
    cuttingPlanes = cuttingSectionOprPtr->GetPlanes();

    setSectioning = cuttingSectionOprPtr->GetSectioning();


    return cuttingPlanes;
}
