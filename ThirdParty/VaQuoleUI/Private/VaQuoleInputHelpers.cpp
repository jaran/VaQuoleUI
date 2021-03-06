// Copyright 2014 Vladimir Alyamkin. All Rights Reserved.

#include "VaQuoleInputHelpers.h"

#include <QApplication>
#include <QMouseEvent>
#include <QPoint>
#include <QWidget>

namespace VaQuole
{

//////////////////////////////////////////////////////////////////////////
// Mouse input

QMouseEvent* createMouseEvent(	const QWidget* const pWidget,
								const QEvent::Type eventType,
								const QPoint& widgetPos,
								const Qt::MouseButton buttons,
								const Qt::KeyboardModifiers modifiers,
								Qt::MouseButton buttonCausingEvent)
{
	if (pWidget == NULL)
	{
		return NULL;
	}

	QMouseEvent* pEvent = new QMouseEvent(	eventType,
											widgetPos,
											pWidget->mapToGlobal(widgetPos),
											buttonCausingEvent,
											buttons,
											modifiers);

	return pEvent;
}

void simulateMouseClick(QWidget* const pWidget,
						const QPoint& widgetPos,
						const Qt::MouseButton button,
						const Qt::KeyboardModifiers modifiers,
						const bool bButtonPressed)
{
	if (pWidget == NULL || QApplication::instance() == NULL)
	{
		return;
	}

	QMouseEvent* pMouseEvent;

	if(bButtonPressed)
	{
		pMouseEvent = createMouseEvent(	pWidget, QEvent::MouseButtonPress,
										widgetPos, button,
										modifiers, button);
	}
	else
	{
		pMouseEvent = createMouseEvent(	pWidget, QEvent::MouseButtonRelease,
										widgetPos, Qt::NoButton,
										modifiers, button);
	}

	QApplication::instance()->sendEvent(pWidget, pMouseEvent);
	// QApplication::processEvents();
}

void simulateMouseMove(	QWidget* const pWidget, const QPoint& widgetPos)
{
	if (pWidget == NULL || QApplication::instance() == NULL)
	{
		return;
	}

	QMouseEvent* pMouseEvent = createMouseEvent(	pWidget, QEvent::MouseMove,
										widgetPos, Qt::NoButton,
										Qt::NoModifier, Qt::NoButton);

	QApplication::instance()->sendEvent(pWidget, pMouseEvent);
}


//////////////////////////////////////////////////////////////////////////
// Keyboard input

QKeyEvent* createKeyEvent(	const QEvent::Type eventType,
							int key,
							const Qt::KeyboardModifiers modifiers,
							QString & text,
							bool autorep,
							ushort count)
{
	QKeyEvent* pEvent = new QKeyEvent(	eventType,
										key,
										modifiers,
										text,
										autorep,
										count);

	return pEvent;
}

void simulateKey(	QWidget* const pWidget,
					const unsigned int key,
					const Qt::KeyboardModifiers modifiers,
					const bool bKeyPressed)
{
	if (pWidget == NULL || QApplication::instance() == NULL)
	{
		return;
	}

	QKeyEvent* pKeyEvent;

	if(bKeyPressed)
	{
		pKeyEvent = createKeyEvent(QEvent::KeyPress, key, modifiers);
	}
	else
	{
		pKeyEvent = createKeyEvent(QEvent::KeyRelease, key, modifiers);
	}

	QApplication::instance()->sendEvent(pWidget, pKeyEvent);
}

} // namespace VaQuole
