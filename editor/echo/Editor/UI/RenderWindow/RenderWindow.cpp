#include <QtGui>
#include "RenderWindow.h"
#include "EchoEngine.h"
#include "MainWindow.h"
#include "InputController2d.h"
#include "InputController3d.h"
#include <QDateTime>

namespace Studio
{
	RenderWindow::RenderWindow(QWidget* parent/* = NULL*/)
		: QWidget(parent)
	{
		setAttribute(Qt::WA_NativeWindow);
		setUpdatesEnabled(false);
		setMouseTracking(true);
		setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
	}

	RenderWindow::~RenderWindow()
	{
		delete m_timer; m_timer = NULL;

		delete m_inputController2d;
		delete m_inputController3d;
	}

	// size hint
	QSize RenderWindow::sizeHint() const
	{
		float width = MainWindow::instance()->width() * 0.3f;
		float height = MainWindow::instance()->height() * 0.65f;
		return QSize( width, height);
	}

	void RenderWindow::BeginRender()
	{
		EchoEngine::instance()->Initialize((size_t)this->winId());

		if (!m_inputController2d)
			m_inputController2d = new InputController2d;

		if (!m_inputController3d)
			m_inputController3d = new InputController3d;

		m_inputController = m_inputController2d;

		m_timer = new QTimer(this);
		QObject::connect(m_timer, SIGNAL(timeout()), this, SLOT(Render()));
		m_timer->start(10);
	}

	void  RenderWindow::Render()
	{
		ResizeWindow();

        static Echo::Dword lastTime = QDateTime::currentMSecsSinceEpoch();

		// calc delta Time
        Echo::Dword curTime = QDateTime::currentMSecsSinceEpoch();
        Echo::Dword elapsedTime = curTime - lastTime;

		QPointF pos = m_inputController->mousePosition();
		Qt::MouseButton button = m_inputController->pressedMouseButton();
		float elapsed = elapsedTime * 0.001f;
		InputContext ctx(pos, button, elapsed);

		m_inputController->tick(ctx);

		// Call the main render function
		EchoEngine::instance()->Render(elapsed, this->isVisible());

		lastTime = curTime;
	}

	void RenderWindow::ResizeWindow()
	{		
		int width = static_cast<int>(this->width());
		int height = static_cast<int>(this->height());

		if (m_dx9Size.width() != width || m_dx9Size.height() != height)
		{
			EchoEngine::instance()->Resize(width, height);
			m_dx9Size.setWidth(width);
			m_dx9Size.setHeight(height);
		}
	}

	void RenderWindow::SetAspectRatio(const QSize& size)
	{
		m_ratio = size;
	}

	void  RenderWindow::ResetDevice()
	{
	}

	void RenderWindow::wheelEvent(QWheelEvent * e)
	{
		m_inputController->wheelEvent(e);
	}

	void RenderWindow::mouseMoveEvent(QMouseEvent* e)
	{
		if ( m_isLeftButtonDown)
		{
			static QPointF lastPos = e->localPos();

			lastPos = e->localPos();
		}

		m_inputController->mouseMoveEvent(e);
	}

	void RenderWindow::mousePressEvent(QMouseEvent* e)
	{
		if (!hasFocus())
		{
			setFocus();
		}

		if ( e->button()==Qt::LeftButton)
		{
			m_isLeftButtonDown = true;
		}

		m_inputController->mousePressEvent(e);
	}

	void RenderWindow::mouseDoubleClickEvent(QMouseEvent* e)
	{
		m_inputController->mouseDoubleClickEvent(e);
	}

	void RenderWindow::mouseReleaseEvent(QMouseEvent* e)
	{
		if (e->button() == Qt::LeftButton)
		{
			m_isLeftButtonDown = false;
		}

		m_inputController->mouseReleaseEvent(e);
	}

	void RenderWindow::keyPressEvent(QKeyEvent* e)
	{
		m_inputController->keyPressEvent(e);
	}

	void RenderWindow::keyReleaseEvent(QKeyEvent* e)
	{
		m_inputController->keyReleaseEvent(e);
	}
}
