#include "HPSWidget.h"

#if _MSC_VER
#define snprintf _snprintf
#endif

#if defined _MSC_VER && defined USING_PUBLISH
#include "sprk_publish.h"
#endif

ts3d::HPSWidget::HPSWidget(QWidget *parent )
: QWidget(parent) {
    setAttribute(Qt::WA_PaintOnScreen);
    setAttribute(Qt::WA_NoBackground);
    setAttribute(Qt::WA_NoSystemBackground);
    setBackgroundRole(QPalette::NoRole);
    
    setFocusPolicy(Qt::StrongFocus);
    
    HPS::ApplicationWindowOptionsKit windowOpts;
    windowOpts.SetAntiAliasCapable(true);
    
    _canvas = HPS::Factory::CreateCanvas(static_cast<HPS::WindowHandle>(winId()), "HPS Qt Sandbox", windowOpts);
    Q_ASSERT(sizeof(HPS::WindowHandle) >= sizeof(WId));
    
    _view = HPS::Factory::CreateView();
    _canvas.AttachViewAsLayout(_view);
    
    setupSceneDefaults();
}

ts3d::HPSWidget::~HPSWidget() {
    _canvas.Delete();
}

HPS::Canvas ts3d::HPSWidget::getCanvas( void ) {
    return _canvas;
}

HPS::View ts3d::HPSWidget::getView( void ) {
    return _view;
}

void ts3d::HPSWidget::setupSceneDefaults() {
    _view.GetOperatorControl()
    .Push(new HPS::MouseWheelOperator(), HPS::Operator::Priority::Low)
    .Push(new HPS::ZoomOperator(HPS::MouseButtons::ButtonMiddle()))
    .Push(new HPS::PanOperator(HPS::MouseButtons::ButtonRight()))
    .Push(new HPS::OrbitOperator(HPS::MouseButtons::ButtonLeft()));
    
    //HPS::Database::GetEventDispatcher().Subscribe(errorHandler, HPS::Object::ClassID<HPS::ErrorEvent>());
    //HPS::Database::GetEventDispatcher().Subscribe(warningHandler, HPS::Object::ClassID<HPS::WarningEvent>());
}

void ts3d::HPSWidget::paintEvent(QPaintEvent *)
{
    _canvas.GetWindowKey().Update( HPS::Window::UpdateType::Refresh );
}

void ts3d::HPSWidget::resizeEvent(QResizeEvent *)
{
    _canvas.GetWindowKey().Update(HPS::Window::UpdateType::Refresh);
}

void ts3d::HPSWidget::mousePressEvent(QMouseEvent * event)
{
    _canvas.GetWindowKey().GetEventDispatcher().InjectEvent(buildMouseEvent(event, HPS::MouseEvent::Action::ButtonDown, 1));
}

void ts3d::HPSWidget::mouseDoubleClickEvent(QMouseEvent * event)
{
    _canvas.GetWindowKey().GetEventDispatcher().InjectEvent(buildMouseEvent(event, HPS::MouseEvent::Action::ButtonDown, 2));
}

void ts3d::HPSWidget::mouseReleaseEvent(QMouseEvent * event)
{
    _canvas.GetWindowKey().GetEventDispatcher().InjectEvent(buildMouseEvent(event, HPS::MouseEvent::Action::ButtonUp, 0));
}

void ts3d::HPSWidget::mouseMoveEvent(QMouseEvent * event)
{
    _canvas.GetWindowKey().GetEventDispatcher().InjectEvent(buildMouseEvent(event, HPS::MouseEvent::Action::Move, 0));
}

void ts3d::HPSWidget::keyPressEvent(QKeyEvent * event)
{
    _canvas.GetWindowKey().GetEventDispatcher().InjectEvent(buildKeyboardEvent(event, HPS::KeyboardEvent::Action::KeyDown));
}

void ts3d::HPSWidget::keyReleaseEvent(QKeyEvent * event)
{
    _canvas.GetWindowKey().GetEventDispatcher().InjectEvent(buildKeyboardEvent(event, HPS::KeyboardEvent::Action::KeyUp));
}

namespace {
    void getModifierKeys(HPS::InputEvent * event)
    {
        Qt::KeyboardModifiers modifiers = QApplication::keyboardModifiers();
        if (modifiers.testFlag(Qt::KeyboardModifier::ShiftModifier))
            event->ModifierKeyState.Shift(true);
        if (modifiers.testFlag(Qt::KeyboardModifier::ControlModifier))
            event->ModifierKeyState.Control(true);
    }
}

void ts3d::HPSWidget::wheelEvent(QWheelEvent * event)
{
    HPS::Point pos(event->x(), event->y(), 0);
    _canvas.GetWindowKey().ConvertCoordinate(HPS::Coordinate::Space::Pixel, pos, HPS::Coordinate::Space::Window, pos);
    
    HPS::MouseEvent out_event;
    out_event.CurrentAction = HPS::MouseEvent::Action::Scroll;
    out_event.Location = pos;
    
    //NOTE: the delta() function is obsolete as of QT5.
    //Try to replace it with pixelDelta or angleDelta
    out_event.WheelDelta = event->delta();
    
    getModifierKeys(&out_event);
    
    _canvas.GetWindowKey().GetEventDispatcher().InjectEvent(out_event);
}


HPS::MouseEvent ts3d::HPSWidget::buildMouseEvent(QMouseEvent * in_event, HPS::MouseEvent::Action action, size_t click_count)
{
    auto scaleFactor = this->devicePixelRatio();
    
    HPS::MouseEvent out_event;
    
    out_event.CurrentAction = action;
    out_event.ClickCount = click_count;
    
    if (in_event->button() == Qt::MouseButton::LeftButton)
        out_event.CurrentButton = HPS::MouseButtons::ButtonLeft();
    else if (in_event->button() == Qt::MouseButton::RightButton)
        out_event.CurrentButton = HPS::MouseButtons::ButtonRight();
    else if (in_event->button() == Qt::MouseButton::MiddleButton)
        out_event.CurrentButton = HPS::MouseButtons::ButtonMiddle();
    
    HPS::Point pos(in_event->x() * scaleFactor, in_event->y() * scaleFactor, 0);
    _canvas.GetWindowKey().ConvertCoordinate(HPS::Coordinate::Space::Pixel, pos, HPS::Coordinate::Space::Window, pos);
    out_event.Location = pos;
    
    getModifierKeys(&out_event);
    
    return out_event;
}

HPS::KeyboardEvent ts3d::HPSWidget::buildKeyboardEvent(QKeyEvent *in_event, HPS::KeyboardEvent::Action action)
{
    HPS::KeyboardEvent out_event;
    out_event.CurrentAction = action;
    
    HPS::KeyboardCodeArray code;
    code.push_back((HPS::KeyboardCode)in_event->key());
    out_event.KeyboardCodes = code;
    
    getModifierKeys(&out_event);
    
    return out_event;
    
}


void ts3d::HPSWidget::focusOutEvent(QFocusEvent *)
{
    _canvas.GetWindowKey().GetEventDispatcher().InjectEvent(HPS::FocusLostEvent());
}
