#pragma once

namespace ts3d {
    /*! \class HPSWidget
    \ingroup toplevel_objects
    \brief This is a simplest-possible implementation of a Qt widget containing an \c HPS::Canvas.

    This object has no dependency on the rest of the project and should remain that way. This
    is important so it can be easily extracted and used in arbitrary Qt projects.
    */
    class HPSWidget : public QWidget {
        Q_OBJECT
    public:
        /*! \brief Constructs an HPS widget. For correct functionality, it is important
        that the lineage of ownership through \c parent is correct.
        */
        HPSWidget( QWidget *parent );
        ~HPSWidget( void );

        /*! \brief Obtains a handle to the \c HPS::Canvas object associated with this widget.
        */
        HPS::Canvas getCanvas( void );

        /*! \brief Convenience function to obtain a handle to the canvas's front view.
        */
        HPS::View getView( void );

    private:
        void setupSceneDefaults();
        //void AttachView( HPS::View const & in_view );

    protected:
        /*! \brief Overridden to update the HPS display. */
        virtual void paintEvent( QPaintEvent * e ) override;

        /*! \brief Overridden to update the HPS display. */
        virtual void resizeEvent( QResizeEvent * e ) override;

        /*! \name Input overrides
        \brief These methods are overriden to forward input to the HPS system.
        @{ */
        virtual void mousePressEvent( QMouseEvent * event ) override;
        virtual void mouseDoubleClickEvent( QMouseEvent * event ) override;
        virtual void mouseReleaseEvent( QMouseEvent * event ) override;
        virtual void mouseMoveEvent( QMouseEvent * event ) override;
        virtual void wheelEvent( QWheelEvent * event ) override;

        virtual void keyPressEvent( QKeyEvent * e ) override;
        virtual void keyReleaseEvent( QKeyEvent * e ) override;
        /*! @} */

        virtual void focusOutEvent( QFocusEvent * ) override;

        /*! \brief This method is overridden to eliminate the paint engine. */
        virtual QPaintEngine* paintEngine() const override { return nullptr; }

    private:
        HPS::Canvas _canvas;
        HPS::View _view;

        /*! \brief Used to compose an \c HPS::MouseEvent from the Qt event info */
        HPS::MouseEvent buildMouseEvent( QMouseEvent * in_event, HPS::MouseEvent::Action action, size_t click_count );

        /*! \brief Used to compose an \c HPS::KeyboardEvent from the Qt event info */
        HPS::KeyboardEvent buildKeyboardEvent( QKeyEvent * in_event, HPS::KeyboardEvent::Action action );
        
    };
}